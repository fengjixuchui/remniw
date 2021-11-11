.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140736611477376:
movq $0,-16(%rbp)
leaq -16(%rbp), %r15
movq %r15, -32(%rbp)
movq -32(%rbp), %r14
movq (%r14), %r15
movq %r15, -24(%rbp)
movq $.L.fmtstr.1, %rdi
movq -32(%rbp), %r14
movq (%r14), %r15
movq %r15, %rsi
callq printf
movq $1,-8(%rbp)
leaq -8(%rbp), %r14
movq %r14, -32(%rbp)
movq $.L.fmtstr.1, %rdi
movq -32(%rbp), %r15
movq (%r15), %r14
movq %r14, %rsi
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr:
.asciz "%lli"
.L.fmtstr.1:
.asciz "%lli\0A"
