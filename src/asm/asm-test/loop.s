.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry_140736812718880:
movq $5,-8(%rbp)
movq $42,-16(%rbp)
movq -8(%rbp), %r15
movq %r15, -24(%rbp)
jmp .LB_while.cond_140736812718944
.LB_while.cond_140736812718944:
movq -16(%rbp), %r14
movq -24(%rbp), %r15
cmpq %r15, %r14
jle .LB_while.end_140736812716672
.LB_while.body_140736812719008:
movq -24(%rbp), %r14
addq $1, %r14
movq %r14, -24(%rbp)
jmp .LB_while.cond_140736812718944
.LB_while.end_140736812716672:
movq -24(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

