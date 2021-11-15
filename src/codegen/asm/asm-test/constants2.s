.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
.BB.entry.0:
	movq	$27, -16(%rbp)
	movq	$fmtstr, %rdi
	leaq	-8(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-8(%rbp), %r15
	movq	%r15, -24(%rbp)
	movq	-16(%rbp), %r14
	imulq	$2, %r14
	movq	-24(%rbp), %r15
	addq	%r14, %r15
	movq	%r15, -32(%rbp)
	movq	-16(%rbp), %r14
	movq	$0, %r15
	cmpq	%r14, %r15
	jle	.BB.if.else.2
.BB.if.then.1:
	movq	-32(%rbp), %r14
	subq	$3, %r14
	movq	%r14, -24(%rbp)
	jmp	.BB.if.end.3
.BB.if.else.2:
	movq	$12, -24(%rbp)
.BB.if.end.3:
	movq	-24(%rbp), %r15
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
