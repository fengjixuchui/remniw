#include "AsmInstruction.h"
#include "llvm/Support/Casting.h"

namespace remniw {

void AsmInstruction::print(llvm::raw_ostream &OS) const {
    switch (getInstKind()) {
    case AsmInstruction::Mov: {
        auto *Inst = llvm::cast<AsmMovInst>(this);
        OS << "\tmovq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Lea: {
        auto *Inst = llvm::cast<AsmLeaInst>(this);
        OS << "\tleaq\t";
        Inst->getSrcOp()->print(OS);
        if (Inst->getSrcOp()->isLabel() &&
            (Inst->getSrcOp()->getLabel()->isFunction() ||
             Inst->getSrcOp()->getLabel()->isGlobalVariable())) {
            OS << "(%rip)";  // rip relative addressing
        }
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Cmp: {
        auto *Inst = llvm::cast<AsmCmpInst>(this);
        OS << "\tcmpq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Jmp: {
        auto *Inst = llvm::cast<AsmJmpInst>(this);
        switch (Inst->getJmpKind()) {
        case AsmJmpInst::Jmp: OS << "\tjmp\t"; break;
        case AsmJmpInst::Je: OS << "\tje\t"; break;
        case AsmJmpInst::Jne: OS << "\tjne\t"; break;
        case AsmJmpInst::Jg: OS << "\tjg\t"; break;
        case AsmJmpInst::Jle: OS << "\tjle\t"; break;
        default: llvm_unreachable("Invalid AsmJmpInst!");
        }
        Inst->getOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Add: {
        auto *Inst = llvm::cast<AsmAddInst>(this);
        OS << "\taddq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Sub: {
        auto *Inst = llvm::cast<AsmSubInst>(this);
        OS << "\tsubq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Imul: {
        auto *Inst = llvm::cast<AsmImulInst>(this);
        OS << "\timulq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Idiv: {
        auto *Inst = llvm::cast<AsmIdivInst>(this);
        OS << "\tidivq\t";
        Inst->getOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Cqto: {
        OS << "\tcqto\n";
        break;
    }
    case AsmInstruction::Call: {
        auto *Inst = llvm::cast<AsmCallInst>(this);
        OS << "\tcallq\t";
        if (!Inst->isDirectCall())
            OS << "*";
        Inst->getCalleeOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Xor: {
        auto *Inst = llvm::cast<AsmXorInst>(this);
        OS << "\txorq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Push: {
        auto *Inst = llvm::cast<AsmPushInst>(this);
        OS << "\tpushq\t";
        Inst->getOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Pop: {
        auto *Inst = llvm::cast<AsmPopInst>(this);
        OS << "\tpopq\t";
        Inst->getOp()->print(OS);
        OS << "\n";
        break;
    }
    case AsmInstruction::Ret: {
        OS << "\tretq\n";
        break;
    }
    case AsmInstruction::Label: {
        auto *Inst = llvm::cast<AsmLabelInst>(this);
        Inst->getLabelOp()->print(OS);
        OS << ":\n";
        break;
    }
    default: llvm_unreachable("Invalid AsmInstruction");
    }
}

}  // namespace remniw
