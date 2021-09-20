#include "AST.h"
#include "ASTPrinter.h"
#include "FrontEnd.h"
#include "SymbolTable.h"
#include "Type.h"
#include "TypeAnalysis.h"
#include "CodeGenerator.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/ToolOutputFile.h"

#include <iostream>
#include <antlr4-runtime.h>

using namespace antlr4;
using namespace remniw;

static llvm::cl::opt<bool>Verbose("v", llvm::cl::desc("Verbose"));

static llvm::cl::opt<std::string>
InputFilename(llvm::cl::Positional,
               llvm::cl::desc("<input remniw source code>"));

static llvm::cl::opt<std::string>
OutputFilename("o", llvm::cl::desc("Override output filename"), llvm::cl::init("a.out"),
               llvm::cl::value_desc("filename"));

int main(int argc, char *argv[])
{
    llvm::cl::ParseCommandLineOptions(argc, argv, "remniw compiler\n");

    // llvm::errs().enable_colors(true);
    // llvm::errs().changeColor(llvm::raw_ostream::RED);
    llvm::LLVMContext TheLLVMContext;
    remniw::TypeContext TheTypeContext;

    std::ifstream Stream;
    Stream.open(InputFilename);
    if(!Stream.good())
    {
        llvm::errs() << "error: no such file: '" << InputFilename << "'\n";
        exit(1);
    }
    FrontEnd FE(TheTypeContext);
    std::unique_ptr<ProgramAST> AST = FE.parse(Stream);

    if (Verbose)
    {
        llvm::outs() << "===== AST Printer ===== \n";
        ASTPrinter PrettyPrinter(llvm::outs());
        PrettyPrinter.print(*AST);
    }

    if (Verbose) llvm::outs() << "===== Symbol Table ===== \n";
    SymbolTableBuilder SymTabBuilder;
    SymTabBuilder.visit(*AST);
    // SymTabBuilder.getSymbolTale().print(llvm::outs());

    if (Verbose) llvm::outs() << "===== Type Analysis ===== \n";
    TypeAnalysis TA(SymTabBuilder.getSymbolTale(), TheTypeContext);
    TA.visit(*AST);
    TA.solve();
    if (Verbose)
    {
        for(auto Constraint: TA.getConstraints())
        {
            Constraint.print(llvm::outs());
        }
    }

    if (Verbose) llvm::outs() << "===== Code Generator ===== \n";
    std::unique_ptr<llvm::Module> M =
        CodeGenerator::emit(*AST, TheLLVMContext);

    std::error_code EC;
    llvm::ToolOutputFile Out(OutputFilename, EC, llvm::sys::fs::OF_Text);
    if (EC)
    {
        llvm::errs() << EC.message() << '\n';
        return 1;
    }
    // M->print(llvm::errs(), nullptr);
    // WriteBitcodeToFile(*M.get(), Out.os());
    M->print(Out.os(), nullptr);
    Out.keep();

    return 0;
}
