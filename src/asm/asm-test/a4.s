.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.LB_entry_140736588166272:
movq $6,-16(%rbp)
leaq -16(%rbp), %r15
movq %r15, -32(%rbp)
movq -32(%rbp), %r14
movq (%r14), %r15
movq %r15, -24(%rbp)
movq -24(%rbp), %r14
movq %r14, -8(%rbp)
leaq -8(%rbp), %r15
movq %r15, -32(%rbp)
movq -32(%rbp), %r14
movq (%r14), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

