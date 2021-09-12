#pragma once

#include "RecursiveASTVisitor.h"
#include "SymbolTable.h"
#include "Type.h"
// #include "TypeVisitor.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/Casting.h"
#include <vector>

namespace remniw
{

struct TypeConstraint
{
    TypeConstraint(Type* LHS, Type* RHS) : LHS(LHS), RHS(RHS) {}

    void print(llvm::raw_ostream &OS) const
    {
        LHS->print(OS);
        OS << " == ";
        RHS->print(OS);
        OS << "\n";
    }

    Type* LHS;
    Type* RHS;
};

class UnionFind
{
public:
    void unionTypes(Type *Ty1, Type *Ty2)
    {
        auto Ty1r = find(Ty1);
        auto Ty2r = find(Ty2);
        if (Ty1r != Ty2r)
            Parent[Ty1r] = Ty2r;
    }

    void makeSet(Type* Ty)
    {
        if (Parent.find(Ty) == Parent.end())
            Parent[Ty] = Ty;
    }

    Type* find(Type* Ty)
    {
        makeSet(Ty);
        if (Parent[Ty] != Ty)
            Parent[Ty] = find(Parent[Ty]);
        return Parent[Ty];
    }

    // std::unique_ptr<UnionFind> copy()
    // {
    //     auto Tmp = std::make_unique<UnionFind>();
    //     for (const auto &p : Parent)
    //     {
    //         auto src = Copier::copy(p.first);
    //         auto dest = Copier::copy(p.second);
    //         Tmp->Parent.insert(std::pair<Type*, Type*>(src, dest));
    //     }
    //     return std::move(Tmp);
    // }

private:
    // Parents[x] = y means the parent of x is y
    llvm::DenseMap<Type*, Type*> Parent;
};

class TypeAnalysis : public RecursiveASTVisitor
{
public:
    TypeAnalysis(SymbolTable &SymTab, TypeContext& TypeCtx)
        : SymTab(SymTab), TypeCtx(TypeCtx), TheUnionFind(std::move(std::make_unique<UnionFind>())) {}

    bool unify(Type* Ty1, Type* Ty2);

    bool solve();

    bool verify();

    // Type* getType(Type* Ty);

    // Type* close(Type* Ty, std::set<std::shared_ptr<VarType>> Visited);

    std::vector<TypeConstraint> getConstraints() { return Constraints; }

    // visitor
    virtual bool actBefore(FunctionAST &Function) override
    {
        CurrentFunction = &Function;
        return false;
    }

    // I: [[I]] = int
    virtual void actAfter(NumberExprAST &NumberExpr) override
    {
        Constraints.emplace_back(ASTNodeToType(&NumberExpr), Type::getIntType(TypeCtx));
    }

    // E1 op E2: [[E1]] = [[E2]] = [[E1 op E2]] = int
    // E1 == E2: [[E1]] = [[E2]] ^ [[E1 == E2]] = int
    virtual void actAfter(BinaryExprAST &BinaryExpr) override
    {
        auto *IntTy = Type::getIntType(TypeCtx);
        Constraints.emplace_back(ASTNodeToType(&BinaryExpr), IntTy);
        if (BinaryExpr.getOp() == BinaryExprAST::OpKind::Eq)
        {
            Constraints.emplace_back(ASTNodeToType(BinaryExpr.getLHS()), ASTNodeToType(BinaryExpr.getRHS()));
        }
        else
        {
            Constraints.emplace_back(ASTNodeToType(BinaryExpr.getLHS()), IntTy);
            Constraints.emplace_back(ASTNodeToType(BinaryExpr.getRHS()), IntTy);
        }
    }

    // input: [[input]] = int
    virtual void actAfter(InputExprAST &InputExpr) override
    {
        Constraints.emplace_back(ASTNodeToType(&InputExpr), Type::getIntType(TypeCtx));
    }

    // X = E: [[X]] = [[E]]
    virtual void actAfter(BasicAssignmentStmtAST &BasicAssignmentStmt) override
    {
        Constraints.emplace_back(ASTNodeToType(BasicAssignmentStmt.getLHS()), ASTNodeToType(BasicAssignmentStmt.getRHS()));
    }

