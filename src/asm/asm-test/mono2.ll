target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @foo(i64 %n) {
entry:
  %n1 = alloca i64, align 8
  store i64 %n, i64* %n1, align 8
  %n2 = load i64, i64* %n1, align 8
  ret i64 %n2
}

define i64 @main() {
entry:
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  store i64 2, i64* %a, align 8
  %a1 = load i64, i64* %a, align 8
  %call = call i64 @foo(i64 %a1)
  store i64 %call, i64* %b, align 8
  %b2 = load i64, i64* %b, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %b2)
  ret i64 0
}

declare i32 @printf(i8*, ...)
