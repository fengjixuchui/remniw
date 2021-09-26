#pragma once

namespace remniw
{

class VarDeclNodeAST;
class NumberExprAST;
class VariableExprAST;
class FunctionCallExprAST;
class NullExprAST;
class AllocExprAST;
class RefExprAST;
class DerefExprAST;
class InputExprAST;
class BinaryExprAST;
class LocalVarDeclStmtAST;
class EmptyStmtAST;
class OutputStmtAST;
class BlockStmtAST;
class ReturnStmtAST;
class IfStmtAST;
class WhileStmtAST;
class BasicAssignmentStmtAST;
class DerefAssignmentStmtAST;
class FunctionAST;
class ProgramAST;

class ASTVisitor
{
public:
    ASTVisitor() {}
    virtual ~ASTVisitor() {}
    virtual void visit(VarDeclNodeAST &) {}
    virtual void visit(NumberExprAST &) {}
    virtual void visit(VariableExprAST &) {}
    virtual void visit(FunctionCallExprAST &) {}
    virtual void visit(NullExprAST &) {}
    virtual void visit(AllocExprAST &) {}
    virtual void visit(RefExprAST &) {}
    virtual void visit(DerefExprAST &) {}
    virtual void visit(InputExprAST &) {}
    virtual void visit(BinaryExprAST &) {}
    virtual void visit(LocalVarDeclStmtAST &) {}
    virtual void visit(EmptyStmtAST &) {}
    virtual void visit(OutputStmtAST &) {}
    virtual void visit(BlockStmtAST &) {}
    virtual void visit(ReturnStmtAST &) {}
    virtual void visit(IfStmtAST &) {}
    virtual void visit(WhileStmtAST &) {}
    virtual void visit(BasicAssignmentStmtAST &) {}
    virtual void visit(DerefAssignmentStmtAST &) {}
    virtual void visit(FunctionAST &) {}
    virtual void visit(ProgramAST &) {}
};

}