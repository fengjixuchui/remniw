target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @f(i64 %a, i64 %b) {
entry:
  %b2 = alloca i64, align 8
  %a1 = alloca i64, align 8
  store i64 %a, i64* %a1, align 8
  store i64 %b, i64* %b2, align 8
  %a3 = load i64, i64* %a1, align 8
  %b4 = load i64, i64* %b2, align 8
  %call = call i64 @g(i64 %a3, i64 %b4)
  ret i64 %call
}

define i64 @g(i64 %a, i64 %b) {
entry:
  %b2 = alloca i64, align 8
  %a1 = alloca i64, align 8
  store i64 %a, i64* %a1, align 8
  store i64 %b, i64* %b2, align 8
  %a3 = load i64, i64* %a1, align 8
  %b4 = load i64, i64* %b2, align 8
  %add = add i64 %a3, %b4
  ret i64 %add
}

define i64 @main() {
entry:
  %input1 = alloca i64, align 8
  %input = alloca i64, align 8
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @fmtstr, i32 0, i32 0), i64* %input)
  %0 = load i64, i64* %input, align 8
  store i64 %0, i64* %a, align 8
  %scanf2 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @fmtstr, i32 0, i32 0), i64* %input1)
  %1 = load i64, i64* %input1, align 8
  store i64 %1, i64* %b, align 8
  %a3 = load i64, i64* %a, align 8
  %b4 = load i64, i64* %b, align 8
  %call = call i64 @f(i64 %a3, i64 %b4)
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %call)
  ret i64 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
