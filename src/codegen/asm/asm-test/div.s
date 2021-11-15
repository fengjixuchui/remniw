.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	$17, -8(%rbp)
	movq	-8(%rbp), %r15
	movq	%r15, %rax
	cqto
	movq	$3, %r14
	idivq	%r14
	movq	%rax, %r14
	addq	$17, %r14
	movq	%r14, -16(%rbp)
	movq	$13, -8(%rbp)
	movq	-8(%rbp), %r15
	cmpq	$17, %r15
	jle	.BB.if.else.2
.BB.if.then.1:
	movq	-16(%rbp), %r14
	imulq	$77, %r14
	movq	%r14, -8(%rbp)
	jmp	.BB.if.end.3
.BB.if.else.2:
	movq	-8(%rbp), %r15
	movq	%r15, %rax
	cqto
	movq	$3, %r14
	idivq	%r14
	movq	%rax, %r14
	movq	%r14, -16(%rbp)
.BB.if.end.3:
	movq	-16(%rbp), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	$117, -16(%rbp)
	movq	-16(%rbp), %r14
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
