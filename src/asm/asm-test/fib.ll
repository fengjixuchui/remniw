target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @fib(i64 %n) {
entry:
  %n1 = alloca i64, align 8
  store i64 %n, i64* %n1, align 8
  %f1 = alloca i64, align 8
  %f2 = alloca i64, align 8
  %i = alloca i64, align 8
  %temp = alloca i64, align 8
  store i64 1, i64* %f1, align 8
  store i64 1, i64* %f2, align 8
  %n2 = load i64, i64* %n1, align 8
  store i64 %n2, i64* %i, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %i3 = load i64, i64* %i, align 8
  %icmp.sgt = icmp sgt i64 %i3, 1
  br i1 %icmp.sgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %f14 = load i64, i64* %f1, align 8
  %f25 = load i64, i64* %f2, align 8
  %add = add i64 %f14, %f25
  store i64 %add, i64* %temp, align 8
  %f26 = load i64, i64* %f2, align 8
  store i64 %f26, i64* %f1, align 8
  %temp7 = load i64, i64* %temp, align 8
  store i64 %temp7, i64* %f2, align 8
  %i8 = load i64, i64* %i, align 8
  %sub = sub i64 %i8, 1
  store i64 %sub, i64* %i, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %f29 = load i64, i64* %f2, align 8
  ret i64 %f29
}

define i64 @main() {
entry:
  %input = alloca i64, align 8
  %n = alloca i64, align 8
  %scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @fmtstr, i32 0, i32 0), i64* %input)
  %0 = load i64, i64* %input, align 8
  store i64 %0, i64* %n, align 8
  %n1 = load i64, i64* %n, align 8
  %call = call i64 @fib(i64 %n1)
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %call)
  ret i64 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
