.text
.globl f
.type f, @function
f:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %r15
	movq	-8(%rbp), %r14
	movq	%r15, %rdi
	movq	%r14, %rsi
	callq	g
	movq	%rax, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl g
.type g, @function
g:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.1:
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %r15
	movq	-8(%rbp), %r14
	addq	%r15, %r14
	movq	%r14, %rax
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
.BB.entry.2:
	movq	$fmtstr, %rdi
	leaq	-16(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-16(%rbp), %r15
	movq	%r15, -24(%rbp)
	movq	$fmtstr, %rdi
	leaq	-8(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-8(%rbp), %r14
	movq	%r14, -32(%rbp)
	movq	-24(%rbp), %r15
	movq	-32(%rbp), %r14
	movq	%r15, %rdi
	movq	%r14, %rsi
	callq	f
	movq	$fmtstr.1, %rdi
	movq	%rax, %rsi
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
