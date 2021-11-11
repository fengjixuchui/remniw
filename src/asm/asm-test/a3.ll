target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64* @bar(i64* %x) {
entry:
  %x1 = alloca i64*, align 8
  store i64* %x, i64** %x1, align 8
  %x2 = load i64*, i64** %x1, align 8
  ret i64* %x2
}

define i64 @foh(i64 %x, i64 %y) {
entry:
  %y2 = alloca i64, align 8
  %x1 = alloca i64, align 8
  store i64 %x, i64* %x1, align 8
  store i64 %y, i64* %y2, align 8
  %x3 = load i64, i64* %x1, align 8
  %y4 = load i64, i64* %y2, align 8
  %add = add i64 %x3, %y4
  ret i64 %add
}

define i64 @baz(i64*** %x, i64* %y) {
entry:
  %y2 = alloca i64*, align 8
  %x1 = alloca i64***, align 8
  store i64*** %x, i64**** %x1, align 8
  store i64* %y, i64** %y2, align 8
  %call = call i64 @foh(i64 4, i64 3)
  %0 = load i64*, i64** %y2, align 8
  store i64 %call, i64* %0, align 8
  %x3 = load i64***, i64**** %x1, align 8
  %1 = load i64**, i64*** %x3, align 8
  %2 = load i64*, i64** %1, align 8
  %3 = load i64, i64* %2, align 8
  %y4 = load i64*, i64** %y2, align 8
  %4 = load i64, i64* %y4, align 8
  %mul = mul i64 %3, %4
  %5 = load i64*, i64** %y2, align 8
  store i64 %mul, i64* %5, align 8
  %y5 = load i64*, i64** %y2, align 8
  %6 = load i64, i64* %y5, align 8
  ret i64 %6
}

define i64 @main() {
entry:
  %z = alloca i64, align 8
  %y = alloca i64*, align 8
  %x = alloca i64**, align 8
  %w = alloca i64 (i64***, i64*)*, align 8
  store i64 (i64***, i64*)* @baz, i64 (i64***, i64*)** %w, align 8
  store i64 8, i64* %z, align 8
  store i64* %z, i64** %y, align 8
  store i64** %y, i64*** %x, align 8
  %0 = load i64**, i64*** %x, align 8
  %w1 = load i64 (i64***, i64*)*, i64 (i64***, i64*)** %w, align 8
  %call = call i64 %w1(i64*** %x, i64* %z)
  %1 = load i64*, i64** %0, align 8
  store i64 %call, i64* %1, align 8
  %x2 = load i64**, i64*** %x, align 8
  %2 = load i64*, i64** %x2, align 8
  %3 = load i64, i64* %2, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %3)
  ret i64 0
}

declare i32 @printf(i8*, ...)
