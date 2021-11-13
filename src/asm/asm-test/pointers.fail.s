.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140736425764592:
movq $5,-8(%rbp)
leaq -8(%rbp), %r15
movq %r15, -16(%rbp)
movq -16(%rbp), %r14
movq %r14, -24(%rbp)
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr.1:
.asciz "%lli\0A"
.L.fmtstr:
.asciz "%lli"
