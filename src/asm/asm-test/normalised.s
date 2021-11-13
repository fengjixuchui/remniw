.text
.globl f
.type f, @function
f:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
.BB.entry.0:
	movq	$0, %rax
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
	callq	f
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %r15
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
.BB.entry.2:
	callq	g
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %r14
	movq	$fmtstr.1, %rdi
	movq	%r14, %rsi
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
