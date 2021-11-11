.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
.L.entry_140736946703840:
movq $2,-32(%rbp)
movq $3,-40(%rbp)
movq -32(%rbp), %r15
movq -40(%rbp), %r14
addq %r15, %r14
movq %r14, -24(%rbp)
movq -32(%rbp), %r15
movq -40(%rbp), %r14
imulq %r15, %r14
movq %r14, -16(%rbp)
jmp .L.while.cond_140736946674912
.L.while.cond_140736946674912:
movq -16(%rbp), %r13
movq -32(%rbp), %r14
movq -40(%rbp), %r15
addq %r14, %r15
cmpq %r15, %r13
jle .L.while.end_140736946705696
.L.while.body_140736946705616:
movq -32(%rbp), %r14
addq $1, %r14
movq %r14, -32(%rbp)
movq -32(%rbp), %r15
movq -40(%rbp), %r14
addq %r15, %r14
movq %r14, -8(%rbp)
jmp .L.while.cond_140736946674912
.L.while.end_140736946705696:
movq $.L.fmtstr.1, %rdi
movq -32(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $.L.fmtstr.1, %rdi
movq -8(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr:
.asciz "%lli"
.L.fmtstr.1:
.asciz "%lli\0A"
