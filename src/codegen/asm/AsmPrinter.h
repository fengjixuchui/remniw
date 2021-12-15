#pragma once

#include "AsmBuilder.h"
#include "llvm/ADT/SmallVector.h"

namespace remniw {

class AsmPrinter {
private:
    llvm::raw_ostream &OS;
    llvm::SmallVector<AsmFunction> AsmFunctions;
    llvm::DenseMap<remniw::AsmSymbol *, llvm::StringRef> GlobalVariables;

public:
    AsmPrinter(llvm::raw_ostream &OS, llvm::SmallVector<AsmFunction> AsmFunctions,
               llvm::DenseMap<remniw::AsmSymbol *, llvm::StringRef> GVs):
        OS(OS),
        AsmFunctions(AsmFunctions), GlobalVariables(GVs) {}

    void print() {
        for (auto &AsmFunc : AsmFunctions) {
            EmitFunctionDeclaration(AsmFunc);
            EmitFunctionPrologue(AsmFunc);
            EmitFunctionBody(AsmFunc);
            EmitFunctionEpilogue(AsmFunc);
        }
        EmitGlobalVariables();
    }

    void EmitFunctionDeclaration(AsmFunction &F) {
        // FIXME
        OS << ".text\n"
           << ".globl " << F.FuncName << "\n"
           << ".type " << F.FuncName << ", @function\n"
           << F.FuncName << ":\n";
    }

    void EmitFunctionPrologue(AsmFunction &F) {
        OS << "\tpushq\t"
           << "%rbp\n";
        OS << "\tmovq\t"
           << "%rsp, %rbp\n";
        OS << "\tsubq\t"
           << "$" << F.StackSizeInBytes << ", %rsp\n";
    }

    void EmitFunctionEpilogue(AsmFunction &F) {
        OS << "\tmovq\t"
           << "%rbp, %rsp\n";
        OS << "\tpopq\t"
           << "%rbp\n";
        OS << "\tretq\n\n";
    }

    void EmitFunctionBody(AsmFunction &F) {
        for (auto *AsmInst : F.Instructions) {
            AsmInst->print(OS);
        }
    }

    void EmitGlobalVariables() {
        for (auto p : GlobalVariables) {
            p.first->print(OS);
            OS << ":\n";
            OS << "\t.asciz ";
            OS << "\"";
            OS.write_escaped(p.second);
            OS << "\"\n";
        }
    }
};

}  // namespace remniw