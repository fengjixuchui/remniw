#pragma once

#include "ASTVisitor.h"

namespace remniw
{

class RecursiveASTVisitor : public ASTVisitor
{
public:
    virtual bool actBefore(VarDeclNodeAST &) { return false; }
    virtual void actAfter(VarDeclNodeAST &) {}
    virtual void visit(VarDeclNodeAST &) override;

    virtual bool actBefore(NumberExprAST &) { return false; }
    virtual void actAfter(NumberExprAST &) {}
    virtual void visit(NumberExprAST &) override;

    virtual bool actBefore(VariableExprAST &) { return false; }
    virtual void actAfter(VariableExprAST &) {}
    virtual void visit(VariableExprAST &) override;

    virtual bool actBefore(FunctionCallExprAST &) { return false; }
    virtual void actAfter(FunctionCallExprAST &) {}
    virtual void visit(FunctionCallExprAST &) override;

    virtual bool actBefore(NullExprAST &) { return false; }
    virtual void actAfter(NullExprAST &) {}
    virtual void visit(NullExprAST &) override;

    virtual bool actBefore(AllocExprAST &) { return false; }
    virtual void actAfter(AllocExprAST &) {}
    virtual void visit(AllocExprAST &) override;

    virtual bool actBefore(RefExprAST &) { return false; }
    virtual void actAfter(RefExprAST &) {}
    virtual void visit(RefExprAST &) override;

    virtual bool actBefore(DerefExprAST &) { return false; }
    virtual void actAfter(DerefExprAST &) {}
    virtual void visit(DerefExprAST &) override;

    virtual bool actBefore(InputExprAST &) { return false; }
    virtual void actAfter(InputExprAST &) {}
    virtual void visit(InputExprAST &) override;

    virtual bool actBefore(BinaryExprAST &) { return false; }
    virtual void actAfter(BinaryExprAST &) {}
    virtual void visit(BinaryExprAST &) override;

    virtual bool actBefore(LocalVarDeclStmtAST &) { return false; }
    virtual void actAfter(LocalVarDeclStmtAST &) {}
    virtual void visit(LocalVarDeclStmtAST &) override;

    virtual bool actBefore(EmptyStmtAST &) { return false; }
    virtual void actAfter(EmptyStmtAST &) {}
    virtual void visit(EmptyStmtAST &) override;

    virtual bool actBefore(OutputStmtAST &) { return false; }
    virtual void actAfter(OutputStmtAST &) {}
    virtual void visit(OutputStmtAST &) override;

    virtual bool actBefore(BlockStmtAST &) { return false; }
    virtual void actAfter(BlockStmtAST &) {}
    virtual void visit(BlockStmtAST &) override;

    virtual bool actBefore(ReturnStmtAST &) { return false; }
    virtual void actAfter(ReturnStmtAST &) {}
    virtual void visit(ReturnStmtAST &) override;

    virtual bool actBefore(IfStmtAST &) { return false; }
    virtual void actAfter(IfStmtAST &) {}
    virtual void visit(IfStmtAST &) override;

    virtual bool actBefore(WhileStmtAST &) { return false; }
    virtual void actAfter(WhileStmtAST &) {}
    virtual void visit(WhileStmtAST &) override;

    virtual bool actBefore(BasicAssignmentStmtAST &) { return false; }
    virtual void actAfter(BasicAssignmentStmtAST &) {}
    virtual void visit(BasicAssignmentStmtAST &) override;

    virtual bool actBefore(DerefAssignmentStmtAST &) { return false; }
    virtual void actAfter(DerefAssignmentStmtAST &) {}
    virtual void visit(DerefAssignmentStmtAST &) override;

    virtual bool actBefore(FunctionAST &) { return false; }
    virtual void actAfter(FunctionAST &) {}
    virtual void visit(FunctionAST &) override;

    virtual bool actBefore(ProgramAST &) { return false; }
    virtual void actAfter(ProgramAST &) {}
    virtual void visit(ProgramAST &) override;
};

}