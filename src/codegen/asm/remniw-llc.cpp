#include "ASMCodeGeneratorHelper.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/SourceMgr.h"

using namespace llvm;

static llvm::cl::opt<std::string> InputFilename(llvm::cl::Positional,
                                                llvm::cl::desc("<input bitcode>"),
                                                llvm::cl::init("-"));

int main(int argc, char *argv[]) {
    // parse arguments from command line
    llvm::cl::ParseCommandLineOptions(argc, argv, "llc-olive\n");

    // prepare llvm context to read bitcode file
    llvm::LLVMContext Context;
    llvm::SMDiagnostic Error;
    std::unique_ptr<llvm::Module> M = parseIRFile(InputFilename, Error, Context);

    remniw::ExprTreeBuilder Builder(M->getDataLayout());
    Builder.visit(*M);

    remniw::AsmCodeGenerator AsmGen(Builder.Functions, Builder.ConstantStrings);
    AsmGen.EmitAssembly();

    return 0;
}
