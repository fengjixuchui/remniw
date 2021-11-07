.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry_140736617070496:
movq $0,-8(%rbp)
movq $0,-16(%rbp)
movq $0,-24(%rbp)
movq -8(%rbp), %r15
cmpq $0, %r15
jne .LB_if.else5_140736617075792
.LB_if.then_140736617077936:
movq -16(%rbp), %r14
cmpq $0, %r14
jne .LB_if.else_140736617075664
.LB_if.then4_140736617078000:
movq $12,-24(%rbp)
jmp .LB_if.end_140736617075728
.LB_if.else_140736617075664:
movq $34,-24(%rbp)
jmp .LB_if.end_140736617075728
.LB_if.end_140736617075728:
jmp .LB_if.end6_140736617076448
.LB_if.else5_140736617075792:
jmp .LB_if.end6_140736617076448
.LB_if.end6_140736617076448:
movq -24(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

