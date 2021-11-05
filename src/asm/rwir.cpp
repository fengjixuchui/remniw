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

int indent);


void reg_action(struct burm_state *_s, 

int indent);


void imm_action(struct burm_state *_s, 

int indent);


void mem_action(struct burm_state *_s, 

int indent);


void label_action(struct burm_state *_s, 

int indent);


void cond_action(struct burm_state *_s, 

int indent);


void arg_action(struct burm_state *_s, 

int indent, unsigned argNo);


void args_action(struct burm_state *_s, 

int indent, unsigned argNo);
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
static short burm_nts_1[] = { burm_reg_NT, 0 };
static short burm_nts_2[] = { burm_imm_NT, 0 };
static short burm_nts_3[] = { burm_mem_NT, 0 };
static short burm_nts_4[] = { burm_reg_NT, burm_mem_NT, 0 };
static short burm_nts_5[] = { burm_reg_NT, burm_reg_NT, 0 };
static short burm_nts_6[] = { burm_imm_NT, burm_mem_NT, 0 };
static short burm_nts_7[] = { burm_mem_NT, burm_mem_NT, 0 };
static short burm_nts_8[] = { burm_label_NT, burm_mem_NT, 0 };
static short burm_nts_9[] = { burm_reg_NT, burm_imm_NT, 0 };
static short burm_nts_10[] = { burm_imm_NT, burm_reg_NT, 0 };
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
  burm_nts_1,  /* 2 */
  burm_nts_2,  /* 3 */
  burm_nts_3,  /* 4 */
  burm_nts_1,  /* 5 */
  burm_nts_4,  /* 6 */
  burm_nts_5,  /* 7 */
  burm_nts_6,  /* 8 */
  burm_nts_7,  /* 9 */
  burm_nts_8,  /* 10 */
  burm_nts_0,  /* 11 */
  burm_nts_5,  /* 12 */
  burm_nts_9,  /* 13 */
  burm_nts_10,  /* 14 */
  burm_nts_11,  /* 15 */
  burm_nts_12,  /* 16 */
  burm_nts_5,  /* 17 */
  burm_nts_9,  /* 18 */
  burm_nts_10,  /* 19 */
  burm_nts_13,  /* 20 */
  burm_nts_5,  /* 21 */
  burm_nts_9,  /* 22 */
  burm_nts_10,  /* 23 */
  burm_nts_13,  /* 24 */
  burm_nts_5,  /* 25 */
  burm_nts_9,  /* 26 */
  burm_nts_10,  /* 27 */
  burm_nts_13,  /* 28 */
  burm_nts_5,  /* 29 */
  burm_nts_9,  /* 30 */
  burm_nts_10,  /* 31 */
  burm_nts_13,  /* 32 */
  burm_nts_1,  /* 33 */
  burm_nts_2,  /* 34 */
  burm_nts_3,  /* 35 */
  burm_nts_0,  /* 36 */
  burm_nts_14,  /* 37 */
  burm_nts_15,  /* 38 */
  burm_nts_16,  /* 39 */
  burm_nts_17,  /* 40 */
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
  /* 0 */  "imm: Const",
  /* 1 */  "reg: Reg",
  /* 2 */  "stmt: Ret(reg)",
  /* 3 */  "mem: Alloca(imm)",
  /* 4 */  "reg: Load(mem)",
  /* 5 */  "reg: Load(reg)",
  /* 6 */  "stmt: Store(reg,mem)",
  /* 7 */  "stmt: Store(reg,reg)",
  /* 8 */  "stmt: Store(imm,mem)",
  /* 9 */  "stmt: Store(mem,mem)",
  /* 10 */  "stmt: Store(label,mem)",
  /* 11 */  "label: Label",
  /* 12 */  "cond: ICmp(reg,reg)",
  /* 13 */  "cond: ICmp(reg,imm)",
  /* 14 */  "cond: ICmp(imm,reg)",
  /* 15 */  "stmt: Br(cond,label,label)",
  /* 16 */  "stmt: Br(label,Undef,Undef)",
  /* 17 */  "reg: Add(reg,reg)",
  /* 18 */  "reg: Add(reg,imm)",
  /* 19 */  "reg: Add(imm,reg)",
  /* 20 */  "reg: Add(imm,imm)",
  /* 21 */  "reg: Sub(reg,reg)",
  /* 22 */  "reg: Sub(reg,imm)",
  /* 23 */  "reg: Sub(imm,reg)",
  /* 24 */  "reg: Sub(imm,imm)",
  /* 25 */  "reg: Mul(reg,reg)",
  /* 26 */  "reg: Mul(reg,imm)",
  /* 27 */  "reg: Mul(imm,reg)",
  /* 28 */  "reg: Mul(imm,imm)",
  /* 29 */  "reg: SDiv(reg,reg)",
  /* 30 */  "reg: SDiv(reg,imm)",
  /* 31 */  "reg: SDiv(imm,reg)",
  /* 32 */  "reg: SDiv(imm,imm)",
  /* 33 */  "arg: reg",
  /* 34 */  "arg: imm",
  /* 35 */  "arg: mem",
  /* 36 */  "args: Args(Undef,Undef)",
  /* 37 */  "args: Args(arg,args)",
  /* 38 */  "reg: Call(label,args)",
  /* 39 */  "reg: Call(reg,args)",
  /* 40 */  "reg: Call(mem,args)",
};


