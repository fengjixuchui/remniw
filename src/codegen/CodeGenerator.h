#pragma once

#include "antlr4-runtime.h"
#include "AST.h"
#include "llvm/IR/LLVMContext.h"

namespace remniw
{

class CodeGenerator
{
public:
    static void emit(ProgramAST &, llvm::LLVMContext&);
};

}