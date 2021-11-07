target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @fn(i64 %a, i64 %b, i64 %c, i64 %d, i64 %e, i64 %f, i64 %g, i64 %h, i64 %i) {
entry:
  %i9 = alloca i64, align 8
  %h8 = alloca i64, align 8
  %g7 = alloca i64, align 8
  %f6 = alloca i64, align 8
  %e5 = alloca i64, align 8
  %d4 = alloca i64, align 8
  %c3 = alloca i64, align 8
  %b2 = alloca i64, align 8
  %a1 = alloca i64, align 8
  store i64 %a, i64* %a1, align 8
  store i64 %b, i64* %b2, align 8
  store i64 %c, i64* %c3, align 8
  store i64 %d, i64* %d4, align 8
  store i64 %e, i64* %e5, align 8
  store i64 %f, i64* %f6, align 8
  store i64 %g, i64* %g7, align 8
  store i64 %h, i64* %h8, align 8
  store i64 %i, i64* %i9, align 8
  %a10 = load i64, i64* %a1, align 8
  %b11 = load i64, i64* %b2, align 8
  %add = add i64 %a10, %b11
  %c12 = load i64, i64* %c3, align 8
  %add13 = add i64 %add, %c12
  %d14 = load i64, i64* %d4, align 8
  %add15 = add i64 %add13, %d14
  %e16 = load i64, i64* %e5, align 8
  %add17 = add i64 %add15, %e16
  %f18 = load i64, i64* %f6, align 8
  %add19 = add i64 %add17, %f18
  %g20 = load i64, i64* %g7, align 8
  %add21 = add i64 %add19, %g20
  %h22 = load i64, i64* %h8, align 8
  %add23 = add i64 %add21, %h22
  %i24 = load i64, i64* %i9, align 8
  %add25 = add i64 %add23, %i24
  ret i64 %add25
}

define i64 @main() {
entry:
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %c = alloca i64, align 8
  %d = alloca i64, align 8
  %e = alloca i64, align 8
  %f = alloca i64, align 8
  %g = alloca i64, align 8
  %h = alloca i64, align 8
  %i = alloca i64, align 8
  %o = alloca i64, align 8
  store i64 1, i64* %a, align 8
  store i64 2, i64* %b, align 8
  store i64 3, i64* %c, align 8
  store i64 4, i64* %d, align 8
  store i64 5, i64* %e, align 8
  store i64 6, i64* %f, align 8
  store i64 7, i64* %g, align 8
  store i64 8, i64* %h, align 8
  store i64 9, i64* %i, align 8
  %a1 = load i64, i64* %a, align 8
  %b2 = load i64, i64* %b, align 8
  %c3 = load i64, i64* %c, align 8
  %d4 = load i64, i64* %d, align 8
  %e5 = load i64, i64* %e, align 8
  %f6 = load i64, i64* %f, align 8
  %g7 = load i64, i64* %g, align 8
  %h8 = load i64, i64* %h, align 8
  %i9 = load i64, i64* %i, align 8
  %call = call i64 @fn(i64 %a1, i64 %b2, i64 %c3, i64 %d4, i64 %e5, i64 %f6, i64 %g7, i64 %h8, i64 %i9)
  store i64 %call, i64* %o, align 8
  %o10 = load i64, i64* %o, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %o10)
  ret i64 0
}

declare i32 @printf(i8*, ...)
