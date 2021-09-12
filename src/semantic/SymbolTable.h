#pragma once

#include "AST.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseMapInfo.h"
#include <unordered_map>

namespace remniw
{

// struct VarMapEntry
// {
//     // Name of the referenced variable and which function it locates in
//     std::string VaribaleName;
//     FunctionAST* Function;

//     VarMapEntry(std::string VarName, FunctionAST* Func) :
//         VaribaleName(VarName), Function(Func) {}

//     // Implement operator== so that FileEntry can be used as key in
//     // unordered containers.
//     bool operator==(const VarMapEntry &RHS) const
//     {
//         return VaribaleName == RHS.VaribaleName && Function == RHS.Function;
//     }
//     bool operator!=(const VarMapEntry &RHS) const {
//         return VaribaleName != RHS.VaribaleName || Function != RHS.Function;
//     };
// };

struct SymbolTable
{
    SymbolTable() {}

    bool addFunction(llvm::StringRef FunctionName, FunctionAST *Function)
    {
        return Functions.insert({FunctionName, Function}).second;
    }

    bool addVariable(llvm::StringRef VariableName, VarDeclNodeAST *Variable, FunctionAST *Function)
    {
        return Variables.insert({{VariableName, Function}, Variable}).second;
    }

    bool addReturnExpr(ExprAST* ReturnExpr, FunctionAST *Function)
    {
        return ReturnExprs.insert({ReturnExpr, Function}).second;
    }

    FunctionAST *getFunction(llvm::StringRef FunctionName)
    {
        if (Functions.count(FunctionName))
            return Functions[FunctionName];
        return nullptr;
    }

    VarDeclNodeAST *getVariable(llvm::StringRef VariableName, FunctionAST* Function)
    {
        auto Key = std::make_pair(VariableName, Function);
        if (Variables.count(Key))
            return Variables[Key];
        return nullptr;
    }

    void print(llvm::raw_ostream &OS)
    {
        for(auto &p: Functions)
            OS << "Function: '" << p.first << "' " << p.second << "\n";
        for(auto &p: Variables)
            OS << "Variable: '" << p.first.first << "' " << p.second
               << " (of function '" << p.first.first << "')\n";
        for(auto &p : ReturnExprs)
            OS << "ReturnExpr: '" << p.first << "' (of function '" << p.second->getFuncName() << "')\n";
    }

    // < FunctionName, FunctionAST* >
    llvm::DenseMap<llvm::StringRef, FunctionAST *> Functions;
    // < <VariableName, FunctionAST*>, VarDeclNodeAST* >
    llvm::DenseMap<std::pair<llvm::StringRef, FunctionAST *>, VarDeclNodeAST *> Variables;
    // <ExprAST of ReturnStmt, FunctionAST*>
    llvm::DenseMap<ExprAST *, FunctionAST *> ReturnExprs;
};

class SymbolTableBuilder : public RecursiveASTVisitor
{
public:
    SymbolTableBuilder() : SymTab(), CurrentFunction(nullptr) {}

    SymbolTable& getSymbolTale()
    {
        return SymTab;
    }

    virtual bool actBefore(FunctionAST &Function) override
    {
        CurrentFunction = &Function;
        return false;
    }

    virtual void actAfter(FunctionAST &Function) override
    {
        SymTab.addFunction(CurrentFunction->getFuncName(), &Function);
    }

    virtual void actAfter(VarDeclNodeAST &VarDeclNode) override
    {
        SymTab.addVariable(VarDeclNode.getName(), &VarDeclNode, CurrentFunction);
    }

    virtual void actAfter(ReturnStmtAST & ReturnStmt) override
    {
        SymTab.addReturnExpr(ReturnStmt.getExpr(), CurrentFunction);
    }

private:
    SymbolTable SymTab;
    FunctionAST* CurrentFunction;
};

}