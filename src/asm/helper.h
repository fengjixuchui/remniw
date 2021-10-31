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

/*
Register Usage function calls
- %rax:
    temporary register; with variable arguments passes information about the
        number of vector registers used; 1st return register
    not preserved across function calls

- %rbx: callee-saved register. preserved across function calls

- %rcx: used to pass 4th integer argument to functions.
        not preserved across function calls

- %rdx: used to pass 3rd argument to functions; 2nd return register.
        not preserved across function calls

- %rsp: stack pointer, preserved across function calls

- %rbp: callee-saved register; optionally used as frame pointer
        preserved across function calls

- %rsi: used to pass 2nd argument to functions
        not preserved across function calls

- %rdi: used to pass 1st argument to functions
        not preserved across function calls

- %r8: used to pass 5th argument to functions
       not preserved across function calls

- %r9: used to pass 6th argument to functions
       not preserved across function calls

- %r10: temporary register, used for passing a function’s static chain pointer
        not preserved across function calls

- %r11: temporary register
        not preserved across function calls

- %r12-r14: callee-saved registers
            preserved across function calls

- %r15: callee-saved register; optionally used as GOT base pointer
        preserved across function calls
*/
enum Register {
    RAX,
    RBX,
    RCX,
    RDX,
    RSP,
    RBP,
    RDI,
    RSI,
    R8,
    R9,
    R10,
    R11,
    R12,
    R13,
    R14,
    R15,
};

class RegisterAllocator {
public:
    RegisterAllocator(): Flip(false) {}
    Register getAvailableRegister(){
        // FIXME
        Register Ret = Flip ? Register::R8 : Register::R9;
        Flip = !Flip;
        return Ret;
    }
private:
    bool Flip;
};


/** ================= Node =================== **/
// FIXME
static RegisterAllocator *RA = new RegisterAllocator();

struct burm_state;

class Node {
public:
    enum Kind {
        UndefNode,
        ImmNode,
        MemNode,
        RegNode,
        InstNode,
        LabelNode
    };

 private:
    const Kind NodeKind;
    int Op;
    burm_state *State;
    std::vector<Node *> Kids;
    union
    {
        // ImmNode members
        int64_t ImmVal;
        // MemNode members
        uint64_t Offset;
        // RegNode members
        Register RegLoc;
        // RegisterAllocator *RA;
        // InstNode members
        llvm::Instruction* Inst;
        // LabelNode members
        llvm::BasicBlock* BB;
    };


public:
    /** ================= Common Functions =================== **/

    Node(Kind NodeKind, int Op, std::vector<Node *> Kids):
        NodeKind(NodeKind), Op(Op), Kids(Kids) {}

    int getOp() { return Op; }

    burm_state* getState() { return State; }

    void setState(burm_state* S) { State = S; }

    // Node: The elements of std::vector are stored contiguously, so elements
    // can be accessed using offsets to regular pointers to elements
    Node** getKids() { return &Kids[0]; }

    static Node* getUndefNode()
    {
        Node* Ret = new Node(Kind::UndefNode, /*Undef*/0, {});
        return Ret;
    }

    static Node* getImmNode(int64_t Val, std::vector<Node *> Kids)
    {
        Node* Ret = new Node(Kind::ImmNode, /*Const*/68, Kids);
        Ret->setImmVal(Val);
        return Ret;
    }

    static Node* getMemNode(uint64_t Offset, std::vector<Node *> Kids)
    {
        Node* Ret = new Node(Kind::MemNode, /*Alloca*/31, Kids);
        Ret->setMemOffset(Offset);
        return Ret;
    }

    static Node* getRegNode(Register Reg, std::vector<Node *> Kids)
    {
        Node* Ret = new Node(Kind::RegNode, /*FIXME*/-1, Kids);
        return Ret;
    }

    static Node* getInstNode(llvm::Instruction* I, std::vector<Node *> Kids)
    {
        Node* Ret = new Node(Kind::InstNode, I->getOpcode(), Kids);
        Ret->setInstruction(I);
        return Ret;
    }

    static Node* getLabelNode(llvm::BasicBlock* BB, std::vector<Node *> Kids)
    {
        Node* Ret = new Node(Kind::LabelNode, /*Label*/69, Kids);
        Ret->setBasicBlock(BB);
        return Ret;
    }

    /** ================= ImmNode Functions =================== **/
    std::string getImmVal() {
        return std::string("$") + std::to_string(ImmVal);
    }

    void setImmVal(int64_t Val) { ImmVal = Val; }

    /** ================= MemNode Functions =================== **/
    std::string getMemLoc() {
        return std::string("-") + std::to_string(Offset) + std::string("(%rbp)");
    }

    void setMemOffset(uint64_t O) { Offset = O; }

    /** ================= RegNode Functions =================== **/
    std::string getRegLocString() {
        return convertRegisterToString(RegLoc);
    }

    Register getRegLoc()
    {
        return RegLoc;
    }

    void setRegLoc(bool UseRegisterAllocator, Register Reg = Register::RAX) {
        if (UseRegisterAllocator) {
            RegLoc = RA->getAvailableRegister();
        }
        else {
            RegLoc = Reg;
        }
    }

    /** ================= InstNode Functions =================== **/
    llvm::Instruction* getInstruction()
    {
        return Inst;
    }

    void setInstruction(llvm::Instruction *I) { Inst = I; }

    /** ================= InstNode Functions =================== **/
    llvm::BasicBlock* getBasicBlock()
    {
        return BB;
    }

    void setBasicBlock(llvm::BasicBlock *B) { BB = B; }

