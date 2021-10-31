target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  %z = alloca i64, align 8
  store i64 42, i64* %x, align 8
  store i64 43, i64* %y, align 8
  %x1 = load i64, i64* %x, align 8
  %icmp.sgt = icmp sgt i64 1, %x1
  br i1 %icmp.sgt, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %x2 = load i64, i64* %x, align 8
  %add = add i64 %x2, 12
  store i64 %add, i64* %y, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  %x3 = load i64, i64* %x, align 8
  %mul = mul i64 %x3, 34
  store i64 %mul, i64* %y, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %y4 = load i64, i64* %y, align 8
  ret i64 %y4
}
