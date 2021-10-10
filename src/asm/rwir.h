#ifndef __OLIVE_HEADER_INCLUDED__
#define __OLIVE_HEADER_INCLUDED__
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "helper.h"
#define Dummy 0
#define Ret 1
#define Br 2
#define Switch 3
#define IndirectBr 4
#define Invoke 5
#define Resume 6
#define Unreachable 7
#define CleanupRet 8
#define CatchRet 9
#define CatchSwitch 10
#define CallBr 11
#define FNeg 12
#define Add 13
#define FAdd 14
#define Sub 15
#define FSub 16
#define Mul 17
#define FMul 18
#define UDiv 19
#define SDiv 20
#define FDiv 21
#define URem 22
#define SRem 23
#define FRem 24
#define Shl 25
#define LShr 26
#define AShr 27
#define And 28
#define Or 29
#define Xor 30
#define Alloca 31
#define Load 32
#define Store 33
#define GetElementPtr 34
#define Fence 35
#define AtomicCmpXchg 36
#define AtomicRMW 37
#define Trunc 38
#define ZExt 39
#define SExt 40
#define FPToUI 41
#define FPToSI 42
#define UIToFP 43
#define SIToFP 44
#define FPTrunc 45
#define FPExt 46
#define PtrToInt 47
#define IntToPtr 48
#define BitCast 49
#define AddrSpaceCast 50
#define CleanupPad 51
#define CatchPad 52
#define ICmp 53
#define FCmp 54
#define PHI 55
#define Call 56
#define Select 57
#define UserOp1 58
#define UserOp2 59
#define VAArg 60
#define ExtractElement 61
#define InsertElement 62
#define ShuffleVector 63
#define ExtractValue 64
#define InsertValue 65
#define LandingPad 66
#define Freeze 67
#define REG 68
#define IMM 69
#define MEM 70
#define LABEL 71
#define ARGS 72
#define NOARGS 73
#define PTR 74
#define GlobalValue 75

struct burm_state {
  int op;
  NODEPTR node;
  struct burm_state **kids;
  COST cost[5];
  struct {
    unsigned burm_stmt:4;
    unsigned burm_reg:2;
    unsigned burm_imm:1;
    unsigned burm_mem:2;
  } rule;
};


struct burm_state *burm_label(NODEPTR);
struct burm_state *burm_label1(NODEPTR);

void dumpCover(NODEPTR,int,int);

#endif
