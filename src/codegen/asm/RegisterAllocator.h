#pragma once

#include "Register.h"
#include <queue>
#include <set>
#include <iostream>

namespace remniw {

class RegisterAllocator {
public:
    RegisterAllocator(): Flip(false) {}
    Register getAvailableRegister() {
        // FIXME
        Register Ret = Flip ? Register::R14 : Register::R15;
        Flip = !Flip;
        return Ret;
    }

private:
    bool Flip;
};

using PhysRegType = unsigned;

struct LiveInterval {
    unsigned StartPoint;
    unsigned EndPoint;

    mutable PhysRegType PhysReg; // FIXME
    mutable unsigned StackSlot;
};

class LinearScanRegisterAllocator {
private:
    static auto StartPointIncreasingOrder = [](const LiveInterval &LHS, const LiveInterval &RHS) {
        return LHS.StartPoint > RHS.StartPoint;
    };
    static auto EndPointIncreasingOrder = [](const LiveInterval &LHS, const LiveInterval &RHS) {
        return LHS.EndPoint > RHS.EndPoint;
    };
    std::priority_queue<LiveInterval, std::vector<LiveInterval>, decltype(StartPointIncreasingOrder)> Unhandled;
    std::vector<LiveInterval> Fixed;
    std::set<LiveInterval, decltype(EndPointIncreasingOrder)> Active;
    std::unordered_map<PhysRegType, bool> FreeRegisters;
    std::vector<unsigned> RegUse;
public:
    void LinearScan() {
        initIntervalSets();

        Active.clear();
        while(!Unhandled.empty()) {
            LiveInterval LI = Unhandled.top();

            ExpireOldIntervals(LI);
            unsigned PhysReg = getAvailablePhysReg(LI);
            if (PhysReg != -1) {
                FreeRegisters[PhysReg] = false;
                LI.PhysReg = PhysReg;
                Active.insert(LI);
            } else {
                spillAtInterval(LI);
            }
            printActive();

            Unhandled.pop();
        }
    }
private:
    void initIntervalSets()
    {
        FreeRegisters[0] = true;
        FreeRegisters[1] = true;

        // A[1, 4]
        // B[2, 5]
        // C[3, 8]
        // D[4, 7]
        // E[5, 6]
        Unhandled.push({1, 4, 0, 0});
        Unhandled.push({2, 5, 0, 0});
        Unhandled.push({3, 8, 0, 0});
        Unhandled.push({4, 7, 0, 0});
        Unhandled.push({5, 6, 0, 0});
    }

    void ExpireOldIntervals(const LiveInterval &LI) {
        for(auto it = Active.begin(), e = Active.end(); it != e; ) {
            if (it->EndPoint > LI.StartPoint) {
                return;
            }
            FreeRegisters[it->PhysReg] = true;
            it = Active.erase(it);
        }
    }

    unsigned getAvailablePhysReg(const LiveInterval &LI) {
        for (auto p : FreeRegisters) {
            if (p.second == false)
                continue;
            bool ConflictWithFixed = false;
            for (auto& FixReg: Fixed) {
                if (FixReg.PhysReg != p.first)
                    continue;
                if (FixReg.EndPoint > LI.StartPoint ||
                    FixReg.StartPoint < LI.EndPoint) {
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
        return -1;
    }

    void spillAtInterval(LiveInterval& LI) {
        auto it = std::prev(Active.end());
        if (it->EndPoint > LI.EndPoint) {
            LI.PhysReg = it->PhysReg;
            it->StackSlot = 1;
            Active.erase(it);
            Active.insert(LI);
        }
        else {
            LI.StackSlot = 1;
        }
    }

    void printActive() {
        for(auto &it : Active) {
            std::cout << "[" << it.StartPoint << "," << it.EndPoint << "]"
                      << "assigned " << it.PhysReg << ":" << it.StackSlot;
        }
    }
};

}  // namespace remniw