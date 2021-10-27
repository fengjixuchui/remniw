.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq $6, -16(%rbp)
leaq  -16(%rbp), %r8
movq %r8, -32(%rbp)
movq -32(%rbp), %r9
movq (%r9), %r10
movq %r10, -24(%rbp)
movq -24(%rbp), %r11
movq %r11, -8(%rbp)
leaq  -8(%rbp), %r12
movq %r12, -32(%rbp)
movq -32(%rbp), %r13
movq (%r13), %r14
movq %r14, %rax
movq %rbp, %rsp
popq %rbp
retq

