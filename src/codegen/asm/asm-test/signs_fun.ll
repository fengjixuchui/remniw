target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @idf(i64 %a) {
entry:
  %a1 = alloca i64, align 8
  store i64 %a, i64* %a1, align 8
  %a2 = load i64, i64* %a1, align 8
  ret i64 %a2
}

define i64 @posf(i64 %b) {
entry:
  %b1 = alloca i64, align 8
  store i64 %b, i64* %b1, align 8
  %b2 = load i64, i64* %b1, align 8
  ret i64 %b2
}

define i64 @negf(i64 %c) {
entry:
  %c1 = alloca i64, align 8
  store i64 %c, i64* %c1, align 8
  %c2 = load i64, i64* %c1, align 8
  ret i64 %c2
}

define i64 @main() {
entry:
  %pos = alloca i64, align 8
  %neg = alloca i64, align 8
  %top = alloca i64, align 8
  %zero = alloca i64, align 8
  store i64 0, i64* %zero, align 8
  %call = call i64 @idf(i64 5)
  store i64 %call, i64* %top, align 8
  %top1 = load i64, i64* %top, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %top1)
  %call2 = call i64 @idf(i64 -4)
  store i64 %call2, i64* %top, align 8
  %top3 = load i64, i64* %top, align 8
  %printf4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %top3)
  %call5 = call i64 @posf(i64 5)
  store i64 %call5, i64* %pos, align 8
  %pos6 = load i64, i64* %pos, align 8
  %printf7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %pos6)
  %call8 = call i64 @posf(i64 7)
  store i64 %call8, i64* %pos, align 8
  %pos9 = load i64, i64* %pos, align 8
  %printf10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %pos9)
  %call11 = call i64 @negf(i64 -4)
  store i64 %call11, i64* %neg, align 8
  %neg12 = load i64, i64* %neg, align 8
  %printf13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %neg12)
  %call14 = call i64 @negf(i64 -8)
  store i64 %call14, i64* %neg, align 8
  %neg15 = load i64, i64* %neg, align 8
  %printf16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %neg15)
  ret i64 0
}

declare i32 @printf(i8*, ...)
