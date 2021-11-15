target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %s1 = alloca i64, align 8
  %s2 = alloca i64, align 8
  %s3 = alloca i64, align 8
  %p = alloca i64*, align 8
  %q = alloca i64*, align 8
  store i64* %s1, i64** %p, align 8
  store i64* %s2, i64** %p, align 8
  store i64* %s3, i64** %q, align 8
  %p1 = load i64*, i64** %p, align 8
  store i64* %p1, i64** %q, align 8
  %q2 = load i64*, i64** %q, align 8
  %icmp.eq = icmp eq i64* %q2, %s2
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i1 %icmp.eq)
  ret i64 0
}

declare i32 @printf(i8*, ...)
