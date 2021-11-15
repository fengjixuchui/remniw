.text
.globl ite
.type ite, @function
ite:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	%rdi, -8(%rbp)
	movq	$1, -16(%rbp)
.BB.while.cond.1:
	movq	-8(%rbp), %r15
	cmpq	$0, %r15
	jle	.BB.while.end.3
.BB.while.body.2:
	movq	-16(%rbp), %r14
	movq	-8(%rbp), %r15
	imulq	%r14, %r15
	movq	%r15, -16(%rbp)
	movq	-8(%rbp), %r14
	subq	$1, %r14
	movq	%r14, -8(%rbp)
	jmp	.BB.while.cond.1
.BB.while.end.3:
	movq	-16(%rbp), %r15
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
	subq	$16, %rsp
.BB.entry.4:
	movq	$fmtstr, %rdi
	leaq	-8(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-8(%rbp), %r14
	movq	%r14, -16(%rbp)
	movq	-16(%rbp), %r15
	movq	%r15, %rdi
	callq	ite
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
