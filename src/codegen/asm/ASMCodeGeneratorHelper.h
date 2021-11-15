#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Instructions.h"

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
enum Register
{
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

static Register ArgRegs[] = {RDI, RSI, RDX, RCX, R8, R9};

static inline const char *convertRegisterToString(Register Reg) {
    switch (Reg) {
    case RAX: return "%rax";
    case RBX: return "%rbx";
    case RCX: return "%rcx";
    case RDX: return "%rdx";
    case RSP: return "%rsp";
    case RBP: return "%rbp";
    case RDI: return "%rdi";
    case RSI: return "%rsi";
    case R8: return "%r8";
    case R9: return "%r9";
    case R10: return "%r10";
    case R11: return "%r11";
    case R12: return "%r12";
    case R13: return "%r13";
    case R14: return "%r14";
    case R15: return "%r15";
    };
    llvm_unreachable("unexpected Register\n");
}

class RegisterAllocator {
public:
    RegisterAllocator(): Flip(false) {}
    Register getAvailableRegister() {
        // FIXME
        Register Ret = Flip ? Register::R14 : Register::R15;
        Flip = !Flip;
        return Ret;
    }

private:
    bool Flip;
};

// FIXME
static RegisterAllocator *RA = new RegisterAllocator();

/** ================= Node =================== **/

struct burm_state;

class Node {
public:
    enum Kind
    {
        UndefNode,
        ImmNode,
        MemNode,
        RegNode,
        InstNode,
        ArgsNode,
        FunctionLabelNode,
        BasicBlockLabelNode,
        ConstantStringLabelNode,
    };

    //  private:
public:
    burm_state *State;
    Kind NodeKind;
    int Op;
    std::vector<Node *> Kids;
    bool ActionExecuted;
    union {
        // ImmNode members
        int64_t ImmVal;
        // MemNode members
        int64_t Offset;
        // RegNode members
        Register RegLoc;
        // InstNode members
        llvm::Instruction *Inst;
        // LabelNode members
        struct {
            const char *StringPtr;
            size_t StringSize;
            uint32_t UniqueCounter;  // Counter for tracking unique names
        };
    };
    static uint32_t LastUnique;

public:
    /** ================= Common Functions =================== **/

    Node(Kind NodeKind, int Op, std::vector<Node *> Kids):
        NodeKind(NodeKind), Op(Op), Kids(Kids), ActionExecuted(false) {}

    const char *getNodeKind() {
        switch (NodeKind) {
        case UndefNode: return "UndefNode";
        case ImmNode: return "ImmNode";
        case MemNode: return "MemNode";
        case RegNode: return "RegNode";
        case InstNode: return "InstNode";
        case ArgsNode: return "ArgsNode";
        case FunctionLabelNode: return "FunctionLabelNode";
        case BasicBlockLabelNode: return "BasicBlockLabelNode";
        case ConstantStringLabelNode: return "ConstantStringLabelNode";
        default: llvm_unreachable("unexpected NodeKind");
        }
    };

    int getOp() { return Op; }

    burm_state *getState() { return State; }

    void setState(burm_state *S) { State = S; }

    // Note: The elements of std::vector are stored contiguously, so elements
    // can be accessed using offsets to regular pointers to elements
    Node **getKids() { return &Kids[0]; }

    void setKids(const std::vector<Node *> &Ks) { Kids = Ks; }

    bool isActionExecuted() { return ActionExecuted; }

    void setActionExecuted() { ActionExecuted = true; }

    static Node *getUndefNode() {
        Node *Ret = new Node(Kind::UndefNode, /*Undef*/ 0, {});
        return Ret;
    }

    static Node *getImmNode(int64_t Val, std::vector<Node *> Kids) {
        Node *Ret = new Node(Kind::ImmNode, /*Const*/ 68, Kids);
        Ret->setImmVal(Val);
        return Ret;
    }

    static Node *getMemNode(int64_t Offset, std::vector<Node *> Kids) {
        Node *Ret = new Node(Kind::MemNode, /*Alloca*/ 31, Kids);
        Ret->setMemOffset(Offset);
        return Ret;
    }

    static Node *getRegNode(Register Reg, std::vector<Node *> Kids) {
        Node *Ret = new Node(Kind::RegNode, /*Reg*/ 71, Kids);
        Ret->setRegLoc(false, Reg);
        return Ret;
    }

