#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AsmOperand.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Instructions.h"

struct burm_state;

class BrgTreeNode {
public:
    enum KindTy
    {
        UndefNode,
        ImmNode,
        MemNode,
        RegNode,
        InstNode,
        ArgsNode,
        LabelNode,
    };

private:
    burm_state *State;
    KindTy Kind;
    int Op;
    std::vector<BrgTreeNode *> Kids;
    bool ActionExecuted;
    union {
        // ImmNode, MemNode, RegNode, LabelNode member
        remniw::AsmOperand *AsmOp;
        // InstNode member
        llvm::Instruction *Inst;
    };

public:
    /** ================= Common Functions =================== **/
    BrgTreeNode(KindTy Kind, int Op): Kind(Kind), Op(Op), Kids(), ActionExecuted(false) {}

    BrgTreeNode(KindTy Kind, int Op, std::vector<BrgTreeNode *> Kids):
        Kind(Kind), Op(Op), Kids(Kids), ActionExecuted(false) {}

    const char *getNodeKind() {
        switch (Kind) {
        case UndefNode: return "UndefNode";
        case ImmNode: return "ImmNode";
        case MemNode: return "MemNode";
        case RegNode: return "RegNode";
        case InstNode: return "InstNode";
        case ArgsNode: return "ArgsNode";
        case LabelNode: return "LabelNode";
        }
        llvm_unreachable("unexpected NodeKind");
    };

    int getOp() { return Op; }

    burm_state *getState() { return State; }

    void setState(burm_state *S) { State = S; }

    // Note: The elements of std::vector are stored contiguously, so elements
    // can be accessed using offsets to regular pointers to elements
    BrgTreeNode **getKids() { return &Kids[0]; }

    std::vector<BrgTreeNode *> getKidsVector() { return Kids; }

    void setKids(const std::vector<BrgTreeNode *> &Nodes) { Kids = Nodes; }

    bool isActionExecuted() { return ActionExecuted; }

    void setActionExecuted() { ActionExecuted = true; }

    static BrgTreeNode *createUndefNode() {
        auto *Ret = new BrgTreeNode(KindTy::UndefNode, /*Undef*/ 0);
        return Ret;
    }

    static BrgTreeNode *createImmNode(int64_t Val) {
        auto *Ret = new BrgTreeNode(KindTy::ImmNode, /*Const*/ 68);
        Ret->AsmOp = remniw::AsmOperand::createImm(Val);
        return Ret;
    }

    static BrgTreeNode *createMemNode(int64_t Offset, std::vector<BrgTreeNode *> Kids) {
        auto *Ret = new BrgTreeNode(KindTy::MemNode, /*Alloca*/ 31, Kids);
        Ret->AsmOp = remniw::AsmOperand::createMem(Offset);
        return Ret;
    }

    static BrgTreeNode *createRegNode(uint32_t Reg) {
        auto *Ret = new BrgTreeNode(KindTy::RegNode, /*Reg*/ 71);
        Ret->AsmOp = remniw::AsmOperand::createReg(Reg);
        return Ret;
    }

    static BrgTreeNode *createInstNode(llvm::Instruction *I,
                                       std::vector<BrgTreeNode *> Kids) {
        auto *Ret = new BrgTreeNode(KindTy::InstNode, I->getOpcode(), Kids);
        Ret->setInstruction(I);
        return Ret;
    }

    static BrgTreeNode *createArgsNode(std::vector<BrgTreeNode *> Kids) {
        auto *Ret = new BrgTreeNode(KindTy::ArgsNode, /*Args*/ 70, Kids);
        return Ret;
    }

    static BrgTreeNode *createLabelNode(remniw::AsmSymbol *Symbol) {
        auto *Ret = new BrgTreeNode(KindTy::LabelNode, /*Label*/ 69);
        Ret->AsmOp = remniw::AsmOperand::createLabel(Symbol);
        return Ret;
    }

    /** ================= ImmNode Functions =================== **/
    remniw::AsmOperand *getAsmOperandImm() {
        assert(Kind == KindTy::ImmNode && "Not a ImmNode");
        return AsmOp;
    }

    /** ================= MemNode Functions =================== **/
    remniw::AsmOperand *getAsmOperandMem() {
        assert(Kind == KindTy::MemNode && "Not a MemNode");
        return AsmOp;
    }

    /** ================= RegNode Functions =================== **/
    remniw::AsmOperand *getAsmOperandReg() {
        assert(Kind == KindTy::RegNode && "Not a RegNode");
        return AsmOp;
    }

    void setAsmOperandReg(remniw::AsmOperand *Op) {
        Kind = KindTy::RegNode;
        AsmOp = Op;
    }

    /** ================= InstNode Functions =================== **/
    llvm::Instruction *getInstruction() { return Inst; }

    void setInstruction(llvm::Instruction *I) { Inst = I; }

    /** ================= LabelNode Functions =================== **/
    remniw::AsmOperand *getAsmOperandLabel() { return AsmOp; }
};

typedef BrgTreeNode *NODEPTR;

