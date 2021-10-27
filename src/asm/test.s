.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $8, %rsp
movq $1, -8(%rbp)
movq -8(%rbp), %rcx
addq $2, %rcx
addq $3, %rcx
addq $4, %rcx
movq %rcx, %rax
movq %rbp, %rsp
popq %rbp
retq