    static Node *getInstNode(llvm::Instruction *I, std::vector<Node *> Kids) {
        Node *Ret = new Node(Kind::InstNode, I->getOpcode(), Kids);
        Ret->setInstruction(I);
        return Ret;
    }

    static Node *getArgsNode(std::vector<Node *> Kids) {
        Node *Ret = new Node(Kind::ArgsNode, /*Args*/ 70, Kids);
        return Ret;
    }

    static Node *getFunctionLabelNode(llvm::StringRef StrRef, std::vector<Node *> Kids) {
        Node *Ret = new Node(Kind::FunctionLabelNode, /*Label*/ 69, Kids);
        Ret->setLabelString(StrRef);
        return Ret;
    }

    static Node *getBasicBlockLabelNode(llvm::StringRef StrRef,
                                        std::vector<Node *> Kids) {
        Node *Ret = new Node(Kind::BasicBlockLabelNode, /*Label*/ 69, Kids);
        Ret->setLabelString(StrRef);
        return Ret;
    }

    static Node *getConstantStringLabelNode(llvm::StringRef StrRef,
                                            std::vector<Node *> Kids) {
        Node *Ret = new Node(Kind::ConstantStringLabelNode, /*Label*/ 69, Kids);
        Ret->setLabelString(StrRef);
        return Ret;
    }

    /** ================= ImmNode Functions =================== **/
    std::string getImmVal() { return std::string("$") + std::to_string(ImmVal); }

    void setImmVal(int64_t Val) { ImmVal = Val; }

    /** ================= MemNode Functions =================== **/
    std::string getMemLoc() { return std::to_string(Offset) + std::string("(%rbp)"); }

    void setMemOffset(int64_t O) { Offset = O; }

    /** ================= RegNode Functions =================== **/
    std::string getRegLocString() { return convertRegisterToString(RegLoc); }

    Register getRegLoc() { return RegLoc; }

    void setRegLoc(bool UseRegisterAllocator, Register Reg = Register::RAX) {
        if (UseRegisterAllocator) {
            RegLoc = RA->getAvailableRegister();
        } else {
            RegLoc = Reg;
        }
    }

    /** ================= InstNode Functions =================== **/
    llvm::Instruction *getInstruction() { return Inst; }

    void setInstruction(llvm::Instruction *I) { Inst = I; }

    /** ================= LabelNode Functions =================== **/

    void setLabelString(llvm::StringRef StrRef) {
        StringPtr = StrRef.data();
        StringSize = StrRef.size();
        if (NodeKind == Kind::BasicBlockLabelNode)
            UniqueCounter = LastUnique++;
    }

    std::string getLabelStringAsLabel() {
        assert((NodeKind == Kind::BasicBlockLabelNode ||
                NodeKind == Kind::FunctionLabelNode) &&
               "NodeKind must be BasicBlockLabelNode or FunctionLabelNode");
        if (NodeKind == Kind::BasicBlockLabelNode) {
            return ".BB." + std::string(StringPtr, StringSize) + '.' +
                   std::to_string(UniqueCounter);
        } else {
            return std::string(StringPtr, StringSize);
        }
    }

    std::string getLabelStringAsConstant() {
        assert((NodeKind == Kind::ConstantStringLabelNode ||
                NodeKind == Kind::FunctionLabelNode) &&
               "NodeKind must be ConstantStringLabelNode or FunctionLabelNode");
        return "$" + std::string(StringPtr, StringSize);
    }
};

typedef Node *NODEPTR;

#define GET_KIDS(p)     ((p)->getKids())
#define PANIC           printf
#define STATE_LABEL(p)  ((p)->getState())
#define SET_STATE(p, s) ((p)->setState(s))
#define DEFAULT_COST    break
#define OP_LABEL(p)     ((p)->getOp())
#define NO_ACTION(x)

/** ================= Cost =================== **/

struct COST {
    COST(int cost):cost(cost) { }
    int cost;
};

#define COST_LESS(a, b) ((a).cost < (b).cost)
static COST COST_INFINITY = COST(32767);
static COST COST_ZERO = COST(0);

static int shouldTrace = 0;
static int shouldCover = 0;

static void burm_trace(NODEPTR, int, COST);


namespace remniw {

struct AsmFunction {
    AsmFunction(int64_t TotalAllocaSizeInBytes, llvm::SmallVector<Node *> ExprTrees,
                std::string FuncName):
        TotalAllocaSizeInBytes(TotalAllocaSizeInBytes),
        ExprTrees(ExprTrees), FuncName(FuncName) {}

