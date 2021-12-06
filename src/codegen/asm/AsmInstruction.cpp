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
        return;
    }
    case AsmInstruction::Lea: {
        auto *Inst = llvm::cast<AsmLeaInst>(this);
        OS << "\tleaq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        return;
    }
    case AsmInstruction::Cmp: {
        auto *Inst = llvm::cast<AsmCmpInst>(this);
        OS << "\tcmpq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        return;
    }
    case AsmInstruction::Jmp: {
        auto *Inst = llvm::cast<AsmJmpInst>(this);
        switch (Inst->getJmpKind())
        {
        case AsmJmpInst::Jmp:
            OS << "\tjmp\t";
            break;
        case AsmJmpInst::Je:
            OS << "\tje\t";
            break;
        case AsmJmpInst::Jne:
            OS << "\tjne\t";
            break;
        case AsmJmpInst::Jg:
            OS << "\tjg\t";
            break;
        case AsmJmpInst::Jle:
            OS << "\tjle\t";
            break;
        default:
            llvm_unreachable("Invalid AsmJmpInst!");
        }
        Inst->getOp()->print(OS);
        OS << "\n";
        return;
    }
    case AsmInstruction::Add: {
        auto *Inst = llvm::cast<AsmAddInst>(this);
        OS << "\taddq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        return;
    }
    case AsmInstruction::Sub: {
        auto *Inst = llvm::cast<AsmSubInst>(this);
        OS << "\tsubq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        return;
    }
    case AsmInstruction::Imul: {
        auto *Inst = llvm::cast<AsmImulInst>(this);
        OS << "\timulq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        return;
    }
    case AsmInstruction::Idiv: {
        auto *Inst = llvm::cast<AsmIdivInst>(this);
        OS << "\tidivq\t";
        Inst->getOp()->print(OS);
        OS << "\n";
        return;
    }
    case AsmInstruction::Cqto: {
        OS << "\tidivq\n";
        return;
    }
    case AsmInstruction::Call: {
        auto *Inst = llvm::cast<AsmCallInst>(this);
        OS << "\tcallq\t";
        if (!Inst->isDirectCall())
            OS << "*";
        Inst->getCalleeOp()->print(OS);
        OS << "\n";
        return;
    }
    case AsmInstruction::Xor: {
        auto *Inst = llvm::cast<AsmXorInst>(this);
        OS << "\txorq\t";
        Inst->getSrcOp()->print(OS);
        OS << ", ";
        Inst->getDstOp()->print(OS);
        OS << "\n";
        return;
    }
    }
    llvm_unreachable("Invalid AsmInstruction");
}

}  // namespace remniw
