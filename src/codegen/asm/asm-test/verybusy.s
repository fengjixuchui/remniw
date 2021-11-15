.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140736464638576:
movq $.L.fmtstr, %rdi
leaq -8(%rbp), %rsi
xorl %eax, %eax
callq scanf
movq -8(%rbp), %r15
movq %r15, -16(%rbp)
movq -16(%rbp), %r14
subq $1, %r14
movq %r14, -24(%rbp)
movq -16(%rbp), %r15
subq $2, %r15
movq %r15, -32(%rbp)
jmp .L.while.cond_140736464638704
.L.while.cond_140736464638704:
movq -16(%rbp), %r14
cmpq $0, %r14
jle .L.while.end_140736464639488
.L.while.body_140736464639408:
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r15
movq -32(%rbp), %r14
imulq %r15, %r14
movq -16(%rbp), %r15
subq %r15, %r14
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq -16(%rbp), %r14
subq $1, %r14
movq %r14, -16(%rbp)
jmp .L.while.cond_140736464638704
.L.while.end_140736464639488:
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r15
movq -32(%rbp), %r14
imulq %r15, %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr.1:
.asciz "%lli\0A"
.L.fmtstr:
.asciz "%lli"
