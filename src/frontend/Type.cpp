#include "Type.h"
// #include "TypeVisitor.h"
#include "llvm/Support/Casting.h"

namespace remniw
{

IntType *Type::getIntType(TypeContext &C)
{
    return &C.IntTy;
}

PointerType *Type::getIntPtrType(TypeContext &C)
{
   return getIntType(C)->getPointerTo();
}

FunctionType* Type::getFunctionType(llvm::ArrayRef<Type*> Params, Type *ReturnType)
{
    return FunctionType::get(Params, ReturnType);
}

VarType* Type::getVarType(const ASTNode *DeclNode, TypeContext &C)
{
    return VarType::get(DeclNode, C);
}

PointerType *Type::getPointerTo()
{
    return PointerType::get(const_cast<Type*>(this));
}

VarType* VarType::get(const ASTNode *DeclNode, TypeContext &C)
{
    const VarTypeKeyInfo::KeyTy Key(DeclNode);
    VarType *VarTy;
    auto Insertion = C.VarTypes.insert_as(nullptr, Key);
    if (Insertion.second)
    {
        VarTy = new VarType(DeclNode, C);
        *Insertion.first = VarTy;
    }
    else
    {
        VarTy = *Insertion.first;
    }
    return VarTy;
}

IntType* IntType::get(TypeContext &C)
{
    return Type::getIntType(C);
}

PointerType* PointerType::get(Type* EltTy)
{
    TypeContext &C = EltTy->getContext();

    if (C.PointerTypes.count(EltTy))
        return C.PointerTypes[EltTy];

    PointerType *Entry = new PointerType(EltTy);
    C.PointerTypes[EltTy] = Entry;
    return Entry;
}

FunctionType* FunctionType::get(llvm::ArrayRef<Type*> Params, Type *ReturnType)
{
    TypeContext &C = ReturnType->getContext();
    const FunctionTypeKeyInfo::KeyTy Key(Params, ReturnType);
    FunctionType *FT;
    auto Insertion = C.FunctionTypes.insert_as(nullptr, Key);
    if (Insertion.second)
    {
        FT = new FunctionType(Params, ReturnType);
        *Insertion.first = FT;
    }
    else
    {
        FT = *Insertion.first;
    }
    return FT;
}

// bool VarType::operator==(const Type &Other) const
// {
//     auto OtherVarType = llvm::dyn_cast<VarType>(&Other);
//     if (!OtherVarType)
//         return false;
//     return DeclNode == OtherVarType->getASTNode();
// }

// bool VarType::operator!=(const Type &Other) const
// {
//     return !(*this == Other);
// }

// bool IntType::operator==(const Type &Other) const
// {
//     auto OtherIntType = llvm::dyn_cast<IntType>(&Other);
//     if (!OtherIntType)
//         return false;
//     return true;
// }

// bool IntType::operator!=(const Type &Other) const
// {
//     return !(*this == Other);
// }

// bool PointerType::operator==(const Type &Other) const
// {
//     auto OtherPointerType = llvm::dyn_cast<PointerType>(&Other);
//     if (!OtherPointerType)
//         return false;
//     return *PointeeTy == *(OtherPointerType->getPointeeType());
// }

// bool PointerType::operator!=(const Type &Other) const
// {
//     return !(*this == Other);
// }

// bool FunctionType::operator==(const Type &Other) const
// {
//     auto OtherFunctionType = llvm::dyn_cast<FunctionType>(&Other);
//     if (!OtherFunctionType)
//         return false;

//     auto OtherParamTys = OtherFunctionType->getParamTypes();
//     if (ParamTys.size() != OtherParamTys.size())
//         return false;

//     for (std::size_t i = 0; i < ParamTys.size(); ++i)
//     {
//         if (*ParamTys[i] != *OtherParamTys[i])
//             return false;
//     }

//     auto OtherRetTy = OtherFunctionType->getReturnType();
//     return *RetTy == *OtherRetTy;
// }

// bool FunctionType::operator!=(const Type &Other) const
// {
//     return !(*this == Other);
// }

void VarType::accept(TypeVisitor& Visitor)
{
    // Visitor.visit(this);
}

void IntType::accept(TypeVisitor& Visitor)
{
    // Visitor.visit(this);
}

void PointerType::accept(TypeVisitor& Visitor)
{
    // Visitor.visit(this);
}

void FunctionType::accept(TypeVisitor& Visitor)
{
    // Visitor.visit(this);
}

// void AlphaType::accept(TypeVisitor& Visitor)
// {
//     Visitor.visit(this);
// }

// void MuType::accept(TypeVisitor& Visitor)
// {
//     Visitor.visit(this);
// }

}

namespace llvm
{
    llvm::raw_ostream &operator<<(llvm::raw_ostream &OS, const remniw::Type &Ty)
    {
        Ty.print(OS);
        return OS;
    }
}