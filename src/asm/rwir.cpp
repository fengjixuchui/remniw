#include "rwir.h"
#define burm_stmt_NT 1
#define burm_reg_NT 2
#define burm_imm_NT 3
#define burm_mem_NT 4
#define burm_label_NT 5
#define burm_cond_NT 6
#define burm_arg_NT 7
#define burm_args_NT 8
extern int burm_max_nt;


void stmt_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void reg_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void imm_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void mem_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void label_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void cond_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void arg_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen, unsigned argNo);


void args_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen, unsigned argNo);
#ifndef ALLOC
#define ALLOC(n) malloc(n)
#endif

#ifndef burm_assert
#define burm_assert(x,y) if (!(x)) {  y; abort(); }
#endif

static NODEPTR burm_np;

#define burm_stmt_NT 1
#define burm_reg_NT 2
#define burm_imm_NT 3
#define burm_mem_NT 4
#define burm_label_NT 5
#define burm_cond_NT 6
#define burm_arg_NT 7
#define burm_args_NT 8
extern int burm_max_nt;
int burm_max_nt = 8;

std::string burm_ntname[] = {
  "",
  "stmt",
  "reg",
  "imm",
  "mem",
  "label",
  "cond",
  "arg",
  "args",
  ""
};

static short burm_nts_0[] = { 0 };
static short burm_nts_1[] = { burm_imm_NT, 0 };
static short burm_nts_2[] = { burm_mem_NT, 0 };
static short burm_nts_3[] = { burm_reg_NT, 0 };
static short burm_nts_4[] = { burm_reg_NT, burm_mem_NT, 0 };
static short burm_nts_5[] = { burm_reg_NT, burm_reg_NT, 0 };
static short burm_nts_6[] = { burm_imm_NT, burm_reg_NT, 0 };
static short burm_nts_7[] = { burm_imm_NT, burm_mem_NT, 0 };
static short burm_nts_8[] = { burm_mem_NT, burm_mem_NT, 0 };
static short burm_nts_9[] = { burm_label_NT, burm_mem_NT, 0 };
static short burm_nts_10[] = { burm_reg_NT, burm_imm_NT, 0 };
static short burm_nts_11[] = { burm_cond_NT, burm_label_NT, burm_label_NT, 0 };
static short burm_nts_12[] = { burm_label_NT, 0 };
static short burm_nts_13[] = { burm_imm_NT, burm_imm_NT, 0 };
static short burm_nts_14[] = { burm_arg_NT, burm_args_NT, 0 };
static short burm_nts_15[] = { burm_label_NT, burm_args_NT, 0 };
static short burm_nts_16[] = { burm_reg_NT, burm_args_NT, 0 };
static short burm_nts_17[] = { burm_mem_NT, burm_args_NT, 0 };

short *burm_nts[] = {
  burm_nts_0,  /* 0 */
  burm_nts_0,  /* 1 */
  burm_nts_0,  /* 2 */
  burm_nts_1,  /* 3 */
  burm_nts_2,  /* 4 */
  burm_nts_3,  /* 5 */
  burm_nts_3,  /* 6 */
  burm_nts_3,  /* 7 */
  burm_nts_1,  /* 8 */
  burm_nts_4,  /* 9 */
  burm_nts_5,  /* 10 */
  burm_nts_6,  /* 11 */
  burm_nts_7,  /* 12 */
  burm_nts_8,  /* 13 */
  burm_nts_9,  /* 14 */
  burm_nts_5,  /* 15 */
  burm_nts_10,  /* 16 */
  burm_nts_6,  /* 17 */
  burm_nts_11,  /* 18 */
  burm_nts_12,  /* 19 */
  burm_nts_5,  /* 20 */
  burm_nts_10,  /* 21 */
  burm_nts_6,  /* 22 */
  burm_nts_13,  /* 23 */
  burm_nts_5,  /* 24 */
  burm_nts_10,  /* 25 */
  burm_nts_6,  /* 26 */
  burm_nts_13,  /* 27 */
  burm_nts_5,  /* 28 */
  burm_nts_10,  /* 29 */
  burm_nts_6,  /* 30 */
  burm_nts_13,  /* 31 */
  burm_nts_5,  /* 32 */
  burm_nts_10,  /* 33 */
  burm_nts_6,  /* 34 */
  burm_nts_13,  /* 35 */
  burm_nts_3,  /* 36 */
  burm_nts_1,  /* 37 */
  burm_nts_2,  /* 38 */
  burm_nts_12,  /* 39 */
  burm_nts_0,  /* 40 */
  burm_nts_14,  /* 41 */
  burm_nts_15,  /* 42 */
  burm_nts_16,  /* 43 */
  burm_nts_17,  /* 44 */
};

char burm_arity[] = {
  0,  /* 0=Undef */
  1,  /* 1=Ret */
  3,  /* 2=Br */
  0,  /* 3=Switch */
  0,  /* 4=IndirectBr */
  0,  /* 5=Invoke */
  0,  /* 6=Resume */
  0,  /* 7=Unreachable */
  0,  /* 8=CleanupRet */
  0,  /* 9=CatchRet */
  0,  /* 10=CatchSwitch */
  0,  /* 11=CallBr */
  0,  /* 12=FNeg */
  2,  /* 13=Add */
  0,  /* 14=FAdd */
  2,  /* 15=Sub */
  0,  /* 16=FSub */
  2,  /* 17=Mul */
  0,  /* 18=FMul */
  0,  /* 19=UDiv */
  2,  /* 20=SDiv */
  0,  /* 21=FDiv */
  0,  /* 22=URem */
  0,  /* 23=SRem */
  0,  /* 24=FRem */
  0,  /* 25=Shl */
  0,  /* 26=LShr */
  0,  /* 27=AShr */
  0,  /* 28=And */
  0,  /* 29=Or */
  0,  /* 30=Xor */
  1,  /* 31=Alloca */
  1,  /* 32=Load */
  2,  /* 33=Store */
  0,  /* 34=GetElementPtr */
  0,  /* 35=Fence */
  0,  /* 36=AtomicCmpXchg */
  0,  /* 37=AtomicRMW */
  0,  /* 38=Trunc */
  0,  /* 39=ZExt */
  0,  /* 40=SExt */
  0,  /* 41=FPToUI */
  0,  /* 42=FPToSI */
  0,  /* 43=UIToFP */
  0,  /* 44=SIToFP */
  0,  /* 45=FPTrunc */
  0,  /* 46=FPExt */
  0,  /* 47=PtrToInt */
  0,  /* 48=IntToPtr */
  0,  /* 49=BitCast */
  0,  /* 50=AddrSpaceCast */
  0,  /* 51=CleanupPad */
  0,  /* 52=CatchPad */
  2,  /* 53=ICmp */
  0,  /* 54=FCmp */
  0,  /* 55=PHI */
  2,  /* 56=Call */
  0,  /* 57=Select */
  0,  /* 58=UserOp1 */
  0,  /* 59=UserOp2 */
  0,  /* 60=VAArg */
  0,  /* 61=ExtractElement */
  0,  /* 62=InsertElement */
  0,  /* 63=ShuffleVector */
  0,  /* 64=ExtractValue */
  0,  /* 65=InsertValue */
  0,  /* 66=LandingPad */
  0,  /* 67=Freeze */
  0,  /* 68=Const */
  0,  /* 69=Label */
  2,  /* 70=Args */
  0,  /* 71=Reg */
};

