target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @div(i64 %a, i64 %b) {
entry:
  %b2 = alloca i64, align 8
  %a1 = alloca i64, align 8
  store i64 %a, i64* %a1, align 8
  store i64 %b, i64* %b2, align 8
  %a3 = load i64, i64* %a1, align 8
  %b4 = load i64, i64* %b2, align 8
  %div = sdiv i64 %a3, %b4
  ret i64 %div
}

define i64 @main() {
entry:
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %c = alloca i64*, align 8
  store i64 18, i64* %a, align 8
  %a1 = load i64, i64* %a, align 8
  %div = sdiv i64 %a1, 3
  %add = add i64 17, %div
  store i64 %add, i64* %b, align 8
  %a2 = load i64, i64* %a, align 8
  %icmp.sgt = icmp sgt i64 %a2, 17
  br i1 %icmp.sgt, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  store i64 7, i64* %a, align 8
  store i64* %a, i64** %c, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  %a3 = load i64, i64* %a, align 8
  %div4 = sdiv i64 %a3, 3
  store i64 %div4, i64* %b, align 8
  store i64* %b, i64** %c, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %c5 = load i64*, i64** %c, align 8
  %0 = load i64, i64* %c5, align 8
  store i64 %0, i64* %a, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %if.end
  %a6 = load i64, i64* %a, align 8
  %icmp.sgt7 = icmp sgt i64 %a6, 5
  br i1 %icmp.sgt7, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %a8 = load i64, i64* %a, align 8
  %div9 = sdiv i64 %a8, 2
  %call = call i64 @div(i64 %div9, i64 3)
  store i64 %call, i64* %a, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %a10 = load i64, i64* %a, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %a10)
  ret i64 0
}

declare i32 @printf(i8*, ...)
