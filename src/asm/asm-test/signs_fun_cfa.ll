target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @posf(i64 %b) {
entry:
  %b1 = alloca i64, align 8
  store i64 %b, i64* %b1, align 8
  ret i64 5
}

define i64 @negf(i64 %c) {
entry:
  %c1 = alloca i64, align 8
  store i64 %c, i64* %c1, align 8
  ret i64 -5
}

define i64 @main() {
entry:
  %pos = alloca i64, align 8
  %neg = alloca i64, align 8
  %top = alloca i64, align 8
  %u = alloca i64, align 8
  %f = alloca i64 (i64)*, align 8
  store i64 0, i64* %u, align 8
  %call = call i64 @posf(i64 -4)
  store i64 %call, i64* %pos, align 8
  %pos1 = load i64, i64* %pos, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %pos1)
  %call2 = call i64 @negf(i64 3)
  store i64 %call2, i64* %neg, align 8
  %neg3 = load i64, i64* %neg, align 8
  %printf4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %neg3)
  %u5 = load i64, i64* %u, align 8
  %icmp.sgt = icmp sgt i64 %u5, 0
  br i1 %icmp.sgt, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  store i64 (i64)* @posf, i64 (i64)** %f, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  store i64 (i64)* @negf, i64 (i64)** %f, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %f6 = load i64 (i64)*, i64 (i64)** %f, align 8
  %call7 = call i64 %f6(i64 4)
  store i64 %call7, i64* %top, align 8
  %top8 = load i64, i64* %top, align 8
  %printf9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %top8)
  ret i64 0
}

declare i32 @printf(i8*, ...)
