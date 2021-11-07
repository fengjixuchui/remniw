.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.L.entry_140737304498816:
movq $27,-8(%rbp)
movq $7,-16(%rbp)
movq -8(%rbp), %r15
imulq $2, %r15
movq -16(%rbp), %r14
addq %r15, %r14
movq %r14, -24(%rbp)
movq -8(%rbp), %r15
movq $0, %r14
cmpq %r15, %r14
jle .L.if.else_140737304478624
.L.if.then_140737304480896:
movq -24(%rbp), %r15
movq $3, %r14
subq %r15, %r14
movq %r14, -16(%rbp)
jmp .L.if.end_140737304478704
.L.if.else_140737304478624:
movq $12,-16(%rbp)
jmp .L.if.end_140737304478704
.L.if.end_140737304478704:
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r15
movq %r15, %rsi
xor 	%rax, %rax
callq printf@PLT
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

	.type	.Lfmtstr,@object                # @fmtstr
.L.fmtstr:
	.asciz	"%lli"
	.size	.Lfmtstr, 5

	.type	.Lfmtstr.1,@object              # @fmtstr.1
.L.fmtstr.1:
	.asciz	"%lli\n"
	.size	.Lfmtstr.1, 6
