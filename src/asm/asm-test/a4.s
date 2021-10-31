.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.LB_entry:
movq $6,-16(%rbp)
leaq -16(%rbp), %r8
movq %r8, -32(%rbp)
movq -32(%rbp), %r8
movq (%r8), %r8
movq %r8, -24(%rbp)
movq -24(%rbp), %r8
movq %r8, -8(%rbp)
leaq -8(%rbp), %r8
movq %r8, -32(%rbp)
movq -32(%rbp), %r8
movq (%r8), %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