std::string burm_files[] = {
"./rwir.brg",
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
};

int burm_line_numbers[] = {
  /* 0 */  110,
  /* 1 */  117,
  /* 2 */  123,
  /* 3 */  132,
  /* 4 */  139,
  /* 5 */  149,
  /* 6 */  159,
  /* 7 */  169,
  /* 8 */  179,
  /* 9 */  189,
  /* 10 */  201,
  /* 11 */  211,
  /* 12 */  217,
  /* 13 */  226,
  /* 14 */  235,
  /* 15 */  248,
  /* 16 */  289,
  /* 17 */  296,
  /* 18 */  306,
  /* 19 */  317,
  /* 20 */  328,
  /* 21 */  337,
  /* 22 */  348,
  /* 23 */  361,
  /* 24 */  372,
  /* 25 */  381,
  /* 26 */  392,
  /* 27 */  403,
  /* 28 */  414,
  /* 29 */  423,
  /* 30 */  435,
  /* 31 */  450,
  /* 32 */  462,
  /* 33 */  477,
  /* 34 */  489,
  /* 35 */  500,
  /* 36 */  511,
  /* 37 */  517,
  /* 38 */  526,
  /* 39 */  538,
  /* 40 */  549,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

static short burm_decode_stmt[] = {
   -1,
  2,
  6,
  7,
  8,
  9,
  10,
  15,
  16,
};

static short burm_decode_reg[] = {
   -1,
  1,
  4,
  5,
  17,
  18,
  19,
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
  38,
  39,
  40,
};

static short burm_decode_imm[] = {
   -1,
  0,
};

static short burm_decode_mem[] = {
   -1,
  3,
};

static short burm_decode_label[] = {
   -1,
  11,
};

static short burm_decode_cond[] = {
   -1,
  12,
  13,
  14,
};

static short burm_decode_arg[] = {
   -1,
  33,
  34,
  35,
};

static short burm_decode_args[] = {
   -1,
  36,
  37,
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


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 3:
{


 (*_c).cost = 1; 
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


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_mem_NT].cost; 
}
  break;
  case 7:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost; 
}
  break;
  case 8:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_mem_NT].cost; 
}
  break;
  case 9:
{


 (*_c).cost = _s->kids[0]->cost[burm_mem_NT].cost + _s->kids[1]->cost[burm_mem_NT].cost; 
}
  break;
  case 10:
{


 (*_c).cost = _s->kids[0]->cost[burm_label_NT].cost + _s->kids[1]->cost[burm_mem_NT].cost; 
}
  break;
  case 11:
{


 (*_c).cost = 0; 
}
  break;
  case 12:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 0; 
}
  break;
  case 13:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 0; 
}
  break;
  case 14:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 0; 
}
  break;
  case 15:
{


 (*_c).cost = _s->kids[0]->cost[burm_cond_NT].cost + _s->kids[1]->cost[burm_label_NT].cost + _s->kids[2]->cost[burm_label_NT].cost + 1; 
}
  break;
  case 16:
{


 (*_c).cost = _s->kids[0]->cost[burm_label_NT].cost + 1; 
}
  break;
  case 17:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 2; 
}
  break;
  case 18:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 19:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 20:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 21:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 2; 
}
  break;
  case 22:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 23:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 24:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 25:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 2; 
}
  break;
  case 26:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 27:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 28:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 29:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 2; 
}
  break;
  case 30:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 31:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 32:
{


 (*_c).cost = _s->kids[0]->cost[burm_imm_NT].cost + _s->kids[1]->cost[burm_imm_NT].cost + 1; 
}
  break;
  case 33:
{


 (*_c).cost = _s->cost[burm_reg_NT].cost; 
}
  break;
  case 34:
{


 (*_c).cost = _s->cost[burm_imm_NT].cost; 
}
  break;
  case 35:
{


 (*_c).cost = _s->cost[burm_mem_NT].cost; 
}
  break;
  case 36:
{


 (*_c).cost = 0; 
}
  break;
  case 37:
{


 (*_c).cost = _s->kids[0]->cost[burm_arg_NT].cost + _s->kids[1]->cost[burm_args_NT].cost + 1; 
}
  break;
  case 38:
{


 (*_c).cost = _s->kids[0]->cost[burm_label_NT].cost + 1; 
}
  break;
  case 39:
{


 (*_c).cost = _s->kids[0]->cost[burm_reg_NT].cost + 1; 
}
  break;
  case 40:
{


 (*_c).cost = _s->kids[0]->cost[burm_mem_NT].cost + 1; 
}
  break;
  }
  return 1;
}


