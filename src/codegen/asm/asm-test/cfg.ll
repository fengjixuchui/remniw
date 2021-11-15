target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %input = alloca i64, align 8
  %n = alloca i64, align 8
  %f = alloca i64, align 8
  %scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @fmtstr, i32 0, i32 0), i64* %input)
  %0 = load i64, i64* %input, align 8
  store i64 %0, i64* %n, align 8
  store i64 1, i64* %f, align 8
  %n1 = load i64, i64* %n, align 8
  %icmp.sgt = icmp sgt i64 %n1, 0
  br i1 %icmp.sgt, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %f2 = load i64, i64* %f, align 8
  %n3 = load i64, i64* %n, align 8
  %mul = mul i64 %f2, %n3
  store i64 %mul, i64* %f, align 8
  %n4 = load i64, i64* %n, align 8
  %sub = sub i64 %n4, 1
  store i64 %sub, i64* %n, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %f5 = load i64, i64* %f, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %f5)
  %n6 = load i64, i64* %n, align 8
  %printf7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %n6)
  ret i64 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
