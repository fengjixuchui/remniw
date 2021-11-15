target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @g(i64* %a) {
entry:
  %a1 = alloca i64*, align 8
  store i64* %a, i64** %a1, align 8
  %0 = load i64*, i64** %a1, align 8
  store i64 17, i64* %0, align 8
  ret i64 11
}

define i64 @succ(i64 %i) {
entry:
  %i1 = alloca i64, align 8
  store i64 %i, i64* %i1, align 8
  %i2 = load i64, i64* %i1, align 8
  %add = add i64 %i2, 1
  ret i64 %add
}

define i64 @h(i64 (i64)* %pf, i64 %i) {
entry:
  %i2 = alloca i64, align 8
  %pf1 = alloca i64 (i64)*, align 8
  store i64 (i64)* %pf, i64 (i64)** %pf1, align 8
  store i64 %i, i64* %i2, align 8
  %pf3 = load i64 (i64)*, i64 (i64)** %pf1, align 8
  %i4 = load i64, i64* %i2, align 8
  %call = call i64 %pf3(i64 %i4)
  ret i64 %call
}

define i64 @f(i64 %a) {
entry:
  %a1 = alloca i64, align 8
  store i64 %a, i64* %a1, align 8
  %b = alloca i64, align 8
  %c = alloca i64, align 8
  %d = alloca i64, align 8
  store i64 3, i64* %b, align 8
  %a2 = load i64, i64* %a1, align 8
  %b3 = load i64, i64* %b, align 8
  %add = add i64 %a2, %b3
  ret i64 %add
}

define i64 @test(i64 %i) {
entry:
  %i1 = alloca i64, align 8
  store i64 %i, i64* %i1, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %i2 = load i64, i64* %i1, align 8
  %icmp.sgt = icmp sgt i64 %i2, 0
  br i1 %icmp.sgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %i3 = load i64, i64* %i1, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %i3)
  %i4 = load i64, i64* %i1, align 8
  %sub = sub i64 %i4, 1
  store i64 %sub, i64* %i1, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  ret i64 0
}

define i64 @main() {
entry:
  %a = alloca i64, align 8
  store i64 17, i64* %a, align 8
  %a1 = load i64, i64* %a, align 8
  %icmp.sgt = icmp sgt i64 %a1, 17
  br i1 %icmp.sgt, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  store i64 13, i64* %a, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  store i64 19, i64* %a, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %call = call i64 @h(i64 (i64)* @succ, i64 17)
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %call)
  ret i64 0
}

declare i32 @printf(i8*, ...)
