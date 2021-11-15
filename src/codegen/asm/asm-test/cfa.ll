target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @inc(i64 %i) {
entry:
  %i1 = alloca i64, align 8
  store i64 %i, i64* %i1, align 8
  %i2 = load i64, i64* %i1, align 8
  %add = add i64 %i2, 1
  ret i64 %add
}

define i64 @dec(i64 %j) {
entry:
  %j1 = alloca i64, align 8
  store i64 %j, i64* %j1, align 8
  %j2 = load i64, i64* %j1, align 8
  %sub = sub i64 %j2, 1
  ret i64 %sub
}

define i64 @ide(i64 %k) {
entry:
  %k1 = alloca i64, align 8
  store i64 %k, i64* %k1, align 8
  %k2 = load i64, i64* %k1, align 8
  ret i64 %k2
}

define i64 @foo(i64 %n) {
entry:
  %n1 = alloca i64, align 8
  store i64 %n, i64* %n1, align 8
  %r = alloca i64, align 8
  %n2 = load i64, i64* %n1, align 8
  %icmp.eq = icmp eq i64 %n2, 0
  br i1 %icmp.eq, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %n3 = load i64, i64* %n1, align 8
  %call = call i64 @dec(i64 %n3)
  store i64 %call, i64* %r, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %n4 = load i64, i64* %n1, align 8
  %call5 = call i64 @inc(i64 %n4)
  store i64 %call5, i64* %r, align 8
  %r6 = load i64, i64* %r, align 8
  ret i64 %r6
}

define i64 @main() {
entry:
  %input = alloca i64, align 8
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  %scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @fmtstr, i32 0, i32 0), i64* %input)
  %0 = load i64, i64* %input, align 8
  store i64 %0, i64* %x, align 8
  %x1 = load i64, i64* %x, align 8
  %icmp.sgt = icmp sgt i64 %x1, 0
  br i1 %icmp.sgt, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %x2 = load i64, i64* %x, align 8
  %call = call i64 @foo(i64 %x2)
  store i64 %call, i64* %y, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  %x3 = load i64, i64* %x, align 8
  %call4 = call i64 @foo(i64 %x3)
  store i64 %call4, i64* %y, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %y5 = load i64, i64* %y, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %y5)
  ret i64 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
