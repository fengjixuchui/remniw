.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.LB_entry_140737073474032:
movq $0,-8(%rbp)
movq -8(%rbp), %r15
movq %r15, -24(%rbp)
movq -24(%rbp), %r14
movq %r14, -32(%rbp)
movq -32(%rbp), %r15
movq %r15, -8(%rbp)
movq -8(%rbp), %r14
addq $1, %r14
movq %r14, -16(%rbp)
movq -16(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