#define GET_KIDS(p)     ((p)->getKids())
#define PANIC           printf
#define STATE_LABEL(p)  ((p)->getState())
#define SET_STATE(p, s) ((p)->setState(s))
#define DEFAULT_COST    break
#define OP_LABEL(p)     ((p)->getOp())
#define NO_ACTION(x)

/** ================= Cost =================== **/

struct COST {
    COST(int cost): cost(cost) {}
    int cost;
};

#define COST_LESS(a, b) ((a).cost < (b).cost)
static COST COST_INFINITY = COST(32767);
static COST COST_ZERO = COST(0);

static int shouldTrace = 0;
static int shouldCover = 0;

static void burm_trace(NODEPTR, int, COST);

namespace remniw {

struct BrgFunction {
    BrgFunction(int64_t StackSizeInBytes, llvm::SmallVector<BrgTreeNode *> ExprTrees,
                std::string FuncName):
        FuncName(FuncName),
        StackSizeInBytes(StackSizeInBytes), ExprTrees(ExprTrees) {}

    std::string FuncName;
    int64_t StackSizeInBytes;
    llvm::SmallVector<BrgTreeNode *> ExprTrees;
};

class BrgTreeBuilder: public llvm::InstVisitor<BrgTreeBuilder, BrgTreeNode *> {
private:
    llvm::DenseMap<remniw::AsmSymbol *, llvm::StringRef> ConstantStrings;
    llvm::SmallVector<BrgFunction> Functions;
    llvm::DenseMap<llvm::Instruction *, BrgTreeNode *> InstMap;
    llvm::DenseMap<llvm::Value *, BrgTreeNode *> LabelMap;
    llvm::DenseMap<llvm::Argument *, BrgTreeNode *> ArgMap;
    llvm::SmallVector<BrgTreeNode *> ExprTrees;
    const llvm::DataLayout &DL;
    AsmContext &AsmCtx;
    int64_t Offset;  // clear per function

public:
    BrgTreeBuilder(const llvm::DataLayout &DL, AsmContext &AsmCtx):
        DL(DL), AsmCtx(AsmCtx), Offset(0) {}

    ~BrgTreeBuilder() {}

    llvm::DenseMap<remniw::AsmSymbol *, llvm::StringRef> getConstantStrings() {
        return ConstantStrings;
    }

    llvm::SmallVector<BrgFunction> getFunctions() { return Functions; }

    template<class Iterator>
    void visit(Iterator Start, Iterator End) {
        while (Start != End) {
            visit(*Start++);
        }
    }

    void visit(llvm::Module &M) {
        // Hanlde constant strings
        for (llvm::GlobalVariable &GV : M.globals()) {
            if (llvm::ConstantDataArray *CDA =
                    llvm::dyn_cast<llvm::ConstantDataArray>(GV.getInitializer())) {
                if (CDA->isCString()) {
                    LabelMap[&GV] =
                        BrgTreeNode::createLabelNode(AsmCtx.getOrCreateSymbol(&GV));
                    ConstantStrings[AsmCtx.getOrCreateSymbol(&GV)] = CDA->getAsCString();
                }
            }
        }
        // Handle functions
        visit(M.begin(), M.end());
    }

