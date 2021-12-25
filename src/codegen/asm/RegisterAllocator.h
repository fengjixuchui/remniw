#pragma once

#include "LiveInterval.h"
#include "Register.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>

namespace remniw {

struct LiveIntervalStartPointIncreasingOrderCompare
    : public std::binary_function<LiveInterval *, LiveInterval *, bool> {
    bool operator()(const LiveInterval *LHS, const LiveInterval *RHS) const {
        return LHS->StartPoint > RHS->StartPoint ||
               (LHS->StartPoint == RHS->StartPoint && LHS->EndPoint > RHS->EndPoint);
    }
};

struct LiveIntervalEndPointIncreasingOrderCompare
    : public std::binary_function<LiveInterval *, LiveInterval *, bool> {
    bool operator()(const LiveInterval *LHS, const LiveInterval *RHS) const {
        return LHS->EndPoint < RHS->EndPoint;
    }
};

class LinearScanRegisterAllocator {
private:
    AsmFunction &AsmFunc;
    std::vector<LiveInterval *> LiveIntervals;
    std::priority_queue<LiveInterval *, std::vector<LiveInterval *>,
                        LiveIntervalStartPointIncreasingOrderCompare>
        Unhandled;
    std::vector<LiveInterval *> Fixed;
    std::vector<LiveInterval *> Active;
    std::vector<LiveInterval *> Spilled;
    llvm::SmallVector<bool, 32> FreeRegisters;
    std::unordered_map<uint32_t, uint32_t> VirtToPhysRegMap;

public:
    LinearScanRegisterAllocator(
        AsmFunction &AsmFunc,
        std::unordered_map<uint32_t, remniw::LiveRanges> &RegLiveRangesMap):
        AsmFunc(AsmFunc) {
        initIntervalSets(RegLiveRangesMap);
        initFreeRegisters();
    }

    void LinearScan() {
        while (!Unhandled.empty()) {
            LiveInterval *LI = Unhandled.top();
            Unhandled.pop();
            std::sort(Active.begin(), Active.end(),
                      LiveIntervalEndPointIncreasingOrderCompare());
            ExpireOldIntervals(LI);
            uint32_t PhysReg = getAvailablePhysReg(LI);
            if (PhysReg != Register::NoRegister) {
                FreeRegisters[PhysReg] = false;
                VirtToPhysRegMap[LI->Reg] = PhysReg;
                LI->Reg = PhysReg;
                Active.push_back(LI);
            } else {
                spillAtInterval(LI);
            }
            printActive();
        }

        std::cout << "===VirtToPhysRegMap===\n";
        for (const auto &p : VirtToPhysRegMap) {
            std::cout << p.first << " ==>> "
                      << Register::convertRegisterToString(p.second) << "\n";
        }
    }

    std::unordered_map<uint32_t, uint32_t> &getVirtToPhysRegMap() {
        return VirtToPhysRegMap;
    }

private:
    void
    initIntervalSets(std::unordered_map<uint32_t, remniw::LiveRanges> &RegLiveRangesMap) {
        Active.clear();
        for (const auto &p : RegLiveRangesMap) {
            if (Register::isVirtualRegister(p.first)) {
                Unhandled.push(new LiveInterval({p.second.Ranges[0].StartPoint,
                                                 p.second.Ranges[0].EndPoint, p.first}));
            }
            if (Register::isPhysicalRegister(p.first)) {
                for (const auto &Range : p.second.Ranges) {
                    Fixed.push_back(
                        new LiveInterval({Range.StartPoint, Range.EndPoint, p.first}));
                }
            }
        }
    }

    void initFreeRegisters() {
        FreeRegisters.resize(16 /*number of registers*/ + 1);
        FreeRegisters[Register::NoRegister /*0*/] = false;
        // Caller saved registers
        FreeRegisters[Register::RAX /*1*/] = true;
        FreeRegisters[Register::RDI /*2*/] = true;
        FreeRegisters[Register::RSI /*3*/] = true;
        FreeRegisters[Register::RDX /*4*/] = true;
        FreeRegisters[Register::RCX /*5*/] = true;
        FreeRegisters[Register::R8 /*6*/] = true;
        FreeRegisters[Register::R9 /*7*/] = true;
        FreeRegisters[Register::R10 /*8*/] = true;
        FreeRegisters[Register::R11 /*9*/] = true;
        // Callee saved registers
        FreeRegisters[Register::RSP /*10*/] = false;
        FreeRegisters[Register::RBP /*11*/] = false;
        FreeRegisters[Register::RBX /*12*/] = true;
        FreeRegisters[Register::R12 /*13*/] = true;
        FreeRegisters[Register::R13 /*14*/] = true;
        FreeRegisters[Register::R14 /*15*/] = true;
        FreeRegisters[Register::R15 /*16*/] = true;
    }
    void ExpireOldIntervals(LiveInterval *LI) {
        for (auto it = Active.begin(); it != Active.end();) {
            if ((*it)->EndPoint > LI->StartPoint) {
                return;
            }
            FreeRegisters[(*it)->Reg] = true;
            it = Active.erase(it);
        }
    }

    uint32_t getAvailablePhysReg(LiveInterval *LI) {
        bool UsedAcrossFunctionCall = false;
        for (uint32_t i = LI->StartPoint; i < LI->EndPoint; ++i) {
            if (llvm::isa<AsmCallInst>(AsmFunc.Instructions[i - 1])) {
                UsedAcrossFunctionCall = true;
                break;
            }
        }

        for (uint32_t Reg = 0, e = FreeRegisters.size(); Reg != e; ++Reg) {
            if (FreeRegisters[Reg] == false)
                continue;
            bool ConflictWithFixed = false;
            for (auto FixReg : Fixed) {
                if (FixReg->Reg != Reg)
                    continue;
                if (FixReg->EndPoint > LI->StartPoint ||
                    FixReg->StartPoint < LI->EndPoint) {
                    ConflictWithFixed = true;
                    break;
                }
            }
            if (ConflictWithFixed)
                continue;

            if (UsedAcrossFunctionCall && !Register::isCalleeSavedRegister(Reg))
                continue;
            if (!UsedAcrossFunctionCall && !Register::isCallerSavedRegister(Reg))
                continue;

            // Find an available PhysReg
            return Reg;
        }

        // non-avaliable PhysReg
        return Register::NoRegister;
    }

    void spillAtInterval(LiveInterval *LI) {
        static uint32_t StackSlotIndex = 0;
        if (!Active.empty() && Active.back()->EndPoint > LI->EndPoint) {
            LI->Reg = Active.back()->Reg;
            Active.back()->Reg = Register::index2StackSlot(StackSlotIndex++);
            Active.pop_back();
            Active.push_back(LI);
        } else {
            LI->Reg = Register::index2StackSlot(StackSlotIndex++);
            Spilled.push_back(LI);
        }
    }

    void printActive() {
        for (auto LI : Active) {
            std::cout << "[" << LI->StartPoint << "," << LI->EndPoint << ")"
                      << " assigned " << Register::convertRegisterToString(LI->Reg)
                      << std::endl;
        }
        for (auto LI : Spilled) {
            std::cout << "[" << LI->StartPoint << "," << LI->EndPoint << ")"
                      << " assigned " << Register::convertRegisterToString(LI->Reg)
                      << std::endl;
        }
        for (auto LI : Fixed) {
            std::cout << "[" << LI->StartPoint << "," << LI->EndPoint << ")"
                      << " assigned " << Register::convertRegisterToString(LI->Reg)
                      << std::endl;
        }
        std::cout << "======\n";
    }
};

}  // namespace remniw
