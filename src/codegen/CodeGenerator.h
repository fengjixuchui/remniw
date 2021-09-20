#pragma once

#include "antlr4-runtime.h"
#include "AST.h"
#include "llvm/IR/LLVMContext.h"

namespace remniw
{

class CodeGenerator
{
public:
    static std::unique_ptr<llvm::Module> emit(ProgramAST &, llvm::LLVMContext&);
};

}