target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  %z = alloca i64, align 8
  store i64 1, i64* %x, align 8
  store i64 0, i64* %y, align 8
  store i64 20, i64* %z, align 8
  %x1 = load i64, i64* %x, align 8
  %icmp.eq = icmp eq i64 %x1, 1
  br i1 %icmp.eq, label %if.then, label %if.else8

if.then:                                          ; preds = %entry
  br label %while.cond

while.cond:                                       ; preds = %if.end, %if.then
  %x2 = load i64, i64* %x, align 8
  %icmp.sgt = icmp sgt i64 %x2, 0
  br i1 %icmp.sgt, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %y3 = load i64, i64* %y, align 8
  %icmp.eq4 = icmp eq i64 %y3, 0
  br i1 %icmp.eq4, label %if.then5, label %if.else

if.then5:                                         ; preds = %while.body
  %z6 = load i64, i64* %z, align 8
  %add = add i64 %z6, 1
  store i64 %add, i64* %z, align 8
  br label %if.end

if.else:                                          ; preds = %while.body
  store i64 0, i64* %x, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then5
  %x7 = load i64, i64* %x, align 8
  %sub = sub i64 %x7, 1
  store i64 %sub, i64* %x, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  br label %if.end9

if.else8:                                         ; preds = %entry
  br label %if.end9

if.end9:                                          ; preds = %if.else8, %while.end
  %z10 = load i64, i64* %z, align 8
  ret i64 %z10
}
