target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %x = alloca i64, align 8
  %y = alloca i64*, align 8
  store i64 10, i64* %x, align 8
  store i64* %x, i64** %y, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %y1 = load i64*, i64** %y, align 8
  %0 = load i64, i64* %y1, align 8
  %icmp.sgt = icmp sgt i64 %0, 0
  br i1 %icmp.sgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %y2 = load i64*, i64** %y, align 8
  %1 = load i64, i64* %y2, align 8
  %sub = sub i64 %1, 1
  %2 = load i64*, i64** %y, align 8
  store i64 %sub, i64* %2, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %x3 = load i64, i64* %x, align 8
  ret i64 %x3
}
