.text
.globl apply
.type apply, @function
apply:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %r15
	movq	-8(%rbp), %r14
	movq	%r14, %rdi
	callq	*%r15
	movq	%rax, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl fib
.type fib, @function
fib:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.1:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %r15
	cmpq	$1, %r15
	jle	.BB.if.else.3
.BB.if.then.2:
	movq	-8(%rbp), %r14
	subq	$1, %r14
	movq	%r14, %rdi
	callq	fib
	movq	%rax, %r13
	movq	-8(%rbp), %r15
	subq	$2, %r15
	movq	%r15, %rdi
	callq	fib
	addq	%r13, %rax
	movq	%rax, -16(%rbp)
	jmp	.BB.if.end.4
.BB.if.else.3:
	movq	$1, -16(%rbp)
.BB.if.end.4:
	movq	-16(%rbp), %r14
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
	subq	$0, %rsp
.BB.entry.5:
	movq	$fib, %rdi
	movq	$5, %rsi
	callq	apply
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
