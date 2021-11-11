target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @f(i64 %x) {
entry:
  %x1 = alloca i64, align 8
  store i64 %x, i64* %x1, align 8
  %x2 = load i64, i64* %x1, align 8
  ret i64 %x2
}

define i64 @g(i64 %y) {
entry:
  %y1 = alloca i64, align 8
  store i64 %y, i64* %y1, align 8
  %y2 = load i64, i64* %y1, align 8
  %call = call i64 @f(i64 %y2)
  ret i64 %call
}

define i64 @main() {
entry:
  %t = alloca i64 (i64)*, align 8
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  store i64 (i64)* @f, i64 (i64)** %t, align 8
  %t1 = load i64 (i64)*, i64 (i64)** %t, align 8
  %call = call i64 %t1(i64 1)
  store i64 %call, i64* %a, align 8
  store i64 (i64)* @g, i64 (i64)** %t, align 8
  %t2 = load i64 (i64)*, i64 (i64)** %t, align 8
  %call3 = call i64 %t2(i64 2)
  store i64 %call3, i64* %b, align 8
  %a4 = load i64, i64* %a, align 8
  %b5 = load i64, i64* %b, align 8
  %add = add i64 %a4, %b5
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %add)
  ret i64 0
}

declare i32 @printf(i8*, ...)