    // *E1 = E2: [[E1]] = &[[E2]]
    virtual void actAfter(DerefAssignmentStmtAST &DerefAssignmentStmt) override
    {
        Constraints.emplace_back(ASTNodeToType(DerefAssignmentStmt.getLHS()),
                                 ASTNodeToType(DerefAssignmentStmt.getRHS())->getPointerTo());
    }

    // output E: [[E]] = int
    virtual void actAfter(OutputStmtAST &OutputStmt) override
    {
        Constraints.emplace_back(ASTNodeToType(OutputStmt.getExpr()), Type::getIntType(TypeCtx));
    }

    // if (E) S1 else S2: [[E]] = int
    virtual void actAfter(IfStmtAST &IfStmt) override
    {
        Constraints.emplace_back(ASTNodeToType(IfStmt.getCond()), Type::getIntType(TypeCtx));
    }

    // while (E) S: [[E]] = int
    virtual void actAfter(WhileStmtAST &WhileStmt) override
    {
        Constraints.emplace_back(ASTNodeToType(WhileStmt.getCond()), Type::getIntType(TypeCtx));
    }

    // main(X1,...,Xn){ ...return E; }: [[X1]] = ...[[Xn]] = [[E]] = int
    // X(X1,...,Xn){ ...return E; }: [[X]] = ([[X1]],...,[[Xn]])->[[E]]
    virtual void actAfter(FunctionAST &Function) override
    {
        std::vector<Type*> ParamTypes;
        ReturnStmtAST *Ret = Function.getReturn();
        if (Function.getFuncName() == "main")
        {
            for (auto *Param : Function.getParamDecls())
            {
                ParamTypes.push_back(ASTNodeToType(Param));
                Constraints.emplace_back(ASTNodeToType(Param), Type::getIntType(TypeCtx));
            }
            Constraints.emplace_back(ASTNodeToType(Ret->getExpr()), Type::getIntType(TypeCtx));
        }
        else
        {
            for (auto *Param : Function.getParamDecls())
            {
                ParamTypes.push_back(ASTNodeToType(Param));
            }
        }
        Constraints.emplace_back(ASTNodeToType(&Function),
                                Type::getFunctionType(ParamTypes, ASTNodeToType(Ret->getExpr())));
    }

    // E(E1,...,En): [[E]] = ([[E1]],...,[[En]])->[[E(E1,...,En)]]
    virtual void actAfter(FunctionCallExprAST &FunctionCallExpr) override
    {
        std::vector<Type*> ArgTypes;
        for (auto *Arg : FunctionCallExpr.getArgs())
        {
            ArgTypes.push_back(ASTNodeToType(Arg));
        }
        Constraints.emplace_back(ASTNodeToType(FunctionCallExpr.getCallee()),
                    Type::getFunctionType(ArgTypes, ASTNodeToType(&FunctionCallExpr)));
    }

    // alloc E: [[alloc E]] = &[[E]]
    virtual void actAfter(AllocExprAST &AllocExpr) override
    {
        Constraints.emplace_back(ASTNodeToType(&AllocExpr),
                    ASTNodeToType(AllocExpr.getInit())->getPointerTo());
    }

    // &X: [[&X]] = &[[X]]
    virtual void actAfter(RefExprAST &RefExpr) override
    {
        Constraints.emplace_back(ASTNodeToType(&RefExpr),
                    ASTNodeToType(RefExpr.getVar())->getPointerTo());
    }

    // FIXME
    // null: [[null]] = &α
    virtual void actAfter(NullExprAST &NullExpr) override
    {
        // Constraints.emplace_back(ASTNodeToType(&NullExpr),
        //                          std::make_shared<PointerType>(std::make_shared<AlphaType>(&NullExpr)));
    }

    // *E: [[E]] = &[[*E]]
    virtual void actAfter(DerefExprAST &DerefExpr) override
    {
        Constraints.emplace_back(ASTNodeToType(DerefExpr.getPtr()),
                    ASTNodeToType(&DerefExpr)->getPointerTo());
    }

private:
    Type* ASTNodeToType(const ASTNode *Node) const;

private:
    SymbolTable &SymTab;
    TypeContext &TypeCtx;
    std::unique_ptr<UnionFind> TheUnionFind;
    FunctionAST* CurrentFunction;
    std::vector<TypeConstraint> Constraints;
    // std::unordered_map<const ASTNode*, Type*> TypeMap;
};

}