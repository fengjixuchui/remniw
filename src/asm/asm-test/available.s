.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $40, %rsp
movq $2, -32(%rbp)
movq $3, -40(%rbp)
movq -32(%rbp), %r8
movq -40(%rbp), %r9
addq %r8, %r9
movq %r9, -24(%rbp)
movq -32(%rbp), %r10
movq -40(%rbp), %r11
imulq %r10, %r11
movq %r11, -16(%rbp)
movq -24(%rbp), %r12
movq -16(%rbp), %r13
addq %r12, %r13
movq %r13, %rax
movq %rbp, %rsp
popq %rbp
retq