void stmt_action(struct burm_state *_s, 

int indent);


void reg_action(struct burm_state *_s, 

int indent);


void imm_action(struct burm_state *_s, 

int indent);


void mem_action(struct burm_state *_s, 

int indent);


void label_action(struct burm_state *_s, 

int indent);


void cond_action(struct burm_state *_s, 

int indent);


void arg_action(struct burm_state *_s, 

int indent, unsigned argNo);


void args_action(struct burm_state *_s, 

int indent, unsigned argNo);


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
      stmt_action(state,va_arg(ap,int));
      break;
    case burm_reg_NT:
      reg_action(state,va_arg(ap,int));
      break;
    case burm_imm_NT:
      imm_action(state,va_arg(ap,int));
      break;
    case burm_mem_NT:
      mem_action(state,va_arg(ap,int));
      break;
    case burm_label_NT:
      label_action(state,va_arg(ap,int));
      break;
    case burm_cond_NT:
      cond_action(state,va_arg(ap,int));
      break;
    case burm_arg_NT:
      arg_action(state,va_arg(ap,int),va_arg(ap,unsigned));
      break;
    case burm_args_NT:
      args_action(state,va_arg(ap,int),va_arg(ap,unsigned));
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

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_stmt[_s->rule.burm_stmt];
  NODEPTR *_children;
  if(_s->rule.burm_stmt==0)
    NO_ACTION(stmt);
  switch(_ern){
  case 2:
{



        reg_action(_s->kids[0],indent);
        // x64 assembly Ret takes no argument, return value is passed by %rax
        std::cerr << "[DEBUG] " << "stmt:    Ret(reg)\n";
        std::cout << "movq " << _s->kids[0]->node->getRegLocString() << ", %rax\n";
    
}
  break;
  case 6:
{



        reg_action(_s->kids[0],indent);
        mem_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "stmt:   Store(reg, mem)\n";
        std::cout << "movq " << _s->kids[0]->node->getRegLocString() << ", "
                  << _s->kids[1]->node->getMemLoc() << "\n";
    
}
  break;
  case 7:
{



        reg_action(_s->kids[0],indent);
        reg_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "stmt:   Store(reg, reg)\n";
        std::cout << "movq " << _s->kids[0]->node->getRegLocString() << ", "
                  << "(" << _s->kids[1]->node->getRegLocString() << ")\n";
    
}
  break;
  case 8:
{



        imm_action(_s->kids[0],indent);
        mem_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "stmt:   Store(imm, mem)\n";
        std::cout << "movq " << _s->kids[0]->node->getImmVal() << ","
                  << _s->kids[1]->node->getMemLoc() << "\n";
    
}
  break;
  case 9:
{



        mem_action(_s->kids[0],indent);
        mem_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "stmt:   Store(imm, mem)\n";
        auto AvailableRegister = RA->getAvailableRegister();
        std::cout << "leaq " << _s->kids[0]->node->getMemLoc() << ", "
                  << convertRegisterToString(AvailableRegister) << "\n";
        std::cout << "movq " << convertRegisterToString(AvailableRegister) << ", " << _s->kids[1]->node->getMemLoc() << "\n";
    
}
  break;
  case 10:
{



        label_action(_s->kids[0],indent);
        mem_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "stmt:   Store(label, mem)\n";
        std::cout << "movq " << _s->kids[0]->node->getLabelString3() << ","
                  << _s->kids[1]->node->getMemLoc() << "\n";
    
}
  break;
  case 15:
{



        cond_action(_s->kids[0],indent);
        std::string JmpTrue, JmpFalse;
        auto *CI = llvm::cast<llvm::CmpInst>(_s->kids[0]->node->getInstruction());
        switch (CI->getPredicate()) {
            case llvm::CmpInst::Predicate::ICMP_EQ:
                JmpTrue = "je ";
                JmpFalse = "jne ";
                break;
            case llvm::CmpInst::Predicate::ICMP_NE:
                JmpTrue = "jne ";
                JmpFalse = "je ";
                break;
            case llvm::CmpInst::Predicate::ICMP_SGT:
                JmpTrue = "jg ";
                JmpFalse = "jle ";
                break;
            default:
                llvm_unreachable("unexpected CmpInst!\n");
        }
        std::cerr << "[DEBUG] " << "stmt: Br(cond, label, label)\n";
        llvm::BasicBlock* NextBB = CI->getParent()->getNextNode();
        auto *BI = llvm::cast<llvm::BranchInst>(_s->node->getInstruction());
        if (NextBB == BI->getSuccessor(0))
        {
            std::cout << JmpFalse << _s->kids[2]->node->getLabelString() << "\n";
        }
        else if (NextBB == BI->getSuccessor(1))
        {
            std::cout << JmpTrue << _s->kids[1]->node->getLabelString() << "\n";
        }
        else
        {
            std::cout << JmpTrue << _s->kids[1]->node->getLabelString() << "\n";
            std::cout << JmpFalse << _s->kids[2]->node->getLabelString() << "\n";
        }
    
}
  break;
  case 16:
{



        std::cerr << "[DEBUG] " << "stmt: Br(label)\n";
        std::cout << "jmp " << _s->kids[0]->node->getLabelString() << "\n";
    
}
  break;
  }
}


