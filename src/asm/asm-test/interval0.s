.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.LB_entry_140737270786912:
movq $0,-16(%rbp)
movq $7,-8(%rbp)
movq -8(%rbp), %r15
addq $1, %r15
movq %r15, -8(%rbp)
jmp .LB_while.cond_140737270786816
.LB_while.cond_140737270786816:
movq -8(%rbp), %r14
cmpq $0, %r14
jle .LB_while.end_140737270787040
.LB_while.body_140737270786976:
movq -16(%rbp), %r15
addq $1, %r15
movq %r15, -16(%rbp)
movq -8(%rbp), %r14
movq $2, %r15
subq %r14, %r15
movq %r15, -8(%rbp)
jmp .LB_while.cond_140737270786816
.LB_while.end_140737270787040:
movq -16(%rbp), %r14
movq %r14, %rax
movq %rbp, %rsp
popq %rbp
retq