std::string burm_opname[] = {
  /* 0 */  "Undef",
  /* 1 */  "Ret",
  /* 2 */  "Br",
  /* 3 */  "Switch",
  /* 4 */  "IndirectBr",
  /* 5 */  "Invoke",
  /* 6 */  "Resume",
  /* 7 */  "Unreachable",
  /* 8 */  "CleanupRet",
  /* 9 */  "CatchRet",
  /* 10 */  "CatchSwitch",
  /* 11 */  "CallBr",
  /* 12 */  "FNeg",
  /* 13 */  "Add",
  /* 14 */  "FAdd",
  /* 15 */  "Sub",
  /* 16 */  "FSub",
  /* 17 */  "Mul",
  /* 18 */  "FMul",
  /* 19 */  "UDiv",
  /* 20 */  "SDiv",
  /* 21 */  "FDiv",
  /* 22 */  "URem",
  /* 23 */  "SRem",
  /* 24 */  "FRem",
  /* 25 */  "Shl",
  /* 26 */  "LShr",
  /* 27 */  "AShr",
  /* 28 */  "And",
  /* 29 */  "Or",
  /* 30 */  "Xor",
  /* 31 */  "Alloca",
  /* 32 */  "Load",
  /* 33 */  "Store",
  /* 34 */  "GetElementPtr",
  /* 35 */  "Fence",
  /* 36 */  "AtomicCmpXchg",
  /* 37 */  "AtomicRMW",
  /* 38 */  "Trunc",
  /* 39 */  "ZExt",
  /* 40 */  "SExt",
  /* 41 */  "FPToUI",
  /* 42 */  "FPToSI",
  /* 43 */  "UIToFP",
  /* 44 */  "SIToFP",
  /* 45 */  "FPTrunc",
  /* 46 */  "FPExt",
  /* 47 */  "PtrToInt",
  /* 48 */  "IntToPtr",
  /* 49 */  "BitCast",
  /* 50 */  "AddrSpaceCast",
  /* 51 */  "CleanupPad",
  /* 52 */  "CatchPad",
  /* 53 */  "ICmp",
  /* 54 */  "FCmp",
  /* 55 */  "PHI",
  /* 56 */  "Call",
  /* 57 */  "Select",
  /* 58 */  "UserOp1",
  /* 59 */  "UserOp2",
  /* 60 */  "VAArg",
  /* 61 */  "ExtractElement",
  /* 62 */  "InsertElement",
  /* 63 */  "ShuffleVector",
  /* 64 */  "ExtractValue",
  /* 65 */  "InsertValue",
  /* 66 */  "LandingPad",
  /* 67 */  "Freeze",
  /* 68 */  "Const",
  /* 69 */  "Label",
  /* 70 */  "Args",
  /* 71 */  "Reg",
};


std::string burm_string[] = {
  /* 0 */  "label: Label",
  /* 1 */  "imm: Const",
  /* 2 */  "reg: Reg",
  /* 3 */  "mem: Alloca(imm)",
  /* 4 */  "reg: Load(mem)",
  /* 5 */  "reg: Load(reg)",
  /* 6 */  "stmt: reg",
  /* 7 */  "stmt: Ret(reg)",
  /* 8 */  "stmt: Ret(imm)",
  /* 9 */  "stmt: Store(reg,mem)",
  /* 10 */  "stmt: Store(reg,reg)",
  /* 11 */  "stmt: Store(imm,reg)",
  /* 12 */  "stmt: Store(imm,mem)",
  /* 13 */  "stmt: Store(mem,mem)",
  /* 14 */  "stmt: Store(label,mem)",
  /* 15 */  "cond: ICmp(reg,reg)",
  /* 16 */  "cond: ICmp(reg,imm)",
  /* 17 */  "cond: ICmp(imm,reg)",
  /* 18 */  "stmt: Br(cond,label,label)",
  /* 19 */  "stmt: Br(label,Undef,Undef)",
  /* 20 */  "reg: Add(reg,reg)",
  /* 21 */  "reg: Add(reg,imm)",
  /* 22 */  "reg: Add(imm,reg)",
  /* 23 */  "reg: Add(imm,imm)",
  /* 24 */  "reg: Sub(reg,reg)",
  /* 25 */  "reg: Sub(reg,imm)",
  /* 26 */  "reg: Sub(imm,reg)",
  /* 27 */  "reg: Sub(imm,imm)",
  /* 28 */  "reg: Mul(reg,reg)",
  /* 29 */  "reg: Mul(reg,imm)",
  /* 30 */  "reg: Mul(imm,reg)",
  /* 31 */  "reg: Mul(imm,imm)",
  /* 32 */  "reg: SDiv(reg,reg)",
  /* 33 */  "reg: SDiv(reg,imm)",
  /* 34 */  "reg: SDiv(imm,reg)",
  /* 35 */  "reg: SDiv(imm,imm)",
  /* 36 */  "arg: reg",
  /* 37 */  "arg: imm",
  /* 38 */  "arg: mem",
  /* 39 */  "arg: label",
  /* 40 */  "args: Args(Undef,Undef)",
  /* 41 */  "args: Args(arg,args)",
  /* 42 */  "reg: Call(label,args)",
  /* 43 */  "reg: Call(reg,args)",
  /* 44 */  "reg: Call(mem,args)",
};


std::string burm_files[] = {
"rwir.brg",
};

int burm_file_numbers[] = {
  /* 0 */  0,
  /* 1 */  0,
  /* 2 */  0,
  /* 3 */  0,
  /* 4 */  0,
  /* 5 */  0,
  /* 6 */  0,
  /* 7 */  0,
  /* 8 */  0,
  /* 9 */  0,
  /* 10 */  0,
  /* 11 */  0,
  /* 12 */  0,
  /* 13 */  0,
  /* 14 */  0,
  /* 15 */  0,
  /* 16 */  0,
  /* 17 */  0,
  /* 18 */  0,
  /* 19 */  0,
  /* 20 */  0,
  /* 21 */  0,
  /* 22 */  0,
  /* 23 */  0,
  /* 24 */  0,
  /* 25 */  0,
  /* 26 */  0,
  /* 27 */  0,
  /* 28 */  0,
  /* 29 */  0,
  /* 30 */  0,
  /* 31 */  0,
  /* 32 */  0,
  /* 33 */  0,
  /* 34 */  0,
  /* 35 */  0,
  /* 36 */  0,
  /* 37 */  0,
  /* 38 */  0,
  /* 39 */  0,
  /* 40 */  0,
  /* 41 */  0,
  /* 42 */  0,
  /* 43 */  0,
  /* 44 */  0,
};