void reg_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_reg[_s->rule.burm_reg];
  NODEPTR *_children;
  if(_s->rule.burm_reg==0)
    NO_ACTION(reg);
  switch(_ern){
  case 1:
{



        std::cerr << "[DEBUG] " << "reg:    Reg\n";
    
}
  break;
  case 4:
{



        mem_action(_s->kids[0],indent);
        _s->node->setRegLoc(true);
        std::cerr << "[DEBUG] " << "reg:   Load(mem)\n";
        std::cout << "movq " << _s->kids[0]->node->getMemLoc() << ", "
                  << _s->node->getRegLocString() << "\n";
    
}
  break;
  case 5:
{



        reg_action(_s->kids[0],indent);
        _s->node->setRegLoc(true);
        std::cerr << "[DEBUG] " << "reg:   Load(reg)\n";
        std::cout << "movq (" << _s->kids[0]->node->getRegLocString() << "), "
                  << _s->node->getRegLocString() << "\n";
    
}
  break;
  case 17:
{



        reg_action(_s->kids[0],indent);
        reg_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Add(reg, reg)\n";
        std::cout << "addq " << _s->kids[0]->node->getRegLocString() << ", " << _s->kids[1]->node->getRegLocString() << "\n";
        _s->node->setRegLoc(false, _s->kids[1]->node->getRegLoc());
    
}
  break;
  case 18:
{



        reg_action(_s->kids[0],indent);
        imm_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Add(reg, imm)\n";
        std::cout << "addq " << _s->kids[1]->node->getImmVal() << ", "
                  << _s->kids[0]->node->getRegLocString() << "\n";
        _s->node->setRegLoc(false, _s->kids[0]->node->getRegLoc());
    
}
  break;
  case 19:
{



        imm_action(_s->kids[0],indent);
        reg_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Add(imm, reg)\n";
        std::cout << "addq " << _s->kids[0]->node->getImmVal() << ", "
                  << _s->kids[1]->node->getRegLocString() << "\n";
        _s->node->setRegLoc(false, _s->kids[1]->node->getRegLoc());
    
}
  break;
  case 20:
{



        imm_action(_s->kids[0],indent);
        imm_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Add(imm, imm)\n";
        std::cout << "FIXME: addq " << _s->kids[0]->node->getImmVal() << ", " << _s->kids[0]->node->getImmVal() << "\n";
    
}
  break;
  case 21:
{



        reg_action(_s->kids[0],indent);
        reg_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Sub(reg, reg)\n";
        std::cout << "subq " << _s->kids[0]->node->getRegLocString() << ", "
                  << _s->kids[1]->node->getRegLocString() << "\n";
        _s->node->setRegLoc(false, _s->kids[1]->node->getRegLoc());
    
}
  break;
  case 22:
{



        reg_action(_s->kids[0],indent);
        imm_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Sub(reg, imm)\n";
        _s->node->setRegLoc(true);
        std::cout << "movq " << _s->kids[1]->node->getImmVal() << ", "
                  << _s->node->getRegLocString() << "\n";
        std::cout << "subq " << _s->kids[0]->node->getRegLocString() << ", "
                  << _s->node->getRegLocString() << "\n";
    
}
  break;
  case 23:
{



        imm_action(_s->kids[0],indent);
        reg_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Sub(imm, reg)\n";
        std::cout << "subq " << _s->kids[0]->node->getImmVal() << ", "
                  << _s->kids[1]->node->getRegLocString() << "\n";
        _s->node->setRegLoc(false, _s->kids[1]->node->getRegLoc());
    
}
  break;
  case 24:
{



        imm_action(_s->kids[0],indent);
        imm_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Sub(imm, imm)\n";
        std::cout << "FIXME: subq " << _s->kids[0]->node->getImmVal() << ", " << _s->kids[0]->node->getImmVal() << "\n";
    
}
  break;
  case 25:
{



        reg_action(_s->kids[0],indent);
        reg_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Mul(reg, reg)\n";
        std::cout << "imulq " << _s->kids[0]->node->getRegLocString() << ", "
                  << _s->kids[1]->node->getRegLocString() << "\n";
        _s->node->setRegLoc(false, _s->kids[1]->node->getRegLoc());
    
}
  break;
  case 26:
{



        reg_action(_s->kids[0],indent);
        imm_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Mul(reg, imm)\n";
        std::cout << "imulq " << _s->kids[1]->node->getImmVal() << ", "
                  << _s->kids[0]->node->getRegLocString() << "\n";
        _s->node->setRegLoc(false, _s->kids[0]->node->getRegLoc());
    
}
  break;
  case 27:
{



        imm_action(_s->kids[0],indent);
        reg_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Mul(imm, reg)\n";
        std::cout << "imulq " << _s->kids[0]->node->getImmVal() << ", "
                  << _s->kids[1]->node->getRegLocString() << "\n";
        _s->node->setRegLoc(false, _s->kids[1]->node->getRegLoc());
    
}
  break;
  case 28:
{



        imm_action(_s->kids[0],indent);
        imm_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   Mul(imm, imm)\n";
        std::cout << "FIXME: imulq " << _s->kids[0]->node->getImmVal() << ", " << _s->kids[0]->node->getImmVal() << "\n";
    
}
  break;
  case 29:
{



        reg_action(_s->kids[0],indent);
        reg_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   SDiv(reg, reg)\n";
        std::cout << "movq " << _s->kids[0]->node->getRegLocString() << ", %rax\n";
        std::cout << "cqto\n";
        std::cout << "idivq " << _s->kids[1]->node->getRegLocString() << "\n";
        _s->node->setRegLoc(false, Register::RAX);
    
}
  break;
  case 30:
{



        reg_action(_s->kids[0],indent);
        imm_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   SDiv(reg, imm)\n";
        std::cout << "movq " << _s->kids[0]->node->getRegLocString() << ", %rax\n";
        std::cout << "cqto\n";
        _s->node->setRegLoc(true);
        std::cout << "movq " << _s->kids[1]->node->getImmVal() << ", "
                  << _s->node->getRegLocString() << "\n";
        std::cout << "idivq " << _s->node->getRegLocString() << "\n";
        std::cout << "movq %rax, " << _s->node->getRegLocString() << "\n";
    
}
  break;
  case 31:
{



        imm_action(_s->kids[0],indent);
        reg_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   SDiv(imm, reg)\n";
        std::cout << "movq " << _s->kids[0]->node->getImmVal() << ", %rax\n";
        std::cout << "cqto\n";
        std::cout << "idivq " << _s->kids[1]->node->getRegLocString() << "\n";
        _s->node->setRegLoc(false, Register::RAX);
    
}
  break;
  case 32:
{



        imm_action(_s->kids[0],indent);
        imm_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "reg:   SDiv(imm, imm)\n";
        std::cout << "movq " << _s->kids[1]->node->getImmVal() << ", %rax\n";
        std::cout << "cqto\n";
        _s->node->setRegLoc(true);
        std::cout << "movq " << _s->kids[0]->node->getImmVal() << ", "
                  << _s->node->getRegLocString() << "\n";
        std::cout << "idivq " << _s->node->getRegLocString() << "\n";
        std::cout << "movq %rax, " << _s->node->getRegLocString() << "\n";
    
}
  break;
  case 38:
{



        std::cerr << "[DEBUG] " << "reg:    Call(label, args)\n";
        label_action(_s->kids[0],indent);
        args_action(_s->kids[1],indent, 0);
        auto* CB = llvm::cast<llvm::CallBase>(_s->node->getInstruction());
        std::cout << "callq " << _s->kids[0]->node->getLabelString2() << "\n";
        _s->node->setRegLoc(false, Register::RAX);
    
}
  break;
  case 39:
{



        std::cerr << "[DEBUG] " << "reg:    Call(args)\n";
        reg_action(_s->kids[0],indent);
        args_action(_s->kids[1],indent, 0);
        std::cout << "callq " << "*" << _s->kids[0]->node->getRegLocString() << "\n";
        _s->node->setRegLoc(false, Register::RAX);
    
}
  break;
  case 40:
{



        std::cerr << "[DEBUG] " << "reg:    Call(args)\n";
        mem_action(_s->kids[0],indent);
        args_action(_s->kids[1],indent, 0);
        std::cout << "callq " << "*" << _s->kids[0]->node->getMemLoc() << "\n";
        _s->node->setRegLoc(false, Register::RAX);
    
}
  break;
  }
}


