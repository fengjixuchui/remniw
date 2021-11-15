target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @rec(i64 %n) {
entry:
  %n1 = alloca i64, align 8
  store i64 %n, i64* %n1, align 8
  %f = alloca i64, align 8
  %n2 = load i64, i64* %n1, align 8
  %icmp.eq = icmp eq i64 %n2, 0
  br i1 %icmp.eq, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  store i64 1, i64* %f, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  %n3 = load i64, i64* %n1, align 8
  %n4 = load i64, i64* %n1, align 8
  %sub = sub i64 %n4, 1
  %call = call i64 @rec(i64 %sub)
  %mul = mul i64 %n3, %call
  store i64 %mul, i64* %f, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %f5 = load i64, i64* %f, align 8
  ret i64 %f5
}

define i64 @main() {
entry:
  %input = alloca i64, align 8
  %n = alloca i64, align 8
  %scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @fmtstr, i32 0, i32 0), i64* %input)
  %0 = load i64, i64* %input, align 8
  store i64 %0, i64* %n, align 8
  %n1 = load i64, i64* %n, align 8
  %call = call i64 @rec(i64 %n1)
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %call)
  ret i64 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
