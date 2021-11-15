target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @foo(i64 %x, i64 %y) {
entry:
  %y2 = alloca i64, align 8
  %x1 = alloca i64, align 8
  store i64 %x, i64* %x1, align 8
  store i64 %y, i64* %y2, align 8
  %y3 = load i64, i64* %y2, align 8
  %mul = mul i64 2, %y3
  store i64 %mul, i64* %x1, align 8
  %x4 = load i64, i64* %x1, align 8
  %add = add i64 %x4, 1
  ret i64 %add
}

define i64 @main() {
entry:
  %input = alloca i64, align 8
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @fmtstr, i32 0, i32 0), i64* %input)
  %0 = load i64, i64* %input, align 8
  store i64 %0, i64* %a, align 8
  %a1 = load i64, i64* %a, align 8
  %call = call i64 @foo(i64 %a1, i64 17)
  store i64 %call, i64* %b, align 8
  %b2 = load i64, i64* %b, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %b2)
  ret i64 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
