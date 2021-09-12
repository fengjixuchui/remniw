#include "CodeGenerator.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/ToolOutputFile.h"
#include <string>

using namespace llvm;

namespace remniw
{

void CodeGenerator::emit(ProgramAST & Program, LLVMContext& Context)
{
    auto M = Program.codegen(Context);
    std::string OutputFilename("a.out");
    if (!OutputFilename.empty())
    {
        std::error_code EC;
        std::unique_ptr<ToolOutputFile> Out(
            new ToolOutputFile(OutputFilename, EC, sys::fs::OF_Text));
        if (EC)
        {
            errs() << EC.message() << '\n';
            return;
        }
        M->print(llvm::errs(), nullptr);
        // WriteBitcodeToFile(*M.get(), Out->os());
        M->print(Out->os(), nullptr);
        Out->keep();
    }
}

}