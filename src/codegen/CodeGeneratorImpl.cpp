#include "AST.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include <cassert>
#include <unordered_map>

using namespace llvm;

namespace remniw
{

static LLVMContext* TheLLVMContext = nullptr;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<IRBuilder<>> IRB;
static std::unordered_map<std::string, Value *> NamedValues;
static std::unordered_map<Value*, Value*> RefExprValues;
static GlobalVariable *InputFmtStr;
static GlobalVariable *OutputFmtStr;

// Convert remniw::Type to corresponding llvm::Type
static llvm::Type *REMNIWTypeToLLVMType(remniw::Type* Ty)
{
    if (llvm::isa<remniw::IntType>(Ty))
    {
        return llvm::Type::getInt64Ty(*TheLLVMContext)/*->getScalarType()*/;
    }
    else if (auto *PointerTy = llvm::dyn_cast<remniw::PointerType>(Ty))
    {
        llvm::Type *PointeeTy = REMNIWTypeToLLVMType(PointerTy->getPointeeType());
        assert(PointeeTy != nullptr && "The pointee type of pointer type is nullptr");
        return PointeeTy->getPointerTo();
    }
    else if (auto* FuncTy = llvm::dyn_cast<remniw::FunctionType>(Ty))
    {
        SmallVector<llvm::Type *, 4> ParamTypes;
        for (auto *ParamType : FuncTy->getParamTypes())
            ParamTypes.push_back(REMNIWTypeToLLVMType(ParamType));
        return llvm::FunctionType::get(
            REMNIWTypeToLLVMType(FuncTy->getReturnType()), ParamTypes, false)->getPointerTo();
    }
    return nullptr;
}

// utility function for emit scanf, printf
static Value *emitLibCall(StringRef LibFuncName, llvm::Type *ReturnType,
                          ArrayRef<llvm::Type *> ParamTypes,
                          ArrayRef<Value *> Operands,
                          bool IsVaArgs = false)
{
    Module *M = IRB->GetInsertBlock()->getModule();
    llvm::FunctionType *FuncType =
        llvm::FunctionType::get(ReturnType, ParamTypes, IsVaArgs);
    FunctionCallee Callee = M->getOrInsertFunction(LibFuncName, FuncType);
    if (LibFuncName.equals("printf"))
    {
        // setRetAndArgsNoUndef(F);
        // setDoesNotThrow(F);
        // setDoesNotCapture(F, 0);
        // setOnlyReadsMemory(F, 0);
    }
    if (LibFuncName.equals("scanf"))
    {
        // setRetAndArgsNoUndef(F);
        // setDoesNotThrow(F);
        // setDoesNotCapture(F, 0);
        // setOnlyReadsMemory(F, 0);
    }
    CallInst *CI = IRB->CreateCall(Callee, Operands, LibFuncName);
    if (const Function *F =
            dyn_cast<Function>(Callee.getCallee()->stripPointerCasts()))
        CI->setCallingConv(F->getCallingConv());
    return CI;
}

static Value *emitPrintf(Value *Fmt, Value *VAList)
{
    unsigned AS = Fmt->getType()->getPointerAddressSpace();
    return emitLibCall("printf", IRB->getInt32Ty(), {IRB->getInt8PtrTy()},
                       {IRB->CreateBitCast(Fmt, IRB->getInt8PtrTy(AS), "cstr"),
                       VAList}, /*IsVaArgs=*/true);
}

static Value *emitScanf(Value *Fmt, Value *VAList)
{
    unsigned AS = Fmt->getType()->getPointerAddressSpace();
    return emitLibCall("scanf", IRB->getInt32Ty(), {IRB->getInt8PtrTy()},
                       {IRB->CreateBitCast(Fmt, IRB->getInt8PtrTy(AS), "cstr"),
                       VAList}, /*IsVaArgs=*/true);
}

/// createEntryBlockAlloca - Create an alloca instruction in the entry block of
/// the function.
static AllocaInst *createEntryBlockAlloca(Function *TheFunction, Twine VarName,
                                          llvm::Type *Ty)
{
    IRBuilder<> Tmp(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return Tmp.CreateAlloca(Ty, nullptr, VarName);
}

Value *NumberExprAST::codegen()
{
    return ConstantInt::get(IRB->getInt64Ty(), Val, /*IsSigned=*/true);
}

Value *VariableExprAST::codegen()
{
    if (NamedValues.count(Name))
    {
        Value *V = NamedValues[Name];
        if (IsLValue())
            return V;
        else
            return IRB->CreateLoad(V->getType()->getPointerElementType(), V, Name);
    }

    if (llvm::Function* F = TheModule->getFunction(Name))
    {
        return F;
    }

    llvm_unreachable("unknown VariableExprAST!");
}

Value *VarDeclNodeAST::codegen()
{
    // We handle VarDeclNode in FunctionAST::codegen()
    return nullptr;
}

Value *FunctionCallExprAST::codegen()
{
    Value* CalledValue = Callee->codegen();
    SmallVector<Value *, 4> CallArgs;
    for (auto &Arg : Args)
    {
        Value *V = Arg->codegen();
        CallArgs.push_back(V);
    }
    if (auto *CalledFunction = llvm::dyn_cast<llvm::Function>(CalledValue))
    {
        assert(CalledFunction->arg_size() == Args.size() && "Incorrect #arguments passed");
        return IRB->CreateCall(CalledFunction, CallArgs, "call");
    }
    else // indirect call
    {
        assert(CalledValue->getType()->isPointerTy() &&
                CalledValue->getType()->getPointerElementType()->isFunctionTy());
        auto *FT = cast<llvm::FunctionType>(CalledValue->getType()->getPointerElementType());
        return IRB->CreateCall(FunctionCallee(FT, CalledValue), CallArgs, "call");
    }
}

// TODO
Value *NullExprAST::codegen()
{
    return nullptr;
}

// TODO
Value *AllocExprAST::codegen()
{
    return nullptr;
}

Value *RefExprAST::codegen()
{
    Value *Ptr = nullptr;
    Value *Val = Var->codegen();
    return Val;
}

Value *DerefExprAST::codegen()
{
    Value *V = Ptr->codegen();
    assert(V && "invalid operand of DerefExpr!");
    return IRB->CreateLoad(V->getType()->getPointerElementType(), V);
}

Value *InputExprAST::codegen()
{
    llvm::Function *F = IRB->GetInsertBlock()->getParent();
    Value* Ptr = createEntryBlockAlloca(F, "input", IRB->getInt64Ty());
    Value* Call = emitScanf(InputFmtStr, Ptr);
    return IRB->CreateLoad(Ptr->getType()->getPointerElementType(), Ptr);
}

Value *BinaryExprAST::codegen()
{
    Value *V1 = LHS->codegen();
    Value *V2 = RHS->codegen();
    Value *V = nullptr;
    assert((V1 && V2) && "invalid operand of BinaryExpr!");
    switch (Op)
    {
        case OpKind::Mul: V = IRB->CreateMul(V1, V2, "mul"); break;
        case OpKind::Div: V = IRB->CreateSDiv(V1, V2, "div"); break;
        case OpKind::Add: V = IRB->CreateAdd(V1, V2, "add"); break;
        case OpKind::Sub: V = IRB->CreateSub(V1, V2, "sub"); break;
        case OpKind::Gt: V = IRB->CreateICmpSGT(V1, V2, "icmp.sgt"); break;
        case OpKind::Eq: V = IRB->CreateICmpEQ(V1, V2, "icmp.eq"); break;
        default: llvm_unreachable("unexpected binary operation!");
    }
    return V;
}

Value *LocalVarDeclStmtAST::codegen()
{
    // We handle LocalVarDeclStmt in FunctionAST::codegen()
    return nullptr;
}

Value *EmptyStmtAST::codegen()
{
    // do nothing
    return nullptr;
}

Value *OutputStmtAST::codegen()
{
    Value* V = Expr->codegen();
    assert(V && "invalid operand of OutputStmt!");
    return emitPrintf(OutputFmtStr, V);
}

Value *BlockStmtAST::codegen()
{
    for (const auto &Stmt : Stmts)
        Stmt->codegen();
    return nullptr;
}

Value *ReturnStmtAST::codegen()
{
    // We handle ReturnStmt in FunctionAST::codegen()
    return nullptr;
}

Value *IfStmtAST::codegen()
{
    Value *CondV = Cond->codegen();
    assert(CondV && "invalid condtion operand of IfStmt!");
    // Convert condition to a bool by comparing non-equal to 0.
    if (!isa<CmpInst>(CondV))
        CondV = IRB->CreateICmpNE(CondV, ConstantInt::get(IRB->getInt64Ty(), 0, /*IsSigned=*/true), "");
    llvm::Function *F = IRB->GetInsertBlock()->getParent();
    // Create blocks for the then and else cases.  Insert the 'then' block at the
    // end of the function.
    BasicBlock *ThenBB = BasicBlock::Create(*TheLLVMContext, "if.then", F);
    BasicBlock *ElseBB = BasicBlock::Create(*TheLLVMContext, "if.else");
    BasicBlock *MergeBB = BasicBlock::Create(*TheLLVMContext, "if.end");
    IRB->CreateCondBr(CondV, ThenBB, ElseBB);

    // Emit then block.
    IRB->SetInsertPoint(ThenBB);
    Then->codegen();
    IRB->CreateBr(MergeBB);
    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
    ThenBB = IRB->GetInsertBlock();
    // Emit else block.
    F->getBasicBlockList().push_back(ElseBB);
    IRB->SetInsertPoint(ElseBB);
    if (Else)
        Else->codegen();
    IRB->CreateBr(MergeBB);
    // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
    ElseBB = IRB->GetInsertBlock();

    // Emit merge block.
    F->getBasicBlockList().push_back(MergeBB);
    IRB->SetInsertPoint(MergeBB);

    return nullptr;
}

Value *WhileStmtAST::codegen()
{
    llvm::Function *F = IRB->GetInsertBlock()->getParent();
    // Make the new basic block for the loop header, inserting after current
    // block.
    BasicBlock *LoopCondBB = BasicBlock::Create(*TheLLVMContext, "while.cond", F);
    // Insert an explicit fall through from the current block to the LoopBB.
    IRB->CreateBr(LoopCondBB);
    // Start insertion in LoopBB.
    IRB->SetInsertPoint(LoopCondBB);

    Value *CondV = Cond->codegen();
    assert(CondV && "invalid condtion operand of WhileStmt!");

    // Convert condition to a bool by comparing non-equal to 0.
    if (!isa<CmpInst>(CondV))
        CondV = IRB->CreateICmpNE(CondV, ConstantInt::get(IRB->getInt64Ty(), 0, /*IsSigned=*/true), "");

    // Create the "loop body" block and the "loop end" block.
    BasicBlock *LoopBodyBB = BasicBlock::Create(*TheLLVMContext, "while.body");
    BasicBlock *LoopEndBB = BasicBlock::Create(*TheLLVMContext, "while.end");
    IRB->CreateCondBr(CondV, LoopBodyBB, LoopEndBB);

    // Emit the "loop body" block
    F->getBasicBlockList().push_back(LoopBodyBB);
    IRB->SetInsertPoint(LoopBodyBB);
    Body->codegen();
    IRB->CreateBr(LoopCondBB);

    // Emit the "loop end" block
    F->getBasicBlockList().push_back(LoopEndBB);
    IRB->SetInsertPoint(LoopEndBB);
    return nullptr;
}

Value *BasicAssignmentStmtAST::codegen()
{
    Value *Ptr = LHS->codegen();
    Value *Val = RHS->codegen();
    assert((Ptr && Val) && "invalid operand of BasicAssignmentStmt");
    return IRB->CreateStore(Val, Ptr);
}

Value *DerefAssignmentStmtAST::codegen()
{
    Value *Ptr = LHS->codegen();
    Value *Val = RHS->codegen();
    assert((Ptr && Val) && "invalid operand of DerefAssignmentStmt");
    Ptr = IRB->CreateLoad(Ptr->getType()->getPointerElementType(), Ptr);
    return IRB->CreateStore(Val, Ptr);
}

Value *FunctionAST::codegen()
{
    // Get the function from the module symbol table.
    llvm::Function *F = TheModule->getFunction(FuncName);
    assert(F && "function is not in the module symbol table");

    // Create a new basic block to start insertion into.
    BasicBlock *BB = BasicBlock::Create(*TheLLVMContext, "entry", F);
    IRB->SetInsertPoint(BB);

    // Record the function arguments in the NamedValues map
    NamedValues.clear();
    unsigned Idx = 0;
    for (auto &Arg : F->args())
    {
        Arg.setName(ParamDecls[Idx++]->getName());
        // Create an alloca for this variable.
        AllocaInst *Alloca =
            createEntryBlockAlloca(F, Arg.getName(), Arg.getType());
        // Store the initial value into the alloca.
        IRB->CreateStore(&Arg, Alloca);
        NamedValues[std::string(Arg.getName())] = Alloca;
    }

    // Create local variables declarations
    for (auto *VarDeclNode : LocalVarDecls->getVars())
    {
        Value *LocalVar = IRB->CreateAlloca(REMNIWTypeToLLVMType(VarDeclNode->getType()), nullptr, VarDeclNode->getName());
        NamedValues[std::string(LocalVar->getName())] = LocalVar;
    }

    // Codegen the function body
    for (const auto &Stmt : Body)
    {
        Stmt->codegen();
    }

    // Finish off the function.
    Value *Ret = ReturnStmt->getExpr()->codegen();
    if (FuncName == "main" && !Ret->getType()->isIntegerTy(64))
        Ret = IRB->CreateIntCast(Ret, IRB->getInt64Ty(), /*isSigned*/true);
    IRB->CreateRet(Ret);

    // Validate the generated code, checking for consistency.
    verifyFunction(*F);
    return F;
}

std::unique_ptr<Module> ProgramAST::codegen(llvm::LLVMContext& Context)
{
    TheLLVMContext = &Context;
    TheModule = std::make_unique<Module>("", *TheLLVMContext);
    InitializeNativeTarget();
    auto TM = std::unique_ptr<TargetMachine>(EngineBuilder().selectTarget());
    assert(TM && "cannot initialize TargetMachine");
    TheModule->setDataLayout(TM->createDataLayout());
    IRB = std::make_unique<IRBuilder<>>(*TheLLVMContext);

    InputFmtStr = IRB->CreateGlobalString("%lli", "fmtstr", 0, TheModule.get());
    OutputFmtStr = IRB->CreateGlobalString("%lli\n", "fmtstr", 0, TheModule.get());

    // Add prototype for each function
    // This make emit FunctionCallExprAST easy
    for(const auto &FuncAST : Functions)
    {
        SmallVector<llvm::Type *, 4> ParamTypes;
        for (auto *ParamType : FuncAST->getParamTypes())
            ParamTypes.push_back(REMNIWTypeToLLVMType(ParamType));
        auto *FT = llvm::FunctionType::get(
            REMNIWTypeToLLVMType(FuncAST->getReturnType()), ParamTypes, false);
        TheModule->getOrInsertFunction(FuncAST->getFuncName(), FT);
        // FIXME: Function::ExternalLinkage ?
        // Function *F =
        //     Function::Create(FT, Function::ExternalLinkage, FuncName, TheModule.get());
    }

    // Emit LLVM IR for all functions
    for (const auto &FuncAST : Functions)
        FuncAST->codegen();

    // Verify the generated code.
    verifyModule(*TheModule);

    return std::move(TheModule);
}

}