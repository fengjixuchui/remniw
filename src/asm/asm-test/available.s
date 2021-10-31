.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $40, %rsp
.LB_entry:
movq $2,-32(%rbp)
movq $3,-40(%rbp)
movq -32(%rbp), %r9
movq -40(%rbp), %r8
addq %r9, %r8
movq %r8, -24(%rbp)
movq -32(%rbp), %r9
movq -40(%rbp), %r8
imulq %r9, %r8
movq %r8, -16(%rbp)
movq -24(%rbp), %r9
movq -16(%rbp), %r8
addq %r9, %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

