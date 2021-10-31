.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.LB_entry:
movq $0,-8(%rbp)
movq -8(%rbp), %r8
movq %r8, -24(%rbp)
movq -24(%rbp), %r8
movq %r8, -32(%rbp)
movq -32(%rbp), %r8
movq %r8, -8(%rbp)
movq -8(%rbp), %r8
addq $1, %r8
movq %r8, -16(%rbp)
movq -16(%rbp), %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

