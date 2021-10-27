.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
movq $17, -8(%rbp)
movq -8(%rbp), %r8
movq %r8, %rax
cqto
movq $3, %r9
idivq %r9
movq %rax, %r9
addq $17, %r9
movq %r9, -16(%rbp)
movq $13, -8(%rbp)
movq -8(%rbp), %r10
movq %r10, %rax
cqto
movq $3, %r11
idivq %r11
movq %rax, %r11
movq %r11, -16(%rbp)
movq -16(%rbp), %r12
movq %r12, %rax
movq %rbp, %rsp
popq %rbp
retq

