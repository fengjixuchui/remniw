#pragma once

#include "AsmBuilder.h"
#include "RegisterAllocator.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/Alignment.h"

namespace remniw {

class AsmRewriter {
private:
    llvm::SmallVector<AsmFunction> AsmFunctions;
    int64_t OriginStackSizeInBytes;
    int64_t StackSizeInBytesWithSpilledReg;
    uint32_t NumReversedStackSlotForReg;

public:
    AsmRewriter(llvm::SmallVector<AsmFunction> AsmFuncs):
        AsmFunctions(AsmFuncs), OriginStackSizeInBytes(0),
        StackSizeInBytesWithSpilledReg(0), NumReversedStackSlotForReg(0) {
        for (auto &AsmFunc : AsmFunctions) {
            std::vector<uint32_t> UsedCalleeSavedRegisters;
            doRegAlloc(AsmFunc, UsedCalleeSavedRegisters);
            AsmFunc.StackSizeInBytes =
                StackSizeInBytesWithSpilledReg + 8 * NumReversedStackSlotForReg;
            insertPrologue(AsmFunc, UsedCalleeSavedRegisters);
            insertEpilogue(AsmFunc, UsedCalleeSavedRegisters);
        }
    }

    llvm::SmallVector<AsmFunction> &getAsmFunctions() { return AsmFunctions; }

    void doRegAlloc(remniw::AsmFunction &AsmFunc,
                    std::vector<uint32_t> &UsedCalleeSavedRegisters) {
        LinearScanRegisterAllocator LSRA(AsmFunc, AsmFunc.RegLiveRangesMap);
        LSRA.LinearScan();
        std::unordered_map<uint32_t, uint32_t> &VirtRegToAllocatedRegMap =
            LSRA.getVirtRegToAllocatedRegMap();
        OriginStackSizeInBytes = AsmFunc.StackSizeInBytes;
        StackSizeInBytesWithSpilledReg =
            OriginStackSizeInBytes + 8 * LSRA.getSpilledRegCount();

        for (auto *AsmInst : AsmFunc.Instructions)
            rewriteAsmInstVirtRegToPhysReg(AsmInst, VirtRegToAllocatedRegMap);

        for (auto p : VirtRegToAllocatedRegMap) {
            if (Register::isCalleeSavedRegister(p.second))
                UsedCalleeSavedRegisters.push_back(p.second);
        }
    }

    void rewriteAsmInstVirtRegToStackSlot(
        remniw::AsmFunction &AsmFunc,
        std::unordered_map<uint32_t, uint32_t> &VirtRegToAllocatedRegMap) {
        llvm::SmallVector<AsmInstruction *> NewInstructions;
        for (auto *AsmInst : AsmFunc.Instructions) {
            rewriteAsmOperandsToStackSlot(AsmFunc, AsmInst, AsmInst->getOperands(),
                                          NewInstructions, VirtRegToAllocatedRegMap);
        }
        AsmFunc.Instructions = NewInstructions;
    }

    void rewriteAsmOperandsToStackSlot(
        AsmFunction &AsmFunc, AsmInstruction *AsmInst,
        llvm::SmallVectorImpl<AsmOperand *> &AsmOps,
        llvm::SmallVectorImpl<AsmInstruction *> &NewAsmInsts,
        std::unordered_map<uint32_t, uint32_t> &VirtRegToAllocatedRegMap) {
        assert(AsmOps.size() <= 2 && "The operands count of AsmInst must <= 2");
        if (AsmOps.size() == 0) {
            NewAsmInsts.push_back(AsmInst);
        }
        if (AsmOps.size() == 1) {
            rewriteAsmOperandToStackSlot(AsmFunc, AsmInst, AsmOps[0], /*IsDst=*/true,
                                         NewAsmInsts, VirtRegToAllocatedRegMap);
        }
        if (AsmOps.size() == 2) {
            rewriteAsmOperandToStackSlot(AsmFunc, AsmInst, AsmOps[0], /*IsDst=*/false,
                                         NewAsmInsts, VirtRegToAllocatedRegMap);
            rewriteAsmOperandToStackSlot(AsmFunc, AsmInst, AsmOps[1], /*IsDst=*/true,
                                         NewAsmInsts, VirtRegToAllocatedRegMap);
        }
    }

