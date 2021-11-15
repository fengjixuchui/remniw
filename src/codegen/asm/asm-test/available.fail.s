.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp
.BB.entry.0:
	movq	$2, -32(%rbp)
	movq	$3, -40(%rbp)
	movq	-32(%rbp), %r15
	movq	-40(%rbp), %r14
	addq	%r15, %r14
	movq	%r14, -24(%rbp)
	movq	-32(%rbp), %r15
	movq	-40(%rbp), %r14
	imulq	%r15, %r14
	movq	%r14, -16(%rbp)
.BB.while.cond.1:
	movq	-16(%rbp), %r15
	movq	-32(%rbp), %r14
	movq	-40(%rbp), %r15
	addq	%r14, %r15
	cmpq	%r15, %r15
	jle	.BB.while.end.3
.BB.while.body.2:
	movq	-32(%rbp), %r14
	addq	$1, %r14
	movq	%r14, -32(%rbp)
	movq	-32(%rbp), %r15
	movq	-40(%rbp), %r14
	addq	%r15, %r14
	movq	%r14, -8(%rbp)
	jmp	.BB.while.cond.1
.BB.while.end.3:
	movq	-32(%rbp), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-8(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	$0, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

fmtstr.1:
.asciz "%lli\0A"
fmtstr:
.asciz "%lli"
