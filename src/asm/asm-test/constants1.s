.text
.globl f
.type f, @function
f:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.LB_entry_f:
movq %rdi, -16(%rbp)
movq %rsi, -8(%rbp)
movq -16(%rbp), %r15
imulq $5, %r15
movq -8(%rbp), %r14
imulq $7, %r14
addq %r15, %r14
movq %r14, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.LB_entry_main:
movq $12,-8(%rbp)
movq $17,-16(%rbp)
movq -8(%rbp), %r15
movq %r15, %rdi
movq -16(%rbp), %r14
movq %r14, %rsi
callq f
movq %rax, -24(%rbp)
movq -24(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

