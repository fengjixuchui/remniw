#pragma once

#include "AsmContext.h"
#include "AsmInstruction.h"
#include "BrgTreeBuilder.h"
#include "LiveInterval.h"
#include "Register.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Instructions.h"
#include <unordered_map>
#include <vector>

namespace remniw {

struct AsmFunction {
    AsmFunction(std::string FuncName, int64_t StackSizeInBytes,
                std::vector<AsmInstruction *> Instructions,
                std::unordered_map<uint32_t, remniw::LiveRanges> RegLiveRangesMap):
        FuncName(FuncName),
        StackSizeInBytes(StackSizeInBytes), Instructions(std::move(Instructions)),
        RegLiveRangesMap(std::move(RegLiveRangesMap)) {}

    std::string FuncName;
    int64_t StackSizeInBytes;
    std::vector<AsmInstruction *> Instructions;
    std::unordered_map<uint32_t, remniw::LiveRanges> RegLiveRangesMap;
};

class AsmBuilder {
private:
    AsmContext &AsmCtx;
    llvm::SmallVector<BrgFunction> BrgFunctions;
    llvm::SmallVector<AsmFunction> AsmFunctions;
    std::vector<AsmInstruction *> CurrentAsmFuncInsts;
    std::unordered_map<uint32_t, remniw::LiveRanges> CurrentRegLiveRangesMap;

public:
    AsmBuilder(AsmContext &AsmCtx, llvm::SmallVector<BrgFunction> Functions):
        AsmCtx(AsmCtx), BrgFunctions(std::move(Functions)) {
        for (const auto &BrgFunc : BrgFunctions) {
            buildAsmFunction(BrgFunc);
        }
    }

    void buildAsmFunction(const BrgFunction &);

    llvm::SmallVector<AsmFunction> &getAsmFunctions() { return AsmFunctions; }

    void updateRegLiveRanges(uint32_t Reg) {
        uint32_t StartPoint = static_cast<uint32_t>(CurrentAsmFuncInsts.size());
        uint32_t EndPoint = StartPoint + 1;
        // For virtual registers, we simply do not consider lifetime holes.
        // The lifetime interval of virtual register is the segment of the program that
        // starts where the virtual register is first live in the static linear order
        // of the code and ends where it is last live.
        // So when we use `struct LiveRanges` to represent the lifetime of virtual
        // registers, the `struct LiveRanges` only consists of one `struct LiveRange`.
        if (Register::isVirtualRegister(Reg)) {
            if (CurrentRegLiveRangesMap.count(Reg)) {
                CurrentRegLiveRangesMap[Reg].Ranges[0].EndPoint = EndPoint;
            } else {
                CurrentRegLiveRangesMap[Reg].Ranges.push_back({StartPoint, EndPoint});
            }

            for (const auto &Range : CurrentRegLiveRangesMap[Reg].Ranges) {
                llvm::outs() << "VirtualRegister " << Reg << " LiveRange: ";
                Range.print(llvm::outs());
                llvm::outs() << "\n";
            }
        }
        // For physical register, we consider lifetime holes.
        // For the segment of the program that starts where the physical register
        // is first live in the static linear order of the code and ends where
        // it is last live, there are one or more holes during which physical register
        // is not used.
        // So when we use `struct LiveRanges` to represent the lifetime of physical
        // registers, the `struct LiveRanges` usually consists of multiple
        // `struct LiveRange`s.
        else if (Register::isPhysicalRegister(Reg)) {
            if (!CurrentRegLiveRangesMap[Reg].Ranges.empty()) {
                auto &LastActiveRange = CurrentRegLiveRangesMap[Reg].Ranges.back();
                if (LastActiveRange.StartPoint == StartPoint &&
                    LastActiveRange.EndPoint == EndPoint) {
                    // Do nothing
                } else if (LastActiveRange.EndPoint == StartPoint) {
                    LastActiveRange.EndPoint = EndPoint;
                } else {
                    CurrentRegLiveRangesMap[Reg].Ranges.push_back({StartPoint, EndPoint});
                }
            } else {
                CurrentRegLiveRangesMap[Reg].Ranges.push_back({StartPoint, EndPoint});
            }

            for (const auto &Range : CurrentRegLiveRangesMap[Reg].Ranges) {
                llvm::outs() << "PhysicalRegiste " << Reg << " LiveRange: ";
                Range.print(llvm::outs());
                llvm::outs() << "\n";
            }
        }
    }

