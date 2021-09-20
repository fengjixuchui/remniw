#include "FrontEnd.h"
#include "ASTBuilder.h"
#include "RemniwLexer.h"
#include "RemniwParser.h"
#include <antlr4-runtime.h>

using namespace antlr4;

namespace remniw
{

std::unique_ptr<ProgramAST> FrontEnd::parse(std::istream& stream)
{
    ANTLRInputStream Input(stream);
    RemniwLexer Lexer(&Input);
    CommonTokenStream Tokens(&Lexer);
    Tokens.fill();
    // if (Verbose)
    // {
        // llvm::outs() << "===== Lexer ===== \n";
        // for (auto token : Tokens.getTokens())
        // {
        //     llvm::outs() << token->toString() << "\n";
        // }
    // }

    RemniwParser Parser(&Tokens);
    RemniwParser::ProgramContext* Program = Parser.program();

    // if (Verbose)
    // {
    //     llvm::outs() << "===== Parser ===== \n";
    //     llvm::outs() << Program->toStringTree(&Parser, true) << "\n";
    // }
    // if (Parser.getNumberOfSyntaxErrors())
    //     llvm::errs() << "===== Parser Failed ===== \n";

    ASTBuilder Builder(TheTypeContext);
    return Builder.build(Program);
}

}