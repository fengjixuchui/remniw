target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  %z = alloca i64, align 8
  store i64 27, i64* %x, align 8
  store i64 7, i64* %y, align 8
  %x1 = load i64, i64* %x, align 8
  %mul = mul i64 2, %x1
  %y2 = load i64, i64* %y, align 8
  %add = add i64 %mul, %y2
  store i64 %add, i64* %z, align 8
  %x3 = load i64, i64* %x, align 8
  %icmp.sgt = icmp sgt i64 0, %x3
  br i1 %icmp.sgt, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %z4 = load i64, i64* %z, align 8
  %sub = sub i64 %z4, 3
  store i64 %sub, i64* %y, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  store i64 12, i64* %y, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %y5 = load i64, i64* %y, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %y5)
  ret i64 0
}

declare i32 @printf(i8*, ...)
