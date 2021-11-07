.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.LB_entry_140736339691920:
movq $17,-8(%rbp)
movq -8(%rbp), %r15
movq %r15, %rax
cqto
movq $3, %r14
idivq %r14
movq %rax, %r14
addq $17, %r14
movq %r14, -16(%rbp)
movq $13,-8(%rbp)
movq -8(%rbp), %r15
movq %r15, %rax
cqto
movq $3, %r14
idivq %r14
movq %rax, %r14
movq %r14, -16(%rbp)
movq -16(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

