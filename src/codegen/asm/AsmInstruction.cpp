#include "AsmInstruction.h"
#include "llvm/Support/Casting.h"

namespace remniw {

void AsmInstruction::print(llvm::raw_ostream &OS) const {
    switch (getInstKind()) {
    case AsmInstruction::Mov: {
        auto *Inst = llvm::cast<AsmMovInst>(this);
        llvm::outs() << "Mov\n";
        llvm::outs() << Inst->getSrcOp() << ", " << Inst->getDstOp() << "\n";
        // OS << "movq "
        //    << "\n";
        return;
    }
    case AsmInstruction::Lea: {
        auto *Inst = llvm::cast<AsmLeaInst>(this);
        llvm::outs() << "Lea\n";
        llvm::outs() << Inst->getSrcOp() << ", " << Inst->getDstOp() << "\n";
        // OS << "leaq "
        //    << "\n";
        return;
    }
    case AsmInstruction::Cmp: {
        auto *Inst = llvm::cast<AsmCmpInst>(this);
        llvm::outs() << "Cmp\n";
        llvm::outs() << Inst->getSrcOp() << ", " << Inst->getDstOp() << "\n";
        // OS << "cmpq "
        //    << "\n";
        return;
    }
    case AsmInstruction::Jmp: {
        auto *Inst = llvm::cast<AsmJmpInst>(this);
        llvm::outs() << "Jmp\n";
        llvm::outs() << Inst->getJmpKind()  << ", " << Inst->getOp() << "\n";
        // OS << "jmp "
        //    << "\n";
        return;
    }
    case AsmInstruction::Add: {
        auto *Inst = llvm::cast<AsmAddInst>(this);
        llvm::outs() << "Add\n";
        llvm::outs() << Inst->getSrcOp() << ", " << Inst->getDstOp() << "\n";
        // OS << "addq "
        //    << "\n";
        return;
    }
    case AsmInstruction::Sub: {
        auto *Inst = llvm::cast<AsmSubInst>(this);
        llvm::outs() << "Sub\n";
        llvm::outs() << Inst->getSrcOp() << ", " << Inst->getDstOp() << "\n";
        // OS << "subq "
        //    << "\n";
        return;
    }
    case AsmInstruction::Imul: {
        auto *Inst = llvm::cast<AsmImulInst>(this);
        llvm::outs() << "Imul\n";
        llvm::outs() << Inst->getSrcOp() << ", " << Inst->getDstOp() << "\n";
        // OS << "imulq "
        //    << "\n";
        return;
    }
    case AsmInstruction::Idiv: {
        auto *Inst = llvm::cast<AsmIdivInst>(this);
        llvm::outs() << "Idiv\n";
        llvm::outs() << Inst->getOp() << "\n";
        // OS << "idivq "
        //    << "\n";
        return;
    }
    case AsmInstruction::Cqto: {
        llvm::outs() << "Cqto\n";
        // OS << "cqto "
        //    << "\n";
        return;
    }
    case AsmInstruction::Call: {
        auto *Inst = llvm::cast<AsmCallInst>(this);
        llvm::outs() << "Call\n";
        llvm::outs() << Inst->getCalleeOp() << ", isDirectCall: " << Inst->isDirectCall()
                     << "\n";
        // OS << "callq "
        //    << "\n";
        return;
    }
    case AsmInstruction::Xor: {
        auto *Inst = llvm::cast<AsmXorInst>(this);
        llvm::outs() << "Xor\n";
        llvm::outs() << Inst->getSrcOp() << ", " << Inst->getDstOp() << "\n";
        // OS << "xorq "
        //    << "\n";
        return;
    }
    }
    llvm_unreachable("Invalid AsmInstruction");
}

}  // namespace remniw
