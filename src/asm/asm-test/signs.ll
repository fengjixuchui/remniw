target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @fun(i64 %x) {
entry:
  %x1 = alloca i64, align 8
  store i64 %x, i64* %x1, align 8
  %y = alloca i64, align 8
  %k = alloca i64, align 8
  store i64 8, i64* %k, align 8
  store i64 7, i64* %y, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %k2 = load i64, i64* %k, align 8
  %y3 = load i64, i64* %y, align 8
  %icmp.sgt = icmp sgt i64 %k2, %y3
  br i1 %icmp.sgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %k4 = load i64, i64* %k, align 8
  %sub = sub i64 %k4, 1
  store i64 %sub, i64* %k, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  ret i64 0
}

define i64 @main() {
entry:
  %pos = alloca i64, align 8
  %neg = alloca i64, align 8
  %top = alloca i64, align 8
  %zero = alloca i64, align 8
  %later = alloca i64, align 8
  store i64 10, i64* %pos, align 8
  %pos1 = load i64, i64* %pos, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %pos1)
  store i64 25, i64* %pos, align 8
  %pos2 = load i64, i64* %pos, align 8
  %printf3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %pos2)
  store i64 -10, i64* %neg, align 8
  %neg4 = load i64, i64* %neg, align 8
  %printf5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %neg4)
  store i64 -25, i64* %neg, align 8
  %neg6 = load i64, i64* %neg, align 8
  %printf7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %neg6)
  store i64 -25, i64* %neg, align 8
  %neg8 = load i64, i64* %neg, align 8
  %printf9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %neg8)
  store i64 0, i64* %top, align 8
  %top10 = load i64, i64* %top, align 8
  %printf11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %top10)
  %top12 = load i64, i64* %top, align 8
  %mul = mul i64 %top12, 5
  store i64 %mul, i64* %top, align 8
  %top13 = load i64, i64* %top, align 8
  %printf14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %top13)
  %top15 = load i64, i64* %top, align 8
  %mul16 = mul i64 %top15, 0
  store i64 %mul16, i64* %zero, align 8
  %zero17 = load i64, i64* %zero, align 8
  %printf18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %zero17)
  %zero19 = load i64, i64* %zero, align 8
  %mul20 = mul i64 5, %zero19
  store i64 %mul20, i64* %zero, align 8
  %zero21 = load i64, i64* %zero, align 8
  %printf22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %zero21)
  store i64 7, i64* %later, align 8
  %later23 = load i64, i64* %later, align 8
  %printf24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %later23)
  ret i64 0
}

declare i32 @printf(i8*, ...)
