.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry:
movq $5,-8(%rbp)
movq $42,-16(%rbp)
movq -8(%rbp), %r8
movq %r8, -24(%rbp)
jmp .LB_while.cond
.LB_while.cond:
movq -16(%rbp), %r8
movq -24(%rbp), %r9
cmpq %r9, %r8
jle .LB_while.end
.LB_while.body:
movq -24(%rbp), %r8
addq $1, %r8
movq %r8, -24(%rbp)
jmp .LB_while.cond
.LB_while.end:
movq -24(%rbp), %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

