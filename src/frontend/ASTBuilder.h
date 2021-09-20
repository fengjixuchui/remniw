#pragma once

#include "antlr4-runtime.h"
#include "RemniwBaseVisitor.h"

namespace remniw
{

class ASTBuilder : public RemniwBaseVisitor
{
private:
    TypeContext& TyCtx;

public:
    ASTBuilder(TypeContext& TyCtx) : TyCtx(TyCtx) {}

    std::unique_ptr<ProgramAST> build(RemniwParser::ProgramContext *Ctx);

    virtual antlrcpp::Any visitIntType(RemniwParser::IntTypeContext *Ctx);

    virtual antlrcpp::Any visitPointerType(RemniwParser::PointerTypeContext *Ctx);

    virtual antlrcpp::Any visitFunctionType(RemniwParser::FunctionTypeContext *Ctx);

    virtual antlrcpp::Any visitProgram(RemniwParser::ProgramContext *Ctx);

    virtual antlrcpp::Any visitFun(RemniwParser::FunContext *Ctx);

    virtual antlrcpp::Any visitMulExpr(RemniwParser::MulExprContext *Ctx);

    virtual antlrcpp::Any visitDivExpr(RemniwParser::DivExprContext *Ctx);

    virtual antlrcpp::Any visitAddExpr(RemniwParser::AddExprContext *Ctx);

    virtual antlrcpp::Any visitSubExpr(RemniwParser::SubExprContext *Ctx);

    virtual antlrcpp::Any visitEqualExpr(RemniwParser::EqualExprContext *Ctx);

    virtual antlrcpp::Any visitRelationalExpr(RemniwParser::RelationalExprContext *Ctx);

    virtual antlrcpp::Any visitIdExpr(RemniwParser::IdExprContext *Ctx);

    virtual antlrcpp::Any visitIntExpr(RemniwParser::IntExprContext *Ctx);

    virtual antlrcpp::Any visitNegIntExpr(RemniwParser::NegIntExprContext *Ctx);

    virtual antlrcpp::Any visitRefExpr(RemniwParser::RefExprContext *Ctx);

    virtual antlrcpp::Any visitDerefExpr(RemniwParser::DerefExprContext *Ctx);

    virtual antlrcpp::Any visitNullExpr(RemniwParser::NullExprContext *Ctx);

    virtual antlrcpp::Any visitAllocExpr(RemniwParser::AllocExprContext *Ctx);

    virtual antlrcpp::Any visitInputExpr(RemniwParser::InputExprContext *Ctx);

    virtual antlrcpp::Any visitParenExpr(RemniwParser::ParenExprContext *Ctx);

    virtual antlrcpp::Any visitFuncCallExpr(RemniwParser::FuncCallExprContext *Ctx);

    // virtual antlrcpp::Any visitRecordCreateExpr(RemniwParser::RecordCreateExprContext *Ctx);

    // virtual antlrcpp::Any visitRecordAccessExpr(RemniwParser::RecordAccessExprContext *Ctx);

    // FIXME: visitID, visitIdExpr
    virtual antlrcpp::Any visitId(RemniwParser::IdContext *Ctx);
/*
    // virtual antlrcpp::Any visitInteger(RemniwParser::IntegerContext *Ctx);

    // virtual antlrcpp::Any visitParameters(RemniwParser::ParametersContext *Ctx);

    // virtual antlrcpp::Any visitVarDeclarations(RemniwParser::VarDeclarationsContext *Ctx);

    // virtual antlrcpp::Any visitArguments(RemniwParser::ArgumentsContext *Ctx);
*/

    virtual antlrcpp::Any visitEmptyStmt(RemniwParser::EmptyStmtContext *Ctx);

    virtual antlrcpp::Any visitOutputStmt(RemniwParser::OutputStmtContext *Ctx);

    virtual antlrcpp::Any visitBlockStmt(RemniwParser::BlockStmtContext *Ctx);

    virtual antlrcpp::Any visitReturnStmt(RemniwParser::ReturnStmtContext *Ctx);

    virtual antlrcpp::Any visitIfStmt(RemniwParser::IfStmtContext *Ctx);

    virtual antlrcpp::Any visitWhileStmt(RemniwParser::WhileStmtContext *Ctx);

    virtual antlrcpp::Any visitBasicAssignmentStmt(RemniwParser::BasicAssignmentStmtContext *Ctx);

    virtual antlrcpp::Any visitDerefAssignmentStmt(RemniwParser::DerefAssignmentStmtContext *Ctx);

    virtual antlrcpp::Any visitRecordFieldBasicAssignmentStmt(RemniwParser::RecordFieldBasicAssignmentStmtContext *Ctx);

    virtual antlrcpp::Any visitRecordFieldDerefAssignmentStmt(RemniwParser::RecordFieldDerefAssignmentStmtContext *Ctx);
};

}