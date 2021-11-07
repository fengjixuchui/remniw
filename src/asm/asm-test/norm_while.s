.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.LB_entry_140736543857424:
movq $10,-8(%rbp)
leaq -8(%rbp), %r15
movq %r15, -16(%rbp)
jmp .LB_while.cond_140736543855504
.LB_while.cond_140736543855504:
movq -16(%rbp), %r14
movq (%r14), %r15
cmpq $0, %r15
jle .LB_while.end_140736543856304
.LB_while.body_140736543857328:
movq -16(%rbp), %r14
movq (%r14), %r15
movq $1, %r14
subq %r15, %r14
movq -16(%rbp), %r15
movq %r14, (%r15)
jmp .LB_while.cond_140736543855504
.LB_while.end_140736543856304:
movq -8(%rbp), %r14
movq %r14, %rax
movq %rbp, %rsp
popq %rbp
retq

