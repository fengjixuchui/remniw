.text
.globl f
.type f, @function
f:
pushq %rbp
movq %rsp, %rbp
subq $8, %rsp
.LB_entry_140736547832336:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry_140736547834384:
movq $f,-8(%rbp)
movq -8(%rbp), %r14
movq $1, %rdi
callq *%r14
movq %rax, -16(%rbp)
movq -16(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

