#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"

class RegisterAllocator {
public:
    RegisterAllocator(): RegIndex(0) {}
    std::string getAvailableRegister(){
        return std::string("%reg") + std::to_string(RegIndex++);
    }
private:
    int RegIndex;
};


/** ================= Node =================== **/

class Node {
public:
    Node(): x{nullptr}, op(0), kids{nullptr, nullptr}, val(0) {}

    Node(int op, Node* l, Node* r, int64_t val, RegisterAllocator* ra):
        x{nullptr}, op(op), kids{l, r}, val(val), RA(ra) {}

    std::string getRegLoc() {
        return MemLoc;
    }

    void setRegLoc(bool UseRegisterAllocator, std::string Loc = "") {
        if (UseRegisterAllocator) {
            MemLoc = RA->getAvailableRegister();
        }
        else {
            MemLoc = Loc;
        }
    }

    std::string getMemLoc() {
        return std::string("-") + std::to_string(offset) + std::string("(%rbp)");
    }

    std::string getImmVal() {
        return std::string("$") + std::to_string(val);
    }

    struct { struct burm_state *state; } x;
    int op;
    struct Node *kids[2];
    int64_t val;
    int offset; // used in alloca
    std::string MemLoc;

    RegisterAllocator *RA;
};

typedef Node *NODEPTR;

#define GET_KIDS(p)	((p)->kids)
#define PANIC printf
#define STATE_LABEL(p) ((p)->x.state)
#define SET_STATE(p,s) (p)->x.state=(s)
#define DEFAULT_COST	break
#define NO_ACTION(x)

/** ================= Cost =================== **/

class COST {
public:
  int cost;
public:
	COST(int Cost) { cost = Cost; }
	int getCost() { return cost; }
	void setCost(int Cost) { cost = Cost; }
};

#define COST_LESS(a,b) ((a).getCost() < (b).getCost())
static COST COST_INFINITY = COST(32767);
static COST COST_ZERO     = COST(0);

static int shouldTrace = 0;
static int shouldCover = 0;

int OP_LABEL(NODEPTR p) {
    switch (p->op) {
    default:     return p->op;
    }
}

static void burm_trace(NODEPTR, int, COST);


void printDebugTree(Node *p, int indent=0) {
    if(p != nullptr) {
        if (indent) std::cerr << "|";
        int i = 0;
        for (; i < indent-4; ++i) std::cerr << " ";
        if (indent-4 > 0) std::cerr << "|";
        for (; i < indent; ++i) std::cerr << "-";
        std::cerr << "+ op:" << p->op << ", val:" << p->val << "\n";

        if (p->kids[0])
            printDebugTree(p->kids[0], (indent+4));
        if (p->kids[1])
            printDebugTree(p->kids[1], (indent+4));
    }
}

class FunctionASM {
public:
    FunctionASM(int64_t LovalVariableSpaceInBytes, llvm::SmallVector<Node *> ExprTrees,
                std::string FuncName):
        LovalVariableSpaceInBytes(LovalVariableSpaceInBytes),
        ExprTrees(ExprTrees),
        FuncName(FuncName) {}
    void EmitAssembly();
private:
    int64_t LovalVariableSpaceInBytes;
    llvm::SmallVector<Node *> ExprTrees;
    std::string FuncName;
};

class ExprTreeBuilder : public llvm::InstVisitor<ExprTreeBuilder, Node*> {
public:
    llvm::SmallVector<FunctionASM> Functions;
    llvm::DenseMap<llvm::Instruction *, Node *> InstMap;
    llvm::SmallVector<Node *> ExprTrees;
    const llvm::DataLayout &DL;
    uint64_t offset; // clear per function
    RegisterAllocator *RA;

public:
    ExprTreeBuilder(const llvm::DataLayout &DL):
        DL(DL), offset(0), RA(new RegisterAllocator()) {}

    ~ExprTreeBuilder() { delete RA; }

    template<class Iterator>
    void visit(Iterator Start, Iterator End) {
        while (Start != End)
            visit(*Start++);
    }

    // Define visitors for functions and basic blocks...
    //
    void visit(llvm::Module &M) {
        visit(M.begin(), M.end());
    }

    void visit(llvm::Function &F)
    {
        if (F.isDeclaration())
            return;

        offset = 0;
        ExprTrees.clear();

        for (auto &I : instructions(F)) {
            if (auto *AI = llvm::dyn_cast<llvm::AllocaInst>(&I)) {
                uint64_t AllocaSizeInBytes = getAllocaSizeInBytes(*AI);
                offset += AllocaSizeInBytes;
                auto *AllocaNode = new Node(
                    I.getOpcode(),
                    new Node(0, nullptr, nullptr, AllocaSizeInBytes, RA),
                    nullptr,
                    0,
                    RA
                    );
                AllocaNode->offset = offset;
                InstMap[&I] = AllocaNode;
            }
        }

        // body
        for (auto &I : instructions(F)) {
            InstVisitor::visit(I);
        }

        FunctionASM Func(offset, ExprTrees, F.getName().str());
        Functions.push_back(Func);
    }

    Node* visitOperand(llvm::Value* V)
    {
        if (auto *CI = llvm::dyn_cast<llvm::ConstantInt>(V)){
            Node* T = new Node;
            T->op = /*Const*/0;
            T->val = CI->getSExtValue();
            T->RA = RA;
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

    Node* visitAllocaInst(llvm::AllocaInst &I){
        // Tree *T = new Tree;
        // T->op = I.getOpcode();
        // T->kids[0] = new Tree(0, nullptr, nullptr, getAllocaSizeInBytes(I));
        // offset += getAllocaSizeInBytes(I);
        // T->offset = offset;
        // InstMap[&I] = T;
        // return T;
        return nullptr;
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
    Node *visitInstruction(llvm::Instruction &I) {
        Node *T = new Node;
        T->op = I.getOpcode();
        T->RA = RA;
        for (unsigned i = 0, e = I.getNumOperands(); i != e; ++i)
        {
            T->kids[i] = visitOperand(I.getOperand(i));
        }
        InstMap[&I] = T;
        if (I.use_empty())
            ExprTrees.push_back(T);
        return T;
    }
};