target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() #0 {
  %1 = alloca i64, align 8
  store i64 1, i64* %1, align 8
  %2 = load i64, i64* %1, align 8
  %3 = add nsw i64 %2, 2
  %4 = add nsw i64 %3, 3
  %5 = add nsw i64 %4, 4
  ret i64 %5
}
