#include "AST.h"
#include "RecursiveASTVisitor.h"

namespace remniw
{

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitExpr(ExprAST *Expr)
{
    switch (Expr->getKind())
    {
    case ASTNode::NumberExpr:
        getDerived().visitNumberExpr(static_cast<NumberExprAST*>(Expr));
        break;
    case ASTNode::VariableExpr:
        getDerived().visitVariableExpr(static_cast<VariableExprAST*>(Expr));
        break;
    case ASTNode::FunctionCallExpr:
        getDerived().visitFunctionCallExpr(static_cast<FunctionCallExprAST*>(Expr));
        break;
    case ASTNode::NullExpr:
        getDerived().visitNullExpr(static_cast<NullExprAST*>(Expr));
        break;
    case ASTNode::AllocExpr:
        getDerived().visitAllocExpr(static_cast<AllocExprAST*>(Expr));
        break;
    case ASTNode::RefExpr:
        getDerived().visitRefExpr(static_cast<RefExprAST*>(Expr));
        break;
    case ASTNode::DerefExpr:
        getDerived().visitDerefExpr(static_cast<DerefExprAST*>(Expr));
        break;
    case ASTNode::InputExpr:
        getDerived().visitInputExpr(static_cast<InputExprAST*>(Expr));
        break;
    case ASTNode::BinaryExpr:
        getDerived().visitBinaryExpr(static_cast<BinaryExprAST*>(Expr));
        break;
    default:
        llvm_unreachable("unexpected expr!");
    }
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitStmt(StmtAST *Stmt)
{
    switch (Stmt->getKind())
    {
    case ASTNode::LocalVarDeclStmt:
        getDerived().visitLocalVarDeclStmt(static_cast<LocalVarDeclStmtAST*>(Stmt));
        break;
    case ASTNode::EmptyStmt:
        getDerived().visitEmptyStmt(static_cast<EmptyStmtAST*>(Stmt));
        break;
    case ASTNode::OutputStmt:
        getDerived().visitOutputStmt(static_cast<OutputStmtAST*>(Stmt));
        break;
    case ASTNode::BlockStmt:
        getDerived().visitBlockStmt(static_cast<BlockStmtAST*>(Stmt));
        break;
    case ASTNode::ReturnStmt:
        getDerived().visitReturnStmt(static_cast<ReturnStmtAST*>(Stmt));
        break;
    case ASTNode::IfStmt:
        getDerived().visitIfStmt(static_cast<IfStmtAST*>(Stmt));
        break;
    case ASTNode::WhileStmt:
        getDerived().visitWhileStmt(static_cast<WhileStmtAST*>(Stmt));
        break;
    case ASTNode::BasicAssignmentStmt:
        getDerived().visitBasicAssignmentStmt(static_cast<BasicAssignmentStmtAST*>(Stmt));
        break;
    case ASTNode::DerefAssignmentStmt:
        getDerived().visitDerefAssignmentStmt(static_cast<DerefAssignmentStmtAST*>(Stmt));
        break;
    default:
        llvm_unreachable("unexpected stmt!");
    }
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitVarDeclNode(VarDeclNodeAST *VarDeclNode)
{
    if (getDerived().actBeforeVisitVarDeclNode(VarDeclNode))
        return;

    getDerived().actAfterVisitVarDeclNode(VarDeclNode);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitNumberExpr(NumberExprAST *NumberExpr)
{
    if (getDerived().actBeforeVisitNumberExpr(NumberExpr))
        return;

    getDerived().actAfterVisitNumberExpr(NumberExpr);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitVariableExpr(VariableExprAST *VariableExpr)
{
    if (getDerived().actBeforeVisitVariableExpr(VariableExpr))
        return;

    getDerived().actAfterVisitVariableExpr(VariableExpr);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitFunctionCallExpr(FunctionCallExprAST *FunctionCallExpr)
{
    if (getDerived().actBeforeVisitFunctionCallExpr(FunctionCallExpr))
        return;

    for (auto *Arg : FunctionCallExpr->getArgs())
        visitExpr(Arg);

    getDerived().actAfterVisitFunctionCallExpr(FunctionCallExpr);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitNullExpr(NullExprAST *NullExpr)
{
    if (getDerived().actBeforeVisitNullExpr(NullExpr))
        return;

    getDerived().actAfterVisitNullExpr(NullExpr);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitAllocExpr(AllocExprAST *AllocExpr)
{
    if (getDerived().actBeforeVisitAllocExpr(AllocExpr))
        return;

    visitExpr(AllocExpr->getInit());

    getDerived().actAfterVisitAllocExpr(AllocExpr);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitRefExpr(RefExprAST *RefExpr)
{
    if (getDerived().actBeforeVisitRefExpr(RefExpr))
        return;

    visitExpr(RefExpr->getVar());

    actAfterVisitRefExpr(RefExpr);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitDerefExpr(DerefExprAST *DerefExpr)
{
    if (getDerived().actBeforeVisitDerefExpr(DerefExpr))
        return;

    visitExpr(DerefExpr->getPtr());

    getDerived().actAfterVisitDerefExpr(DerefExpr);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitInputExpr(InputExprAST *InputExpr)
{
    if (getDerived().actBeforeVisitInputExpr(InputExpr))
        return;

    getDerived().actAfterVisitInputExpr(InputExpr);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitBinaryExpr(BinaryExprAST *BinaryExpr)
{
    if (getDerived().actBeforeVisitBinaryExpr(BinaryExpr))
        return;

    visitExpr(BinaryExpr->getLHS());
    visitExpr(BinaryExpr->getRHS());

    getDerived().actAfterVisitBinaryExpr(BinaryExpr);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitLocalVarDeclStmt(LocalVarDeclStmtAST *LocalVarDeclStmt)
{
    if (getDerived().actBeforeVisitLocalVarDeclStmt(LocalVarDeclStmt))
        return;

    for (auto *VarDeclNode : LocalVarDeclStmt->getVars())
        visitVarDeclNode(VarDeclNode);

    actAfterVisitLocalVarDeclStmt(LocalVarDeclStmt);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitEmptyStmt(EmptyStmtAST *EmptyStmt)
{
    if (getDerived().actBeforeVisitEmptyStmt(EmptyStmt))
        return;

    getDerived().actAfterVisitEmptyStmt(EmptyStmt);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitOutputStmt(OutputStmtAST *OutputStmt)
{
    if (getDerived().actBeforeVisitOutputStmt(OutputStmt))
        return;

    visitExpr(OutputStmt->getExpr());

    getDerived().actAfterVisitOutputStmt(OutputStmt);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitBlockStmt(BlockStmtAST *BlockStmt)
{
    if (getDerived().actBeforeVisitBlockStmt(BlockStmt))
        return;

    for (auto *Stmt : BlockStmt->getStmts())
        visitStmt(Stmt);

    getDerived().actAfterVisitBlockStmt(BlockStmt);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitReturnStmt(ReturnStmtAST *ReturnStmt)
{
    if (getDerived().actBeforeVisitReturnStmt(ReturnStmt))
        return;

    visitExpr(ReturnStmt->getExpr());

    getDerived().actAfterVisitReturnStmt(ReturnStmt);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitIfStmt(IfStmtAST *IfStmt)
{
    if (getDerived().actBeforeVisitIfStmt(IfStmt))
        return;

    visitExpr(IfStmt->getCond());
    visitStmt(IfStmt->getThen());
    if (IfStmt->getElse())
        visitStmt(IfStmt->getElse());

    getDerived().actAfterVisitIfStmt(IfStmt);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitWhileStmt(WhileStmtAST *WhileStmt)
{
    if (getDerived().actBeforeVisitWhileStmt(WhileStmt))
        return;

    visitExpr(WhileStmt->getCond());
    visitStmt(WhileStmt->getBody());

    getDerived().actAfterVisitWhileStmt(WhileStmt);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitBasicAssignmentStmt(BasicAssignmentStmtAST *BasicAssignmentStmt)
{
    if (getDerived().actBeforeVisitBasicAssignmentStmt(BasicAssignmentStmt))
        return;

    visitExpr(BasicAssignmentStmt->getLHS());
    visitExpr(BasicAssignmentStmt->getRHS());

    getDerived().actAfterVisitBasicAssignmentStmt(BasicAssignmentStmt);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitDerefAssignmentStmt(DerefAssignmentStmtAST *DerefAssignmentStmt)
{
    if (getDerived().actBeforeVisitDerefAssignmentStmt(DerefAssignmentStmt))
        return;

    visitExpr(DerefAssignmentStmt->getLHS());
    visitExpr(DerefAssignmentStmt->getRHS());

    getDerived().actAfterVisitDerefAssignmentStmt(DerefAssignmentStmt);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitFunction(FunctionAST *Function)
{
    if (getDerived().actBeforeVisitFunction(Function))
        return;

    for (auto *VarDeclNode : Function->getParamDecls())
        visitVarDeclNode(VarDeclNode);
    visitLocalVarDeclStmt(Function->getLocalVarDecls());
    for (auto *Stmt : Function->getBody())
        visitStmt(Stmt);
    visitReturnStmt(Function->getReturn());

    getDerived().actAfterVisitFunction(Function);
}

template <typename Derived>
void RecursiveASTVisitor<Derived>::visitProgram(ProgramAST *Program)
{
    if (getDerived().actBeforeVisitProgram(Program))
        return;

    for (auto *Function : Program->getFunctions())
        visitFunction(Function);

    getDerived().actAfterVisitFunction(Program);
}

}