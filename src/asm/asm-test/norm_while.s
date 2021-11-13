.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	$10, -8(%rbp)
	leaq	-8(%rbp), %r15
	movq	%r15, -16(%rbp)
.BB.while.cond.1:
	movq	-16(%rbp), %r14
	movq	(%r14), %r15
	cmpq	$0, %r15
	jle	.BB.while.end.3
.BB.while.body.2:
	movq	-16(%rbp), %r14
	movq	(%r14), %r15
	subq	$1, %r15
	movq	-16(%rbp), %r14
	movq	%r15, (%r14)
	jmp	.BB.while.cond.1
.BB.while.end.3:
	movq	-8(%rbp), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
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
