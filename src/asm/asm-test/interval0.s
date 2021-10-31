.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.LB_entry:
movq $0,-16(%rbp)
movq $7,-8(%rbp)
movq -8(%rbp), %r8
addq $1, %r8
movq %r8, -8(%rbp)
jmp .LB_while.cond
.LB_while.cond:
movq -8(%rbp), %r8
cmpq $0, %r8
jle .LB_while.end
.LB_while.body:
movq -16(%rbp), %r8
addq $1, %r8
movq %r8, -16(%rbp)
movq -8(%rbp), %r8
movq $2, %r9
subq %r9, %r8
movq %r8, -8(%rbp)
jmp .LB_while.cond
.LB_while.end:
movq -16(%rbp), %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

