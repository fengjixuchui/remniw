.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
.BB.entry.0:
	movq	$0, -8(%rbp)
	movq	-8(%rbp), %r15
	movq	%r15, -24(%rbp)
	movq	-24(%rbp), %r14
	movq	%r14, -32(%rbp)
	movq	-32(%rbp), %r15
	movq	%r15, -8(%rbp)
	movq	-8(%rbp), %r14
	addq	$1, %r14
	movq	%r14, -16(%rbp)
	movq	-8(%rbp), %r15
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
