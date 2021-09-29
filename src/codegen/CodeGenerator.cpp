#include "CodeGenerator.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/ToolOutputFile.h"
#include <string>

using namespace llvm;

namespace remniw {

std::unique_ptr<Module> CodeGenerator::emit(ProgramAST *AST) {
    return pImpl->codegen(AST);
}

}  // namespace remniw