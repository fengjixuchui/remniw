target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  %z = alloca i64, align 8
  store i64 0, i64* %x, align 8
  store i64 0, i64* %y, align 8
  store i64 0, i64* %z, align 8
  %x1 = load i64, i64* %x, align 8
  %icmp.eq = icmp eq i64 %x1, 0
  br i1 %icmp.eq, label %if.then, label %if.else5

if.then:                                          ; preds = %entry
  %y2 = load i64, i64* %y, align 8
  %icmp.eq3 = icmp eq i64 %y2, 0
  br i1 %icmp.eq3, label %if.then4, label %if.else

if.then4:                                         ; preds = %if.then
  store i64 12, i64* %z, align 8
  br label %if.end

if.else:                                          ; preds = %if.then
  store i64 34, i64* %z, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then4
  br label %if.end6

if.else5:                                         ; preds = %entry
  br label %if.end6

if.end6:                                          ; preds = %if.else5, %if.end
  %z7 = load i64, i64* %z, align 8
  ret i64 %z7
}
