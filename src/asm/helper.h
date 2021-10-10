#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"

struct Tree {
    Tree(): op(0), kids{nullptr, nullptr}, val(0), x{nullptr} {}
    Tree(int op, Tree* l, Tree* r, int64_t val):
        op(op), kids{l, r}, val(val), x{nullptr} {}
    int op;
    struct Tree *kids[2];
    int64_t val;
    struct { struct burm_state *state; } x;

    int offset; // used in alloca
};

typedef Tree *NODEPTR;
// typedef Tree *Tree_;

#define GET_KIDS(p)	((p)->kids)
#define PANIC printf
#define STATE_LABEL(p) ((p)->x.state)
#define SET_STATE(p,s) (p)->x.state=(s)
#define DEFAULT_COST	break
#define NO_ACTION(x)

typedef struct COST {
    int cost;
} COST;

#define COST_LESS(a,b) ((a).cost < (b).cost)
static COST COST_INFINITY = { 32767 };
static COST COST_ZERO     = { 0 };

static int shouldTrace = 0;
static int shouldCover = 0;

int OP_LABEL(NODEPTR p) {
    switch (p->op) {
    default:     return p->op;
    }
}

static void burm_trace(NODEPTR, int, COST);

class ExprTreeBuilder : public llvm::InstVisitor<ExprTreeBuilder, Tree*> {
public:
    llvm::DenseMap<llvm::Instruction *, Tree *> InstMap;
    llvm::SmallVector<Tree *> ExprTrees;
    const llvm::DataLayout &DL;

    int offset; // clear per function

public:
    ExprTreeBuilder(const llvm::DataLayout &DL):DL(DL), offset(0) {}

    Tree* visitOperand(llvm::Value* V)
    {
        if (auto *CI = llvm::dyn_cast<llvm::ConstantInt>(V)){
            Tree* T = new Tree;
            T->op = /*IMM*/69;
            T->val = CI->getSExtValue();
            return T;
        }
        else if (auto *I = llvm::dyn_cast<llvm::Instruction>(V))
        {
            auto it = InstMap.find(I);
            assert(it != InstMap.end() && "operands must be previously defined");
            return it->second;
        }
        assert("unhandled operand");
        return nullptr;
    }
    uint64_t getAllocaSizeInBytes(const llvm::AllocaInst &AI) const {
        uint64_t ArraySize = 1;
        if (AI.isArrayAllocation()) {
            const llvm::ConstantInt *CI = llvm::dyn_cast<llvm::ConstantInt>(AI.getArraySize());
            assert(CI && "non-constant array size");
            ArraySize = CI->getZExtValue();
        }
        llvm::Type *Ty = AI.getAllocatedType();
        uint64_t SizeInBytes =
            AI.getModule()->getDataLayout().getTypeAllocSize(Ty);
        return SizeInBytes * ArraySize;
    }

    Tree* visitAllocaInst(llvm::AllocaInst &I){
        Tree *T = new Tree;
        T->op = I.getOpcode();
        T->kids[0] = new Tree(69, nullptr, nullptr, getAllocaSizeInBytes(I));
        offset += getAllocaSizeInBytes(I);
        T->offset = offset; 
        InstMap[&I] = T;
        ExprTrees.push_back(T);
        return T; 
    }
    // Tree visitReturnInst(llvm::ReturnInst &I);
    // Tree visitLoadInst(llvm::LoadInst &I);
    // Tree visitStoreInst(llvm::StoreInst &I);
    // Tree visitCallInst(llvm::CallInst &I);
    // Tree visitICmpInst(llvm::ICmpInst &I); 
    // Tree visitBranchInst(llvm::BranchInst &I);
    // Tree visitAdd(llvm::BinaryOperator &I);
    // Tree visitSub(llvm::BinaryOperator &I);
    // Tree visitMul(llvm::BinaryOperator &I);
    // Tree visitSDiv(llvm::BinaryOperator &I);

    /// Specify what to return for unhandled instructions.
    Tree *visitInstruction(llvm::Instruction &I) {
        Tree *T = new Tree;
        T->op = I.getOpcode();
        for (unsigned i = 0, e = I.getNumOperands(); i != e; ++i)
        {
            T->kids[i] = visitOperand(I.getOperand(i));
        }
        InstMap[&I] = T;
        ExprTrees.push_back(T);
        return T;
    }
};