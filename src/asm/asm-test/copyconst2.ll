target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@fmtstr = private unnamed_addr constant [5 x i8] c"%lli\00", align 1
@fmtstr.1 = private unnamed_addr constant [6 x i8] c"%lli\0A\00", align 1

define i64 @main() {
entry:
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  %z = alloca i64, align 8
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %c = alloca i64, align 8
  %t = alloca i64, align 8
  %u = alloca i64, align 8
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 123)
  %call = call i64 @f(i64 87)
  store i64 %call, i64* %x, align 8
  %x1 = load i64, i64* %x, align 8
  store i64 %x1, i64* %y, align 8
  %x2 = load i64, i64* %x, align 8
  %add = add i64 %x2, 1
  store i64 %add, i64* %z, align 8
  %x3 = load i64, i64* %x, align 8
  %call4 = call i64 @f(i64 %x3)
  store i64 %call4, i64* %t, align 8
  %t5 = load i64, i64* %t, align 8
  %call6 = call i64 @g(i64 %t5)
  store i64 %call6, i64* %t, align 8
  %call7 = call i64 @g(i64 123)
  store i64 %call7, i64* %u, align 8
  %u8 = load i64, i64* %u, align 8
  store i64 %u8, i64* %u, align 8
  %z9 = load i64, i64* %z, align 8
  %printf10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %z9)
  %z11 = load i64, i64* %z, align 8
  %call12 = call i64 @Deref(i64* %x, i64 %z11, i64* %u)
  store i64 %call12, i64* %u, align 8
  %z13 = load i64, i64* %z, align 8
  %0 = icmp ne i64 %z13, 0
  br i1 %0, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %x14 = load i64, i64* %x, align 8
  store i64 %x14, i64* %a, align 8
  %y15 = load i64, i64* %y, align 8
  %call16 = call i64 @f(i64 %y15)
  store i64 %call16, i64* %b, align 8
  %z17 = load i64, i64* %z, align 8
  store i64 %z17, i64* %c, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  %call18 = call i64 @g(i64 1)
  store i64 %call18, i64* %a, align 8
  store i64 2, i64* %b, align 8
  store i64 1, i64* %c, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %x19 = load i64, i64* %x, align 8
  %printf20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %x19)
  %y21 = load i64, i64* %y, align 8
  %printf22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %y21)
  %z23 = load i64, i64* %z, align 8
  %printf24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %z23)
  %a25 = load i64, i64* %a, align 8
  %printf26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %a25)
  %b27 = load i64, i64* %b, align 8
  %printf28 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %b27)
  %c29 = load i64, i64* %c, align 8
  %printf30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %c29)
  %t31 = load i64, i64* %t, align 8
  %printf32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %t31)
  %u33 = load i64, i64* %u, align 8
  %printf34 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @fmtstr.1, i32 0, i32 0), i64 %u33)
  ret i64 0
}

define i64 @f(i64 %x) {
entry:
  %x1 = alloca i64, align 8
  store i64 %x, i64* %x1, align 8
  ret i64 555
}

define i64 @g(i64 %p) {
entry:
  %p1 = alloca i64, align 8
  store i64 %p, i64* %p1, align 8
  %p2 = load i64, i64* %p1, align 8
  ret i64 %p2
}

define i64 @h() {
entry:
  ret i64 1234
}

define i64 @Deref(i64* %a1, i64 %a2, i64* %a3) {
entry:
  %a33 = alloca i64*, align 8
  %a22 = alloca i64, align 8
  %a11 = alloca i64*, align 8
  store i64* %a1, i64** %a11, align 8
  store i64 %a2, i64* %a22, align 8
  store i64* %a3, i64** %a33, align 8
  %a14 = load i64*, i64** %a11, align 8
  %0 = load i64, i64* %a14, align 8
  %a25 = load i64, i64* %a22, align 8
  %add = add i64 %0, %a25
  %a36 = load i64*, i64** %a33, align 8
  %1 = load i64, i64* %a36, align 8
  %add7 = add i64 %add, %1
  ret i64 %add7
}

declare i32 @printf(i8*, ...)