int burm_line_numbers[] = {
  /* 0 */  108,
  /* 1 */  110,
  /* 2 */  112,
  /* 3 */  114,
  /* 4 */  117,
  /* 5 */  128,
  /* 6 */  140,
  /* 7 */  149,
  /* 8 */  156,
  /* 9 */  163,
  /* 10 */  171,
  /* 11 */  180,
  /* 12 */  189,
  /* 13 */  197,
  /* 14 */  208,
  /* 15 */  216,
  /* 16 */  227,
  /* 17 */  238,
  /* 18 */  254,
  /* 19 */  291,
  /* 20 */  301,
  /* 21 */  313,
  /* 22 */  325,
  /* 23 */  337,
  /* 24 */  348,
  /* 25 */  360,
  /* 26 */  372,
  /* 27 */  385,
  /* 28 */  396,
  /* 29 */  408,
  /* 30 */  420,
  /* 31 */  432,
  /* 32 */  443,
  /* 33 */  457,
  /* 34 */  473,
  /* 35 */  487,
  /* 36 */  504,
  /* 37 */  517,
  /* 38 */  530,
  /* 39 */  543,
  /* 40 */  556,
  /* 41 */  561,
  /* 42 */  569,
  /* 43 */  587,
  /* 44 */  600,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

static short burm_decode_stmt[] = {
   -1,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  18,
  19,
};

static short burm_decode_reg[] = {
   -1,
  2,
  4,
  5,
  20,
  21,
  22,
  23,
  24,
  25,
  26,
  27,
  28,
  29,
  30,
  31,
  32,
  33,
  34,
  35,
  42,
  43,
  44,
};

static short burm_decode_imm[] = {
   -1,
  1,
};

static short burm_decode_mem[] = {
   -1,
  3,
};

static short burm_decode_label[] = {
   -1,
  0,
};

static short burm_decode_cond[] = {
   -1,
  15,
  16,
  17,
};

static short burm_decode_arg[] = {
   -1,
  36,
  37,
  38,
  39,
};

static short burm_decode_args[] = {
   -1,
  40,
  41,
};

int burm_rule(struct burm_state *state, int goalnt) {
  burm_assert(goalnt >= 1 && goalnt <= 8,
        PANIC("Bad goal nonterminal %d in burm_rule\n", goalnt));
  if (!state)
    return 0;
  switch (goalnt) {
  case burm_stmt_NT:  return burm_decode_stmt[((struct burm_state *)state)->rule.burm_stmt];
  case burm_reg_NT:  return burm_decode_reg[((struct burm_state *)state)->rule.burm_reg];
  case burm_imm_NT:  return burm_decode_imm[((struct burm_state *)state)->rule.burm_imm];
  case burm_mem_NT:  return burm_decode_mem[((struct burm_state *)state)->rule.burm_mem];
  case burm_label_NT:  return burm_decode_label[((struct burm_state *)state)->rule.burm_label];
  case burm_cond_NT:  return burm_decode_cond[((struct burm_state *)state)->rule.burm_cond];
  case burm_arg_NT:  return burm_decode_arg[((struct burm_state *)state)->rule.burm_arg];
  case burm_args_NT:  return burm_decode_args[((struct burm_state *)state)->rule.burm_args];
  default:
    burm_assert(0, PANIC("Bad goal nonterminal %d in burm_rule\n", goalnt));
  }
  return 0;
}


struct burm_action {
  int nt;
  struct burm_state* st;
};

#ifndef RULE
#define RULE(n,s) \
    (act = (burm_action*) malloc(sizeof(struct burm_action)),act->nt=n,act->st=s,act)
#endif

int burm_cost_code(COST *_c, int _ern,struct burm_state *_s)
{
  NODEPTR *_children;
  struct burm_action *act;
  switch(_ern){
  default:
    DEFAULT_COST;
  case 0:
{


 (*_c).cost = 0; 
}
  break;
  case 1:
{


 (*_c).cost = 0; 
}
  break;
  case 2:
{


 (*_c).cost = 0; 
}
  break;
  case 3:
{


 (*_c).cost = 0; 
}
  break;
  case 4:
{


 (*_c).cost = _s->kids[0]->cost[burm_mem_NT].cost + 1; 
}
  break;
  case 5:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 6:
{


 (*_c).cost = _s->cost[burm_reg_NT].cost; 
}
  break;
  case 7:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 8:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 9:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_mem_NT].cost + 1; 
}
  break;
  case 10:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 11:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 12:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_mem_NT].cost + 1; 
}
  break;
  case 13:
{


 (*_c).cost = _s->kids[0]->cost[burm_mem_NT].cost + _s->kids[1]->cost[burm_mem_NT].cost + 1; 
}
  break;
  case 14:
{


 (*_c).cost = _s->kids[0]->cost[burm_label_NT].cost + _s->kids[1]->cost[burm_mem_NT].cost + 1; 
}
  break;
  case 15:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 16:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 17:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 18:
{


 (*_c).cost = _s->kids[0]->cost[burm_cond_NT].cost + _s->kids[1]->cost[burm_label_NT].cost + _s->kids[2]->cost[burm_label_NT].cost + 1; 
}
  break;
  case 19:
{


 (*_c).cost = _s->kids[0]->cost[burm_label_NT].cost + 1; 
}
  break;
  case 20:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 21:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 22:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 23:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 24:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 25:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 26:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 2; 
}
  break;
  case 27:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 28:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 29:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 30:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 31:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 32:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 2; 
}
  break;
  case 33:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 3; 
}
  break;
  case 34:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 2; 
}
  break;
  case 35:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 3; 
}
  break;
  case 36:
{


 (*_c).cost = _s->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 37:
{


 (*_c).cost = _s->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 38:
{


 (*_c).cost = _s->cost[burm_mem_NT].cost + 1; 
}
  break;
  case 39:
{


 (*_c).cost = _s->cost[burm_label_NT].cost + 1; 
}
  break;
  case 40:
{


 (*_c).cost = 0; 
}
  break;
  case 41:
{


 (*_c).cost = _s->kids[0]->cost[burm_arg_NT].cost + _s->kids[1]->cost[burm_args_NT].cost; 
}
  break;
  case 42:
{


 (*_c).cost = _s->kids[0]->cost[burm_label_NT].cost + 1; 
}
  break;
  case 43:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 44:
{


 (*_c).cost = _s->kids[0]->cost[burm_mem_NT].cost + 1; 
}
  break;
  }
  return 1;
}


void stmt_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void reg_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void imm_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void mem_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void label_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void cond_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen);


void arg_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen, unsigned argNo);


void args_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen, unsigned argNo);


#include <stdarg.h>

void burm_exec(struct burm_state *state, int nterm, ...) 
{
  va_list(ap);
  va_start(ap,nterm);

  burm_assert(nterm >= 1 && nterm <= 8,
        PANIC("Bad nonterminal %d in $exec\n", nterm));

  if (state)
    switch (nterm) {
    case burm_stmt_NT:
      stmt_action(state,va_arg(ap,AsmCodeGeneratorPtr));
      break;
    case burm_reg_NT:
      reg_action(state,va_arg(ap,AsmCodeGeneratorPtr));
      break;
    case burm_imm_NT:
      imm_action(state,va_arg(ap,AsmCodeGeneratorPtr));
      break;
    case burm_mem_NT:
      mem_action(state,va_arg(ap,AsmCodeGeneratorPtr));
      break;
    case burm_label_NT:
      label_action(state,va_arg(ap,AsmCodeGeneratorPtr));
      break;
    case burm_cond_NT:
      cond_action(state,va_arg(ap,AsmCodeGeneratorPtr));
      break;
    case burm_arg_NT:
      arg_action(state,va_arg(ap,AsmCodeGeneratorPtr),va_arg(ap,unsigned));
      break;
    case burm_args_NT:
      args_action(state,va_arg(ap,AsmCodeGeneratorPtr),va_arg(ap,unsigned));
      break;
    default:
      PANIC("Bad nonterminal %d in $exec\n", nterm);
      break;
    }
  else
    PANIC("Bad state for $exec in nonterminal %d \n",nterm);
  va_end(ap);
}

#define EXEC(s,n,a) ( \
  (n == burm_stmt_NT)? burm_exec(s,n,a): \
  (n == burm_reg_NT)? burm_exec(s,n,a): \
  (n == burm_imm_NT)? burm_exec(s,n,a): \
  (n == burm_mem_NT)? burm_exec(s,n,a): \
  (n == burm_label_NT)? burm_exec(s,n,a): \
  (n == burm_cond_NT)? burm_exec(s,n,a): \
  (n == burm_arg_NT)? burm_exec(s,n,a): \
  (n == burm_args_NT)? burm_exec(s,n,a): \
  PANIC("Bad nonterminal %d in $exec\n", n))

struct burm_state *burm_immed(struct burm_state *s,int n);
#ifndef NO_ACTION
#define NO_ACTION assert(0)
#endif


