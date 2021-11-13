.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp
.BB.entry.0:
	leaq	-8(%rbp), %r15
	movq	%r15, -32(%rbp)
	leaq	-16(%rbp), %r14
	movq	%r14, -32(%rbp)
	leaq	-24(%rbp), %r15
	movq	%r15, -40(%rbp)
	movq	-32(%rbp), %r14
	movq	%r14, -40(%rbp)
	movq	-40(%rbp), %r15
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
.BB.if.end.3:
	movq	$0, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

fmtstr.1:
.asciz "%lli\0A"
fmtstr:
.asciz "%lli"
