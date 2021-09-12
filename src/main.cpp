#include "RemniwLexer.h"
#include "RemniwParser.h"
#include "AST.h"
#include "ASTBuilder.h"
#include "ASTPrinter.h"
#include "SymbolTable.h"
#include "Type.h"
#include "TypeAnalysis.h"
#include "CodeGenerator.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include <antlr4-runtime.h>

using namespace antlr4;
using namespace remniw;

int main(int argc, char *argv[])
{
    // llvm::errs().enable_colors(true);
    // llvm::errs().changeColor(llvm::raw_ostream::RED);
    llvm::LLVMContext TheLLVMContext;
    remniw::TypeContext TheTypeContext;
    std::ifstream stream;

    stream.open(argv[1]);
    ANTLRInputStream input(stream);
    RemniwLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    llvm::outs() << "===== Lexer ===== \n";
    for (auto token : tokens.getTokens())
    {
        llvm::outs() << token->toString() << "\n";
    }

    RemniwParser parser(&tokens);
    RemniwParser::ProgramContext* program = parser.program();
    llvm::outs() << "===== Parser ===== \n";
    llvm::outs() << program->toStringTree(&parser, true) << "\n";
    if (parser.getNumberOfSyntaxErrors())
        llvm::errs() << "===== Parser Failed ===== \n";

    ASTBuilder AstBuilder(TheTypeContext);
    std::unique_ptr<ProgramAST> AST =
        std::move(AstBuilder.visitProgram(program).as<std::unique_ptr<ProgramAST>>());

    llvm::outs() << "===== AST Printer ===== \n";
    ASTPrinter PrettyPrinter(llvm::outs());
    PrettyPrinter.print(*AST);

    llvm::outs() << "===== Symbol Table ===== \n";
    SymbolTableBuilder SymTabBuilder;
    SymTabBuilder.visit(*AST);
    // SymTabBuilder.getSymbolTale().print(llvm::outs());

    llvm::outs() << "===== Type Analysis ===== \n";
    TypeAnalysis TA(SymTabBuilder.getSymbolTale(), TheTypeContext);
    TA.visit(*AST);
    for(auto Constraint: TA.getConstraints())
    {
        Constraint.print(llvm::outs());
    }
    TA.solve();

    llvm::outs() << "===== Code Generator ===== \n";
    CodeGenerator::emit(*AST, TheLLVMContext);

    return 0;
}
