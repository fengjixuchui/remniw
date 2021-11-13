target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %input = alloca i64, align 8
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  store i64 0, i64* %x, align 8
  store i64 0, i64* %y, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @fmtstr, i32 0, i32 0), i64* %input)
  %0 = load i64, i64* %input, align 8
  %1 = icmp ne i64 %0, 0
  br i1 %1, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  store i64 7, i64* %x, align 8
  %x1 = load i64, i64* %x, align 8
  %add = add i64 %x1, 1
  store i64 %add, i64* %x, align 8
  %y2 = load i64, i64* %y, align 8
  %add3 = add i64 %y2, 1
  store i64 %add3, i64* %y, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %x4 = load i64, i64* %x, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %x4)
  %y5 = load i64, i64* %y, align 8
  %printf6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %y5)
  ret i64 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