void imm_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_imm[_s->rule.burm_imm];
  NODEPTR *_children;
  if(_s->rule.burm_imm==0)
    NO_ACTION(imm);
  switch(_ern){
  case 0:
{



        std::cerr << "[DEBUG] " << "imm:    Const\n";
        std::cerr << "[DEBUG] " << "\t" << _s->node->getImmVal() << "\n";
    
}
  break;
  }
}


void mem_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_mem[_s->rule.burm_mem];
  NODEPTR *_children;
  if(_s->rule.burm_mem==0)
    NO_ACTION(mem);
  switch(_ern){
  case 3:
{



        imm_action(_s->kids[0],indent);
        std::cerr << "[DEBUG] " << "mem:    Alloca(imm)\n";
    
}
  break;
  }
}


void label_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_label[_s->rule.burm_label];
  NODEPTR *_children;
  if(_s->rule.burm_label==0)
    NO_ACTION(label);
  switch(_ern){
  case 11:
{



        std::cerr << "[DEBUG] " << "label: Label\n";
    
}
  break;
  }
}


void cond_action(struct burm_state *_s, 

int indent)
{
  struct burm_state *_t;
  int _ern=burm_decode_cond[_s->rule.burm_cond];
  NODEPTR *_children;
  if(_s->rule.burm_cond==0)
    NO_ACTION(cond);
  switch(_ern){
  case 12:
{



        reg_action(_s->kids[0],indent);
        reg_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "cond: ICmp(reg, reg)\n";
        std::cout << "cmpq " << _s->kids[1]->node->getRegLocString() << ", " << _s->kids[0]->node->getRegLocString() << "\n";
    
}
  break;
  case 13:
{



        reg_action(_s->kids[0],indent);
        imm_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "cond: ICmp(reg, imm)\n";
        std::cout << "cmpq " << _s->kids[1]->node->getImmVal() << ", " << _s->kids[0]->node->getRegLocString() << "\n";
    
}
  break;
  case 14:
{



        imm_action(_s->kids[0],indent);
        reg_action(_s->kids[1],indent);
        std::cerr << "[DEBUG] " << "cond: ICmp(imm, reg)\n";
        auto AvailableRegister = RA->getAvailableRegister();
        std::cout << "movq " << _s->kids[0]->node->getImmVal() << ", "
                  << convertRegisterToString(AvailableRegister) << "\n";
        std::cout << "cmpq " << _s->kids[1]->node->getRegLocString() << ", " << convertRegisterToString(AvailableRegister) << "\n";
    
}
  break;
  }
}


