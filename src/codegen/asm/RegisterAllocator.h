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

// struct LiveInterval {
//     enum Kind
//     {
//         VirtualRegister,
//         PhysicalResigter,
//         StackSlot,
//     };

//     Kind Kind_;
//     // [StartPoint, EndPoint)
//     unsigned StartPoint;
//     unsigned EndPoint;
//     unsigned Reg;
//     unsigned StackSlot_;

//     LiveInterval(Kind Kind_, unsigned StartPoint, unsigned EndPoint):
//         Kind_(Kind_), StartPoint(StartPoint), EndPoint(EndPoint), Reg(0),
//         StackSlot_(0) {}

//     bool isStackSlot() { return Kind_ == StackSlot && StackSlot_ != 0; }

//     bool isPhysicalRegister() { return Kind_ == PhysicalResigter && Reg != 0; }

//     void assignToPhysicalRegister(unsigned PhysReg) {
//         Kind_ = PhysicalResigter;
//         Reg = PhysReg;
//     }

//     void spillToStackSlot() {
//         Kind_ = StackSlot;
//         StackSlot_ = 1;
//     }

//     bool operator<(const LiveInterval &other) const {
//         return StartPoint < other.StartPoint;
//     }
// };

auto StartPointIncreasingOrder = [](const LiveInterval *LHS, const LiveInterval *RHS) {
    if (LHS->StartPoint != RHS->StartPoint)
        return LHS->StartPoint > RHS->StartPoint;
    else
        return LHS->EndPoint > RHS->EndPoint;
};

auto EndPointIncreasingOrder = [](const LiveInterval *LHS, const LiveInterval *RHS) {
    return LHS->EndPoint < RHS->EndPoint;
};

class LinearScanRegisterAllocator {
private:
    std::unordered_map<uint32_t, remniw::LiveRanges> &RegLiveRangesMap;
    std::vector<LiveInterval *> LiveIntervals;
    std::priority_queue<LiveInterval *, std::vector<LiveInterval *>,
                        decltype(StartPointIncreasingOrder)>
        Unhandled;
    std::vector<LiveInterval *> Fixed;
    std::vector<LiveInterval *> Active;
    std::vector<LiveInterval *> Spilled;
    std::map<unsigned, bool> FreeRegisters;
    std::unordered_map<uint32_t, uint32_t> VirtToPhysRegMap;

public:
    LinearScanRegisterAllocator(
        std::unordered_map<uint32_t, remniw::LiveRanges> &RegLiveRangesMap):
        RegLiveRangesMap(RegLiveRangesMap),
        Unhandled(StartPointIncreasingOrder) {
        FreeRegisters[Register::RAX] = true;
        FreeRegisters[Register::RDX] = true;
        FreeRegisters[Register::RCX] = true;
        FreeRegisters[Register::RBX] = true;
        FreeRegisters[Register::RSI] = true;
        FreeRegisters[Register::RDI] = true;
        FreeRegisters[Register::R8] = true;
        FreeRegisters[Register::R9] = true;
        FreeRegisters[Register::R10] = true;
        FreeRegisters[Register::R11] = true;
        FreeRegisters[Register::R12] = true;
        FreeRegisters[Register::R13] = true;
        FreeRegisters[Register::R14] = true;
        FreeRegisters[Register::R15] = true;
    }

    void LinearScan() {
        initIntervalSets();

        while (!Unhandled.empty()) {
            LiveInterval *LI = Unhandled.top();
            Unhandled.pop();
            std::sort(Active.begin(), Active.end(), EndPointIncreasingOrder);
            ExpireOldIntervals(LI);
            unsigned PhysReg = getAvailablePhysReg(LI);
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

    void setFreeRegisters(std::map<unsigned, bool> FR) { FreeRegisters = FR; }

    std::unordered_map<uint32_t, uint32_t> &getVirtToPhysRegMap() {
        return VirtToPhysRegMap;
    }

private:
    void initIntervalSets() {
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

    void ExpireOldIntervals(LiveInterval *LI) {
        for (auto it = Active.begin(); it != Active.end();) {
            if ((*it)->EndPoint > LI->StartPoint) {
                return;
            }
            FreeRegisters[(*it)->Reg] = true;
            it = Active.erase(it);
        }
    }

    unsigned getAvailablePhysReg(LiveInterval *LI) {
        for (auto p : FreeRegisters) {
            if (p.second == false)
                continue;
            bool ConflictWithFixed = false;
            for (auto FixReg : Fixed) {
                if (FixReg->Reg != p.first)
                    continue;
                if (FixReg->EndPoint > LI->StartPoint ||
                    FixReg->StartPoint < LI->EndPoint) {
                    ConflictWithFixed = true;
                    break;
                }
            }
            if (ConflictWithFixed) {
                continue;
            }
            // Find an available PhysReg
            return p.first;
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