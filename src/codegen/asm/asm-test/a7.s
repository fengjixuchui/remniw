.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
.BB.entry.0:
	movq	$42, -8(%rbp)
	movq	$43, -16(%rbp)
	movq	-8(%rbp), %r15
	cmpq	$0, %r15
	je	.BB.if.else.2
.BB.if.then.1:
	movq	$fmtstr.1, %rdi
	movq	$0, %rsi
	xorq	%rax, %rax
	callq	printf
	jmp	.BB.if.end.3
.BB.if.else.2:
	movq	$fmtstr.1, %rdi
	movq	$1, %rsi
	xorq	%rax, %rax
	callq	printf
.BB.if.end.3:
	movq	$0, %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq

fmtstr:
.asciz "%lli"
fmtstr.1:
.asciz "%lli\0A"
