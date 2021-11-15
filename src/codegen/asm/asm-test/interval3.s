.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
.BB.entry.0:
	movq	$0, -16(%rbp)
	movq	$0, -24(%rbp)
.BB.while.cond.1:
	movq	$fmtstr, %rdi
	leaq	-8(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-8(%rbp), %r15
	cmpq	$0, %r15
	je	.BB.while.end.3
.BB.while.body.2:
	movq	$7, -16(%rbp)
	movq	-16(%rbp), %r14
	addq	$1, %r14
	movq	%r14, -16(%rbp)
	movq	-24(%rbp), %r15
	addq	$1, %r15
	movq	%r15, -24(%rbp)
	jmp	.BB.while.cond.1
.BB.while.end.3:
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
	movq	$0, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

fmtstr.1:
.asciz "%lli\0A"
fmtstr:
.asciz "%lli"
