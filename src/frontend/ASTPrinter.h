#include "RecursiveASTVisitor.h"
#include "llvm/Support/raw_ostream.h"

namespace remniw
{

class ASTPrinter : public RecursiveASTVisitor
{
private:
    unsigned Ind;
    llvm::raw_ostream &Out;

public:
    ASTPrinter(llvm::raw_ostream &Out): RecursiveASTVisitor(), Ind(0), Out(Out) {}

    void print(ProgramAST& AST) { AST.accept(*this); }

    virtual bool actBefore(VarDeclNodeAST & Node) override
    {
        Out.indent(Ind) << "VarDeclNode " << &Node << " '" << Node.getName() << "' "
            << *Node.getType() << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        return false;
    }

    virtual bool actBefore(NumberExprAST &Node) override
    {
        Out.indent(Ind) << "NumberExpr " << &Node << " '" << Node.getValue() << "' "
            << (Node.IsLValue() ? "lvalue" : "rvalue")
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        return false;
    }

    virtual bool actBefore(VariableExprAST &Node) override
    {
        Out.indent(Ind) << "VariableExpr " << &Node << " '" << Node.getName() << "' "
            << (Node.IsLValue() ? "lvalue" : "rvalue")
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";;
        return false;
    }

    virtual void visit(FunctionCallExprAST &Node) override
    {
        Out.indent(Ind) << "FunctionCallExpr " << &Node << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";;
        Out.indent(Ind+1) << "Callee:\n";
        Ind += 2;
        Node.getCallee()->accept(*this);
        Ind -= 2;
        Out.indent(Ind+1) << "Args:\n";
        Ind += 2;
        for (auto* Arg: Node.getArgs())
            Arg->accept(*this);
        Ind -= 2;
    }

    virtual bool actBefore(NullExprAST &Node) override
    {
        Out.indent(Ind) << "NullExpr " << &Node << ", "
            << (Node.IsLValue() ? "lvalue" : "rvalue")
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        return false;
    }

    virtual bool actBefore(AllocExprAST &Node) override
    {
        Out.indent(Ind) << "AllocExpr " << &Node << ", "
            << (Node.IsLValue() ? "lvalue" : "rvalue")
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        return false;
    }

    virtual bool actBefore(RefExprAST &Node) override
    {
        Out.indent(Ind) << "RefExpr " << &Node << ", "
            << (Node.IsLValue() ? "lvalue" : "rvalue")
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        Ind += 1;
        return false;
    }

    virtual void actAfter(RefExprAST &) override
    {
        Ind -= 1;
    }

    virtual bool actBefore(DerefExprAST &Node) override
    {
        Out.indent(Ind) << "DerefExpr " << &Node << ", "
            << (Node.IsLValue() ? "lvalue" : "rvalue")
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        Ind += 1;
        return false;
    }

    virtual void actAfter(DerefExprAST &) override
    {
        Ind -= 1;
    }

    virtual bool actBefore(InputExprAST &Node) override
    {
        Out.indent(Ind) << "InputExpr " << &Node << ", "
            << (Node.IsLValue() ? "lvalue" : "rvalue")
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        return false;
    }

    virtual bool actBefore(BinaryExprAST &Node) override
    {
        Out.indent(Ind) << "BinaryExpr " << &Node << " '" << Node.getOpString() << "' "
            << (Node.IsLValue() ? "lvalue" : "rvalue")
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        Ind += 1;
        return false;
    }

    virtual void actAfter(BinaryExprAST &) override
    {
        Ind -= 1;
    }

    virtual bool actBefore(LocalVarDeclStmtAST &Node) override
    {
        Out.indent(Ind) << "LocalVarDeclStmt " << &Node
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        Ind += 1;
        return false;
    }

    virtual void actAfter(LocalVarDeclStmtAST &) override
    {
        Ind -= 1;
    }

    virtual bool actBefore(EmptyStmtAST &Node) override
    {
        Out.indent(Ind) << "EmptyStmt " << &Node
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        return false;
    }

    virtual bool actBefore(OutputStmtAST &Node) override
    {
        Out.indent(Ind) << "OutputStmt " << &Node
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        Ind += 1;
        return false;
    }

    virtual void actAfter(OutputStmtAST &) override
    {
        Ind -= 1;
    }

    virtual bool actBefore(BlockStmtAST &Node) override
    {
        Out.indent(Ind) << "BlockStmt " << &Node
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        Ind += 1;
        return false;
    }

    virtual void actAfter(BlockStmtAST &) override
    {
        Ind -= 1;
    }

    virtual bool actBefore(ReturnStmtAST &Node) override
    {
        Out.indent(Ind) << "ReturnStmt " << &Node
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        Ind += 1;
        return false;
    }

    virtual void actAfter(ReturnStmtAST &) override
    {
        Ind -= 1;
    }

    virtual void visit(IfStmtAST &Node) override
    {
        Out.indent(Ind) << "IfStmt " << &Node
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        Out.indent(Ind+1) << "Cond:\n";
        Ind += 2;
        Node.getCond()->accept(*this);
        Ind -= 2;
        Out.indent(Ind+1) << "Then:\n";
        Ind += 2;
        Node.getThen()->accept(*this);
        Ind -= 2;
        if (Node.getElse())
        {
            Out.indent(Ind+1) << "Else:\n";
            Ind += 2;
            Node.getElse()->accept(*this);
            Ind -= 2;
        }
    }

    virtual void visit(WhileStmtAST &Node) override
    {
        Out.indent(Ind) << "WhileStmt" << &Node
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        Out.indent(Ind+1) << "Cond:\n";
        Ind += 2;
        Node.getCond()->accept(*this);
        Ind -= 2;
        Out.indent(Ind+1) << "Body:\n";
        Ind += 2;
        Node.getBody()->accept(*this);
        Ind -= 2;
    }

    virtual bool actBefore(BasicAssignmentStmtAST &Node) override
    {
        Out.indent(Ind) << "BasicAssignmentStmt " << &Node
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        Ind += 1;
        return false;
    }

    virtual void actAfter(BasicAssignmentStmtAST &) override
    {
        Ind -= 1;
    }

    virtual bool actBefore(DerefAssignmentStmtAST &Node) override
    {
        Out.indent(Ind) << "DerefAssignmentStmt " << &Node
            << " <" << Node.getLine() << ':' << Node.getCol() << ">\n";
        Ind += 1;
        return false;
    }

    virtual void actAfter(DerefAssignmentStmtAST &) override
    {
        Ind -= 1;
    }

    virtual void visit(FunctionAST &Node) override
    {
        Out.indent(Ind) << "Function " << &Node << " '" << Node.getFuncName() << "' "
            << *Node.getType() << "\n";
        Out.indent(Ind+1) << "ParamDecls:\n";
        Ind += 2;
        for (auto *ParmDecl : Node.getParamDecls())
            ParmDecl->accept(*this);
        Ind -= 2;
        Out.indent(Ind+1) << "LocalVarDecls:\n";
        Ind += 2;
        Node.getLocalVarDecls()->accept(*this);
        Ind -= 2;
        Out.indent(Ind+1) << "Body:\n";
        Ind += 2;
        for (auto *Stmt : Node.getBody())
            Stmt->accept(*this);
        Ind -= 2;
        Out.indent(Ind+1) << "Return:\n";
        Ind += 2;
        Node.getReturn()->accept(*this);
        Ind -= 2;
        Out.indent(Ind) << "\n";
    }

private:
    static std::ostream &indent(std::ostream &O, int Size)
    {
        return O << std::string(Size, ' ');
    }

};

}
