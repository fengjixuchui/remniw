#pragma once

#include "AsmBuilder.h"
#include "RegisterAllocator.h"
#include "llvm/ADT/SmallVector.h"

namespace remniw {

class AsmRewriter {
private:
    llvm::SmallVector<AsmFunction> AsmFunctions;

public:
    AsmRewriter(llvm::SmallVector<AsmFunction> AsmFunctions): AsmFunctions(AsmFunctions) {
        for (auto &AsmFunc : AsmFunctions) {
            LinearScanRegisterAllocator LSRA(AsmFunc.RegLiveRangesMap);
            LSRA.LinearScan();
            std::unordered_map<uint32_t, uint32_t> &VirtToPhysRegMap =
                LSRA.getVirtToPhysRegMap();
            for (auto *AsmInst : AsmFunc.Instructions) {
                rewriteAsmInstVirtRegToPhysReg(AsmInst, VirtToPhysRegMap);
            }
        }

        llvm::outs() << "===== AsmRewriter =====\n";
        for (auto &AsmFunc : AsmFunctions) {
            for (auto *AsmInst : AsmFunc.Instructions) {
                AsmInst->print(llvm::outs());
            }
        }
    }

    void doRegAlloc() {
        for (auto &AsmFunc : AsmFunctions) {
            LinearScanRegisterAllocator LSRA(AsmFunc.RegLiveRangesMap);
            LSRA.LinearScan();
            std::unordered_map<uint32_t, uint32_t> &VirtToPhysRegMap =
                LSRA.getVirtToPhysRegMap();
            for (auto *AsmInst : AsmFunc.Instructions) {
                rewriteAsmInstVirtRegToPhysReg(AsmInst, VirtToPhysRegMap);
            }
        }
    }

    void rewriteAsmOperandVirtRegToPhysReg(
        AsmOperand *AsmOp, std::unordered_map<uint32_t, uint32_t> &VirtToPhysRegMap) {
        if (AsmOp->isVirtReg()) {
            AsmOp->Reg.RegNo = VirtToPhysRegMap[AsmOp->Reg.RegNo];
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
            return;
        }
        case AsmInstruction::Lea: {
            auto *Inst = llvm::cast<AsmLeaInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            return;
        }
        case AsmInstruction::Cmp: {
            auto *Inst = llvm::cast<AsmCmpInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            return;
        }
        case AsmInstruction::Jmp: {
            auto *Inst = llvm::cast<AsmJmpInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getOp(), VirtToPhysRegMap);
            return;
        }
        case AsmInstruction::Add: {
            auto *Inst = llvm::cast<AsmAddInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            return;
        }
        case AsmInstruction::Sub: {
            auto *Inst = llvm::cast<AsmSubInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            return;
        }
        case AsmInstruction::Imul: {
            auto *Inst = llvm::cast<AsmImulInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            return;
        }
        case AsmInstruction::Idiv: {
            auto *Inst = llvm::cast<AsmIdivInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getOp(), VirtToPhysRegMap);
            return;
        }
        case AsmInstruction::Cqto: {
            return;
        }
        case AsmInstruction::Call: {
            auto *Inst = llvm::cast<AsmCallInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getCalleeOp(), VirtToPhysRegMap);
            return;
        }
        case AsmInstruction::Xor: {
            auto *Inst = llvm::cast<AsmXorInst>(AsmInst);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getSrcOp(), VirtToPhysRegMap);
            rewriteAsmOperandVirtRegToPhysReg(Inst->getDstOp(), VirtToPhysRegMap);
            return;
        }
        }
        llvm_unreachable("Invalid AsmInstruction");
    }
};

}  // namespace remniw