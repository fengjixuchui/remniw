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
	movq	$11, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl succ
.type succ, @function
succ:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.1:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %r14
	addq	$1, %r14
	movq	%r14, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl h
.type h, @function
h:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.2:
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
.globl f
.type f, @function
f:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
.BB.entry.3:
	movq	%rdi, -8(%rbp)
	movq	$3, -16(%rbp)
	movq	-8(%rbp), %r15
	movq	-16(%rbp), %r14
	addq	%r15, %r14
	movq	%r14, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

.text
.globl test
.type test, @function
test:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
.BB.entry.4:
	movq	%rdi, -8(%rbp)
.BB.while.cond.5:
	movq	-8(%rbp), %r15
	cmpq	$0, %r15
	jle	.BB.while.end.7
.BB.while.body.6:
	movq	-8(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
	xorq	%rax, %rax
	callq	printf
	movq	-8(%rbp), %r15
	subq	$1, %r15
	movq	%r15, -8(%rbp)
	jmp	.BB.while.cond.5
.BB.while.end.7:
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
	subq	$16, %rsp
.BB.entry.8:
	movq	$17, -8(%rbp)
	movq	-8(%rbp), %r14
	cmpq	$17, %r14
	jle	.BB.if.else.10
.BB.if.then.9:
	movq	$13, -8(%rbp)
	jmp	.BB.if.end.11
.BB.if.else.10:
	movq	$19, -8(%rbp)
.BB.if.end.11:
	movq	$succ, %rdi
	movq	$17, %rsi
	callq	h
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
