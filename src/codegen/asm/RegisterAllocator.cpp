// #include "Register.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
namespace remniw {

struct LiveInterval {
    enum Kind
    {
        VirtualRegister,
        PhysicalResigter,
        StackSlot,
    };

    Kind Kind_;
    // [StartPoint, EndPoint)
    unsigned StartPoint;
    unsigned EndPoint;
    unsigned PhysReg_;
    unsigned StackSlot_;

    LiveInterval(Kind Kind_, unsigned StartPoint, unsigned EndPoint):
        Kind_(Kind_), StartPoint(StartPoint), EndPoint(EndPoint), PhysReg_(0),
        StackSlot_(0) {}

    bool isStackSlot() { return Kind_ == StackSlot && StackSlot_ != 0; }

    bool isPhysicalRegister() { return Kind_ == PhysicalResigter && PhysReg_ != 0; }

    void assignToPhysicalRegister(unsigned PhysReg) {
        Kind_ = PhysicalResigter;
        PhysReg_ = PhysReg;
    }

    void spillToStackSlot() {
        Kind_ = StackSlot;
        StackSlot_ = 1;
    }

    bool operator<(const LiveInterval &other) const {
        return StartPoint < other.StartPoint;
    }
};

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
    std::vector<LiveInterval *> LiveIntervals;
    std::priority_queue<LiveInterval *, std::vector<LiveInterval *>,
                        decltype(StartPointIncreasingOrder)>
        Unhandled;
    std::vector<LiveInterval *> Fixed;
    std::vector<LiveInterval *> Active;
    std::vector<LiveInterval *> Spilled;
    std::map<unsigned, bool> FreeRegisters;
    std::vector<unsigned> RegUse;

public:
    LinearScanRegisterAllocator(std::vector<LiveInterval *> LiveIntervals):
        LiveIntervals(LiveIntervals), Unhandled(StartPointIncreasingOrder) {}

    void LinearScan() {
        initIntervalSets();

        while (!Unhandled.empty()) {
            LiveInterval *LI = Unhandled.top();
            Unhandled.pop();
            std::sort(Active.begin(), Active.end(), EndPointIncreasingOrder);
            ExpireOldIntervals(LI);
            unsigned PhysReg = getAvailablePhysReg(LI);
            if (PhysReg != 0) {
                FreeRegisters[PhysReg] = false;
                LI->assignToPhysicalRegister(PhysReg);
                Active.push_back(LI);
            } else {
                spillAtInterval(LI);
            }
            printActive();
        }
    }

    void setFreeRegisters(std::map<unsigned, bool> FR) { FreeRegisters = FR; }

private:
    void initIntervalSets() {
        Active.clear();
        for (auto p : LiveIntervals) {
            if (p->isPhysicalRegister()) {
                Fixed.push_back(p);
            } else {
                Unhandled.push(p);
            }
        }
    }

    void ExpireOldIntervals(LiveInterval *LI) {
        for (auto it = Active.begin(); it != Active.end();) {
            if ((*it)->EndPoint > LI->StartPoint) {
                return;
            }
            FreeRegisters[(*it)->PhysReg_] = true;
            it = Active.erase(it);
        }
    }

    unsigned getAvailablePhysReg(LiveInterval *LI) {
        for (auto p : FreeRegisters) {
            if (p.second == false)
                continue;
            bool ConflictWithFixed = false;
            for (auto FixReg : Fixed) {
                if (FixReg->PhysReg_ != p.first)
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
        return 0;
    }

    void spillAtInterval(LiveInterval *LI) {
        if (!Active.empty() && Active.back()->EndPoint > LI->EndPoint) {
            Active.back()->spillToStackSlot();
            Active.pop_back();
            LI->PhysReg_ = Active.back()->PhysReg_;
            Active.push_back(LI);
        } else {
            LI->spillToStackSlot();
            Spilled.push_back(LI);
        }
    }

    void printActive() {
        for (auto LI : Active) {
            std::cout << "[" << LI->StartPoint << "," << LI->EndPoint << "]"
                      << " assigned " << LI->PhysReg_ << ":" << LI->StackSlot_
                      << std::endl;
        }
        for (auto LI : Spilled) {
            std::cout << "[" << LI->StartPoint << "," << LI->EndPoint << "]"
                      << " assigned " << LI->PhysReg_ << ":" << LI->StackSlot_
                      << std::endl;
        }
        for (auto LI : Fixed) {
            std::cout << "[" << LI->StartPoint << "," << LI->EndPoint << "]"
                      << " assigned " << LI->PhysReg_ << ":" << LI->StackSlot_
                      << std::endl;
        }
        std::cout << "======\n";
    }
};

}  // namespace remniw

using namespace remniw;

int main() {
    {
        std::map<unsigned, bool> FreeRegisters;
        FreeRegisters[1] = true;
        FreeRegisters[2] = true;
        std::vector<LiveInterval *> LiveIntervals;
        // A[1, 4)
        // B[2, 5)
        // C[3, 8)
        // D[4, 7)
        // E[5, 6)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 1, 4});
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 2, 5});
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 3, 8});
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 4, 7});
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 5, 6});
        remniw::LinearScanRegisterAllocator LSRA(LiveIntervals);
        LSRA.setFreeRegisters(FreeRegisters);
        // LSRA.LinearScan();
    }

    {
        std::map<unsigned, bool> FreeRegisters;
        FreeRegisters[1] = true;
        FreeRegisters[2] = true;
        FreeRegisters[3] = true;
        FreeRegisters[4] = true;
        std::vector<LiveInterval *> LiveIntervals;
        // a[1,2)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 1, 2});
        // b[1,4)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 1, 4});
        // c[1,3]
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 1, 3});
        // d[1,11)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 1, 11});
        // e[2, 9)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 2, 9});
        // f[3, 9)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 3, 9});
        // g[11,12)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 11, 12});
        remniw::LinearScanRegisterAllocator LSRA(LiveIntervals);
        LSRA.setFreeRegisters(FreeRegisters);
        // LSRA.LinearScan();
    }

    {
        std::map<unsigned, bool> FreeRegisters;
        FreeRegisters[1] = true;
        FreeRegisters[2] = true;
        FreeRegisters[3] = true;
        FreeRegisters[4] = true;
        std::vector<LiveInterval *> LiveIntervals;
        // a[1,2)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 1, 2});
        // b[1,4)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 1, 4});
        // c[1,3)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 1, 3});
        // d[1,11)
        auto d = new LiveInterval {LiveInterval::PhysicalResigter, 1, 11};
        d->PhysReg_ = 1;
        LiveIntervals.push_back(d);
        // e[2, 9)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 2, 9});
        // f[3, 9)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 3, 9});
        // g[11,12)
        LiveIntervals.push_back(new LiveInterval {LiveInterval::VirtualRegister, 11, 12});
        remniw::LinearScanRegisterAllocator LSRA(LiveIntervals);
        LSRA.setFreeRegisters(FreeRegisters);
        LSRA.LinearScan();
    }

    return 0;
}