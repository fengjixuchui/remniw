.text
.globl g
.type g, @function
g:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %r15
	movq	(%r15), %r14
	movq	%r14, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl f
.type f, @function
f:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.1:
	movq	$10, -8(%rbp)
	movq	-8(%rbp), %r15
	cmpq	$10, %r15
	jne	.BB.if.else.3
.BB.if.then.2:
	leaq	-8(%rbp), %rdi
	callq	g
	movq	%rax, -16(%rbp)
	jmp	.BB.if.end.4
.BB.if.else.3:
.BB.if.end.4:
	movq	-8(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-16(%rbp), %r15
	movq	$fmtstr.1, %rdi
	movq	%r15, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	$0, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
.BB.entry.5:
	callq	f
	movq	%rax, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

fmtstr:
.asciz "%lli"
fmtstr.1:
.asciz "%lli\0A"
