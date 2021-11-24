#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AsmInstruction.h"
#include "AsmOperand.h"
#include "LiveInterval.h"
#include "Register.h"
// #include "RegisterAllocator.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Instructions.h"

/** ================= Node =================== **/

struct burm_state;

class Node {
public:
    enum KindTy
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

private:
    burm_state *State;
    KindTy Kind;
    int Op;
    std::vector<Node *> Kids;
    bool ActionExecuted;
    union {
        // ImmNode, MemNode, RegNode, LabelNode
        remniw::AsmOperand *AsmOp;
        // InstNode members
        llvm::Instruction *Inst;
    };

public:
    /** ================= Common Functions =================== **/

    Node(KindTy Kind, int Op, std::vector<Node *> Kids):
        Kind(Kind), Op(Op), Kids(Kids), ActionExecuted(false) {}

    const char *getNodeKind() {
        switch (Kind) {
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

    std::vector<Node *> getKidsVector() { return Kids; }

    void setKids(const std::vector<Node *> &Ks) { Kids = Ks; }

    bool isActionExecuted() { return ActionExecuted; }

    void setActionExecuted() { ActionExecuted = true; }

    static Node *createUndefNode() {
        Node *Ret = new Node(KindTy::UndefNode, /*Undef*/ 0, {});
        return Ret;
    }

    static Node *createImmNode(int64_t Val, std::vector<Node *> Kids) {
        Node *Ret = new Node(KindTy::ImmNode, /*Const*/ 68, Kids);
        Ret->AsmOp = remniw::AsmOperand::createImm(Val);
        return Ret;
    }

    static Node *createMemNode(int64_t Offset, std::vector<Node *> Kids) {
        Node *Ret = new Node(KindTy::MemNode, /*Alloca*/ 31, Kids);
        Ret->AsmOp = remniw::AsmOperand::createMem(Offset);
        return Ret;
    }

    static Node *createRegNode(remniw::Register Reg) {
        Node *Ret = new Node(KindTy::RegNode, /*Reg*/ 71, {});
        Ret->AsmOp = remniw::AsmOperand::createReg(Reg);
        return Ret;
    }

    static Node *createInstNode(llvm::Instruction *I, std::vector<Node *> Kids) {
        Node *Ret = new Node(KindTy::InstNode, I->getOpcode(), Kids);
        Ret->setInstruction(I);
        return Ret;
    }

    static Node *createArgsNode(std::vector<Node *> Kids) {
        Node *Ret = new Node(KindTy::ArgsNode, /*Args*/ 70, Kids);
        return Ret;
    }

    static Node *createFunctionLabelNode(llvm::StringRef StrRef,
                                         std::vector<Node *> Kids) {
        Node *Ret = new Node(KindTy::FunctionLabelNode, /*Label*/ 69, Kids);
        Ret->AsmOp = remniw::AsmOperand::createLabel(StrRef.data(), StrRef.size());
        return Ret;
    }

    static Node *createBasicBlockLabelNode(llvm::StringRef StrRef,
                                           std::vector<Node *> Kids) {
        static uint32_t LastUnique = 0;
        LastUnique++;
        Node *Ret = new Node(KindTy::BasicBlockLabelNode, /*Label*/ 69, Kids);
        Ret->AsmOp =
            remniw::AsmOperand::createLabel(StrRef.data(), StrRef.size(), LastUnique);
        return Ret;
    }

    static Node *createConstantStringLabelNode(llvm::StringRef StrRef,
                                               std::vector<Node *> Kids) {
        Node *Ret = new Node(KindTy::ConstantStringLabelNode, /*Label*/ 69, Kids);
        Ret->AsmOp = remniw::AsmOperand::createLabel(StrRef.data(), StrRef.size());
        return Ret;
    }

    /** ================= ImmNode Functions =================== **/
    remniw::AsmOperand *getAsmOperandImm() {
        assert(Kind == KindTy::ImmNode && "Not a ImmNode");
        return AsmOp;
    }
    // std::string getImmVal() { return std::string("$") + std::to_string(ImmVal); }
    // void setImmVal(int64_t Val) { ImmVal = Val; }

    /** ================= MemNode Functions =================== **/
    remniw::AsmOperand *getAsmOperandMem() {
        assert(Kind == KindTy::MemNode && "Not a MemNode");
        return AsmOp;
    }
    // std::string getMemLoc() { return std::to_string(Offset) + std::string("(%rbp)"); }
    // int64_t getMemOffset() { return Offset; }
    // void setMemOffset(int64_t O) { Offset = O; }

    /** ================= RegNode Functions =================== **/
    remniw::AsmOperand *getAsmOperandReg() {
        assert(Kind == KindTy::RegNode && "Not a RegNode");
        return AsmOp;
    }

    void setAsmOperandReg(remniw::AsmOperand *Op) {
        Kind = KindTy::RegNode;
        AsmOp = Op;
    }

    // void setReg(remniw::Register R) { Reg = R; }

    /** ================= InstNode Functions =================== **/
    llvm::Instruction *getInstruction() { return Inst; }

    void setInstruction(llvm::Instruction *I) { Inst = I; }

    /** ================= LabelNode Functions =================== **/
    remniw::AsmOperand *getAsmOperandLabel() {
        assert((Kind == KindTy::FunctionLabelNode ||
                Kind == KindTy::BasicBlockLabelNode ||
                Kind == KindTy::ConstantStringLabelNode) &&
               "Not a LabelNode");
        return AsmOp;
    }

    std::string getLabelStringAsLabel() {
        assert(
            (Kind == KindTy::BasicBlockLabelNode || Kind == KindTy::FunctionLabelNode) &&
            "Kind must be BasicBlockLabelNode or FunctionLabelNode");
        if (Kind == KindTy::BasicBlockLabelNode) {
            return ".BB." + std::string(AsmOp->Label.StringPtr, AsmOp->Label.StringSize) +
                   '.' + std::to_string(AsmOp->Label.UniqueCounter);
        } else {
            return std::string(AsmOp->Label.StringPtr, AsmOp->Label.StringSize);
        }
    }

    std::string getLabelStringAsConstant() {
        assert((Kind == KindTy::ConstantStringLabelNode ||
                Kind == KindTy::FunctionLabelNode) &&
               "Kind must be ConstantStringLabelNode or FunctionLabelNode");
        return "$" + std::string(AsmOp->Label.StringPtr, AsmOp->Label.StringSize);
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
    // RegisterAllocator *RA;

public:
    AsmCodeGenerator(
        llvm::raw_ostream &Out, llvm::SmallVector<AsmFunction> Functions,
        llvm::DenseMap<llvm::GlobalVariable *, llvm::StringRef> GlobalVariables):
        Out(Out),
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

public:
    std::vector<AsmInstruction *> AsmInstructions;
    std::unordered_map<uint32_t, remniw::LiveIntervalTy> RegLiveIntervalMap;

public:
    void updateRegLiveInterval(uint32_t Reg) {
        uint32_t StartPoint = static_cast<uint32_t>(AsmInstructions.size());
        uint32_t EndPoint = StartPoint + 1;
        if (Register::isVirtualRegister(Reg)) {
            if (RegLiveIntervalMap.count(Reg)) {
                RegLiveIntervalMap[Reg].Ranges[0].EndPoint = EndPoint;
            } else {
                RegLiveIntervalMap[Reg].Ranges.push_back({StartPoint, EndPoint});
            }

            for (const auto &Range : RegLiveIntervalMap[Reg].Ranges) {
                llvm::outs() << "VirtualRegister " << Reg << " LiveInternal: ";
                Range.print(llvm::outs());
                llvm::outs() << "\n";
            }
        } else if (Register::isPhysicalRegister(Reg)) {
            if (!RegLiveIntervalMap[Reg].Ranges.empty()) {
                auto &LastActiveRange = RegLiveIntervalMap[Reg].Ranges.back();
                if (LastActiveRange.StartPoint == StartPoint &&
                    LastActiveRange.EndPoint == EndPoint) {
                    // Do nothing
                } else if (LastActiveRange.EndPoint == StartPoint) {
                    LastActiveRange.EndPoint = EndPoint;
                } else {
                    RegLiveIntervalMap[Reg].Ranges.push_back({StartPoint, EndPoint});
                }
            } else {
                RegLiveIntervalMap[Reg].Ranges.push_back({StartPoint, EndPoint});
            }

            for (const auto &Range : RegLiveIntervalMap[Reg].Ranges) {
                llvm::outs() << "PhysicalRegiste " << Reg << " LiveInternal: ";
                Range.print(llvm::outs());
                llvm::outs() << "\n";
            }
        }
    }

    void updateAsmOperandLiveInterval(AsmOperand *Op) {
        llvm::outs() << "updateAsmOperandLiveInterval " << Op << "\n";
        uint32_t Reg;
        if (Op->isReg()) {
            updateRegLiveInterval(Op->getReg());
        }
        if (Op->isMem()) {
            uint32_t MemBaseReg = Op->getMemBaseReg();
            if (MemBaseReg != Register::RBP) {
                updateRegLiveInterval(MemBaseReg);
            }
            uint32_t MemIndexReg = Op->getMemIndexReg();
            if (MemIndexReg != Register::NoRegister) {
                updateRegLiveInterval(MemIndexReg);
            }
        }
        llvm::outs() << "\n";
    }

    void createMov(AsmOperand *Src, AsmOperand *Dst) {
        AsmInstructions.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmMovInst(Src, Dst)));
        llvm::outs() << AsmInstructions.size();
        AsmInstructions.back()->print(llvm::outs());
        updateAsmOperandLiveInterval(Src);
        updateAsmOperandLiveInterval(Dst);
    }

    void createLea(AsmOperand *Src, AsmOperand *Dst) {
        AsmInstructions.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmLeaInst(Src, Dst)));
        llvm::outs() << AsmInstructions.size();
        AsmInstructions.back()->print(llvm::outs());
        updateAsmOperandLiveInterval(Src);
        updateAsmOperandLiveInterval(Dst);
    }

    void createCmp(AsmOperand *Src, AsmOperand *Dst) {
        AsmInstructions.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmCmpInst(Src, Dst)));
        llvm::outs() << AsmInstructions.size();
        AsmInstructions.back()->print(llvm::outs());
        updateAsmOperandLiveInterval(Src);
        updateAsmOperandLiveInterval(Dst);
    }

    void createJmp(AsmJmpInst::JmpKindTy JmpKind, AsmOperand *Op) {
        AsmInstructions.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmJmpInst(JmpKind, Op)));
        llvm::outs() << AsmInstructions.size();
        AsmInstructions.back()->print(llvm::outs());
        updateAsmOperandLiveInterval(Op);
    }

    void createAdd(AsmOperand *Src, AsmOperand *Dst) {
        AsmInstructions.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmAddInst(Src, Dst)));
        llvm::outs() << AsmInstructions.size();
        AsmInstructions.back()->print(llvm::outs());
        updateAsmOperandLiveInterval(Src);
        updateAsmOperandLiveInterval(Dst);
    }

    void createSub(AsmOperand *Src, AsmOperand *Dst) {
        AsmInstructions.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmSubInst(Src, Dst)));
        llvm::outs() << AsmInstructions.size();
        AsmInstructions.back()->print(llvm::outs());
        updateAsmOperandLiveInterval(Src);
        updateAsmOperandLiveInterval(Dst);
    }

    void createImul(AsmOperand *Src, AsmOperand *Dst) {
        AsmInstructions.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmImulInst(Src, Dst)));
        llvm::outs() << AsmInstructions.size();
        AsmInstructions.back()->print(llvm::outs());
        updateAsmOperandLiveInterval(Src);
        updateAsmOperandLiveInterval(Dst);
    }

    void createIdiv(AsmOperand *Op) {
        AsmInstructions.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmIdivInst(Op)));
        llvm::outs() << AsmInstructions.size();
        AsmInstructions.back()->print(llvm::outs());
        updateAsmOperandLiveInterval(Op);
    }

    void createCqto() {
        AsmInstructions.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmCqtoInst()));
        llvm::outs() << AsmInstructions.size();
        AsmInstructions.back()->print(llvm::outs());
    }

    void createCall(AsmOperand *Callee, bool DirectCall) {
        AsmInstructions.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmCallInst(Callee, DirectCall)));
        llvm::outs() << AsmInstructions.size();
        AsmInstructions.back()->print(llvm::outs());
        updateAsmOperandLiveInterval(Callee);
    }

    void createXor(AsmOperand *Src, AsmOperand *Dst) {
        AsmInstructions.push_back(
            /*std::make_unique<AsmInstruction>*/ (new AsmXorInst(Src, Dst)));
        llvm::outs() << AsmInstructions.size();
        AsmInstructions.back()->print(llvm::outs());
        updateAsmOperandLiveInterval(Src);
        updateAsmOperandLiveInterval(Dst);
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

public:
    ExprTreeBuilder(const llvm::DataLayout &DL): DL(DL), offset(0) {}

    ~ExprTreeBuilder() {}

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
                    LabelMap[&GV] = Node::createConstantStringLabelNode(GV.getName(), {});
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
                ArgNode = Node::createRegNode(ArgRegs[i]);
            } else {
                llvm::Type *Ty = F.getArg(i)->getType();
                uint64_t SizeInBytes =
                    F.getParent()->getDataLayout().getTypeAllocSize(Ty);
                ArgNode = Node::createMemNode(8 * (i - 6 + 2),
                                              {Node::createImmNode(SizeInBytes, {})});
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
            Node *T = Node::createImmNode(CI->getSExtValue(), {});
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
                LabelMap[V] = Node::createFunctionLabelNode(F->getName(), {});
                return LabelMap[V];
            }
            return it->second;
        } else if (auto *BB = llvm::dyn_cast<llvm::BasicBlock>(V)) {
            auto it = LabelMap.find(V);
            if (it == LabelMap.end()) {
                LabelMap[V] = Node::createBasicBlockLabelNode(BB->getName(), {});
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
            Node::createMemNode(offset, {Node::createImmNode(AllocaSizeInBytes, {})});
        InstMap[&AI] = AllocaNode;
        ExprTrees.push_back(AllocaNode);
        return AllocaNode;
    }

    Node *visitBranchInst(llvm::BranchInst &BI) {
        Node *InstNode;
        if (BI.isUnconditional()) {
            InstNode = Node::createInstNode(&BI, {visitOperand(BI.getSuccessor(0)),
                                                  Node::createUndefNode(),
                                                  Node::createUndefNode()});
        } else {
            if (BI.getCondition() ==
                llvm::ConstantInt::getTrue(llvm::Type::getInt1Ty(BI.getContext()))) {
                InstNode = Node::createInstNode(&BI, {visitOperand(BI.getSuccessor(0)),
                                                      Node::createUndefNode(),
                                                      Node::createUndefNode()});
            } else if (BI.getCondition() == llvm::ConstantInt::getFalse(
                                                llvm::Type::getInt1Ty(BI.getContext()))) {
                InstNode = Node::createInstNode(&BI, {visitOperand(BI.getSuccessor(1)),
                                                      Node::createUndefNode(),
                                                      Node::createUndefNode()});
            } else {
                auto *ICI = llvm::cast<llvm::ICmpInst>(BI.getCondition());
                assert(InstMap.count(ICI) && "BI.getCondition() not in InstMap");
                InstNode = Node::createInstNode(&BI, {InstMap[ICI],
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
        Node *Args =
            Node::createArgsNode({Node::createUndefNode(), Node::createUndefNode()});
        Node *CurrentNode = Args;
        for (unsigned i = 0, e = CI.arg_size(); i != e; ++i) {
            Node *ArgsTmp =
                Node::createArgsNode({Node::createUndefNode(), Node::createUndefNode()});
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
            Ret = Node::createInstNode(&CI, {visitOperand(Callee), Args});
        } else  // indirect call
        {
            Ret = Node::createInstNode(&CI, {visitOperand(CI.getCalledOperand()), Args});
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
        Node *T = Node::createInstNode(&I, Kids);
        InstMap[&I] = T;
        ExprTrees.push_back(T);
        return T;
    }
};

}  // namespace remniw