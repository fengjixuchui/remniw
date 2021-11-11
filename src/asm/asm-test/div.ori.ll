target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  store i64 17, i64* %a, align 8
  %a1 = load i64, i64* %a, align 8
  %div = sdiv i64 %a1, 3
  %add = add i64 17, %div
  store i64 %add, i64* %b, align 8
  store i64 13, i64* %a, align 8
  %a2 = load i64, i64* %a, align 8
  %icmp.sgt = icmp sgt i64 %a2, 17
  br i1 %icmp.sgt, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %b3 = load i64, i64* %b, align 8
  %mul = mul i64 77, %b3
  store i64 %mul, i64* %a, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  %a4 = load i64, i64* %a, align 8
  %div5 = sdiv i64 %a4, 3
  store i64 %div5, i64* %b, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %b6 = load i64, i64* %b, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %b6)
  store i64 117, i64* %b, align 8
  %b7 = load i64, i64* %b, align 8
  %printf8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %b7)
  ret i64 0
}

declare i32 @printf(i8*, ...)
