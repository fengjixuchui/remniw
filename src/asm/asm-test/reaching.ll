target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %input = alloca i64, align 8
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  %z = alloca i64, align 8
  %scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @fmtstr, i32 0, i32 0), i64* %input)
  %0 = load i64, i64* %input, align 8
  store i64 %0, i64* %x, align 8
  br label %while.cond

while.cond:                                       ; preds = %if.end15, %entry
  %x1 = load i64, i64* %x, align 8
  %icmp.sgt = icmp sgt i64 %x1, 1
  br i1 %icmp.sgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %x2 = load i64, i64* %x, align 8
  %div = sdiv i64 %x2, 2
  store i64 %div, i64* %y, align 8
  %y3 = load i64, i64* %y, align 8
  %icmp.sgt4 = icmp sgt i64 %y3, 3
  br i1 %icmp.sgt4, label %if.then, label %if.else

if.then:                                          ; preds = %while.body
  %x5 = load i64, i64* %x, align 8
  %y6 = load i64, i64* %y, align 8
  %sub = sub i64 %x5, %y6
  store i64 %sub, i64* %x, align 8
  br label %if.end

if.else:                                          ; preds = %while.body
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %x7 = load i64, i64* %x, align 8
  %sub8 = sub i64 %x7, 4
  store i64 %sub8, i64* %z, align 8
  %z9 = load i64, i64* %z, align 8
  %icmp.sgt10 = icmp sgt i64 %z9, 0
  br i1 %icmp.sgt10, label %if.then11, label %if.else14

if.then11:                                        ; preds = %if.end
  %x12 = load i64, i64* %x, align 8
  %div13 = sdiv i64 %x12, 2
  store i64 %div13, i64* %x, align 8
  br label %if.end15

if.else14:                                        ; preds = %if.end
  br label %if.end15

if.end15:                                         ; preds = %if.else14, %if.then11
  %z16 = load i64, i64* %z, align 8
  %sub17 = sub i64 %z16, 1
  store i64 %sub17, i64* %z, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %x18 = load i64, i64* %x, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %x18)
  ret i64 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
