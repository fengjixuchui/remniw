.text
.globl div
.type div, @function
div:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %r15
	movq	-8(%rbp), %r14
	movq	%r15, %rax
	cqto
	idivq	%r14
	movq	%rax, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
.BB.entry.1:
	movq	$18, -8(%rbp)
	movq	-8(%rbp), %r15
	movq	%r15, %rax
	cqto
	movq	$3, %r14
	idivq	%r14
	movq	%rax, %r14
	addq	$17, %r14
	movq	%r14, -16(%rbp)
	movq	-8(%rbp), %r15
	cmpq	$17, %r15
	jle	.BB.if.else.3
.BB.if.then.2:
	movq	$7, -8(%rbp)
	leaq	-8(%rbp), %r14
	movq	%r14, -24(%rbp)
	jmp	.BB.if.end.4
.BB.if.else.3:
	movq	-8(%rbp), %r15
	movq	%r15, %rax
	cqto
	movq	$3, %r14
	idivq	%r14
	movq	%rax, %r14
	movq	%r14, -16(%rbp)
	leaq	-16(%rbp), %r15
	movq	%r15, -24(%rbp)
.BB.if.end.4:
	movq	-24(%rbp), %r14
	movq	(%r14), %r15
	movq	%r15, -8(%rbp)
.BB.while.cond.5:
	movq	-8(%rbp), %r14
	cmpq	$5, %r14
	jle	.BB.while.end.7
.BB.while.body.6:
	movq	-8(%rbp), %r15
	movq	%r15, %rax
	cqto
	movq	$2, %r14
	idivq	%r14
	movq	%rax, %r14
	movq	%r14, %rdi
	movq	$3, %rsi
	callq	div
	movq	%rax, -8(%rbp)
	jmp	.BB.while.cond.5
.BB.while.end.7:
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
