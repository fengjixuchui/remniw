target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %input = alloca i64, align 8
  %x = alloca i64, align 8
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @fmtstr, i32 0, i32 0), i64* %input)
  %0 = load i64, i64* %input, align 8
  store i64 %0, i64* %x, align 8
  %x1 = load i64, i64* %x, align 8
  %sub = sub i64 %x1, 1
  store i64 %sub, i64* %a, align 8
  %x2 = load i64, i64* %x, align 8
  %sub3 = sub i64 %x2, 2
  store i64 %sub3, i64* %b, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %x4 = load i64, i64* %x, align 8
  %icmp.sgt = icmp sgt i64 %x4, 0
  br i1 %icmp.sgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %a5 = load i64, i64* %a, align 8
  %b6 = load i64, i64* %b, align 8
  %mul = mul i64 %a5, %b6
  %x7 = load i64, i64* %x, align 8
  %sub8 = sub i64 %mul, %x7
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %sub8)
  %x9 = load i64, i64* %x, align 8
  %sub10 = sub i64 %x9, 1
  store i64 %sub10, i64* %x, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %a11 = load i64, i64* %a, align 8
  %b12 = load i64, i64* %b, align 8
  %mul13 = mul i64 %a11, %b12
  %printf14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %mul13)
  ret i64 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
