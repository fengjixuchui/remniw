target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @g(i64* %a) {
entry:
  %a1 = alloca i64*, align 8
  store i64* %a, i64** %a1, align 8
  %a2 = load i64*, i64** %a1, align 8
  %0 = load i64, i64* %a2, align 8
  ret i64 %0
}

define i64 @f() {
entry:
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  store i64 10, i64* %a, align 8
  %a1 = load i64, i64* %a, align 8
  %icmp.eq = icmp eq i64 %a1, 10
  br i1 %icmp.eq, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %call = call i64 @g(i64* %a)
  store i64 %call, i64* %b, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %a2 = load i64, i64* %a, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %a2)
  %b3 = load i64, i64* %b, align 8
  %printf4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %b3)
  ret i64 0
}

define i64 @main() {
entry:
  %call = call i64 @f()
  ret i64 %call
}

declare i32 @printf(i8*, ...)
