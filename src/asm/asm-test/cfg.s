.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
.BB.entry.0:
	movq	$fmtstr, %rdi
	leaq	-8(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-8(%rbp), %r15
	movq	%r15, -16(%rbp)
	movq	$1, -24(%rbp)
	movq	-16(%rbp), %r14
	cmpq	$0, %r14
	jle	.BB.if.else.2
.BB.if.then.1:
	movq	-24(%rbp), %r15
	movq	-16(%rbp), %r14
	imulq	%r15, %r14
	movq	%r14, -24(%rbp)
	movq	-16(%rbp), %r15
	subq	$1, %r15
	movq	%r15, -16(%rbp)
	jmp	.BB.if.end.3
.BB.if.else.2:
.BB.if.end.3:
	movq	-24(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-16(%rbp), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	$0, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

fmtstr:
.asciz "%lli"
fmtstr.1:
.asciz "%lli\0A"