    bool rewriteAsmOperandToStackSlot(
        AsmFunction &AsmFunc, AsmInstruction *AsmInst, AsmOperand *&AsmOp, bool IsDst,
        llvm::SmallVectorImpl<AsmInstruction *> &NewAsmInsts,
        std::unordered_map<uint32_t, uint32_t> &VirtRegToAllocatedRegMap) {
        bool changed = false;
        llvm::SmallVector<uint32_t, 4> UsedRegs;
        getUsedRegisters(AsmInst, UsedRegs);
        if (AsmOp->isVirtReg()) {
            assert(VirtRegToAllocatedRegMap.count(AsmOp->Reg.RegNo));
            uint32_t AllocatedReg = VirtRegToAllocatedRegMap[AsmOp->Reg.RegNo];
            assert(Register::isStackSlot(AllocatedReg));
            int64_t Offset = getStackSlotOffsetForSpilledReg(AsmOp->Reg.RegNo, AsmFunc);
            AsmOperand *StackSlot = AsmOperand::createMem(Offset);
            if (IsDst) {
                uint32_t AvailReg = getAvailableRegister(AsmInst, UsedRegs);
                AsmOperand *Reg = AsmOperand::createReg(AvailReg);
                AsmOperand *ReservedStackSlot = getReservedStackSlotForReg();
                NewAsmInsts.push_back(new AsmMovInst(Reg, ReservedStackSlot));
                NewAsmInsts.push_back(new AsmMovInst(StackSlot, Reg));
                AsmOp = Reg;
                NewAsmInsts.push_back(AsmInst);
                NewAsmInsts.push_back(new AsmMovInst(Reg, StackSlot));
                NewAsmInsts.push_back(new AsmMovInst(ReservedStackSlot, Reg));
                changed = true;
            } else {
                AsmOp = StackSlot;
                NewAsmInsts.push_back(AsmInst);
                changed = false;
            }
        }

        if (AsmOp->isMem()) {
            if (Register::isVirtualRegister(AsmOp->Mem.BaseReg)) {
                assert(VirtRegToAllocatedRegMap.count(AsmOp->Mem.BaseReg));
                uint32_t AllocatedReg = VirtRegToAllocatedRegMap[AsmOp->Mem.BaseReg];
                assert(Register::isStackSlot(AllocatedReg));
                int64_t Offset =
                    getStackSlotOffsetForSpilledReg(AsmOp->Mem.BaseReg, AsmFunc);
                AsmOperand *StackSlot = AsmOperand::createMem(Offset);
                uint32_t AvailReg = getAvailableRegister(AsmInst, UsedRegs);
                UsedRegs.push_back(AvailReg);
                AsmOperand *Reg = AsmOperand::createReg(AvailReg);
                AsmOperand *ReservedStackSlot = getReservedStackSlotForReg();
                NewAsmInsts.push_back(new AsmMovInst(Reg, ReservedStackSlot));
                NewAsmInsts.push_back(new AsmMovInst(StackSlot, Reg));
                AsmOp->Mem.BaseReg = AvailReg;
                NewAsmInsts.push_back(AsmInst);
                NewAsmInsts.push_back(new AsmMovInst(Reg, StackSlot));
                NewAsmInsts.push_back(new AsmMovInst(ReservedStackSlot, Reg));
                changed = true;
            }
            if (Register::isVirtualRegister(AsmOp->Mem.IndexReg)) {
                assert(VirtRegToAllocatedRegMap.count(AsmOp->Mem.IndexReg));
                uint32_t AllocatedReg = VirtRegToAllocatedRegMap[AsmOp->Mem.IndexReg];
                assert(Register::isStackSlot(AllocatedReg));
                int64_t Offset =
                    getStackSlotOffsetForSpilledReg(AsmOp->Mem.IndexReg, AsmFunc);
                AsmOperand *StackSlot = AsmOperand::createMem(Offset);
                uint32_t AvailReg = getAvailableRegister(AsmInst, UsedRegs);
                UsedRegs.push_back(AvailReg);
                AsmOperand *Reg = AsmOperand::createReg(AvailReg);
                AsmOperand *ReservedStackSlot = getReservedStackSlotForReg();
                NewAsmInsts.push_back(new AsmMovInst(Reg, ReservedStackSlot));
                NewAsmInsts.push_back(new AsmMovInst(StackSlot, Reg));
                AsmOp->Mem.IndexReg = AvailReg;
                NewAsmInsts.push_back(AsmInst);
                NewAsmInsts.push_back(new AsmMovInst(Reg, StackSlot));
                NewAsmInsts.push_back(new AsmMovInst(ReservedStackSlot, Reg));
                changed = true;
            }
            if (!changed)
                NewAsmInsts.push_back(AsmInst);
        }
        return changed;
    }

    int64_t getStackSlotOffsetForSpilledReg(uint32_t RegNo, AsmFunction &AsmFunc) {
        assert(Register::isStackSlot(RegNo) && "Must be StackSlot");
        uint32_t StackSlotIndex = Register::stackSlot2Index(RegNo);
        return -(AsmFunc.StackSizeInBytes + 8 * StackSlotIndex);
    }

