.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
movq $18,-8(%rbp)
movq -8(%rbp), %r8
movq %r8, %rax
cqto
movq $3, %r9
idivq %r9
movq %rax, %r9
addq $17, %r9
movq %r9, -16(%rbp)
movq $7,-8(%rbp)
leaq -8(%rbp), %r10
movq %r10, -24(%rbp)
movq -24(%rbp), %r11
movq (%r11), %rdi
movq %rdi, -8(%rbp)
movq -8(%rbp), %r12
movq %r12, %rax
cqto
movq $2, %r13
idivq %r13
movq %rax, %r13
movq %r13, %rax
cqto
movq $3, %r14
idivq %r14
movq %rax, %r14
movq %r14, -8(%rbp)
movq -8(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

