.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
.L.entry_140737152661312:
leaq -8(%rbp), %r15
movq %r15, -32(%rbp)
leaq -16(%rbp), %r14
movq %r14, -32(%rbp)
leaq -24(%rbp), %r15
movq %r15, -40(%rbp)
movq -32(%rbp), %r14
movq %r14, -40(%rbp)
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr.1:
.asciz "%lli\0A"
.L.fmtstr:
.asciz "%lli"