void stmt_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen)
{
  struct burm_state *_t;
  int _ern=burm_decode_stmt[_s->rule.burm_stmt];
  NODEPTR *_children;
  if(_s->rule.burm_stmt==0)
    NO_ACTION(stmt);
  switch(_ern){
  case 6:
{



    std::cerr << "[DEBUG] " << "stmt:    reg\n";
    // if (_s->node->isActionExecuted())
    //     return;
    // _s->node->setActionExecuted();
    reg_action(_s,AsmGen);

}
  break;
  case 7:
{



    std::cerr << "[DEBUG] " << "stmt:    Ret(reg)\n";
    reg_action(_s->kids[0],AsmGen);
    AsmGen->EmitMov(_s->kids[0]->node->getRegLocString(), "%rax");

}
  break;
  case 8:
{



    std::cerr << "[DEBUG] " << "stmt:    Ret(imm)\n";
    imm_action(_s->kids[0],AsmGen);
    AsmGen->EmitMov(_s->kids[0]->node->getImmVal(), "%rax");

}
  break;
  case 9:
{



    std::cerr << "[DEBUG] " << "stmt:   Store(reg, mem)\n";
    reg_action(_s->kids[0],AsmGen);
    mem_action(_s->kids[1],AsmGen);
    AsmGen->EmitMov(_s->kids[0]->node->getRegLocString(), _s->kids[1]->node->getMemLoc());

}
  break;
  case 10:
{



    std::cerr << "[DEBUG] " << "stmt:   Store(reg, reg)\n";
    reg_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    AsmGen->EmitMov(_s->kids[0]->node->getRegLocString(),
                    '(' + _s->kids[1]->node->getRegLocString() + ')');

}
  break;
  case 11:
{



    std::cerr << "[DEBUG] " << "stmt:   Store(imm, reg)\n";
    imm_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    AsmGen->EmitMov(_s->kids[0]->node->getImmVal(),
                    '(' + _s->kids[1]->node->getRegLocString() + ')');

}
  break;
  case 12:
{



    std::cerr << "[DEBUG] " << "stmt:   Store(imm, mem)\n";
    imm_action(_s->kids[0],AsmGen);
    mem_action(_s->kids[1],AsmGen);
    AsmGen->EmitMov(_s->kids[0]->node->getImmVal(), _s->kids[1]->node->getMemLoc());

}
  break;
  case 13:
{



    std::cerr << "[DEBUG] " << "stmt:   Store(mem, mem)\n";
    mem_action(_s->kids[0],AsmGen);
    mem_action(_s->kids[1],AsmGen);
    auto AvailReg = RA->getAvailableRegister();
    const char* AvailRegStr = convertRegisterToString(AvailReg);
    AsmGen->EmitLea(_s->kids[0]->node->getMemLoc(), AvailRegStr);
    AsmGen->EmitMov(AvailRegStr, _s->kids[1]->node->getMemLoc());

}
  break;
  case 14:
{



    std::cerr << "[DEBUG] " << "stmt:   Store(label, mem)\n";
    label_action(_s->kids[0],AsmGen);
    mem_action(_s->kids[1],AsmGen);
    AsmGen->EmitMov(_s->kids[0]->node->getLabelStringAsConstant(), _s->kids[1]->node->getMemLoc());

}
  break;
  case 18:
{



    std::cerr << "[DEBUG] " << "stmt: Br(cond, label, label)\n";
    cond_action(_s->kids[0],AsmGen);
    std::string JmpTrue, JmpFalse;
    auto *CI = llvm::cast<llvm::CmpInst>(_s->kids[0]->node->getInstruction());
    switch (CI->getPredicate()) {
    case llvm::CmpInst::Predicate::ICMP_EQ:
        JmpTrue = "je";
        JmpFalse = "jne";
        break;
    case llvm::CmpInst::Predicate::ICMP_NE:
        JmpTrue = "jne";
        JmpFalse = "je";
        break;
    case llvm::CmpInst::Predicate::ICMP_SGT:
        JmpTrue = "jg";
        JmpFalse = "jle";
        break;
    default:
        llvm_unreachable("unexpected CmpInst!\n");
    }
    auto *BI = llvm::cast<llvm::BranchInst>(_s->node->getInstruction());
    llvm::BasicBlock* NextBB = BI->getParent()->getNextNode();
    if (NextBB == BI->getSuccessor(0)) {
        AsmGen->EmitJmp(JmpFalse, _s->kids[2]->node->getLabelStringAsLabel());
    }
    else if (NextBB == BI->getSuccessor(1)) {
        AsmGen->EmitJmp(JmpTrue, _s->kids[1]->node->getLabelStringAsLabel());
    }
    else {
        AsmGen->EmitJmp(JmpTrue, _s->kids[1]->node->getLabelStringAsLabel());
        AsmGen->EmitJmp(JmpFalse, _s->kids[2]->node->getLabelStringAsLabel());
    }

}
  break;
  case 19:
{



    std::cerr << "[DEBUG] " << "stmt: Br(label)\n";
    auto *BI = llvm::cast<llvm::BranchInst>(_s->node->getInstruction());
    llvm::BasicBlock* NextBB = BI->getParent()->getNextNode();
    if (NextBB != BI->getSuccessor(0)) {
        AsmGen->EmitJmp("jmp", _s->kids[0]->node->getLabelStringAsLabel());
    }

}
  break;
  }
}


