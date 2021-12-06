#pragma once

#include "Register.h"
#include "llvm/Support/raw_ostream.h"
#include <cassert>
#include <cstdint>
#include <memory>

namespace remniw {

struct AsmOperand {
    enum KindTy
    {
        Register,
        Memory,
        Immediate,
        LabelString
    } Kind;

    struct RegOp {
        uint32_t RegNo;
    };

    struct MemOp {
        int64_t Disp;
        uint32_t BaseReg;
        uint32_t IndexReg;
        uint32_t Scale;
    };

    struct ImmOp {
        int64_t Val;
    };

    struct LabelOp {
        const char* StringPtr;
        size_t StringSize;
        uint32_t UniqueCounter;  // Counter for tracking unique names
    };

    union {
        struct RegOp Reg;
        struct MemOp Mem;
        struct ImmOp Imm;
        struct LabelOp Label;
    };

    AsmOperand(KindTy Kind): Kind(Kind) {}

    static AsmOperand* createReg(uint32_t RegNo) {
        auto Res = new AsmOperand(KindTy::Register);
        Res->Reg.RegNo = RegNo;
        return Res;
    }

    static AsmOperand* createImm(int64_t Val) {
        auto Res = new AsmOperand(KindTy::Immediate);
        Res->Imm.Val = Val;
        return Res;
    }

    static AsmOperand* createMem(int64_t Disp, uint32_t BaseReg = Register::RBP,
                                 uint32_t IndexReg = Register::NoRegister,
                                 uint32_t Scale = 1) {
        auto Res = new AsmOperand(KindTy::Memory);
        Res->Mem.Disp = Disp;
        Res->Mem.BaseReg = BaseReg;
        Res->Mem.IndexReg = IndexReg;
        Res->Mem.Scale = Scale;
        return Res;
    }

    static AsmOperand* createLabel(const char* Ptr, size_t Size, uint32_t Counter = 0) {
        auto Res = new AsmOperand(KindTy::LabelString);
        Res->Label.StringPtr = Ptr;
        Res->Label.StringSize = Size;
        Res->Label.UniqueCounter = Counter;
        return Res;
    }

    bool isReg() const { return Kind == Register; }

    bool isVirtReg() const {
        return Kind == Register && Register::isVirtualRegister(Reg.RegNo);
    }

    bool isPhysReg() const {
        return Kind == Register && Register::isPhysicalRegister(Reg.RegNo);
    }

    bool isStackSlotReg() const {
        return Kind == Register && Register::isStackSlot(Reg.RegNo);
    }

    bool isMem() const { return Kind == Memory; }

    bool isImm() const { return Kind == Immediate; }

    uint32_t getReg() const {
        assert(Kind == Register && "Invalid access!");
        return Reg.RegNo;
    }

    uint32_t getMemDisp() const {
        assert(Kind == Memory && "Invalid access!");
        return Mem.Disp;
    }

    uint32_t getMemBaseReg() const {
        assert(Kind == Memory && "Invalid access!");
        return Mem.BaseReg;
    }

    uint32_t getMemIndexReg() const {
        assert(Kind == Memory && "Invalid access!");
        return Mem.IndexReg;
    }

    uint32_t getMemScale() const {
        assert(Kind == Memory && "Invalid access!");
        return Mem.Scale;
    }

    void print(llvm::raw_ostream& OS) const {
        switch (Kind) {
        case Register: OS << Register::convertRegisterToString(Reg.RegNo); break;
        case Immediate: OS << "$" << Imm.Val; break;
        case Memory:
            if (Mem.Disp != 0)
                OS << Mem.Disp;
            OS << "(";
            if (Mem.BaseReg)
                OS << Register::convertRegisterToString(Mem.BaseReg);
            if (Mem.IndexReg) {
                OS << ", " << Register::convertRegisterToString(Mem.IndexReg);
                OS << ", " << Mem.Scale;
            }
            OS << ")";
            break;
        case LabelString: OS << "TODO LabelString"; break;
        }
    }
};

}  // namespace remniw