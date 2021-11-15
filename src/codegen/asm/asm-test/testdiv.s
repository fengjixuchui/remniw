.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140736918769152:
movq $.L.fmtstr, %rdi
leaq -16(%rbp), %rsi
xorl %eax, %eax
callq scanf
movq -16(%rbp), %r15
movq %r15, -24(%rbp)
movq $.L.fmtstr, %rdi
leaq -8(%rbp), %rsi
xorl %eax, %eax
callq scanf
movq -8(%rbp), %r14
movq %r14, -32(%rbp)
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r15
movq -32(%rbp), %r14
movq %r15, %rax
cqto
idivq %r14
movq %rax, %rsi
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
