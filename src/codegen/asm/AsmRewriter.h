#pragma once

#include "AsmBuilder.h"
#include "RegisterAllocator.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/Alignment.h"

namespace remniw {

class AsmRewriter {
private:
    llvm::SmallVector<AsmFunction> AsmFunctions;

public:
    AsmRewriter(llvm::SmallVector<AsmFunction> AsmFuncs): AsmFunctions(AsmFuncs) {
        for (auto &AsmFunc : AsmFunctions) {
            std::vector<uint32_t> UsedCalleeSavedRegisters;
            doRegAlloc(AsmFunc, UsedCalleeSavedRegisters);

            insertPrologue(AsmFunc, UsedCalleeSavedRegisters);
            insertEpilogue(AsmFunc, UsedCalleeSavedRegisters);
        }
    }

    llvm::SmallVector<AsmFunction> &getAsmFunctions() { return AsmFunctions; }

    void doRegAlloc(remniw::AsmFunction &AsmFunc,
                    std::vector<uint32_t> &UsedCalleeSavedRegisters) {
        LinearScanRegisterAllocator LSRA(AsmFunc, AsmFunc.RegLiveRangesMap);
        LSRA.LinearScan();
        std::unordered_map<uint32_t, uint32_t> &VirtToPhysRegMap =
            LSRA.getVirtToPhysRegMap();
        for (auto *AsmInst : AsmFunc.Instructions)
            rewriteAsmInstVirtRegToPhysReg(AsmInst, VirtToPhysRegMap);

        for (auto p : VirtToPhysRegMap) {
            if (Register::isCalleeSavedRegister(p.second))
                UsedCalleeSavedRegisters.push_back(p.second);
        }
    }

    void insertPrologue(remniw::AsmFunction &AsmFunc,
                        std::vector<uint32_t> &UsedCalleeSavedRegisters) {
        std::vector<remniw::AsmInstruction *> InsertedPrologue;
        if (AsmFunc.FuncName != "main") {
            for (uint32_t Reg : UsedCalleeSavedRegisters) {
                InsertedPrologue.push_back(new AsmPushInst(AsmOperand::createReg(Reg)));
            }
        }
        InsertedPrologue.push_back(new AsmPushInst(AsmOperand::createReg(Register::RBP)));
        InsertedPrologue.push_back(new AsmMovInst(AsmOperand::createReg(Register::RSP),
                                                  AsmOperand::createReg(Register::RBP)));
        int64_t AlignedStackSizeInBytes = llvm::alignTo(
            AsmFunc.StackSizeInBytes + (UsedCalleeSavedRegisters.size() * 8) % 16, 16);
        InsertedPrologue.push_back(
            new AsmSubInst(AsmOperand::createImm(AlignedStackSizeInBytes),
                           AsmOperand::createReg(Register::RSP)));
        AsmFunc.Instructions.insert(AsmFunc.Instructions.begin(),
                                    InsertedPrologue.begin(), InsertedPrologue.end());
    }

    void insertEpilogue(remniw::AsmFunction &AsmFunc,
                        std::vector<uint32_t> &UsedCalleeSavedRegisters) {
        std::vector<remniw::AsmInstruction *> InsertedEpilogue;
        InsertedEpilogue.push_back(new AsmMovInst(AsmOperand::createReg(Register::RBP),
                                                  AsmOperand::createReg(Register::RSP)));
        InsertedEpilogue.push_back(new AsmPopInst(AsmOperand::createReg(Register::RBP)));
        if (AsmFunc.FuncName != "main") {
            for (auto i = UsedCalleeSavedRegisters.rbegin(),
                      e = UsedCalleeSavedRegisters.rend();
                 i != e; ++i) {
                InsertedEpilogue.push_back(new AsmPopInst(AsmOperand::createReg(*i)));
            }
        }
        InsertedEpilogue.push_back(new AsmRetInst());
        AsmFunc.Instructions.insert(AsmFunc.Instructions.end(), InsertedEpilogue.begin(),
                                    InsertedEpilogue.end());
    }

private:
    void rewriteAsmOperandVirtRegToPhysReg(
        AsmOperand *AsmOp, std::unordered_map<uint32_t, uint32_t> &VirtToPhysRegMap) {
        if (AsmOp->isVirtReg()) {
            AsmOp->Reg.RegNo = VirtToPhysRegMap[AsmOp->Reg.RegNo];
        }
        if (AsmOp->isMem()) {
            if (Register::isVirtualRegister(AsmOp->Mem.BaseReg))
                AsmOp->Mem.BaseReg = VirtToPhysRegMap[AsmOp->Mem.BaseReg];
            if (Register::isVirtualRegister(AsmOp->Mem.IndexReg))
                AsmOp->Mem.IndexReg = VirtToPhysRegMap[AsmOp->Mem.IndexReg];
        }
        if (AsmOp->isStackSlotReg()) {
            // TODO
        }
    }

    void rewriteAsmInstVirtRegToPhysReg(
        AsmInstruction *AsmInst,
        std::unordered_map<uint32_t, uint32_t> &VirtToPhysRegMap) {
        switch (AsmInst->getInstKind()) {
        case AsmInstruction::Mov: {
            auto *Inst = llvm::cast<AsmMovInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            break;
        }
        case AsmInstruction::Lea: {
            auto *Inst = llvm::cast<AsmLeaInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            break;
        }
        case AsmInstruction::Cmp: {
            auto *Inst = llvm::cast<AsmCmpInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            break;
        }
        case AsmInstruction::Jmp: {
            auto *Inst = llvm::cast<AsmJmpInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getOp(), VirtToPhysRegMap);
            break;
        }
        case AsmInstruction::Add: {
            auto *Inst = llvm::cast<AsmAddInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            break;
        }
        case AsmInstruction::Sub: {
            auto *Inst = llvm::cast<AsmSubInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            break;
        }
        case AsmInstruction::Imul: {
            auto *Inst = llvm::cast<AsmImulInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            break;
        }
        case AsmInstruction::Idiv: {
            auto *Inst = llvm::cast<AsmIdivInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getOp(), VirtToPhysRegMap);
            break;
        }
        case AsmInstruction::Cqto: {
            break;
        }
        case AsmInstruction::Call: {
            auto *Inst = llvm::cast<AsmCallInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getCalleeOp(), VirtToPhysRegMap);
            break;
        }
        case AsmInstruction::Xor: {
            auto *Inst = llvm::cast<AsmXorInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            break;
        }
        case AsmInstruction::Label: {
            break;
        }
        default: llvm_unreachable("Invalid AsmInstruction");
        }
    }
};

}  // namespace remniw