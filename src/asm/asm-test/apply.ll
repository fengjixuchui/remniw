target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @apply(i64 (i64)* %f, i64 %a) {
entry:
  %a2 = alloca i64, align 8
  %f1 = alloca i64 (i64)*, align 8
  store i64 (i64)* %f, i64 (i64)** %f1, align 8
  store i64 %a, i64* %a2, align 8
  %f3 = load i64 (i64)*, i64 (i64)** %f1, align 8
  %a4 = load i64, i64* %a2, align 8
  %call = call i64 %f3(i64 %a4)
  ret i64 %call
}

define i64 @fib(i64 %n) {
entry:
  %n1 = alloca i64, align 8
  store i64 %n, i64* %n1, align 8
  %result = alloca i64, align 8
  %n2 = load i64, i64* %n1, align 8
  %icmp.sgt = icmp sgt i64 %n2, 1
  br i1 %icmp.sgt, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %n3 = load i64, i64* %n1, align 8
  %sub = sub i64 %n3, 1
  %call = call i64 @fib(i64 %sub)
  %n4 = load i64, i64* %n1, align 8
  %sub5 = sub i64 %n4, 2
  %call6 = call i64 @fib(i64 %sub5)
  %add = add i64 %call, %call6
  store i64 %add, i64* %result, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  store i64 1, i64* %result, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %result7 = load i64, i64* %result, align 8
  ret i64 %result7
}

define i64 @main() {
entry:
  %call = call i64 @apply(i64 (i64)* @fib, i64 5)
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %call)
  ret i64 0
}

declare i32 @printf(i8*, ...)