    int64_t TotalAllocaSizeInBytes;
    llvm::SmallVector<Node *> ExprTrees;
    std::string FuncName;
};

class AsmCodeGenerator {
private:
    llvm::raw_ostream &Out;
    llvm::SmallVector<AsmFunction> Functions;
    // llvm::SmallVector<llvm::GlobalVariable*> GlobalVariables;
    llvm::DenseMap<llvm::GlobalVariable *, llvm::StringRef> GlobalVariables;

public:
    AsmCodeGenerator(
        llvm::SmallVector<AsmFunction> Functions,
        llvm::DenseMap<llvm::GlobalVariable *, llvm::StringRef> GlobalVariables):
        Out(llvm::outs()),
        Functions(std::move(Functions)), GlobalVariables(std::move(GlobalVariables)) {}

    void EmitAssembly() {
        for (auto &F : Functions) {
            EmitFunction(F);
        }
        EmitGlobalVariables();
    }

    void EmitFunction(AsmFunction &F);

    void EmitFunctionDeclaration(AsmFunction &F) {
        // FIXME
        Out << ".text\n"
            << ".globl " << F.FuncName << "\n"
            << ".type " << F.FuncName << ", @function\n"
            << F.FuncName << ":\n";
    }

    void EmitFunctionPrologue(AsmFunction &F) {
        Out << "\tpushq\t"
            << "%rbp\n";
        Out << "\tmovq\t"
            << "%rsp, %rbp\n";
        Out << "\tsubq\t"
            << "$" << F.TotalAllocaSizeInBytes << ", %rsp\n";
    }

    void EmitFunctionEpilogue(AsmFunction &F) {
        Out << "\tmovq\t"
            << "%rbp, %rsp\n";
        Out << "\tpopq\t"
            << "%rbp\n";
        Out << "\tretq\n\n";
    }

    void EmitGlobalVariables() {
        for (auto p : GlobalVariables) {
            Out << p.first->getName().str() << ":\n";
            Out << "\t.asciz ";
            Out << "\"";
            Out.write_escaped(p.second);
            Out << "\"\n";
        }
    }

    void EmitMov(std::string Src, std::string Dst) {
        Out << "\tmovq\t" << Src << ", " << Dst << "\n";
    }

    void EmitLea(std::string Src, std::string Dst) {
        Out << "\tleaq\t" << Src << ", " << Dst << "\n";
    }

    void EmitCmp(std::string Src, std::string Dst) {
        Out << "\tcmpq\t" << Src << ", " << Dst << "\n";
    }

    void EmitJmp(std::string Jmp, std::string Dst) {
        Out << '\t' << Jmp << '\t' << Dst << "\n";
    }

    void EmitAdd(std::string Src, std::string Dst) {
        Out << "\taddq\t" << Src << ", " << Dst << "\n";
    }

    void EmitSub(std::string Src, std::string Dst) {
        Out << "\tsubq\t" << Src << ", " << Dst << "\n";
    }

    void EmitImul(std::string Src, std::string Dst) {
        Out << "\timulq\t" << Src << ", " << Dst << "\n";
    }

    void EmitIdiv(std::string Src) { Out << "\tidivq\t" << Src << "\n"; }

    // Convert quadword in %rax to octoword in %rdx:%rax
    void EmitCqto() { Out << "\tcqto\n"; }

    void EmitCall(std::string label) { Out << "\tcallq\t" << label << "\n"; }

    void EmitXor(std::string Src, std::string Dst) {
        Out << "\txorq\t" << Src << ", " << Dst << "\n";
    }
};

typedef AsmCodeGenerator *AsmCodeGeneratorPtr;

class ExprTreeBuilder: public llvm::InstVisitor<ExprTreeBuilder, Node *> {
public:
    llvm::DenseMap<llvm::GlobalVariable *, llvm::StringRef> ConstantStrings;
    llvm::SmallVector<AsmFunction> Functions;
    llvm::DenseMap<llvm::Instruction *, Node *> InstMap;
    llvm::DenseMap<llvm::Value *, Node *> LabelMap;
    llvm::DenseMap<llvm::Argument *, Node *> ArgMap;
    llvm::SmallVector<Node *> ExprTrees;
    const llvm::DataLayout &DL;
    int64_t offset;  // clear per function
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

