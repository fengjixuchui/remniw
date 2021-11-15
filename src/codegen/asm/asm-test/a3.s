.text
.globl bar
.type bar, @function
bar:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %r15
	movq	%r15, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl foh
.type foh, @function
foh:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.1:
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %r14
	movq	-8(%rbp), %r15
	addq	%r14, %r15
	movq	%r15, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl baz
.type baz, @function
baz:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.2:
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	$4, %rdi
	movq	$3, %rsi
	callq	foh
	movq	-8(%rbp), %r14
	movq	%rax, (%r14)
	movq	-16(%rbp), %r15
	movq	(%r15), %r14
	movq	(%r14), %r15
	movq	(%r15), %r14
	movq	-8(%rbp), %r15
	movq	(%r15), %r14
	imulq	%r14, %r14
	movq	-8(%rbp), %r15
	movq	%r14, (%r15)
	movq	-8(%rbp), %r14
	movq	(%r14), %r15
	movq	%r15, %rax
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
.BB.entry.3:
	movq	$baz, -32(%rbp)
	movq	$8, -8(%rbp)
	leaq	-8(%rbp), %r14
	movq	%r14, -16(%rbp)
	leaq	-16(%rbp), %r15
	movq	%r15, -24(%rbp)
	movq	-24(%rbp), %r14
	movq	-32(%rbp), %r15
	leaq	-24(%rbp), %rdi
	leaq	-8(%rbp), %rsi
	callq	*%r15
	movq	(%r14), %r14
	movq	%rax, (%r14)
	movq	-24(%rbp), %r15
	movq	(%r15), %r14
	movq	(%r14), %r15
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
