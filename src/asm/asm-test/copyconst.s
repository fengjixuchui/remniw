.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$64, %rsp
.BB.entry.0:
	movq	$fmtstr.1, %rdi
	movq	$123, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	$87, %rdi
	callq	f
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %r15
	movq	%r15, -16(%rbp)
	movq	-8(%rbp), %r14
	addq	$1, %r14
	movq	%r14, -24(%rbp)
	movq	-8(%rbp), %r15
	movq	%r15, %rdi
	callq	f
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %r14
	movq	%r14, %rdi
	callq	g
	movq	%rax, -56(%rbp)
	movq	$123, %rdi
	callq	g
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %r15
	movq	%r15, -64(%rbp)
	movq	-24(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-24(%rbp), %r15
	cmpq	$0, %r15
	je	.BB.if.else.2
.BB.if.then.1:
	movq	-8(%rbp), %r14
	movq	%r14, -32(%rbp)
	movq	-16(%rbp), %r15
	movq	%r15, %rdi
	callq	f
	movq	%rax, -40(%rbp)
	movq	-24(%rbp), %r14
	movq	%r14, -48(%rbp)
	jmp	.BB.if.end.3
.BB.if.else.2:
	movq	$1, %rdi
	callq	g
	movq	%rax, -32(%rbp)
	movq	$2, -40(%rbp)
	movq	$1, -48(%rbp)
.BB.if.end.3:
	movq	-8(%rbp), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-16(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-24(%rbp), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-32(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-40(%rbp), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-48(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-56(%rbp), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-64(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	$0, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl f
.type f, @function
f:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.4:
	movq	%rdi, -8(%rbp)
	movq	$555, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl g
.type g, @function
g:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.5:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %r15
	movq	%r15, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl h
.type h, @function
h:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
.BB.entry.6:
	movq	$1234, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

fmtstr.1:
.asciz "%lli\0A"
fmtstr:
.asciz "%lli"
