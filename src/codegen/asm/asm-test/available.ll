target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  %z = alloca i64, align 8
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  store i64 2, i64* %a, align 8
  store i64 3, i64* %b, align 8
  %a1 = load i64, i64* %a, align 8
  %b2 = load i64, i64* %b, align 8
  %add = add i64 %a1, %b2
  store i64 %add, i64* %z, align 8
  %a3 = load i64, i64* %a, align 8
  %b4 = load i64, i64* %b, align 8
  %mul = mul i64 %a3, %b4
  store i64 %mul, i64* %y, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %y5 = load i64, i64* %y, align 8
  %a6 = load i64, i64* %a, align 8
  %b7 = load i64, i64* %b, align 8
  %add8 = add i64 %a6, %b7
  %icmp.sgt = icmp sgt i64 %y5, %add8
  br i1 %icmp.sgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %a9 = load i64, i64* %a, align 8
  %add10 = add i64 %a9, 1
  store i64 %add10, i64* %a, align 8
  %a11 = load i64, i64* %a, align 8
  %b12 = load i64, i64* %b, align 8
  %add13 = add i64 %a11, %b12
  store i64 %add13, i64* %x, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %a14 = load i64, i64* %a, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %a14)
  %x15 = load i64, i64* %x, align 8
  %printf16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %x15)
  ret i64 0
}

declare i32 @printf(i8*, ...)