void arg_action(struct burm_state *_s, 

int indent, unsigned argNo)
{
  struct burm_state *_t;
  int _ern=burm_decode_arg[_s->rule.burm_arg];
  NODEPTR *_children;
  if(_s->rule.burm_arg==0)
    NO_ACTION(arg);
  switch(_ern){
  case 33:
{



        reg_action(_s,indent);
        std::cerr << "[DEBUG] " << "arg:  reg\n";
        if (argNo < 6)
            std::cout << "movq " << _s->node->getRegLocString() << ", "
                      << convertRegisterToString(ArgRegs[argNo]) << "\n";
        else
            std::cout << "TODO: stack pass argument\n";
    
}
  break;
  case 34:
{



        std::cerr << "[DEBUG] " << "arg:  imm\n";
        if (argNo < 6)
            std::cout << "movq " << _s->node->getImmVal() << ", "
                      << convertRegisterToString(ArgRegs[argNo]) << "\n";
        else
            std::cout << "TODO: stack pass argument\n";
    
}
  break;
  case 35:
{



        std::cerr << "[DEBUG] " << "arg:  mem\n";
        if (argNo < 6)
            std::cout << "movq " << _s->node->getMemLoc() << ", "
                      << convertRegisterToString(ArgRegs[argNo]) << "\n";
        else
            std::cout << "TODO: stack pass argument\n";
    
}
  break;
  }
}


void args_action(struct burm_state *_s, 

int indent, unsigned argNo)
{
  struct burm_state *_t;
  int _ern=burm_decode_args[_s->rule.burm_args];
  NODEPTR *_children;
  if(_s->rule.burm_args==0)
    NO_ACTION(args);
  switch(_ern){
  case 36:
{



        std::cerr << "[DEBUG] " << "args:   ARGS(Undef, Undef)\n";
    
}
  break;
  case 37:
{



        arg_action(_s->kids[0],indent, argNo);
        args_action(_s->kids[1],indent, argNo+1);
        std::cerr << "[DEBUG] " << "args:   ARGS(value, args)\n";
    
}
  break;
  }
}
static void burm_closure_reg(struct burm_state *, COST);
static void burm_closure_imm(struct burm_state *, COST);
static void burm_closure_mem(struct burm_state *, COST);

static void burm_closure_reg(struct burm_state *s, COST c) {
  if(burm_cost_code(&c,33,s) && COST_LESS(c,s->cost[burm_arg_NT])) {
burm_trace(burm_np, 33, c);     s->cost[burm_arg_NT] = c ;
    s->rule.burm_arg = 1;
  }
}

static void burm_closure_imm(struct burm_state *s, COST c) {
  if(burm_cost_code(&c,34,s) && COST_LESS(c,s->cost[burm_arg_NT])) {
burm_trace(burm_np, 34, c);     s->cost[burm_arg_NT] = c ;
    s->rule.burm_arg = 2;
  }
}