    void visit(llvm::Module &M) {
        for (llvm::GlobalVariable &GV : M.globals()) {
            if (llvm::ConstantDataArray *CDA =
                    llvm::dyn_cast<llvm::ConstantDataArray>(GV.getInitializer())) {
                if (CDA->isCString()) {
                    LabelMap[&GV] = Node::getConstantStringLabelNode(GV.getName(), {});
                    ConstantStrings[&GV] = CDA->getAsCString();
                }
            }
        }
        visit(M.begin(), M.end());
    }

    void visit(llvm::Function &F) {
        if (F.isDeclaration())
            return;

        offset = 0;
        ExprTrees.clear();

        for (unsigned i = 0, e = F.arg_size(); i != e; ++i) {
            llvm::Argument *Arg = F.getArg(i);
            Node *ArgNode;
            if (i < 6) {
                ArgNode = Node::getRegNode(ArgRegs[i], {});
            } else {
                llvm::Type *Ty = F.getArg(i)->getType();
                uint64_t SizeInBytes =
                    F.getParent()->getDataLayout().getTypeAllocSize(Ty);
                ArgNode = Node::getMemNode(8 * (i - 6 + 2),
                                           {Node::getImmNode(SizeInBytes, {})});
            }
            ArgMap[Arg] = ArgNode;
        }

        // body
        for (auto &BB : F) {
            ExprTrees.push_back(visitOperand(&BB));
            for (auto &I : BB) {
                InstVisitor::visit(I);
            }
        }

        AsmFunction Func((-offset + 16 - 1) / 16 * 16 /* align to 16-bytes*/, ExprTrees,
                         F.getName().str());
        Functions.push_back(Func);
    }

    Node *visitOperand(llvm::Value *V) {
        if (auto *CE = llvm::dyn_cast<llvm::ConstantExpr>(V)) {
            // FIXME
            return visitOperand(CE->getOperand(0));
        } else if (auto *GV = llvm::dyn_cast<llvm::GlobalVariable>(V)) {
            auto it = LabelMap.find(GV);
            assert(it != LabelMap.end() && "operands must be previously defined");
            return it->second;
        } else if (auto *CI = llvm::dyn_cast<llvm::ConstantInt>(V)) {
            Node *T = Node::getImmNode(CI->getSExtValue(), {});
            return T;
        } else if (auto *I = llvm::dyn_cast<llvm::Instruction>(V)) {
            auto it = InstMap.find(I);
            assert(it != InstMap.end() && "operands must be previously defined");
            return it->second;
        } else if (auto *Arg = llvm::dyn_cast<llvm::Argument>(V)) {
            auto it = ArgMap.find(Arg);
            assert(it != ArgMap.end() && "operands must be previously defined");
            return it->second;
        } else if (auto *F = llvm::dyn_cast<llvm::Function>(V)) {
            auto it = LabelMap.find(V);
            if (it == LabelMap.end()) {
                LabelMap[V] = Node::getFunctionLabelNode(F->getName(), {});
                return LabelMap[V];
            }
            return it->second;
        } else if (auto *BB = llvm::dyn_cast<llvm::BasicBlock>(V)) {
            auto it = LabelMap.find(V);
            if (it == LabelMap.end()) {
                LabelMap[V] = Node::getBasicBlockLabelNode(BB->getName(), {});
                return LabelMap[V];
            }
            return it->second;
        }
        llvm_unreachable("unhandled operand");
        return nullptr;
    }

    uint64_t getAllocaSizeInBytes(const llvm::AllocaInst &AI) const {
        uint64_t ArraySize = 1;
        if (AI.isArrayAllocation()) {
            const llvm::ConstantInt *CI =
                llvm::dyn_cast<llvm::ConstantInt>(AI.getArraySize());
            assert(CI && "non-constant array size");
            ArraySize = CI->getZExtValue();
        }
        llvm::Type *Ty = AI.getAllocatedType();
        uint64_t SizeInBytes = AI.getModule()->getDataLayout().getTypeAllocSize(Ty);
        return SizeInBytes * ArraySize;
    }

