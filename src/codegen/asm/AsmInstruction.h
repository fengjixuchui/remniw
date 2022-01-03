#pragma once

#include "AsmOperand.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/raw_ostream.h"
#include <cstdint>
#include <memory>

namespace remniw {

class AsmInstruction {
public:
    enum KindTy
    {
        Mov,
        Lea,
        Cmp,
        Jmp,
        Add,
        Sub,
        Imul,
        Idiv,
        Cqto,
        Call,
        Xor,
        Push,
        Pop,
        Ret,
        Label,
    };

    AsmInstruction(KindTy Kind): Kind(Kind) {}

    AsmInstruction(KindTy Kind, AsmOperand *Dst): Kind(Kind), Operands({Dst}) {}

    AsmInstruction(KindTy Kind, AsmOperand *Src, AsmOperand *Dst):
        Kind(Kind), Operands({Src, Dst}) {}

    void addOperand(AsmOperand *Op) { Operands.push_back(Op); }

    llvm::SmallVectorImpl<AsmOperand *> &getOperands() { return Operands; }

    const llvm::SmallVectorImpl<AsmOperand *> &getOperands() const { return Operands; }

    KindTy getInstKind() const { return Kind; }

    void print(llvm::raw_ostream &OS) const;

private:
    KindTy Kind;
    llvm::SmallVector<AsmOperand *, 2> Operands;
};

class AsmMovInst: public AsmInstruction {
public:
    AsmMovInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Mov, Src, Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Mov;
    }

    AsmOperand *getSrcOp() const { return getOperands()[0]; }
    AsmOperand *getDstOp() const { return getOperands()[1]; }
};

class AsmLeaInst: public AsmInstruction {
public:
    AsmLeaInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Lea, Src, Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Lea;
    }

    AsmOperand *getSrcOp() const { return getOperands()[0]; }
    AsmOperand *getDstOp() const { return getOperands()[1]; }
};

class AsmCmpInst: public AsmInstruction {
public:
    AsmCmpInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Cmp, Src, Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Cmp;
    }

    AsmOperand *getSrcOp() const { return getOperands()[0]; }
    AsmOperand *getDstOp() const { return getOperands()[1]; }
};

class AsmJmpInst: public AsmInstruction {
public:
    enum JmpKindTy
    {
        Jmp,
        Je,
        Jne,
        Jg,
        Jle
    };

    AsmJmpInst(AsmJmpInst::JmpKindTy JmpKind, AsmOperand *Op):
        AsmInstruction(AsmInstruction::Jmp, Op), JmpKind(JmpKind) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Jmp;
    }

    AsmJmpInst::JmpKindTy getJmpKind() const { return JmpKind; }
    AsmOperand *getOp() const { return getOperands()[0]; }

private:
    AsmJmpInst::JmpKindTy JmpKind;
};

class AsmAddInst: public AsmInstruction {
public:
    AsmAddInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Add, Src, Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Add;
    }

    AsmOperand *getSrcOp() const { return getOperands()[0]; }
    AsmOperand *getDstOp() const { return getOperands()[1]; }
};

class AsmSubInst: public AsmInstruction {
public:
    AsmSubInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Sub, Src, Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Sub;
    }

    AsmOperand *getSrcOp() const { return getOperands()[0]; }
    AsmOperand *getDstOp() const { return getOperands()[1]; }
};

class AsmImulInst: public AsmInstruction {
public:
    AsmImulInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Imul, Src, Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Imul;
    }

    AsmOperand *getSrcOp() const { return getOperands()[0]; }
    AsmOperand *getDstOp() const { return getOperands()[1]; }
};

class AsmIdivInst: public AsmInstruction {
public:
    AsmIdivInst(AsmOperand *Op): AsmInstruction(AsmInstruction::Idiv, Op) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Idiv;
    }

    AsmOperand *getOp() const { return getOperands()[0]; }
};

class AsmCqtoInst: public AsmInstruction {
public:
    AsmCqtoInst(): AsmInstruction(AsmInstruction::Cqto) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Cqto;
    }
};

class AsmCallInst: public AsmInstruction {
private:
    bool DirectCall;

public:
    AsmCallInst(AsmOperand *Callee, bool DirectCall):
        AsmInstruction(AsmInstruction::Call, Callee), DirectCall(DirectCall) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Call;
    }

    AsmOperand *getCalleeOp() const { return getOperands()[0]; }

    bool isDirectCall() const { return DirectCall; }
};

class AsmXorInst: public AsmInstruction {
public:
    AsmXorInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Xor, Src, Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Xor;
    }

    AsmOperand *getSrcOp() const { return getOperands()[0]; }
    AsmOperand *getDstOp() const { return getOperands()[1]; }
};

class AsmPushInst: public AsmInstruction {
public:
    AsmPushInst(AsmOperand *Op): AsmInstruction(AsmInstruction::Push, Op) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Push;
    }

    AsmOperand *getOp() const { return getOperands()[0]; }
};

class AsmPopInst: public AsmInstruction {
public:
    AsmPopInst(AsmOperand *Op): AsmInstruction(AsmInstruction::Pop, Op) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Pop;
    }

    AsmOperand *getOp() const { return getOperands()[0]; }
};

class AsmRetInst: public AsmInstruction {
public:
    AsmRetInst(): AsmInstruction(AsmInstruction::Ret) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Ret;
    }
};

class AsmLabelInst: public AsmInstruction {
public:
    AsmLabelInst(AsmOperand *LabelOp): AsmInstruction(AsmInstruction::Label, LabelOp) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Label;
    }

    AsmOperand *getLabelOp() const { return getOperands()[0]; }
};

}  // namespace remniw
