#pragma once

#include "AsmOperand.h"
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
    };

    AsmInstruction(KindTy Kind): Kind(Kind) {}

    KindTy getInstKind() const { return Kind; }

    void print(llvm::raw_ostream &OS) const;

private:
    KindTy Kind;
};

class AsmMovInst: public AsmInstruction {
private:
    AsmOperand *Src;
    AsmOperand *Dst;

public:
    AsmMovInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Mov), Src(Src), Dst(Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Mov;
    }

    AsmOperand *getSrcOp() const { return Src; }
    AsmOperand *getDstOp() const { return Dst; }
};

class AsmLeaInst: public AsmInstruction {
private:
    AsmOperand *Src;
    AsmOperand *Dst;

public:
    AsmLeaInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Lea), Src(Src), Dst(Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Lea;
    }

    AsmOperand *getSrcOp() const { return Src; }
    AsmOperand *getDstOp() const { return Dst; }
};

class AsmCmpInst: public AsmInstruction {
private:
    AsmOperand *Src;
    AsmOperand *Dst;

public:
    AsmCmpInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Cmp), Src(Src), Dst(Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Cmp;
    }

    AsmOperand *getSrcOp() const { return Src; }
    AsmOperand *getDstOp() const { return Dst; }
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
        AsmInstruction(AsmInstruction::Jmp), JmpKind(JmpKind), Op(Op) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Jmp;
    }

    AsmJmpInst::JmpKindTy getJmpKind() const { return JmpKind; }
    AsmOperand *getOp() const { return Op; }

private:
    AsmJmpInst::JmpKindTy JmpKind;
    AsmOperand *Op;
};

class AsmAddInst: public AsmInstruction {
private:
    AsmOperand *Src;
    AsmOperand *Dst;

public:
    AsmAddInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Add), Src(Src), Dst(Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Add;
    }

    AsmOperand *getSrcOp() const { return Src; }
    AsmOperand *getDstOp() const { return Dst; }
};

class AsmSubInst: public AsmInstruction {
private:
    AsmOperand *Src;
    AsmOperand *Dst;

public:
    AsmSubInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Sub), Src(Src), Dst(Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Sub;
    }

    AsmOperand *getSrcOp() const { return Src; }
    AsmOperand *getDstOp() const { return Dst; }
};

class AsmImulInst: public AsmInstruction {
private:
    AsmOperand *Src;
    AsmOperand *Dst;

public:
    AsmImulInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Imul), Src(Src), Dst(Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Imul;
    }

    AsmOperand *getSrcOp() const { return Src; }
    AsmOperand *getDstOp() const { return Dst; }
};

class AsmIdivInst: public AsmInstruction {
private:
    AsmOperand *Op;

public:
    AsmIdivInst(AsmOperand *Op): AsmInstruction(AsmInstruction::Idiv), Op(Op) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Idiv;
    }

    AsmOperand *getOp() const { return Op; }
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
    AsmOperand *Callee;
    bool DirectCall;

public:
    AsmCallInst(AsmOperand *Callee, bool DirectCall):
        AsmInstruction(AsmInstruction::Call), Callee(Callee), DirectCall(DirectCall) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Call;
    }

    AsmOperand *getCalleeOp() const { return Callee; }

    bool isDirectCall() const { return DirectCall; }
};

class AsmXorInst: public AsmInstruction {
private:
    AsmOperand *Src;
    AsmOperand *Dst;

public:
    AsmXorInst(AsmOperand *Src, AsmOperand *Dst):
        AsmInstruction(AsmInstruction::Xor), Src(Src), Dst(Dst) {}

    static bool classof(const AsmInstruction *I) {
        return I->getInstKind() == AsmInstruction::Xor;
    }

    AsmOperand *getSrcOp() const { return Src; }
    AsmOperand *getDstOp() const { return Dst; }
};

}  // namespace remniw
