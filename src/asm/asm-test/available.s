.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $40, %rsp
.LB_entry_140737166694992:
movq $2,-32(%rbp)
movq $3,-40(%rbp)
movq -32(%rbp), %r15
movq -40(%rbp), %r14
addq %r15, %r14
movq %r14, -24(%rbp)
movq -32(%rbp), %r15
movq -40(%rbp), %r14
imulq %r15, %r14
movq %r14, -16(%rbp)
movq -24(%rbp), %r15
movq -16(%rbp), %r14
addq %r15, %r14
movq %r14, %rax
movq %rbp, %rsp
popq %rbp
retq