static void burm_closure_mem(struct burm_state *s, COST c) {
  if(burm_cost_code(&c,35,s) && COST_LESS(c,s->cost[burm_arg_NT])) {
burm_trace(burm_np, 35, c);     s->cost[burm_arg_NT] = c ;
    s->rule.burm_arg = 3;
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
    if (   /* stmt: Ret(reg) */
      k[0]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,2,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 2, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 1;
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
      if(burm_cost_code(&c,16,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 16, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 8;
      }
    }
    if (   /* stmt: Br(cond,label,label) */
      k[0]->rule.burm_cond && 
      k[1]->rule.burm_label && 
      k[2]->rule.burm_label
    ) {
      if(burm_cost_code(&c,15,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 15, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 7;
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
      if(burm_cost_code(&c,20,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 20, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 7;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Add(imm,reg) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,19,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 19, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 6;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Add(reg,imm) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,18,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 18, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 5;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Add(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,17,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 17, c);         s->cost[burm_reg_NT] = c ;
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
      if(burm_cost_code(&c,24,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 24, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 11;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Sub(imm,reg) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,23,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 23, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 10;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Sub(reg,imm) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,22,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 22, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 9;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Sub(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,21,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 21, c);         s->cost[burm_reg_NT] = c ;
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
      if(burm_cost_code(&c,28,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 28, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 15;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Mul(imm,reg) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,27,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 27, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 14;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Mul(reg,imm) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,26,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 26, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 13;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Mul(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,25,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 25, c);         s->cost[burm_reg_NT] = c ;
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
      if(burm_cost_code(&c,32,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 32, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 19;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: SDiv(imm,reg) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,31,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 31, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 18;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: SDiv(reg,imm) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,30,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 30, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 17;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: SDiv(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,29,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 29, c);         s->cost[burm_reg_NT] = c ;
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
      if(burm_cost_code(&c,10,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 10, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 6;
      }
    }
    if (   /* stmt: Store(mem,mem) */
      k[0]->rule.burm_mem && 
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,9,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 9, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 5;
      }
    }
    if (   /* stmt: Store(imm,mem) */
      k[0]->rule.burm_imm && 
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,8,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 8, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 4;
      }
    }
    if (   /* stmt: Store(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,7,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 7, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 3;
      }
    }
    if (   /* stmt: Store(reg,mem) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_mem
    ) {
      if(burm_cost_code(&c,6,s) && COST_LESS(c,s->cost[burm_stmt_NT])) {
burm_trace(burm_np, 6, c);         s->cost[burm_stmt_NT] = c ;
        s->rule.burm_stmt = 2;
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
      if(burm_cost_code(&c,14,s) && COST_LESS(c,s->cost[burm_cond_NT])) {
burm_trace(burm_np, 14, c);         s->cost[burm_cond_NT] = c ;
        s->rule.burm_cond = 3;
      }
    }
    if (   /* cond: ICmp(reg,imm) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_imm
    ) {
      if(burm_cost_code(&c,13,s) && COST_LESS(c,s->cost[burm_cond_NT])) {
burm_trace(burm_np, 13, c);         s->cost[burm_cond_NT] = c ;
        s->rule.burm_cond = 2;
      }
    }
    if (   /* cond: ICmp(reg,reg) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_reg
    ) {
      if(burm_cost_code(&c,12,s) && COST_LESS(c,s->cost[burm_cond_NT])) {
burm_trace(burm_np, 12, c);         s->cost[burm_cond_NT] = c ;
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
      if(burm_cost_code(&c,40,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 40, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 22;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Call(reg,args) */
      k[0]->rule.burm_reg && 
      k[1]->rule.burm_args
    ) {
      if(burm_cost_code(&c,39,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 39, c);         s->cost[burm_reg_NT] = c ;
        s->rule.burm_reg = 21;
        burm_closure_reg(s, c );
      }
    }
    if (   /* reg: Call(label,args) */
      k[0]->rule.burm_label && 
      k[1]->rule.burm_args
    ) {
      if(burm_cost_code(&c,38,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 38, c);         s->cost[burm_reg_NT] = c ;
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
      if(burm_cost_code(&c,0,s) && COST_LESS(c,s->cost[burm_imm_NT])) {
burm_trace(burm_np, 0, c);         s->cost[burm_imm_NT] = c ;
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
      if(burm_cost_code(&c,11,s) && COST_LESS(c,s->cost[burm_label_NT])) {
burm_trace(burm_np, 11, c);         s->cost[burm_label_NT] = c ;
        s->rule.burm_label = 1;
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
      if(burm_cost_code(&c,37,s) && COST_LESS(c,s->cost[burm_args_NT])) {
burm_trace(burm_np, 37, c);         s->cost[burm_args_NT] = c ;
        s->rule.burm_args = 2;
      }
    }
    if (   /* args: Args(Undef,Undef) */
      k[0]->op == 0 &&  /* Undef */
      k[1]->op == 0 /* Undef */
    ) {
      if(burm_cost_code(&c,36,s) && COST_LESS(c,s->cost[burm_args_NT])) {
burm_trace(burm_np, 36, c);         s->cost[burm_args_NT] = c ;
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
      if(burm_cost_code(&c,1,s) && COST_LESS(c,s->cost[burm_reg_NT])) {
burm_trace(burm_np, 1, c);         s->cost[burm_reg_NT] = c ;
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
  case 36: /* args: Args(Undef,Undef) */
  case 11: /* label: Label */
  case 1: /* reg: Reg */
  case 0: /* imm: Const */
    break;
  case 16: /* stmt: Br(label,Undef,Undef) */
  case 5: /* reg: Load(reg) */
  case 4: /* reg: Load(mem) */
  case 3: /* mem: Alloca(imm) */
  case 2: /* stmt: Ret(reg) */
    kids[0] = burm_child(p,0);
    break;
  case 40: /* reg: Call(mem,args) */
  case 39: /* reg: Call(reg,args) */
  case 38: /* reg: Call(label,args) */
  case 37: /* args: Args(arg,args) */
  case 32: /* reg: SDiv(imm,imm) */
  case 31: /* reg: SDiv(imm,reg) */
  case 30: /* reg: SDiv(reg,imm) */
  case 29: /* reg: SDiv(reg,reg) */
  case 28: /* reg: Mul(imm,imm) */
  case 27: /* reg: Mul(imm,reg) */
  case 26: /* reg: Mul(reg,imm) */
  case 25: /* reg: Mul(reg,reg) */
  case 24: /* reg: Sub(imm,imm) */
  case 23: /* reg: Sub(imm,reg) */
  case 22: /* reg: Sub(reg,imm) */
  case 21: /* reg: Sub(reg,reg) */
  case 20: /* reg: Add(imm,imm) */
  case 19: /* reg: Add(imm,reg) */
  case 18: /* reg: Add(reg,imm) */
  case 17: /* reg: Add(reg,reg) */
  case 14: /* cond: ICmp(imm,reg) */
  case 13: /* cond: ICmp(reg,imm) */
  case 12: /* cond: ICmp(reg,reg) */
  case 10: /* stmt: Store(label,mem) */
  case 9: /* stmt: Store(mem,mem) */
  case 8: /* stmt: Store(imm,mem) */
  case 7: /* stmt: Store(reg,reg) */
  case 6: /* stmt: Store(reg,mem) */
    kids[0] = burm_child(p,0);
    kids[1] = burm_child(p,1);
    break;
  case 15: /* stmt: Br(cond,label,label) */
    kids[0] = burm_child(p,0);
    kids[1] = burm_child(p,1);
    kids[2] = burm_child(p,2);
    break;
  case 35: /* arg: mem */
  case 34: /* arg: imm */
  case 33: /* arg: reg */
    kids[0] = p;
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
static void burm_trace(NODEPTR p, int eruleno, COST cost) {
	if (shouldTrace)
		std::cerr << "[DEBUG] " << "0x" << p << " matched " << burm_string[eruleno] << " = " << eruleno << " with cost " << cost.getCost() << "\n";
}

static void gen(NODEPTR p) {
    if (burm_label(p) == 0)
        std::cerr << "[DEBUG] " << "no cover\n";
    else {
        stmt_action(p->getState(),0);
        if (shouldCover != 0)
            dumpCover(p, 1, 0);
    }
}

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
// #include "llvm/Support/CommandLine.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IRReader/IRReader.h"

using namespace llvm;

void FunctionASM::EmitAssembly()
{
    // FIXME
    std::cout << ".text\n"
              << ".globl " << FuncName << "\n"
              << ".type " << FuncName << ", @function\n"
              << FuncName << ":\n";

    // prologue
    std::cout << "pushq %rbp\n";
    std::cout << "movq %rsp, %rbp\n";
    std::cout << "subq $" << std::to_string(TotalAllocaSizeInBytes) << ", %rsp\n";

    // body
    for(auto* T: ExprTrees)
    {
        if (T->getOp() == /*Label*/69)
            std::cout << T->getLabelString() << ":\n";
        gen(T);
    }

    // epilogue
    std::cout << "movq %rbp, %rsp\n";
    std::cout << "popq %rbp\n";
    std::cout << "retq\n\n";
}

//static cl::opt<std::string>
//InputFilename(cl::Positional, cl::desc("<input bitcode>"), cl::init("-"));

int main(int argc, char *argv[]) {
/*
    Tree t;
    int i;

    for (i = 1; i < argc ; ++i) {
        if (strcmp(argv[i], "--cover") == 0){
            shouldCover = 1;
        }
        if (strcmp(argv[i], "--trace") == 0){
            shouldTrace = 1;
        }
    }
*/

    // parse arguments from command line
    // cl::ParseCommandLineOptions(argc, argv, "llc-olive\n");

    // prepare llvm context to read bitcode file
    LLVMContext Context;
    SMDiagnostic Error;
    std::unique_ptr<Module> M = parseIRFile(/*InputFilename*/argv[1], Error, Context);

    ExprTreeBuilder Builder(M->getDataLayout());
    Builder.visit(*M);
    for(auto& F: Builder.Functions)
    {
        F.EmitAssembly();
    }
    return 0;
}