    void visit(llvm::Function &F) {
        if (F.isDeclaration())
            return;

        Offset = 0;
        ExprTrees.clear();

        for (unsigned i = 0, e = F.arg_size(); i != e; ++i) {
            llvm::Argument *Arg = F.getArg(i);
            BrgTreeNode *ArgNode;
            if (i < 6) {
                ArgNode = BrgTreeNode::createRegNode(ArgRegs[i]);
            } else {
                llvm::Type *Ty = F.getArg(i)->getType();
                uint64_t SizeInBytes =
                    F.getParent()->getDataLayout().getTypeAllocSize(Ty);
                ArgNode = BrgTreeNode::createMemNode(
                    8 * (i - 6 + 2), {BrgTreeNode::createImmNode(SizeInBytes)});
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

        /* align to 16-bytes*/
        int64_t StackSizesInBytes = (-Offset + 16 - 1) / 16 * 16;
        BrgFunction Func(StackSizesInBytes, ExprTrees, F.getName().str());
        Functions.push_back(Func);
    }

    BrgTreeNode *visitOperand(llvm::Value *V) {
        if (auto *CE = llvm::dyn_cast<llvm::ConstantExpr>(V)) {
            // FIXME
            return visitOperand(CE->getOperand(0));
        } else if (auto *GV = llvm::dyn_cast<llvm::GlobalVariable>(V)) {
            auto it = LabelMap.find(GV);
            assert(it != LabelMap.end() && "operands must be previously defined");
            return it->second;
        } else if (auto *CI = llvm::dyn_cast<llvm::ConstantInt>(V)) {
            BrgTreeNode *T = BrgTreeNode::createImmNode(CI->getSExtValue());
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
                LabelMap[V] = BrgTreeNode::createLabelNode(AsmCtx.getOrCreateSymbol(F));
                return LabelMap[V];
            }
            return it->second;
        } else if (auto *BB = llvm::dyn_cast<llvm::BasicBlock>(V)) {
            auto it = LabelMap.find(V);
            if (it == LabelMap.end()) {
                LabelMap[V] = BrgTreeNode::createLabelNode(AsmCtx.getOrCreateSymbol(BB));
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

    BrgTreeNode *visitAllocaInst(llvm::AllocaInst &AI) {
        uint64_t AllocaSizeInBytes = getAllocaSizeInBytes(AI);
        Offset -= AllocaSizeInBytes;
        auto *AllocaNode = BrgTreeNode::createMemNode(
            Offset, {BrgTreeNode::createImmNode(AllocaSizeInBytes)});
        InstMap[&AI] = AllocaNode;
        ExprTrees.push_back(AllocaNode);
        return AllocaNode;
    }

    BrgTreeNode *visitBranchInst(llvm::BranchInst &BI) {
        BrgTreeNode *InstNode;
        if (BI.isUnconditional()) {
            InstNode = BrgTreeNode::createInstNode(&BI, {visitOperand(BI.getSuccessor(0)),
                                                         BrgTreeNode::createUndefNode(),
                                                         BrgTreeNode::createUndefNode()});
        } else {
            if (BI.getCondition() ==
                llvm::ConstantInt::getTrue(llvm::Type::getInt1Ty(BI.getContext()))) {
                InstNode =
                    BrgTreeNode::createInstNode(&BI, {visitOperand(BI.getSuccessor(0)),
                                                      BrgTreeNode::createUndefNode(),
                                                      BrgTreeNode::createUndefNode()});
            } else if (BI.getCondition() == llvm::ConstantInt::getFalse(
                                                llvm::Type::getInt1Ty(BI.getContext()))) {
                InstNode =
                    BrgTreeNode::createInstNode(&BI, {visitOperand(BI.getSuccessor(1)),
                                                      BrgTreeNode::createUndefNode(),
                                                      BrgTreeNode::createUndefNode()});
            } else {
                auto *ICI = llvm::cast<llvm::ICmpInst>(BI.getCondition());
                assert(InstMap.count(ICI) && "BI.getCondition() not in InstMap");
                InstNode = BrgTreeNode::createInstNode(
                    &BI, {InstMap[ICI], visitOperand(BI.getSuccessor(0)),
                          visitOperand(BI.getSuccessor(1))});
            }
        }
        InstMap[&BI] = InstNode;
        ExprTrees.push_back(InstNode);
        return InstNode;
    }

    BrgTreeNode *visitCallInst(llvm::CallInst &CI) {
        std::vector<BrgTreeNode *> Kids;
        BrgTreeNode *Args = BrgTreeNode::createArgsNode(
            {BrgTreeNode::createUndefNode(), BrgTreeNode::createUndefNode()});
        BrgTreeNode *CurrentNode = Args;
        for (unsigned i = 0, e = CI.arg_size(); i != e; ++i) {
            BrgTreeNode *ArgsTmp = BrgTreeNode::createArgsNode(
                {BrgTreeNode::createUndefNode(), BrgTreeNode::createUndefNode()});
            CurrentNode->setKids({visitOperand(CI.getArgOperand(i)), ArgsTmp});
            CurrentNode = ArgsTmp;
            if (i >= 6)  // push arg on stack
            {
                llvm::Type *Ty = CI.getArgOperand(i)->getType();
                uint64_t SizeInBytes =
                    CI.getModule()->getDataLayout().getTypeAllocSize(Ty);
                Offset -= SizeInBytes;
            }
        }
        BrgTreeNode *Ret;
        if (auto *Callee = CI.getCalledFunction()) {
            // direct call
            Ret = BrgTreeNode::createInstNode(&CI, {visitOperand(Callee), Args});
        } else {
            // indirect call
            Ret = BrgTreeNode::createInstNode(
                &CI, {visitOperand(CI.getCalledOperand()), Args});
        }
        InstMap[&CI] = Ret;
        ExprTrees.push_back(Ret);
        return Ret;
    }

    // BrgTreeNode* visitReturnInst(llvm::ReturnInst &I);
    // BrgTreeNode* visitLoadInst(llvm::LoadInst &I);
    // BrgTreeNode* visitStoreInst(llvm::StoreInst &I);
    // BrgTreeNode* visitICmpInst(llvm::ICmpInst &I);
    // BrgTreeNode* visitAdd(llvm::BinaryOperator &I);
    // BrgTreeNode* visitSub(llvm::BinaryOperator &I);
    // BrgTreeNode* visitMul(llvm::BinaryOperator &I);
    // BrgTreeNode* visitSDiv(llvm::BinaryOperator &I);

    /// Specify what to return for unhandled instructions.
    BrgTreeNode *visitInstruction(llvm::Instruction &I) {
        std::vector<BrgTreeNode *> Kids;
        for (unsigned i = 0, e = I.getNumOperands(); i != e; ++i) {
            Kids.push_back(visitOperand(I.getOperand(i)));
        }
        BrgTreeNode *T = BrgTreeNode::createInstNode(&I, Kids);
        InstMap[&I] = T;
        ExprTrees.push_back(T);
        return T;
    }
};

}  // namespace remniw