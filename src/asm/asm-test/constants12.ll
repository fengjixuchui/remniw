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
  %mul = mul i64 5, %a3
  %b4 = load i64, i64* %b2, align 8
  %mul5 = mul i64 7, %b4
  %add = add i64 %mul, %mul5
  ret i64 %add
}

define i64 @main() {
entry:
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  %z = alloca i64, align 8
  %n = alloca i64, align 8
  store i64 12, i64* %x, align 8
  store i64 17, i64* %y, align 8
  %call = call i64 @f(i64 1, i64 2)
  store i64 %call, i64* %z, align 8
  %z1 = load i64, i64* %z, align 8
  ret i64 %z1
}