void reg_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen)
{
  struct burm_state *_t;
  int _ern=burm_decode_reg[_s->rule.burm_reg];
  NODEPTR *_children;
  if(_s->rule.burm_reg==0)
    NO_ACTION(reg);
  switch(_ern){
  case 2:
{


 
}
  break;
  case 4:
{



    std::cerr << "[DEBUG] " << "reg:   Load(mem)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    mem_action(_s->kids[0],AsmGen);
    _s->node->setRegLoc(true);
    AsmGen->EmitMov(_s->kids[0]->node->getMemLoc(), _s->node->getRegLocString());

}
  break;
  case 5:
{



    std::cerr << "[DEBUG] " << "reg:   Load(reg)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    _s->node->setRegLoc(true);
    AsmGen->EmitMov('(' + _s->kids[0]->node->getRegLocString() + ')',
                       _s->node->getRegLocString());

}
  break;
  case 20:
{



    std::cerr << "[DEBUG] " << "reg:   Add(reg, reg)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    AsmGen->EmitAdd(_s->kids[0]->node->getRegLocString(), _s->kids[1]->node->getRegLocString());
    _s->node->setRegLoc(false, _s->kids[1]->node->getRegLoc());

}
  break;
  case 21:
{



    std::cerr << "[DEBUG] " << "reg:   Add(reg, imm)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    imm_action(_s->kids[1],AsmGen);
    AsmGen->EmitAdd(_s->kids[1]->node->getImmVal(), _s->kids[0]->node->getRegLocString());
    _s->node->setRegLoc(false, _s->kids[0]->node->getRegLoc());

}
  break;
  case 22:
{



    std::cerr << "[DEBUG] " << "reg:   Add(imm, reg)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    imm_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    AsmGen->EmitAdd(_s->kids[0]->node->getImmVal(), _s->kids[1]->node->getRegLocString());
    _s->node->setRegLoc(false, _s->kids[1]->node->getRegLoc());

}
  break;
  case 23:
{



    std::cerr << "[DEBUG] " << "reg:   Add(imm, imm)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    imm_action(_s->kids[0],AsmGen);
    imm_action(_s->kids[1],AsmGen);
    llvm_unreachable("unexpected `reg: Add(imm, imm)!`\n");

}
  break;
  case 24:
{



    std::cerr << "[DEBUG] " << "reg:   Sub(reg, reg)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    AsmGen->EmitSub(_s->kids[1]->node->getRegLocString(), _s->kids[0]->node->getRegLocString());
    _s->node->setRegLoc(false, _s->kids[1]->node->getRegLoc());

}
  break;
  case 25:
{



    std::cerr << "[DEBUG] " << "reg:   Sub(reg, imm)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    imm_action(_s->kids[1],AsmGen);
    AsmGen->EmitSub(_s->kids[1]->node->getImmVal(), _s->kids[0]->node->getRegLocString());
    _s->node->setRegLoc(false, _s->kids[0]->node->getRegLoc());

}
  break;
  case 26:
{



    std::cerr << "[DEBUG] " << "reg:   Sub(imm, reg)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    imm_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    _s->node->setRegLoc(true);
    AsmGen->EmitMov(_s->kids[0]->node->getImmVal(), _s->node->getRegLocString());
    AsmGen->EmitSub(_s->kids[1]->node->getRegLocString(), _s->node->getRegLocString());

}
  break;
  case 27:
{



    std::cerr << "[DEBUG] " << "reg:   Sub(imm, imm)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    imm_action(_s->kids[0],AsmGen);
    imm_action(_s->kids[1],AsmGen);
    llvm_unreachable("unexpected `reg: Sub(imm, imm)!`\n");

}
  break;
  case 28:
{



    std::cerr << "[DEBUG] " << "reg:   Mul(reg, reg)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    AsmGen->EmitImul(_s->kids[0]->node->getRegLocString(), _s->kids[1]->node->getRegLocString());
    _s->node->setRegLoc(false, _s->kids[1]->node->getRegLoc());

}
  break;
  case 29:
{



    std::cerr << "[DEBUG] " << "reg:   Mul(reg, imm)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    imm_action(_s->kids[1],AsmGen);
    AsmGen->EmitImul(_s->kids[1]->node->getImmVal(), _s->kids[0]->node->getRegLocString());
    _s->node->setRegLoc(false, _s->kids[0]->node->getRegLoc());

}
  break;
  case 30:
{



    std::cerr << "[DEBUG] " << "reg:   Mul(imm, reg)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    imm_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    AsmGen->EmitImul(_s->kids[0]->node->getImmVal(), _s->kids[1]->node->getRegLocString());
    _s->node->setRegLoc(false, _s->kids[1]->node->getRegLoc());

}
  break;
  case 31:
{



    std::cerr << "[DEBUG] " << "reg:   Mul(imm, imm)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    imm_action(_s->kids[0],AsmGen);
    imm_action(_s->kids[1],AsmGen);
    llvm_unreachable("unexpected `reg: Mul(imm, imm)!`\n");

}
  break;
  case 32:
{



    std::cerr << "[DEBUG] " << "reg:   SDiv(reg, reg)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    AsmGen->EmitMov(_s->kids[0]->node->getRegLocString(), "%rax");
    AsmGen->EmitCqto();
    AsmGen->EmitIdiv(_s->kids[1]->node->getRegLocString());
    _s->node->setRegLoc(false, Register::RAX);

}
  break;
  case 33:
{



    std::cerr << "[DEBUG] " << "reg:   SDiv(reg, imm)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    imm_action(_s->kids[1],AsmGen);
    _s->node->setRegLoc(true);
    AsmGen->EmitMov(_s->kids[0]->node->getRegLocString(), "%rax");
    AsmGen->EmitCqto();
    AsmGen->EmitMov(_s->kids[1]->node->getImmVal(), _s->node->getRegLocString());
    AsmGen->EmitIdiv(_s->node->getRegLocString());
    AsmGen->EmitMov("%rax", _s->node->getRegLocString());

}
  break;
  case 34:
{



    std::cerr << "[DEBUG] " << "reg:   SDiv(imm, reg)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    imm_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    AsmGen->EmitMov(_s->kids[0]->node->getImmVal(), "%rax");
    AsmGen->EmitCqto();
    AsmGen->EmitIdiv(_s->kids[1]->node->getRegLocString());
    _s->node->setRegLoc(false, Register::RAX);

}
  break;
  case 35:
{



    std::cerr << "[DEBUG] " << "reg:   SDiv(imm, imm)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    imm_action(_s->kids[0],AsmGen);
    imm_action(_s->kids[1],AsmGen);
    llvm_unreachable("unexpected `reg: SDiv(imm, imm)!`\n");
    _s->node->setRegLoc(true);
    AsmGen->EmitMov(_s->kids[1]->node->getImmVal(), "%rax");
    AsmGen->EmitCqto();
    AsmGen->EmitMov(_s->kids[0]->node->getImmVal(), _s->node->getRegLocString());
    AsmGen->EmitIdiv(_s->node->getRegLocString());
    AsmGen->EmitMov("%rax", _s->node->getRegLocString());

}
  break;
  case 42:
{



    std::cerr << "[DEBUG] " << "reg:    Call(label, args)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    label_action(_s->kids[0],AsmGen);
    args_action(_s->kids[1],AsmGen, 0);
    auto* CB = llvm::cast<llvm::CallBase>(_s->node->getInstruction());
    std::string Callee = _s->kids[0]->node->getLabelStringAsLabel();
    if (Callee == "printf" || Callee == "scanf") {
        AsmGen->EmitXor("%rax", "%rax");
    }
    AsmGen->EmitCall(_s->kids[0]->node->getLabelStringAsLabel());
    _s->node->setRegLoc(false, Register::RAX);

}
  break;
  case 43:
{



    std::cerr << "[DEBUG] " << "reg:    Call(reg, args)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    args_action(_s->kids[1],AsmGen, 0);
    AsmGen->EmitCall("*" + _s->kids[0]->node->getRegLocString());
    _s->node->setRegLoc(false, Register::RAX);

}
  break;
  case 44:
{



    std::cerr << "[DEBUG] " << "reg:    Call(mem, args)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    mem_action(_s->kids[0],AsmGen);
    args_action(_s->kids[1],AsmGen, 0);
    AsmGen->EmitCall("*" + _s->kids[0]->node->getMemLoc());
    _s->node->setRegLoc(false, Register::RAX);

}
  break;
  }
}


void imm_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen)
{
  struct burm_state *_t;
  int _ern=burm_decode_imm[_s->rule.burm_imm];
  NODEPTR *_children;
  if(_s->rule.burm_imm==0)
    NO_ACTION(imm);
  switch(_ern){
  case 1:
{


 
}
  break;
  }
}


void mem_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen)
{
  struct burm_state *_t;
  int _ern=burm_decode_mem[_s->rule.burm_mem];
  NODEPTR *_children;
  if(_s->rule.burm_mem==0)
    NO_ACTION(mem);
  switch(_ern){
  case 3:
{


 
}
  break;
  }
}


void label_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen)
{
  struct burm_state *_t;
  int _ern=burm_decode_label[_s->rule.burm_label];
  NODEPTR *_children;
  if(_s->rule.burm_label==0)
    NO_ACTION(label);
  switch(_ern){
  case 0:
{


 
}
  break;
  }
}


