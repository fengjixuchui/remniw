.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.LB_entry:
movq $17,-8(%rbp)
movq -8(%rbp), %r8
movq %r8, %rax
cqto
movq $3, %r8
idivq %r8
movq %rax, %r8
addq $17, %r8
movq %r8, -16(%rbp)
movq $13,-8(%rbp)
movq -8(%rbp), %r8
movq %r8, %rax
cqto
movq $3, %r8
idivq %r8
movq %rax, %r8
movq %r8, -16(%rbp)
movq -16(%rbp), %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

