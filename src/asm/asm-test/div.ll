target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  store i64 17, i64* %a, align 8
  %a1 = load i64, i64* %a, align 8
  %div = sdiv i64 %a1, 3
  %add = add i64 17, %div
  store i64 %add, i64* %b, align 8
  store i64 13, i64* %a, align 8
  %a2 = load i64, i64* %a, align 8
  %div3 = sdiv i64 %a2, 3
  store i64 %div3, i64* %b, align 8
  %b4 = load i64, i64* %b, align 8
  ret i64 %b4
}