    std::string getLabelString()
    {
        return std::string(".LB_") + BB->getName().str();
    }

private:
    const char* convertRegisterToString(Register Reg)
    {
        switch (Reg) {
        case RAX:   return "%rax";
        case RBX:   return "%rbx";
        case RCX:   return "%rcx";
        case RDX:   return "%rdx";
        case RSP:   return "%rsp";
        case RBP:   return "%rbp";
        case RDI:   return "%rdi";
        case RSI:   return "%rsi";
        case R8:    return "%r8";
        case R9:    return "%r9";
        case R10:   return "%r10";
        case R11:   return "%r11";
        case R12:   return "%r12";
        case R13:   return "%r13";
        case R14:   return "%r14";
        case R15:   return "%r15";
        default:    llvm_unreachable("unexpected Register\n");
        };
    }
};

typedef Node *NODEPTR;

#define GET_KIDS(p)	((p)->getKids())
#define PANIC printf
#define STATE_LABEL(p) ((p)->getState())
#define SET_STATE(p,s) ((p)->setState(s))
#define DEFAULT_COST	break
#define OP_LABEL(p) ((p)->getOp())
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

static void burm_trace(NODEPTR, int, COST);

// void printDebugTree(Node *p, int indent=0) {
//     if(p != nullptr) {
//         if (indent) std::cerr << "|";
//         int i = 0;
//         for (; i < indent-4; ++i) std::cerr << " ";
//         if (indent-4 > 0) std::cerr << "|";
//         for (; i < indent; ++i) std::cerr << "-";
//         std::cerr << "+ op:" << p->op << ", val:" << p->val << "\n";

//         if (p->kids[0])
//             printDebugTree(p->kids[0], (indent+4));
//         if (p->kids[1])
//             printDebugTree(p->kids[1], (indent+4));
//     }
// }

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
    llvm::DenseMap<llvm::BasicBlock *, Node *> BBNodeMap;
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
                auto *AllocaNode =
                    Node::getMemNode(offset,
                        { Node::getImmNode(AllocaSizeInBytes, {}) });
                InstMap[&I] = AllocaNode;
            }
        }

        // body
        for (auto &BB : F) {
            // FIXME:
            // Here we push_back a LabelNode for generating label in assembly
            // when calling FunctionASM::EmitAssembly.
            // But multiple redundant LabelNodes for same BB is used,
            // cause we also have LabelNode for same BB used in BranchInstNode.
            ExprTrees.push_back(Node::getLabelNode(&BB, {}));
            for(auto &I : BB) {
                InstVisitor::visit(I);
            }
        }

        FunctionASM Func(offset, ExprTrees, F.getName().str());
        Functions.push_back(Func);
    }

    Node* visitOperand(llvm::Value* V)
    {
        if (auto *CI = llvm::dyn_cast<llvm::ConstantInt>(V)){
            Node* T =  Node::getImmNode(CI->getSExtValue(), {});
            return T;
        }
        else if (auto *I = llvm::dyn_cast<llvm::Instruction>(V))
        {
            auto it = InstMap.find(I);
            assert(it != InstMap.end() && "operands must be previously defined");
            return it->second;
        }
        llvm_unreachable("unhandled operand");
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
        return nullptr;
    }

    Node* visitBranchInst(llvm::BranchInst &BI)
    {
        Node *InstNode;
        if (BI.isUnconditional()) {
            InstNode = Node::getInstNode(&BI,
                                         {Node::getLabelNode(BI.getSuccessor(0), {}),
                                          Node::getUndefNode(),
                                          Node::getUndefNode()});
        }
        else
        {
            if (BI.getCondition() ==
                llvm::ConstantInt::getTrue(llvm::Type::getInt1Ty(BI.getContext())))
            {
                InstNode = Node::getInstNode(&BI,
                                            {Node::getLabelNode(BI.getSuccessor(0), {}),
                                            Node::getUndefNode(),
                                            Node::getUndefNode()});
            }
            else if (BI.getCondition() ==
                llvm::ConstantInt::getFalse(llvm::Type::getInt1Ty(BI.getContext())))
            {
                InstNode = Node::getInstNode(&BI,
                                            {Node::getLabelNode(BI.getSuccessor(1), {}),
                                            Node::getUndefNode(),
                                            Node::getUndefNode()});
            }
            else
            {
                auto* ICI = llvm::cast<llvm::ICmpInst>(BI.getCondition());
                assert(InstMap.count(ICI) &&
                    "BI.getCondition() not in InstMap");
                InstNode = Node::getInstNode(&BI,
                                    { InstMap[ICI],
                                        Node::getLabelNode(BI.getSuccessor(0), {}),
                                        Node::getLabelNode(BI.getSuccessor(1), {})});
            }

        }
        InstMap[&BI] = InstNode;
        if (BI.use_empty())
            ExprTrees.push_back(InstNode);
    }

    // Node* visitReturnInst(llvm::ReturnInst &I);
    // Node* visitLoadInst(llvm::LoadInst &I);
    // Node* visitStoreInst(llvm::StoreInst &I);
    // Node* visitCallInst(llvm::CallInst &I);
    // Node* visitICmpInst(llvm::ICmpInst &I);
    // Node* visitAdd(llvm::BinaryOperator &I);
    // Node* visitSub(llvm::BinaryOperator &I);
    // Node* visitMul(llvm::BinaryOperator &I);
    // Node* visitSDiv(llvm::BinaryOperator &I);

    /// Specify what to return for unhandled instructions.
    Node *visitInstruction(llvm::Instruction &I) {
        std::vector<Node*> Kids;
        for (unsigned i = 0, e = I.getNumOperands(); i != e; ++i)
        {
            Kids.push_back(visitOperand(I.getOperand(i)));
        }
        Node *T = Node::getInstNode(&I, Kids);
        InstMap[&I] = T;
        if (I.use_empty())
            ExprTrees.push_back(T);
        return T;
    }
};