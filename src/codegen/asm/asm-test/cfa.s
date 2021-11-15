.text
.globl inc
.type inc, @function
inc:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.0:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %r15
	addq	$1, %r15
	movq	%r15, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl dec
.type dec, @function
dec:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.1:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %r14
	subq	$1, %r14
	movq	%r14, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl ide
.type ide, @function
ide:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.2:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %r15
	movq	%r15, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl foo
.type foo, @function
foo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.3:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %r14
	cmpq	$0, %r14
	jne	.BB.if.else.5
.BB.if.then.4:
	movq	-8(%rbp), %r15
	movq	%r15, %rdi
	callq	dec
	movq	%rax, -16(%rbp)
	jmp	.BB.if.end.6
.BB.if.else.5:
.BB.if.end.6:
	movq	-8(%rbp), %r14
	movq	%r14, %rdi
	callq	inc
	movq	%rax, -16(%rbp)
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
	subq	$32, %rsp
.BB.entry.7:
	movq	$fmtstr, %rdi
	leaq	-8(%rbp), %rsi
	xorq	%rax, %rax
	callq	scanf
	movq	-8(%rbp), %r14
	movq	%r14, -16(%rbp)
	movq	-16(%rbp), %r15
	cmpq	$0, %r15
	jle	.BB.if.else.9
.BB.if.then.8:
	movq	-16(%rbp), %r14
	movq	%r14, %rdi
	callq	foo
	movq	%rax, -24(%rbp)
	jmp	.BB.if.end.10
.BB.if.else.9:
	movq	-16(%rbp), %r15
	movq	%r15, %rdi
	callq	foo
	movq	%rax, -24(%rbp)
.BB.if.end.10:
	movq	-24(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
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
