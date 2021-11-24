#pragma once

#include <cstdint>
#include <vector>
#include "llvm/Support/raw_ostream.h"

namespace remniw {

struct LiveRange {
    uint32_t StartPoint;
    uint32_t EndPoint;

    void print(llvm::raw_ostream &OS) const {
        OS << "[" << StartPoint << ", " << EndPoint << ")";
    }
};

struct LiveIntervalTy {
    std::vector<LiveRange> Ranges;
};

}  // namespace remniw
