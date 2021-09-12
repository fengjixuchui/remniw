#pragma once

#include "ASTVisitor.h"
#include "Type.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

namespace remniw
{

class ASTVisitor;

template <typename T>
std::vector<T *> rawPtrs(const std::vector<std::unique_ptr<T>> &v)
{
    std::vector<T *> r;
    std::transform(v.begin(), v.end(), std::back_inserter(r),
                   [](auto &up)
                   { return up.get(); });
    return r;
}

struct SourceLocation
{
    size_t Line;
    size_t Col;
};

class ASTNode
{
public:
    ASTNode(SourceLocation Loc) : Loc(Loc) {}
    virtual ~ASTNode() {}

    virtual void accept(ASTVisitor &visitor) = 0;

    virtual llvm::Value *codegen() { return nullptr; }

    int getLine() const { return Loc.Line; }
    int getCol() const { return Loc.Col; }

private:
    SourceLocation Loc;
};

class ExprAST : public ASTNode
{
public:
    ExprAST(SourceLocation Loc) : ASTNode(Loc), LValue(false) {}
    ExprAST(SourceLocation Loc, bool LValue) : ASTNode(Loc), LValue(LValue) {}
    bool IsLValue() const { return LValue; }

private:
    bool LValue;
};

class StmtAST : public ASTNode
{
public:
    StmtAST(SourceLocation Loc) : ASTNode(Loc) {}
};

class VarDeclNodeAST : public ASTNode
{
public:
    VarDeclNodeAST(SourceLocation Loc, std::string Name, remniw::Type* Ty)
        : ASTNode(Loc), Name(Name), Ty(Ty) {}

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    llvm::StringRef getName() const { return Name; }

    remniw::Type* getType() const { return Ty; }

    llvm::Value *codegen() override;

private:
    std::string Name;
    remniw::Type* Ty;
};

class NumberExprAST : public ExprAST
{
public:
    NumberExprAST(SourceLocation Loc, int64_t Val) :
        ExprAST(Loc, /*LValue*/false), Val(Val) {}

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    int64_t getValue() const { return Val; }

    llvm::Value *codegen() override;

private:
    int64_t Val;
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST
{
public:
    // VariableExprAST(SourceLocation Loc, const std::string &Name)
    //     : ExprAST(Loc), Name(Name) { }
    VariableExprAST(SourceLocation Loc, std::string Name, bool LValue)
        : ExprAST(Loc, LValue), Name(Name) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    llvm::StringRef getName() const { return Name; }

    llvm::Value *codegen() override;

private:
    std::string Name;
};

class FunctionCallExprAST : public ExprAST
{
public:
    FunctionCallExprAST(SourceLocation Loc, std::unique_ptr<ExprAST> Callee,
                        std::vector<std::unique_ptr<ExprAST>> Args)
        : ExprAST(Loc), Callee(std::move(Callee)), Args(std::move(Args)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    ExprAST *getCallee() const { return Callee.get(); }

    std::vector<ExprAST *> getArgs() const { return rawPtrs(Args); }

    llvm::Value *codegen() override;

private:
    std::unique_ptr<ExprAST> Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;
};

class NullExprAST : public ExprAST
{
public:
    NullExprAST(SourceLocation Loc) : ExprAST(Loc, /*LValue*/false) {}

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    llvm::Value *codegen() override;
};

class AllocExprAST : public ExprAST
{
private:
    std::unique_ptr<ExprAST> Init;

public:
    AllocExprAST(SourceLocation Loc, std::unique_ptr<ExprAST> Init)
        : ExprAST(Loc, /*LValue*/true), Init(std::move(Init)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    ExprAST *getInit() const { return Init.get(); }

    llvm::Value *codegen() override;
};

class RefExprAST : public ExprAST
{
public:
    RefExprAST(SourceLocation Loc, std::unique_ptr<VariableExprAST> Var)
        : ExprAST(Loc, /*LValue*/false), Var(std::move(Var)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    VariableExprAST *getVar() const { return Var.get(); }

    llvm::Value *codegen() override;

private:
    std::unique_ptr<VariableExprAST> Var;
};

class DerefExprAST : public ExprAST
{
public:
    DerefExprAST(SourceLocation Loc, std::unique_ptr<ExprAST> Ptr, bool LValue)
        : ExprAST(Loc, LValue), Ptr(std::move(Ptr)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    ExprAST *getPtr() const { return Ptr.get(); }

    llvm::Value *codegen() override;

private:
    std::unique_ptr<ExprAST> Ptr;

};

class InputExprAST : public ExprAST
{
public:
    InputExprAST(SourceLocation Loc) : ExprAST(Loc, /*LValue*/false) {}

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    llvm::Value *codegen() override;
};

// class RecordCreateExprAST : public ExprAST
// {

// public:
//     RecordCreateExprAST(SourceLocation Loc)
//         : ExprAST(Loc)
//     {
//     }
//     llvm::Value *codegen() override;
//     void accept(ASTVisitor &visitor) override
//     {
//         visitor.visit(*this);
//     }
// };

// class RecordAccessExprAST : public ExprAST
// {

// public:
//     RecordAccessExprAST(SourceLocation Loc)
//         : ExprAST(Loc)
//     {
//     }
//    llvm::Value *codegen() override;
//     void accept(ASTVisitor &visitor) override
//     {
//         visitor.visit(*this);
//     }
// };

class BinaryExprAST : public ExprAST
{
public:
    enum OpKind
    {
        Mul,
        Div,
        Add,
        Sub,
        Gt,
        Eq,
    };

