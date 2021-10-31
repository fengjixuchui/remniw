target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %i = alloca i64, align 8
  store i64 5, i64* %a, align 8
  store i64 42, i64* %b, align 8
  %a1 = load i64, i64* %a, align 8
  store i64 %a1, i64* %i, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %b2 = load i64, i64* %b, align 8
  %i3 = load i64, i64* %i, align 8
  %icmp.sgt = icmp sgt i64 %b2, %i3
  br i1 %icmp.sgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %i4 = load i64, i64* %i, align 8
  %add = add i64 %i4, 1
  store i64 %add, i64* %i, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %i5 = load i64, i64* %i, align 8
  ret i64 %i5
}