    void updateAsmOperandLiveRanges(AsmOperand *Op) {
        llvm::outs() << "updateAsmOperandLiveRanges " << Op << "\n";
        uint32_t Reg;
        if (Op->isReg()) {
            updateRegLiveRanges(Op->getReg());
        }
        if (Op->isMem()) {
            uint32_t MemBaseReg = Op->getMemBaseReg();
            if (MemBaseReg != Register::RBP) {
                updateRegLiveRanges(MemBaseReg);
            }
            uint32_t MemIndexReg = Op->getMemIndexReg();
            if (MemIndexReg != Register::NoRegister) {
                updateRegLiveRanges(MemIndexReg);
            }
        }
        llvm::outs() << "\n";
    }

    void createMov(AsmOperand *Src, AsmOperand *Dst) {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmMovInst(Src, Dst)));
        llvm::outs() << CurrentAsmFuncInsts.size();
        CurrentAsmFuncInsts.back()->print(llvm::outs());
        updateAsmOperandLiveRanges(Src);
        updateAsmOperandLiveRanges(Dst);
    }

    void createLea(AsmOperand *Src, AsmOperand *Dst) {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmLeaInst(Src, Dst)));
        llvm::outs() << CurrentAsmFuncInsts.size();
        CurrentAsmFuncInsts.back()->print(llvm::outs());
        updateAsmOperandLiveRanges(Src);
        updateAsmOperandLiveRanges(Dst);
    }

    void createCmp(AsmOperand *Src, AsmOperand *Dst) {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmCmpInst(Src, Dst)));
        llvm::outs() << CurrentAsmFuncInsts.size();
        CurrentAsmFuncInsts.back()->print(llvm::outs());
        updateAsmOperandLiveRanges(Src);
        updateAsmOperandLiveRanges(Dst);
    }

    void createJmp(AsmJmpInst::JmpKindTy JmpKind, AsmOperand *Op) {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmJmpInst(JmpKind, Op)));
        llvm::outs() << CurrentAsmFuncInsts.size();
        CurrentAsmFuncInsts.back()->print(llvm::outs());
        updateAsmOperandLiveRanges(Op);
    }

    void createAdd(AsmOperand *Src, AsmOperand *Dst) {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmAddInst(Src, Dst)));
        llvm::outs() << CurrentAsmFuncInsts.size();
        CurrentAsmFuncInsts.back()->print(llvm::outs());
        updateAsmOperandLiveRanges(Src);
        updateAsmOperandLiveRanges(Dst);
    }

    void createSub(AsmOperand *Src, AsmOperand *Dst) {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmSubInst(Src, Dst)));
        llvm::outs() << CurrentAsmFuncInsts.size();
        CurrentAsmFuncInsts.back()->print(llvm::outs());
        updateAsmOperandLiveRanges(Src);
        updateAsmOperandLiveRanges(Dst);
    }

    void createImul(AsmOperand *Src, AsmOperand *Dst) {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmImulInst(Src, Dst)));
        llvm::outs() << CurrentAsmFuncInsts.size();
        CurrentAsmFuncInsts.back()->print(llvm::outs());
        updateAsmOperandLiveRanges(Src);
        updateAsmOperandLiveRanges(Dst);
    }

    void createIdiv(AsmOperand *Op) {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmIdivInst(Op)));
        llvm::outs() << CurrentAsmFuncInsts.size();
        CurrentAsmFuncInsts.back()->print(llvm::outs());
        updateAsmOperandLiveRanges(Op);
        updateRegLiveRanges(Register::RAX);
        updateRegLiveRanges(Register::RDX);
    }

    void createCqto() {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmCqtoInst()));
        llvm::outs() << CurrentAsmFuncInsts.size();
        CurrentAsmFuncInsts.back()->print(llvm::outs());
        updateRegLiveRanges(Register::RAX);
        updateRegLiveRanges(Register::RDX);
    }

    void createCall(AsmOperand *Callee, bool DirectCall) {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmCallInst(Callee, DirectCall)));
        llvm::outs() << CurrentAsmFuncInsts.size();
        CurrentAsmFuncInsts.back()->print(llvm::outs());
        updateAsmOperandLiveRanges(Callee);
    }

    void createXor(AsmOperand *Src, AsmOperand *Dst) {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmXorInst(Src, Dst)));
        llvm::outs() << CurrentAsmFuncInsts.size();
        CurrentAsmFuncInsts.back()->print(llvm::outs());
        updateAsmOperandLiveRanges(Src);
        updateAsmOperandLiveRanges(Dst);
    }

    void createLabel(AsmOperand *LabelOp) {
        CurrentAsmFuncInsts.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmLabelInst(LabelOp)));
    }
};

using AsmBuilderPtr = AsmBuilder *;

}  // namespace remniw
