.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
.BB.entry.0:
	movq	$0, -16(%rbp)
	leaq	-16(%rbp), %r15
	movq	%r15, -32(%rbp)
	movq	-32(%rbp), %r14
	movq	(%r14), %r15
	movq	%r15, -24(%rbp)
	movq	-32(%rbp), %r14
	movq	(%r14), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	$1, -8(%rbp)
	leaq	-8(%rbp), %r14
	movq	%r14, -32(%rbp)
	movq	-32(%rbp), %r15
	movq	(%r15), %r14
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
