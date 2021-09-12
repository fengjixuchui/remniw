#include "AST.h"
#include "RecursiveASTVisitor.h"

namespace remniw
{

void RecursiveASTVisitor::visit(VarDeclNodeAST &VarDeclNode)
{
    if (actBefore(VarDeclNode))
        return;

    actAfter(VarDeclNode);
}

void RecursiveASTVisitor::visit(NumberExprAST &NumberExpr)
{
    if (actBefore(NumberExpr))
        return;

    actAfter(NumberExpr);
}

void RecursiveASTVisitor::visit(VariableExprAST &VariableExpr)
{
    if (actBefore(VariableExpr))
        return;

    actAfter(VariableExpr);
}

void RecursiveASTVisitor::visit(FunctionCallExprAST &FunctionCallExpr)
{
    if (actBefore(FunctionCallExpr))
        return;

    for (auto *Arg : FunctionCallExpr.getArgs())
        Arg->accept(*this);

    actAfter(FunctionCallExpr);
}

void RecursiveASTVisitor::visit(NullExprAST &NullExpr)
{
    if (actBefore(NullExpr))
        return;

    actAfter(NullExpr);
}

void RecursiveASTVisitor::visit(AllocExprAST &AllocExpr)
{
    if (actBefore(AllocExpr))
        return;

    AllocExpr.getInit()->accept(*this);

    actAfter(AllocExpr);
}

void RecursiveASTVisitor::visit(RefExprAST &RefExpr)
{
    if (actBefore(RefExpr))
        return;

    RefExpr.getVar()->accept(*this);

    actAfter(RefExpr);
}

void RecursiveASTVisitor::visit(DerefExprAST &DerefExpr)
{
    if (actBefore(DerefExpr))
        return;

    DerefExpr.getPtr()->accept(*this);

    actAfter(DerefExpr);
}

void RecursiveASTVisitor::visit(InputExprAST &InputExpr)
{
    if (actBefore(InputExpr))
        return;

    actAfter(InputExpr);
}

void RecursiveASTVisitor::visit(BinaryExprAST &BinaryExpr)
{
    if (actBefore(BinaryExpr))
        return;

    BinaryExpr.getLHS()->accept(*this);
    BinaryExpr.getRHS()->accept(*this);

    actAfter(BinaryExpr);
}

void RecursiveASTVisitor::visit(LocalVarDeclStmtAST &LocalVarDeclStmt)
{
    if (actBefore(LocalVarDeclStmt))
        return;

    for (auto *VarDeclNode : LocalVarDeclStmt.getVars())
        VarDeclNode->accept(*this);

    actAfter(LocalVarDeclStmt);
}

void RecursiveASTVisitor::visit(EmptyStmtAST &EmptyStmt)
{
    if (actBefore(EmptyStmt))
        return;

    actAfter(EmptyStmt);
}

void RecursiveASTVisitor::visit(OutputStmtAST &OutputStmt)
{
    if (actBefore(OutputStmt))
        return;

    OutputStmt.getExpr()->accept(*this);

    actAfter(OutputStmt);
}

void RecursiveASTVisitor::visit(BlockStmtAST &BlockStmt)
{
    if (actBefore(BlockStmt))
        return;

    for (auto *Stmt : BlockStmt.getStmts())
        Stmt->accept(*this);

    actAfter(BlockStmt);
}

void RecursiveASTVisitor::visit(ReturnStmtAST &ReturnStmt)
{
    if (actBefore(ReturnStmt))
        return;

    ReturnStmt.getExpr()->accept(*this);

    actAfter(ReturnStmt);
}

void RecursiveASTVisitor::visit(IfStmtAST &IfStmt)
{
    if (actBefore(IfStmt))
        return;

    IfStmt.getCond()->accept(*this);
    IfStmt.getThen()->accept(*this);
    if (IfStmt.getElse())
        IfStmt.getElse()->accept(*this);

    actAfter(IfStmt);
}

void RecursiveASTVisitor::visit(WhileStmtAST &WhileStmt)
{
    if (actBefore(WhileStmt))
        return;

    WhileStmt.getCond()->accept(*this);
    WhileStmt.getBody()->accept(*this);

    actAfter(WhileStmt);
}

void RecursiveASTVisitor::visit(BasicAssignmentStmtAST &BasicAssignmentStmt)
{
    if (actBefore(BasicAssignmentStmt))
        return;

    BasicAssignmentStmt.getLHS()->accept(*this);
    BasicAssignmentStmt.getRHS()->accept(*this);

    actAfter(BasicAssignmentStmt);
}

void RecursiveASTVisitor::visit(DerefAssignmentStmtAST &DerefAssignmentStmt)
{
    if (actBefore(DerefAssignmentStmt))
        return;

    DerefAssignmentStmt.getLHS()->accept(*this);
    DerefAssignmentStmt.getRHS()->accept(*this);

    actAfter(DerefAssignmentStmt);
}

void RecursiveASTVisitor::visit(FunctionAST &Function)
{
    if (actBefore(Function))
        return;

    for (auto *VarDeclNode : Function.getParamDecls())
        VarDeclNode->accept(*this);
    Function.getLocalVarDecls()->accept(*this);
    for (auto *Stmt : Function.getBody())
        Stmt->accept(*this);
    Function.getReturn()->accept(*this);

    actAfter(Function);
}

void RecursiveASTVisitor::visit(ProgramAST &Program)
{
    if (actBefore(Program))
        return;

    for (auto *Function : Program.getFunctions())
        Function->accept(*this);

    actAfter(Program);
}

}