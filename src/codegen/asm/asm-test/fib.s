.text
.globl fib
.type fib, @function
fib:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp
.BB.entry.0:
	movq	%rdi, -8(%rbp)
	movq	$1, -16(%rbp)
	movq	$1, -24(%rbp)
	movq	-8(%rbp), %r15
	movq	%r15, -32(%rbp)
.BB.while.cond.1:
	movq	-32(%rbp), %r14
	cmpq	$1, %r14
	jle	.BB.while.end.3
.BB.while.body.2:
	movq	-16(%rbp), %r15
	movq	-24(%rbp), %r14
	addq	%r15, %r14
	movq	%r14, -40(%rbp)
	movq	-24(%rbp), %r15
	movq	%r15, -16(%rbp)
	movq	-40(%rbp), %r14
	movq	%r14, -24(%rbp)
	movq	-32(%rbp), %r15
	subq	$1, %r15
	movq	%r15, -32(%rbp)
	jmp	.BB.while.cond.1
.BB.while.end.3:
	movq	-24(%rbp), %r14
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
	subq	$16, %rsp
.BB.entry.4:
	movq	$fmtstr, %rdi
	leaq	-8(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-8(%rbp), %r15
	movq	%r15, -16(%rbp)
	movq	-16(%rbp), %r14
	movq	%r14, %rdi
	callq	fib
	movq	$fmtstr.1, %rdi
	movq	%rax, %rsi
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