    AsmOperand *getReservedStackSlotForReg() {
        NumReversedStackSlotForReg++;
        int64_t Offset =
            -(StackSizeInBytesWithSpilledReg + 8 * NumReversedStackSlotForReg);
        return AsmOperand::createMem(Offset);
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
        AsmOperand *AsmOp,
        std::unordered_map<uint32_t, uint32_t> &VirtRegToAllocatedRegMap) {
        if (AsmOp->isVirtReg()) {
            assert(VirtRegToAllocatedRegMap.count(AsmOp->Reg.RegNo));
            uint32_t AllocatedReg = VirtRegToAllocatedRegMap[AsmOp->Reg.RegNo];
            if (Register::isPhysicalRegister(AllocatedReg)) {
                AsmOp->Reg.RegNo = VirtRegToAllocatedRegMap[AsmOp->Reg.RegNo];
            } else if (Register::isStackSlot(AllocatedReg)) {
                // TODO
            }
        }
        if (AsmOp->isMem()) {
            if (Register::isVirtualRegister(AsmOp->Mem.BaseReg)) {
                assert(VirtRegToAllocatedRegMap.count(AsmOp->Mem.BaseReg));
                uint32_t AllocatedReg = VirtRegToAllocatedRegMap[AsmOp->Mem.BaseReg];
                if (Register::isPhysicalRegister(AllocatedReg)) {
                    AsmOp->Mem.BaseReg = VirtRegToAllocatedRegMap[AsmOp->Mem.BaseReg];
                } else if (Register::isStackSlot(AllocatedReg)) {
                    // TODO
                }
            }
            if (Register::isVirtualRegister(AsmOp->Mem.IndexReg)) {
                assert(VirtRegToAllocatedRegMap.count(AsmOp->Mem.IndexReg));
                uint32_t AllocatedReg = VirtRegToAllocatedRegMap[AsmOp->Mem.IndexReg];
                if (Register::isPhysicalRegister(AllocatedReg)) {
                    AsmOp->Mem.IndexReg = VirtRegToAllocatedRegMap[AsmOp->Mem.IndexReg];
                } else if (Register::isStackSlot(AllocatedReg)) {
                    // TODO
                }
            }
        }
    }

    void rewriteAsmInstVirtRegToPhysReg(
        AsmInstruction *AsmInst,
        std::unordered_map<uint32_t, uint32_t> &VirtRegToAllocatedRegMap) {
        switch (AsmInst->getInstKind()) {
        case AsmInstruction::Mov: {
            auto *Inst = llvm::cast<AsmMovInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtRegToAllocatedRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtRegToAllocatedRegMap);
            break;
        }
        case AsmInstruction::Lea: {
            auto *Inst = llvm::cast<AsmLeaInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtRegToAllocatedRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtRegToAllocatedRegMap);
            break;
        }
        case AsmInstruction::Cmp: {
            auto *Inst = llvm::cast<AsmCmpInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtRegToAllocatedRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtRegToAllocatedRegMap);
            break;
        }
        case AsmInstruction::Jmp: {
            auto *Inst = llvm::cast<AsmJmpInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getOp(), VirtRegToAllocatedRegMap);
            break;
        }
        case AsmInstruction::Add: {
            auto *Inst = llvm::cast<AsmAddInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtRegToAllocatedRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtRegToAllocatedRegMap);
            break;
        }
        case AsmInstruction::Sub: {
            auto *Inst = llvm::cast<AsmSubInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtRegToAllocatedRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtRegToAllocatedRegMap);
            break;
        }
        case AsmInstruction::Imul: {
            auto *Inst = llvm::cast<AsmImulInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtRegToAllocatedRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtRegToAllocatedRegMap);
            break;
        }
        case AsmInstruction::Idiv: {
            auto *Inst = llvm::cast<AsmIdivInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getOp(), VirtRegToAllocatedRegMap);
            break;
        }
        case AsmInstruction::Cqto: {
            break;
        }
        case AsmInstruction::Call: {
            auto *Inst = llvm::cast<AsmCallInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getCalleeOp(),
                                              VirtRegToAllocatedRegMap);
            break;
        }
        case AsmInstruction::Xor: {
            auto *Inst = llvm::cast<AsmXorInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtRegToAllocatedRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtRegToAllocatedRegMap);
            break;
        }
        case AsmInstruction::Label: {
            break;
        }
        default: llvm_unreachable("Invalid AsmInstruction");
        }
    }

    void getUsedRegisters(AsmInstruction *AsmInst,
                          llvm::SmallVectorImpl<uint32_t> &UsedRegs) {
        for (auto *AsmOp : AsmInst->getOperands()) {
            if (AsmOp->isPhysReg()) {
                UsedRegs.push_back(AsmOp->Reg.RegNo);
            }
            if (AsmOp->isMem()) {
                if (Register::isPhysicalRegister(AsmOp->Mem.BaseReg))
                    UsedRegs.push_back(AsmOp->Mem.BaseReg);
                if (Register::isPhysicalRegister(AsmOp->Mem.IndexReg))
                    UsedRegs.push_back(AsmOp->Mem.IndexReg);
            }
        }
    }

    uint32_t getAvailableRegister(AsmInstruction *AsmInst,
                                  llvm::SmallVectorImpl<uint32_t> &UsedRegs) {
        for (uint32_t Reg = Register::RAX; Reg <= Register::R15; ++Reg) {
            if (std::find(UsedRegs.begin(), UsedRegs.end(), Reg) != UsedRegs.end())
                continue;
            return Reg;
        }
        return Register::NoRegister;
    }
};

}  // namespace remniw