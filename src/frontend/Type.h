#pragma once

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseMapInfo.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

namespace remniw
{

class ASTNode;
class TypeVisitor;
class TypeContext;
class IntType;
class PointerType;
class FunctionType;
class VarType;

class Type
{
public:
    enum TypeKind
    {
        TK_VARTYPE,
        TK_INTTYPE,
        TK_POINTERTYPE,
        TK_FUNCTIONTYPE,
    };

public:
    Type(TypeKind TyKind, TypeContext &C) : TyKind(TyKind), Context(C) {}

    void print(llvm::raw_ostream &OS) const;

    TypeContext &getContext() const { return Context; }
    TypeKind getTypeKind() const { return TyKind; }

    static IntType *getIntType(TypeContext &C);
    static PointerType *getIntPtrType(TypeContext &C);
    static FunctionType* getFunctionType(llvm::ArrayRef<Type*> Params, Type *ReturnType);
    static VarType* getVarType(const ASTNode *DeclNode, TypeContext &C);
    PointerType *getPointerTo();

private:
    const TypeKind TyKind;
    TypeContext &Context;
};

// Class to represent type variable.
class VarType : public Type
{
public:
    VarType(const ASTNode *DeclNode, TypeContext &C) :
        Type(TK_VARTYPE, C), DeclNode(DeclNode) {}

    static bool classof(const Type *Ty)
    {
        return Ty->getTypeKind() == TK_VARTYPE;
    }

    static VarType* get(const ASTNode *DeclNode, TypeContext &C);

    const ASTNode *getASTNode() const { return DeclNode; }

private:
    const ASTNode *DeclNode;
};

struct VarTypeKeyInfo
{
    struct KeyTy
    {
        const ASTNode *DeclNode;
        KeyTy(const ASTNode *DeclNode) : DeclNode(DeclNode) {}
        KeyTy(const VarType *Ty) : DeclNode(Ty->getASTNode()) {}

        bool operator==(const KeyTy& That) const
        {
            if (DeclNode != That.DeclNode)
                return false;
            return true;
        }
        bool operator!=(const KeyTy& that) const
        {
            return !this->operator==(that);
        }
    };

    static inline VarType* getEmptyKey()
    {
        return llvm::DenseMapInfo<VarType*>::getEmptyKey();
    }

    static inline VarType* getTombstoneKey()
    {
        return llvm::DenseMapInfo<VarType*>::getTombstoneKey();
    }

    static unsigned getHashValue(const KeyTy& Key)
    {
        return llvm::hash_value(Key.DeclNode);
    }

    static unsigned getHashValue(const VarType *Ty)
    {
        return getHashValue(KeyTy(Ty));
    }

    static bool isEqual(const KeyTy& LHS, const VarType *RHS)
    {
        if (RHS == getEmptyKey() || RHS == getTombstoneKey())
            return false;
        return LHS == KeyTy(RHS);
    }

    static bool isEqual(const VarType *LHS, const VarType *RHS)
    {
        return LHS == RHS;
    }
};

// Class to represent integer types (proper type).
class IntType : public Type
{
public:
    IntType(TypeContext &C) : Type(TK_INTTYPE, C) {}

    static bool classof(const Type *Ty)
    {
        return Ty->getTypeKind() == TK_INTTYPE;
    }

    static IntType* get(TypeContext &C);
};

// Class to represent pointers (proper type).
class PointerType : public Type
{
public:
    PointerType(Type* E) : Type(TK_POINTERTYPE, E->getContext()), PointeeTy(E) {}

    PointerType(const PointerType &) = delete;
    PointerType &operator=(const PointerType &) = delete;

    static bool classof(const Type *Ty)
    {
        return Ty->getTypeKind() == TK_POINTERTYPE;
    }

    static PointerType* get(Type* EltTy);

    Type* getPointeeType() const { return PointeeTy; }

private:
    Type* PointeeTy;
};

// Class to represent function types (proper type).
class FunctionType : public Type
{
public:
    FunctionType(llvm::ArrayRef<Type*> ParamTys, Type* RetTy)
        : Type(TK_FUNCTIONTYPE, RetTy->getContext()),
          ParamTys(ParamTys),
          RetTy(RetTy) {}

    FunctionType(const FunctionType &) = delete;
    FunctionType &operator=(const FunctionType &) = delete;

    static bool classof(const Type *Ty)
    {
        return Ty->getTypeKind() == TK_FUNCTIONTYPE;
    }

    static FunctionType* get(llvm::ArrayRef<Type*> Params, Type *ReturnType);

    llvm::ArrayRef<Type*> getParamTypes() const { return ParamTys; }
    Type* getReturnType() const { return RetTy; }

private:
    std::vector<Type*> ParamTys;
    Type* RetTy;
};

struct FunctionTypeKeyInfo
{
    struct KeyTy
    {
        llvm::ArrayRef<Type*> Params;
        const Type *ReturnType;
        KeyTy(const llvm::ArrayRef<Type*>& P, const Type* R) :
            Params(P), ReturnType(R) {}
        KeyTy(const FunctionType *FT) :
            Params(FT->getParamTypes()), ReturnType(FT->getReturnType()) {}

        bool operator==(const KeyTy& That) const
        {
            if (ReturnType != That.ReturnType)
                return false;
            if (Params != That.Params)
                return false;
            return true;
        }
        bool operator!=(const KeyTy& that) const
        {
            return !this->operator==(that);
        }
    };

    static inline FunctionType* getEmptyKey()
    {
        return llvm::DenseMapInfo<FunctionType*>::getEmptyKey();
    }

    static inline FunctionType* getTombstoneKey()
    {
        return llvm::DenseMapInfo<FunctionType*>::getTombstoneKey();
    }

    static unsigned getHashValue(const KeyTy& Key)
    {
        return llvm::hash_combine(Key.ReturnType,
                                  llvm::hash_combine_range(Key.Params.begin(),
                                                           Key.Params.end()));
    }

    static unsigned getHashValue(const FunctionType *FT)
    {
        return getHashValue(KeyTy(FT));
    }

    static bool isEqual(const KeyTy& LHS, const FunctionType *RHS)
    {
        if (RHS == getEmptyKey() || RHS == getTombstoneKey())
            return false;
        return LHS == KeyTy(RHS);
    }

    static bool isEqual(const FunctionType *LHS, const FunctionType *RHS)
    {
        return LHS == RHS;
    }
};

class TypeContext
{
public:
    TypeContext() : IntTy(*this) {}
    ~TypeContext()
    {
        for(auto p : PointerTypes)
        {
            delete p.second;
        }
        for (auto *FT : FunctionTypes)
        {
            delete FT;
        }
        for (auto *VarTy: VarTypes)
        {
            delete VarTy;
        }
    }

    IntType IntTy;
    llvm::DenseMap<Type*, PointerType*> PointerTypes;
    using FunctionTypeSet = llvm::DenseSet<FunctionType *, FunctionTypeKeyInfo>;
    FunctionTypeSet FunctionTypes;
    using VarTypeSet = llvm::DenseSet<VarType *, VarTypeKeyInfo>;
    VarTypeSet VarTypes;
};

}

namespace llvm
{
    llvm::raw_ostream &operator<<(llvm::raw_ostream &OS, const remniw::Type &Ty);
}
