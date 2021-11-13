target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  %z = alloca i64, align 8
  %w = alloca i64, align 8
  store i64 0, i64* %x, align 8
  %x1 = load i64, i64* %x, align 8
  store i64 %x1, i64* %z, align 8
  %z2 = load i64, i64* %z, align 8
  store i64 %z2, i64* %w, align 8
  %w3 = load i64, i64* %w, align 8
  store i64 %w3, i64* %x, align 8
  %x4 = load i64, i64* %x, align 8
  %add = add i64 %x4, 1
  store i64 %add, i64* %y, align 8
  %x5 = load i64, i64* %x, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %x5)
  ret i64 0
}

declare i32 @printf(i8*, ...)