void cond_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen)
{
  struct burm_state *_t;
  int _ern=burm_decode_cond[_s->rule.burm_cond];
  NODEPTR *_children;
  if(_s->rule.burm_cond==0)
    NO_ACTION(cond);
  switch(_ern){
  case 15:
{



    std::cerr << "[DEBUG] " << "cond: ICmp(reg, reg)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    AsmGen->EmitCmp(_s->kids[1]->node->getRegLocString(), _s->kids[0]->node->getRegLocString());

}
  break;
  case 16:
{



    std::cerr << "[DEBUG] " << "cond: ICmp(reg, imm)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    reg_action(_s->kids[0],AsmGen);
    imm_action(_s->kids[1],AsmGen);
    AsmGen->EmitCmp(_s->kids[1]->node->getImmVal(), _s->kids[0]->node->getRegLocString());

}
  break;
  case 17:
{



    std::cerr << "[DEBUG] " << "cond: ICmp(imm, reg)\n";
    if (_s->node->isActionExecuted())
        return;
    _s->node->setActionExecuted();
    imm_action(_s->kids[0],AsmGen);
    reg_action(_s->kids[1],AsmGen);
    auto AvailReg = RA->getAvailableRegister();
    const char* AvailRegStr = convertRegisterToString(AvailReg);
    AsmGen->EmitMov(_s->kids[0]->node->getImmVal(), AvailRegStr);
    AsmGen->EmitCmp(_s->kids[1]->node->getRegLocString(), AvailRegStr);

}
  break;
  }
}


void arg_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen, unsigned argNo)
{
  struct burm_state *_t;
  int _ern=burm_decode_arg[_s->rule.burm_arg];
  NODEPTR *_children;
  if(_s->rule.burm_arg==0)
    NO_ACTION(arg);
  switch(_ern){
  case 36:
{



    std::cerr << "[DEBUG] " << "arg:  reg\n";
    reg_action(_s,AsmGen);
    if (argNo < 6) {
        AsmGen->EmitMov(_s->node->getRegLocString(),
                           convertRegisterToString(ArgRegs[argNo]));
    } else {
        AsmGen->EmitMov(_s->node->getRegLocString(),
                           std::to_string(8 * (argNo - 6)) + "(%rsp)");
    }

}
  break;
  case 37:
{



    std::cerr << "[DEBUG] " << "arg:  imm\n";
    imm_action(_s,AsmGen);
    if (argNo < 6) {
        AsmGen->EmitMov(_s->node->getImmVal(),
                           convertRegisterToString(ArgRegs[argNo]));
    } else {
        AsmGen->EmitMov(_s->node->getImmVal(),
                           std::to_string(8 * (argNo - 6)) + "(%rsp)");
    }

}
  break;
  case 38:
{



    std::cerr << "[DEBUG] " << "arg:  mem\n";
    mem_action(_s,AsmGen);
    if (argNo < 6) {
        AsmGen->EmitLea(_s->node->getMemLoc(),
                           convertRegisterToString(ArgRegs[argNo]));
    } else {
        AsmGen->EmitMov(_s->node->getMemLoc(),
                           std::to_string(8 * (argNo - 6)) + "(%rsp)");
    }

}
  break;
  case 39:
{



    std::cerr << "[DEBUG] " << "arg:  mem\n";
    label_action(_s,AsmGen);
    if (argNo < 6) {
        AsmGen->EmitMov(_s->node->getLabelStringAsConstant(),
                           convertRegisterToString(ArgRegs[argNo]));
    } else {
        AsmGen->EmitMov(_s->node->getLabelStringAsConstant(),
                           std::to_string(8 * (argNo - 6)) + "(%rsp)");
    }

}
  break;
  }
}


void args_action(struct burm_state *_s, 

AsmCodeGeneratorPtr AsmGen, unsigned argNo)
{
  struct burm_state *_t;
  int _ern=burm_decode_args[_s->rule.burm_args];
  NODEPTR *_children;
  if(_s->rule.burm_args==0)
    NO_ACTION(args);
  switch(_ern){
  case 40:
{



    std::cerr << "[DEBUG] " << "args:   ARGS(Undef, Undef)\n";

}
  break;
  case 41:
{



    std::cerr << "[DEBUG] " << "args:   ARGS(value, args)\n";
    arg_action(_s->kids[0],AsmGen, argNo);
    args_action(_s->kids[1],AsmGen, argNo+1);

}
  break;
  }
}
static void burm_closure_reg(struct burm_state *, COST);
static void burm_closure_imm(struct burm_state *, COST);
static void burm_closure_mem(struct burm_state *, COST);
static void burm_closure_label(struct burm_state *, COST);

static void burm_closure_reg(struct burm_state *s, COST c) {
  if(burm_cost_code(&c,36,s) && COST_LESS(c,s->cost[burm_arg_NT])) {
burm_trace(burm_np, 36, c);     s->cost[burm_arg_NT] = c ;
    s->rule.burm_arg = 1;
  }
  if(burm_cost_code(&c,6,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 6, c);     s->cost[burm_stmt_NT] = c ;
    s->rule.burm_stmt = 1;
  }
}

static void burm_closure_imm(struct burm_state *s, COST c) {
  if(burm_cost_code(&c,37,s) && COST_LESS(c,s->cost[burm_arg_NT])) {
burm_trace(burm_np, 37, c);     s->cost[burm_arg_NT] = c ;
    s->rule.burm_arg = 2;
  }
}

static void burm_closure_mem(struct burm_state *s, COST c) {
  if(burm_cost_code(&c,38,s) && COST_LESS(c,s->cost[burm_arg_NT])) {
burm_trace(burm_np, 38, c);     s->cost[burm_arg_NT] = c ;
    s->rule.burm_arg = 3;
  }
}

static void burm_closure_label(struct burm_state *s, COST c) {
  if(burm_cost_code(&c,39,s) && COST_LESS(c,s->cost[burm_arg_NT])) {
burm_trace(burm_np, 39, c);     s->cost[burm_arg_NT] = c ;
    s->rule.burm_arg = 4;
  }
}

