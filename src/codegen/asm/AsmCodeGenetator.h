#pragma once

#include "AsmBuilder.h"
#include "AsmContext.h"
#include "AsmRewriter.h"
#include "BrgTreeBuilder.h"

namespace remniw {

class AsmCodeGenerator {
public:
    AsmCodeGenerator(llvm::Module *M): DL(M->getDataLayout()), AsmCtx() {
        BrgTreeBuilder BBuilder(DL, AsmCtx);
        BBuilder.visit(*M);
        AsmBuilder ABuilder(AsmCtx, BBuilder.getFunctions(),
                            BBuilder.getConstantStrings());
        AsmRewriter Rewriter(ABuilder.getAsmFunctions());
        // remniw::AsmPrinter Printer;
    }

private:
    const llvm::DataLayout &DL;
    AsmContext AsmCtx;
};
}  // namespace remniw