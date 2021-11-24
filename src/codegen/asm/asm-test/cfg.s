.text
.globl main
.type main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
.BB.entry.0:
	movq	$fmtstr, %rdi	;1
	leaq	-8(%rbp), %rsi	;2
	xorq	%rax, %rax		;3
	callq	scanf			;4
	movq	-8(%rbp), %r15	;5
	movq	%r15, -16(%rbp)	;6
	movq	$1, -24(%rbp)	;7
	movq	-16(%rbp), %r14	;8
	cmpq	$0, %r14		;9
	jle	.BB.if.else.2		;10
.BB.if.then.1:
	movq	-24(%rbp), %r15	;11
	movq	-16(%rbp), %r14	;12
	imulq	%r15, %r14		;13
	movq	%r14, -24(%rbp)	;14
	movq	-16(%rbp), %r15	;15
	subq	$1, %r15		;16
	movq	%r15, -16(%rbp)	;17
	jmp	.BB.if.end.3		;18
.BB.if.else.2:
.BB.if.end.3:
	movq	-24(%rbp), %r14	;19
	movq	$fmtstr.1, %rdi	;20
	movq	%r14, %rsi		;21
	xorq	%rax, %rax		;22
	callq	printf			;23
	movq	-16(%rbp), %r15	;24
	movq	$fmtstr.1, %rdi	;25
	movq	%r15, %rsi		;26
	xorq	%rax, %rax		;27
	callq	printf			;28
	movq	$0, %rax		;29
	movq	%rbp, %rsp		;30
	popq	%rbp
	retq

fmtstr:
.asciz "%lli"
fmtstr.1:
.asciz "%lli\0A"