    Node *visitAllocaInst(llvm::AllocaInst &AI) {
        uint64_t AllocaSizeInBytes = getAllocaSizeInBytes(AI);
        offset -= AllocaSizeInBytes;
        auto *AllocaNode =
            Node::getMemNode(offset, {Node::getImmNode(AllocaSizeInBytes, {})});
        InstMap[&AI] = AllocaNode;
        ExprTrees.push_back(AllocaNode);
        return AllocaNode;
    }

    Node *visitBranchInst(llvm::BranchInst &BI) {
        Node *InstNode;
        if (BI.isUnconditional()) {
            InstNode =
                Node::getInstNode(&BI, {visitOperand(BI.getSuccessor(0)),
                                        Node::getUndefNode(), Node::getUndefNode()});
        } else {
            if (BI.getCondition() ==
                llvm::ConstantInt::getTrue(llvm::Type::getInt1Ty(BI.getContext()))) {
                InstNode =
                    Node::getInstNode(&BI, {visitOperand(BI.getSuccessor(0)),
                                            Node::getUndefNode(), Node::getUndefNode()});
            } else if (BI.getCondition() == llvm::ConstantInt::getFalse(
                                                llvm::Type::getInt1Ty(BI.getContext()))) {
                InstNode =
                    Node::getInstNode(&BI, {visitOperand(BI.getSuccessor(1)),
                                            Node::getUndefNode(), Node::getUndefNode()});
            } else {
                auto *ICI = llvm::cast<llvm::ICmpInst>(BI.getCondition());
                assert(InstMap.count(ICI) && "BI.getCondition() not in InstMap");
                InstNode = Node::getInstNode(&BI, {InstMap[ICI],
                                                   visitOperand(BI.getSuccessor(0)),
                                                   visitOperand(BI.getSuccessor(1))});
            }
        }
        InstMap[&BI] = InstNode;
        ExprTrees.push_back(InstNode);
        return InstNode;
    }

    Node *visitCallInst(llvm::CallInst &CI) {
        std::vector<Node *> Kids;
        Node *Args = Node::getArgsNode({Node::getUndefNode(), Node::getUndefNode()});
        Node *CurrentNode = Args;
        for (unsigned i = 0, e = CI.arg_size(); i != e; ++i) {
            Node *ArgsTmp =
                Node::getArgsNode({Node::getUndefNode(), Node::getUndefNode()});
            CurrentNode->setKids({visitOperand(CI.getArgOperand(i)), ArgsTmp});
            CurrentNode = ArgsTmp;
            if (i >= 6)  // push arg on stack
            {
                llvm::Type *Ty = CI.getArgOperand(i)->getType();
                uint64_t SizeInBytes =
                    CI.getModule()->getDataLayout().getTypeAllocSize(Ty);
                offset -= SizeInBytes;
            }
        }
        Node *Ret;
        if (auto *Callee = CI.getCalledFunction())  // direct call
        {
            Ret = Node::getInstNode(&CI, {visitOperand(Callee), Args});
        } else  // indirect call
        {
            Ret = Node::getInstNode(&CI, {visitOperand(CI.getCalledOperand()), Args});
        }
        InstMap[&CI] = Ret;
        ExprTrees.push_back(Ret);
        return Ret;
    }

    // Node* visitReturnInst(llvm::ReturnInst &I);
    // Node* visitLoadInst(llvm::LoadInst &I);
    // Node* visitStoreInst(llvm::StoreInst &I);
    // Node* visitICmpInst(llvm::ICmpInst &I);
    // Node* visitAdd(llvm::BinaryOperator &I);
    // Node* visitSub(llvm::BinaryOperator &I);
    // Node* visitMul(llvm::BinaryOperator &I);
    // Node* visitSDiv(llvm::BinaryOperator &I);

    /// Specify what to return for unhandled instructions.
    Node *visitInstruction(llvm::Instruction &I) {
        std::vector<Node *> Kids;
        for (unsigned i = 0, e = I.getNumOperands(); i != e; ++i) {
            Kids.push_back(visitOperand(I.getOperand(i)));
        }
        Node *T = Node::getInstNode(&I, Kids);
        InstMap[&I] = T;
        ExprTrees.push_back(T);
        return T;
    }
};

}  // namespace remniw