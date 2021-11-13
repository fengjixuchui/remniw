target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @f(i64 %x) {
entry:
  %x1 = alloca i64, align 8
  store i64 %x, i64* %x1, align 8
  %r = alloca i64, align 8
  %x2 = load i64, i64* %x1, align 8
  %icmp.sgt = icmp sgt i64 %x2, 100
  br i1 %icmp.sgt, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %x3 = load i64, i64* %x1, align 8
  %add = add i64 %x3, -10
  store i64 %add, i64* %r, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  %x4 = load i64, i64* %x1, align 8
  %add5 = add i64 %x4, 11
  %call = call i64 @f(i64 %add5)
  %call6 = call i64 @f(i64 %call)
  store i64 %call6, i64* %r, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %r7 = load i64, i64* %r, align 8
  ret i64 %r7
}

define i64 @main() {
entry:
  %call = call i64 @f(i64 17)
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %call)
  %call1 = call i64 @f(i64 95)
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %call1)
  %call3 = call i64 @f(i64 150)
  %printf4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %call3)
  %call5 = call i64 @f(i64 200)
  %printf6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %call5)
  ret i64 0
}

declare i32 @printf(i8*, ...)