    BinaryExprAST(SourceLocation Loc, OpKind Op,
                  std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
        : ExprAST(Loc, /*LValue*/false), Op(Op),
          LHS(std::move(LHS)), RHS(std::move(RHS)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    OpKind getOp() const { return Op; }

    std::string getOpString() const
    {
        std::string OpStr;
        switch (Op)
        {
            case OpKind::Mul: OpStr = "*"; break;
            case OpKind::Div: OpStr = "/"; break;
            case OpKind::Add: OpStr = "+"; break;
            case OpKind::Sub: OpStr = "-"; break;
            case OpKind::Gt: OpStr = ">"; break;
            case OpKind::Eq: OpStr = "=="; break;
            default: break;
        }
        return OpStr;
    }

    ExprAST *getLHS() const { return LHS.get(); }

    ExprAST *getRHS() const { return RHS.get(); }

    llvm::Value *codegen() override;

private:
    OpKind Op;
    std::unique_ptr<ExprAST> LHS, RHS;

};

class LocalVarDeclStmtAST : public StmtAST
{
public:
    LocalVarDeclStmtAST(SourceLocation Loc,
                        std::vector<std::unique_ptr<VarDeclNodeAST>> Vars)
        : StmtAST(Loc), Vars(std::move(Vars)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    std::vector<VarDeclNodeAST *> getVars() const { return rawPtrs(Vars); }

    llvm::Value *codegen() override;

private:
    std::vector<std::unique_ptr<VarDeclNodeAST>> Vars;
};

class EmptyStmtAST : public StmtAST
{
public:
    EmptyStmtAST(SourceLocation Loc) : StmtAST(Loc) {}

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    llvm::Value *codegen() override;
};

class OutputStmtAST : public StmtAST
{
public:
    OutputStmtAST(SourceLocation Loc, std::unique_ptr<ExprAST> Expr)
        : StmtAST(Loc), Expr(std::move(Expr)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    ExprAST *getExpr() const { return Expr.get(); }

    llvm::Value *codegen() override;

private:
    std::unique_ptr<ExprAST> Expr;
};

class BlockStmtAST : public StmtAST
{
public:
    BlockStmtAST(SourceLocation Loc, std::vector<std::unique_ptr<StmtAST>> Stmts)
        : StmtAST(Loc), Stmts(std::move(Stmts)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    std::vector<StmtAST *> getStmts() const { return rawPtrs(Stmts); }

    llvm::Value *codegen() override;

private:
    std::vector<std::unique_ptr<StmtAST>> Stmts;

};

class ReturnStmtAST : public StmtAST
{
public:
    ReturnStmtAST(SourceLocation Loc, std::unique_ptr<ExprAST> Expr)
        : StmtAST(Loc), Expr(std::move(Expr)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    ExprAST *getExpr() const { return Expr.get(); }

    llvm::Value *codegen() override;

private:
    std::unique_ptr<ExprAST> Expr;
};

class IfStmtAST : public StmtAST
{
public:
    IfStmtAST(SourceLocation Loc, std::unique_ptr<ExprAST> Cond,
              std::unique_ptr<StmtAST> Then, std::unique_ptr<StmtAST> Else)
        : StmtAST(Loc), Cond(std::move(Cond)), Then(std::move(Then)),
          Else(std::move(Else)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    ExprAST *getCond() const { return Cond.get(); }

    StmtAST *getThen() const { return Then.get(); }

    StmtAST *getElse() const { return Else.get(); }

    llvm::Value *codegen() override;

private:
    std::unique_ptr<ExprAST> Cond;
    std::unique_ptr<StmtAST> Then, Else;

};

class WhileStmtAST : public StmtAST
{
public:
    WhileStmtAST(SourceLocation Loc, std::unique_ptr<ExprAST> Cond,
                 std::unique_ptr<StmtAST> Body)
        : StmtAST(Loc), Cond(std::move(Cond)), Body(std::move(Body)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    ExprAST *getCond() const { return Cond.get(); }

    StmtAST *getBody() const { return Body.get(); }

    llvm::Value *codegen() override;

private:
    std::unique_ptr<ExprAST> Cond;
    std::unique_ptr<StmtAST> Body;
};

class BasicAssignmentStmtAST : public StmtAST
{
public:
    BasicAssignmentStmtAST(SourceLocation Loc, std::unique_ptr<ExprAST> LHS,
                           std::unique_ptr<ExprAST> RHS)
        : StmtAST(Loc), LHS(std::move(LHS)), RHS(std::move(RHS)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    ExprAST *getLHS() const { return LHS.get(); }

    ExprAST *getRHS() const { return RHS.get(); }

    llvm::Value *codegen() override;

private:
    std::unique_ptr<ExprAST> LHS;
    std::unique_ptr<ExprAST> RHS;
};

class DerefAssignmentStmtAST : public StmtAST
{
public:
    DerefAssignmentStmtAST(SourceLocation Loc, std::unique_ptr<ExprAST> LHS,
                           std::unique_ptr<ExprAST> RHS)
        : StmtAST(Loc), LHS(std::move(LHS)), RHS(std::move(RHS)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    ExprAST *getLHS() const { return LHS.get(); }

    ExprAST *getRHS() const { return RHS.get(); }

    llvm::Value *codegen() override;

private:
    std::unique_ptr<ExprAST> LHS, RHS;
};

// class RecordFieldBasicAssignmentStmtAST : public StmtAST
// {
// public:
//     RecordFieldBasicAssignmentStmtAST(SourceLocation Loc)
//         : StmtAST(Loc)
//     {
//     }
//     llvm::Value *codegen() override;
//     void accept(ASTVisitor &visitor) override
//     {
//         visitor.visit(*this);
//     }
// };

// class RecordFieldDerefAssignmentStmtAST : public StmtAST
// {
// public:
//     RecordFieldDerefAssignmentStmtAST(SourceLocation Loc)
//         : StmtAST(Loc)
//     {
//     }
//     llvm::Value *codegen() override;
//     void accept(ASTVisitor &visitor) override
//     {
//         visitor.visit(*this);
//     }
// };

/// FunctionAST - This class represents a function definition itself.
class FunctionAST : public ASTNode
{
public:
    FunctionAST(std::string FuncName,
                remniw::FunctionType* FuncTy,
                std::vector<std::unique_ptr<VarDeclNodeAST>> ParamDecls,
                std::unique_ptr<LocalVarDeclStmtAST> LocalVarDecls,
                std::vector<std::unique_ptr<StmtAST>> Body,
                std::unique_ptr<ReturnStmtAST> ReturnStmt)
        : ASTNode(SourceLocation{0, 0}),
          FuncName(FuncName),
          FuncTy(FuncTy),
          ParamDecls(std::move(ParamDecls)),
          LocalVarDecls(std::move(LocalVarDecls)),
          Body(std::move(Body)),
          ReturnStmt(std::move(ReturnStmt)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    llvm::StringRef getFuncName() const { return FuncName; }

    std::vector<VarDeclNodeAST *> getParamDecls() const
    {
        return rawPtrs(ParamDecls);
    }

    std::size_t getParamSize() const { return ParamDecls.size(); }

    LocalVarDeclStmtAST *getLocalVarDecls() const { return LocalVarDecls.get(); }

    std::vector<StmtAST *> getBody() const  { return rawPtrs(Body); }

    ReturnStmtAST *getReturn() const { return ReturnStmt.get(); }

    remniw::FunctionType* getType() const { return FuncTy; }

    llvm::ArrayRef<remniw::Type*> getParamTypes() const { return FuncTy->getParamTypes(); }

    remniw::Type* getReturnType() const { return FuncTy->getReturnType(); }

    llvm::Value *codegen() override;

private:
    std::string FuncName;
    remniw::FunctionType* FuncTy;
    std::vector<std::unique_ptr<VarDeclNodeAST>> ParamDecls;
    std::unique_ptr<LocalVarDeclStmtAST> LocalVarDecls;
    std::vector<std::unique_ptr<StmtAST>> Body;
    std::unique_ptr<ReturnStmtAST> ReturnStmt;
};

class ProgramAST : public ASTNode
{
public:
    ProgramAST(std::vector<std::unique_ptr<FunctionAST>> Functions)
        : ASTNode(SourceLocation{0, 0}), Functions(std::move(Functions)) { }

    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }

    std::vector<FunctionAST *> getFunctions() const { return rawPtrs(Functions); }

    std::unique_ptr<llvm::Module> codegen(llvm::LLVMContext&);

private:
    std::vector<std::unique_ptr<FunctionAST>> Functions;
};

}