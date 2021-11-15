.text
.globl rec
.type rec, @function
rec:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %r15
	cmpq	$0, %r15
	jne	.BB.if.else.2
.BB.if.then.1:
	movq	$1, -16(%rbp)
	jmp	.BB.if.end.3
.BB.if.else.2:
	movq	-8(%rbp), %r14
	movq	-8(%rbp), %r15
	subq	$1, %r15
	movq	%r15, %rdi
	callq	rec
	imulq	%r14, %rax
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
	callq	rec
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
