.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp
.BB.entry.0:
	movq	$fmtstr, %rdi
	leaq	-24(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-24(%rbp), %r15
	movq	%r15, -32(%rbp)
	movq	$fmtstr, %rdi
	leaq	-16(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-16(%rbp), %r14
	movq	%r14, -40(%rbp)
	movq	$fmtstr, %rdi
	leaq	-8(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-8(%rbp), %r15
	movq	%r15, -48(%rbp)
	movq	-32(%rbp), %r14
	cmpq	$0, %r14
	jne	.BB.if.else12.2
.BB.if.then.1:
	movq	-40(%rbp), %r15
	cmpq	$0, %r15
	jne	.BB.if.else.4
.BB.if.then8.3:
	movq	-48(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
	xorq	%rax, %rax
	callq	printf
	jmp	.BB.if.end.5
.BB.if.else.4:
	movq	-32(%rbp), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
	xorq	%rax, %rax
	callq	printf
.BB.if.end.5:
	jmp	.BB.if.end13.6
.BB.if.else12.2:
.BB.if.end13.6:
	movq	$0, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

fmtstr:
.asciz "%lli"
fmtstr.1:
.asciz "%lli\0A"
