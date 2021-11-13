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
.BB.while.cond.1:
	movq	-16(%rbp), %r14
	cmpq	$1, %r14
	jle	.BB.while.end.3
.BB.while.body.2:
	movq	-16(%rbp), %r15
	movq	%r15, %rax
	cqto
	movq	$2, %r14
	idivq	%r14
	movq	%rax, %r14
	movq	%r14, -24(%rbp)
	movq	-24(%rbp), %r15
	cmpq	$3, %r15
	jle	.BB.if.else.5
.BB.if.then.4:
	movq	-16(%rbp), %r14
	movq	-24(%rbp), %r15
	subq	%r15, %r14
	movq	%r15, -16(%rbp)
	jmp	.BB.if.end.6
.BB.if.else.5:
.BB.if.end.6:
	movq	-16(%rbp), %r14
	subq	$4, %r14
	movq	%r14, -32(%rbp)
	movq	-32(%rbp), %r15
	cmpq	$0, %r15
	jle	.BB.if.else14.8
.BB.if.then11.7:
	movq	-16(%rbp), %r14
	movq	%r14, %rax
	cqto
	movq	$2, %r15
	idivq	%r15
	movq	%rax, %r15
	movq	%r15, -16(%rbp)
	jmp	.BB.if.end15.9
.BB.if.else14.8:
.BB.if.end15.9:
	movq	-32(%rbp), %r14
	subq	$1, %r14
	movq	%r14, -32(%rbp)
	jmp	.BB.while.cond.1
.BB.while.end.3:
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
