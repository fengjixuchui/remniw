#pragma once

#include "AST.h"
#include "CodeGeneratorImpl.h"
#include "llvm/IR/LLVMContext.h"

namespace remniw
{

class CodeGenerator
{
private:
    CodeGeneratorImpl *pImpl;

public:
    CodeGenerator(llvm::LLVMContext* LLVMContext): pImpl(new CodeGeneratorImpl(LLVMContext)) {}
    ~CodeGenerator() { delete pImpl; }
    std::unique_ptr<llvm::Module> emit(ProgramAST*);
};

}