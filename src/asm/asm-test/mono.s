.text
.globl foo
.type foo, @function
foo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-8(%rbp), %r15
	imulq	$2, %r15
	movq	%r15, -16(%rbp)
	movq	-16(%rbp), %r14
	addq	$1, %r14
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
.BB.entry.1:
	movq	$fmtstr, %rdi
	leaq	-8(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-8(%rbp), %r15
	movq	%r15, -16(%rbp)
	movq	-16(%rbp), %r14
	movq	%r14, %rdi
	movq	$17, %rsi
	callq	foo
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %r15
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
