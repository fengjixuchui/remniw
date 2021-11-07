.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry_140737010575952:
movq $18,-8(%rbp)
movq -8(%rbp), %r15
movq %r15, %rax
cqto
movq $3, %r14
idivq %r14
movq %rax, %r14
addq $17, %r14
movq %r14, -16(%rbp)
movq $7,-8(%rbp)
leaq -8(%rbp), %r15
movq %r15, -24(%rbp)
movq -24(%rbp), %r14
movq (%r14), %r15
movq %r15, -8(%rbp)
movq -8(%rbp), %r14
movq %r14, %rax
cqto
movq $2, %r15
idivq %r15
movq %rax, %r15
movq %r15, %rax
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

