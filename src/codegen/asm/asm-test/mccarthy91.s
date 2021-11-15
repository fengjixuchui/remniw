.text
.globl f
.type f, @function
f:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %r15
	cmpq	$100, %r15
	jle	.BB.if.else.2
.BB.if.then.1:
	movq	-8(%rbp), %r14
	addq	$-10, %r14
	movq	%r14, -16(%rbp)
	jmp	.BB.if.end.3
.BB.if.else.2:
	movq	-8(%rbp), %r15
	addq	$11, %r15
	movq	%r15, %rdi
	callq	f
	movq	%rax, %rdi
	callq	f
	movq	%rax, -16(%rbp)
.BB.if.end.3:
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
.BB.entry.4:
	movq	$17, %rdi
	callq	f
	movq	$fmtstr.1, %rdi
	movq	%rax, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	$95, %rdi
	callq	f
	movq	$fmtstr.1, %rdi
	movq	%rax, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	$150, %rdi
	callq	f
	movq	$fmtstr.1, %rdi
	movq	%rax, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	$200, %rdi
	callq	f
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
