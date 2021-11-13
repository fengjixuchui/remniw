target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %p = alloca i64, align 8
  %q = alloca i64, align 8
  %x = alloca i64, align 8
  %y = alloca i64*, align 8
  store i64 0, i64* %q, align 8
  store i64* %q, i64** %y, align 8
  %y1 = load i64*, i64** %y, align 8
  %0 = load i64, i64* %y1, align 8
  store i64 %0, i64* %x, align 8
  %y2 = load i64*, i64** %y, align 8
  %1 = load i64, i64* %y2, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %1)
  store i64 1, i64* %p, align 8
  store i64* %p, i64** %y, align 8
  %y3 = load i64*, i64** %y, align 8
  %2 = load i64, i64* %y3, align 8
  %printf4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %2)
  ret i64 0
}

declare i32 @printf(i8*, ...)
