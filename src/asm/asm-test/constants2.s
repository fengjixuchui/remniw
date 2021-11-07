.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry_140737127369536:
movq $27,-8(%rbp)
movq -8(%rbp), %r15
imulq $2, %r15
movq -16(%rbp), %r14
addq %r15, %r14
movq %r14, -24(%rbp)
movq -8(%rbp), %r15
movq $0, %r14
cmpq %r15, %r14
jle .LB_if.else_140737127369664
.LB_if.then_140737127369600:
movq -24(%rbp), %r15
movq $3, %r14
subq %r15, %r14
movq %r14, -16(%rbp)
jmp .LB_if.end_140737127367328
.LB_if.else_140737127369664:
movq $12,-16(%rbp)
jmp .LB_if.end_140737127367328
.LB_if.end_140737127367328:
movq -16(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

