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
  %z5 = load i64, i64* %z, align 8
  %y6 = load i64, i64* %y, align 8
  %add7 = add i64 %z5, %y6
  ret i64 %add7
}
