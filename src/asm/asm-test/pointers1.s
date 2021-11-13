.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
.BB.entry.0:
	movq	$5, -8(%rbp)
	leaq	-8(%rbp), %r15
	movq	%r15, -16(%rbp)
	movq	-16(%rbp), %r14
	movq	%r14, -24(%rbp)
	movq	-24(%rbp), %r15
	movq	$2, (%r15)
	movq	-8(%rbp), %r14
	cmpq	$2, %r14
	jne	.BB.if.else.2
.BB.if.then.1:
	movq	$fmtstr.1, %rdi
	movq	$1, %rsi
	xorq	%rax, %rax
	callq	printf
	jmp	.BB.if.end.3
.BB.if.else.2:
	movq	$fmtstr.1, %rdi
	movq	$0, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-8(%rbp), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
	xorq	%rax, %rax
	callq	printf
.BB.if.end.3:
	movq	$0, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

fmtstr:
.asciz "%lli"
fmtstr.1:
.asciz "%lli\0A"