struct burm_state *burm_alloc_state(NODEPTR u,int op,int arity)
{
  struct burm_state *p, **k;
  p = (struct burm_state *)ALLOC(sizeof *p);
  burm_assert(p, PANIC("1:ALLOC returned NULL in burm_alloc_state\n"));
    burm_np = u;
  p->op = op;
  p->node = u;
  if(arity){
    k=(struct burm_state **)ALLOC(arity*sizeof (struct burm_state *));
    burm_assert(k, PANIC("2:ALLOC returned NULL in burm_alloc_state\n"));
    p->kids=k;
  }else
    p->kids=0;
  p->rule.burm_stmt =
  p->rule.burm_reg =
  p->rule.burm_imm =
  p->rule.burm_mem =
  p->rule.burm_label =
  p->rule.burm_cond =
  p->rule.burm_arg =
  p->rule.burm_args =
    0;
  p->cost[1] =
  p->cost[2] =
  p->cost[3] =
  p->cost[4] =
  p->cost[5] =
  p->cost[6] =
  p->cost[7] =
  p->cost[8] =
    COST_INFINITY;
  return p;
}
struct burm_state *burm_label1(NODEPTR u) {
  int op, arity, i, immed_matched=0;
  COST c=COST_ZERO;
  struct burm_state *s,**k;
  NODEPTR *children;
  op=OP_LABEL(u);
  arity=burm_arity[op];
  switch(op){
  case 0:   /* Undef */
#ifdef LEAF_TRAP
    if(s=LEAF_TRAP(u,op))
      return s;
#endif
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=0;
    break;
  case 1:   /* Ret */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* stmt: Ret(imm) */
      k[0]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,8,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 8, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 3;
      }
    }
    if (   /* stmt: Ret(reg) */
      k[0]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,7,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 7, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 2;
      }
    }
    break;
  case 2:   /* Br */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* stmt: Br(label,Undef,Undef) */
      k[0]->rule.burm_label && 
      k[1]->op == 0 &&  /* Undef */
      k[2]->op == 0 /* Undef */
    ) {
      if(burm_cost_code(&c,19,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 19, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 11;
      }
    }
    if (   /* stmt: Br(cond,label,label) */
      k[0]->rule.burm_cond && 
      k[1]->rule.burm_label && 
      k[2]->rule.burm_label
    ) {
      if(burm_cost_code(&c,18,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 18, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 10;
      }
    }
    break;
  case 3:   /* Switch */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 4:   /* IndirectBr */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 5:   /* Invoke */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 6:   /* Resume */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 7:   /* Unreachable */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 8:   /* CleanupRet */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 9:   /* CatchRet */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 10:   /* CatchSwitch */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 11:   /* CallBr */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 12:   /* FNeg */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 13:   /* Add */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: Add(imm,imm) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,23,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 23, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 7;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Add(imm,reg) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,22,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 22, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 6;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Add(reg,imm) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,21,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 21, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 5;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Add(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,20,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 20, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 4;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 14:   /* FAdd */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 15:   /* Sub */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: Sub(imm,imm) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,27,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 27, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 11;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Sub(imm,reg) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,26,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 26, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 10;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Sub(reg,imm) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,25,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 25, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 9;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Sub(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,24,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 24, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 8;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 16:   /* FSub */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 17:   /* Mul */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: Mul(imm,imm) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,31,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 31, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 15;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Mul(imm,reg) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,30,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 30, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 14;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Mul(reg,imm) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,29,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 29, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 13;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Mul(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,28,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 28, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 12;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 18:   /* FMul */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 19:   /* UDiv */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 20:   /* SDiv */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: SDiv(imm,imm) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,35,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 35, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 19;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: SDiv(imm,reg) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,34,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 34, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 18;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: SDiv(reg,imm) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,33,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 33, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 17;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: SDiv(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,32,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 32, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 16;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 21:   /* FDiv */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 22:   /* URem */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 23:   /* SRem */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 24:   /* FRem */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 25:   /* Shl */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 26:   /* LShr */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 27:   /* AShr */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 28:   /* And */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 29:   /* Or */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 30:   /* Xor */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 31:   /* Alloca */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* mem: Alloca(imm) */
      k[0]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,3,s) && COST_LESS(c,s->cost[burm_mem_NT])) {
burm_trace(burm_np, 3, c);         s->cost[burm_mem_NT] = c ;
        s->rule.burm_mem = 1;
        burm_closure_mem(s, c );
      }
    }
    break;
  case 32:   /* Load */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: Load(reg) */
      k[0]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,5,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 5, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 3;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Load(mem) */
      k[0]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,4,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 4, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 2;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 33:   /* Store */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* stmt: Store(label,mem) */
      k[0]->rule.burm_label && 
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,14,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 14, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 9;
      }
    }
    if (   /* stmt: Store(mem,mem) */
      k[0]->rule.burm_mem && 
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,13,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 13, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 8;
      }
    }
    if (   /* stmt: Store(imm,mem) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,12,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 12, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 7;
      }
    }
    if (   /* stmt: Store(imm,reg) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,11,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 11, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 6;
      }
    }
    if (   /* stmt: Store(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,10,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 10, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 5;
      }
    }
    if (   /* stmt: Store(reg,mem) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,9,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 9, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 4;
      }
    }
    break;
  case 34:   /* GetElementPtr */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 35:   /* Fence */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 36:   /* AtomicCmpXchg */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 37:   /* AtomicRMW */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 38:   /* Trunc */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 39:   /* ZExt */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 40:   /* SExt */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 41:   /* FPToUI */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 42:   /* FPToSI */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 43:   /* UIToFP */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 44:   /* SIToFP */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 45:   /* FPTrunc */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 46:   /* FPExt */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 47:   /* PtrToInt */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 48:   /* IntToPtr */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 49:   /* BitCast */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 50:   /* AddrSpaceCast */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 51:   /* CleanupPad */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 52:   /* CatchPad */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 53:   /* ICmp */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* cond: ICmp(imm,reg) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,17,s) && COST_LESS(c,s->cost[burm_cond_NT])) {
burm_trace(burm_np, 17, c);         s->cost[burm_cond_NT] = c ;
        s->rule.burm_cond = 3;
      }
    }
    if (   /* cond: ICmp(reg,imm) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,16,s) && COST_LESS(c,s->cost[burm_cond_NT])) {
burm_trace(burm_np, 16, c);         s->cost[burm_cond_NT] = c ;
        s->rule.burm_cond = 2;
      }
    }
    if (   /* cond: ICmp(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,15,s) && COST_LESS(c,s->cost[burm_cond_NT])) {
burm_trace(burm_np, 15, c);         s->cost[burm_cond_NT] = c ;
        s->rule.burm_cond = 1;
      }
    }
    break;
  case 54:   /* FCmp */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 55:   /* PHI */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 56:   /* Call */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* reg: Call(mem,args) */
      k[0]->rule.burm_mem && 
      k[1]->rule.burm_args
    ) {
      if(burm_cost_code(&c,44,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 44, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 22;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Call(reg,args) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_args
    ) {
      if(burm_cost_code(&c,43,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 43, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 21;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Call(label,args) */
      k[0]->rule.burm_label && 
      k[1]->rule.burm_args
    ) {
      if(burm_cost_code(&c,42,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 42, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 20;
        burm_closure_reg(s, c );
      }
    }
    break;
  case 57:   /* Select */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 58:   /* UserOp1 */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 59:   /* UserOp2 */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 60:   /* VAArg */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 61:   /* ExtractElement */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 62:   /* InsertElement */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 63:   /* ShuffleVector */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 64:   /* ExtractValue */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 65:   /* InsertValue */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 66:   /* LandingPad */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 67:   /* Freeze */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    break;
  case 68:   /* Const */
#ifdef LEAF_TRAP
    if(s=LEAF_TRAP(u,op))
      return s;
#endif
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=0;
    {      /* imm: Const */
      if(burm_cost_code(&c,1,s) && COST_LESS(c,s->cost[burm_imm_NT])) {
burm_trace(burm_np, 1, c);         s->cost[burm_imm_NT] = c ;
        s->rule.burm_imm = 1;
        burm_closure_imm(s, c );
      }
    }
    break;
  case 69:   /* Label */
#ifdef LEAF_TRAP
    if(s=LEAF_TRAP(u,op))
      return s;
#endif
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=0;
    {      /* label: Label */
      if(burm_cost_code(&c,0,s) && COST_LESS(c,s->cost[burm_label_NT])) {
burm_trace(burm_np, 0, c);         s->cost[burm_label_NT] = c ;
        s->rule.burm_label = 1;
        burm_closure_label(s, c );
      }
    }
    break;
  case 70:   /* Args */
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=s->kids;
    children=GET_KIDS(u);
    for(i=0;i<arity;i++)
      k[i]=burm_label1(children[i]);
    if (   /* args: Args(arg,args) */
      k[0]->rule.burm_arg && 
      k[1]->rule.burm_args
    ) {
      if(burm_cost_code(&c,41,s) && COST_LESS(c,s->cost[burm_args_NT])) {
burm_trace(burm_np, 41, c);         s->cost[burm_args_NT] = c ;
        s->rule.burm_args = 2;
      }
    }
    if (   /* args: Args(Undef,Undef) */
      k[0]->op == 0 &&  /* Undef */
      k[1]->op == 0 /* Undef */
    ) {
      if(burm_cost_code(&c,40,s) && COST_LESS(c,s->cost[burm_args_NT])) {
burm_trace(burm_np, 40, c);         s->cost[burm_args_NT] = c ;
        s->rule.burm_args = 1;
      }
    }
    break;
  case 71:   /* Reg */
#ifdef LEAF_TRAP
    if(s=LEAF_TRAP(u,op))
      return s;
#endif
    s=burm_alloc_state(u,op,arity);
    SET_STATE(u,s);
    k=0;
    {      /* reg: Reg */
      if(burm_cost_code(&c,2,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 2, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 1;
        burm_closure_reg(s, c );
      }
    }
    break;
  default:
    burm_assert(0, PANIC("Bad operator %d in burm_state\n", op));
  }
  return s;
}

struct burm_state *burm_label(NODEPTR p) {
  burm_label1(p);
  return ((struct burm_state *)STATE_LABEL(p))->rule.burm_stmt ? STATE_LABEL(p) : 0;
}

void burm_free(struct burm_state *s)
{
  int i,arity=burm_arity[s->op];
  if(s->kids==0)
    free(s);
  else {
    for(i=0;i<arity;i++)
      burm_free(s->kids[i]);
    free(s->kids);
  }
}
struct burm_state *burm_immed(struct burm_state *s,int n)
{
  NODEPTR *children = GET_KIDS(s->node);
  if(s->kids[n])
    return s->kids[n];
  else
  return s->kids[n]=burm_label1(children[n]);
}
int burm_op_label(NODEPTR p) {
  burm_assert(p, PANIC("NULL tree in burm_op_label\n"));
  return OP_LABEL(p);
}

struct burm_state *burm_state_label(NODEPTR p) {
  burm_assert(p, PANIC("NULL tree in burm_state_label\n"));
  return STATE_LABEL(p);
}

NODEPTR burm_child(NODEPTR p, int index) {
  NODEPTR *kids;
  burm_assert(p, PANIC("NULL tree in burm_child\n"));
  kids=GET_KIDS(p);
  burm_assert((0<=index && index<burm_arity[OP_LABEL(p)]),
    PANIC("Bad index %d in burm_child\n", index));

  return kids[index];
}
NODEPTR *burm_kids(NODEPTR p, int eruleno, NODEPTR kids[]) {
  burm_assert(p, PANIC("NULL tree in burm_kids\n"));
  burm_assert(kids, PANIC("NULL kids in burm_kids\n"));
  switch (eruleno) {
  case 40: /* args: Args(Undef,Undef) */
  case 2: /* reg: Reg */
  case 1: /* imm: Const */
  case 0: /* label: Label */
    break;
  case 19: /* stmt: Br(label,Undef,Undef) */
  case 8: /* stmt: Ret(imm) */
  case 7: /* stmt: Ret(reg) */
  case 5: /* reg: Load(reg) */
  case 4: /* reg: Load(mem) */
  case 3: /* mem: Alloca(imm) */
    kids[0] = burm_child(p,0);
    break;
  case 39: /* arg: label */
  case 38: /* arg: mem */
  case 37: /* arg: imm */
  case 36: /* arg: reg */
  case 6: /* stmt: reg */
    kids[0] = p;
    break;
  case 44: /* reg: Call(mem,args) */
  case 43: /* reg: Call(reg,args) */
  case 42: /* reg: Call(label,args) */
  case 41: /* args: Args(arg,args) */
  case 35: /* reg: SDiv(imm,imm) */
  case 34: /* reg: SDiv(imm,reg) */
  case 33: /* reg: SDiv(reg,imm) */
  case 32: /* reg: SDiv(reg,reg) */
  case 31: /* reg: Mul(imm,imm) */
  case 30: /* reg: Mul(imm,reg) */
  case 29: /* reg: Mul(reg,imm) */
  case 28: /* reg: Mul(reg,reg) */
  case 27: /* reg: Sub(imm,imm) */
  case 26: /* reg: Sub(imm,reg) */
  case 25: /* reg: Sub(reg,imm) */
  case 24: /* reg: Sub(reg,reg) */
  case 23: /* reg: Add(imm,imm) */
  case 22: /* reg: Add(imm,reg) */
  case 21: /* reg: Add(reg,imm) */
  case 20: /* reg: Add(reg,reg) */
  case 17: /* cond: ICmp(imm,reg) */
  case 16: /* cond: ICmp(reg,imm) */
  case 15: /* cond: ICmp(reg,reg) */
  case 14: /* stmt: Store(label,mem) */
  case 13: /* stmt: Store(mem,mem) */
  case 12: /* stmt: Store(imm,mem) */
  case 11: /* stmt: Store(imm,reg) */
  case 10: /* stmt: Store(reg,reg) */
  case 9: /* stmt: Store(reg,mem) */
    kids[0] = burm_child(p,0);
    kids[1] = burm_child(p,1);
    break;
  case 18: /* stmt: Br(cond,label,label) */
    kids[0] = burm_child(p,0);
    kids[1] = burm_child(p,1);
    kids[2] = burm_child(p,2);
    break;
  default:
    burm_assert(0, PANIC("Bad external rule number %d in burm_kids\n", eruleno));
  }
  return kids;
}

void dumpCover(NODEPTR p, int goalnt, int indent)
{
  int eruleno = burm_rule(STATE_LABEL(p), goalnt);
  short *nts = burm_nts[eruleno];
  NODEPTR kids[10];
  int i;

  std::cerr << "\t\t";
  for (i = 0; i < indent; i++)
    std::cerr << " ";
  std::cerr << burm_string[eruleno] << "\n";
  burm_kids(p, eruleno, kids);
  for (i = 0; nts[i]; i++)
    dumpCover(kids[i], nts[i], indent + 1);
}


#pragma GCC diagnostic pop



/* burm_trace - print trace message for matching p */
static void burm_trace(NODEPTR p, int eruleno, COST cost) { }

static void gen(NODEPTR p, AsmCodeGenerator *AsmGen) {
    if (burm_label(p) == 0)
        std::cerr << "[DEBUG] " << "no cover\n";
    else {
        stmt_action(p->getState(), AsmGen);
    }
}

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
// #include "llvm/Support/CommandLine.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IRReader/IRReader.h"

using namespace llvm;

void printDebugTree(Node *p, int indent=0) {
    if(p != nullptr) {
        if (indent) std::cerr << "|";
        int i = 0;
        for (; i < indent-4; ++i) std::cerr << " ";
        if (indent-4 > 0) std::cerr << "|";
        for (; i < indent; ++i) std::cerr << "-";
        std::cerr << "+ op:" << p->getOp() << ", Kind:" << p->getNodeKind() << "\n";

        for(auto *kid: p->Kids)
        {
            printDebugTree(kid, (indent+4));
        }
    }
}

void AsmCodeGenerator::EmitFunction(AsmFunction &F)
{
    EmitFunctionDeclaration(F);

    EmitFunctionPrologue(F);

    // body
    for (auto* T: F.ExprTrees)
    {
        printDebugTree(T);
        if (T->getOp() == /*Label*/69)
            Out << T->getLabelStringAsLabel() << ":\n";
        gen(T, this);
    }

    EmitFunctionEpilogue(F);
}

// static cl::opt<std::string>
// InputFilename(cl::Positional, cl::desc("<input bitcode>"), cl::init("-"));

int main(int argc, char *argv[]) {
    // parse arguments from command line
    // cl::ParseCommandLineOptions(argc, argv, "llc-olive\n");

    // prepare llvm context to read bitcode file
    LLVMContext Context;
    SMDiagnostic Error;
    std::unique_ptr<Module> M = parseIRFile(/*InputFilename*/argv[1], Error, Context);

    ExprTreeBuilder Builder(M->getDataLayout());
    Builder.visit(*M);

    AsmCodeGenerator AsmGen(Builder.Functions, Builder.ConstantStrings);
    AsmGen.EmitAssembly();

    return 0;
}
