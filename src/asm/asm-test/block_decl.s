.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq $0, -8(%rbp)
movq -8(%rbp), %r8
movq %r8, -24(%rbp)
movq -24(%rbp), %r9
movq %r9, -32(%rbp)
movq -32(%rbp), %r10
movq %r10, -8(%rbp)
movq -8(%rbp), %r11
addq $1, %r11
movq %r11, -16(%rbp)
movq -16(%rbp), %r12
movq %r12, %rax
movq %rbp, %rsp
popq %rbp
retq

