.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry_140736635611872:
movq $42,-8(%rbp)
movq $43,-16(%rbp)
movq -8(%rbp), %r15
cmpq $0, %r15
je .LB_if.else_140736635612000
.LB_if.then_140736635611936:
movq -8(%rbp), %r14
addq $12, %r14
movq %r14, -16(%rbp)
jmp .LB_if.end_140736635609664
.LB_if.else_140736635612000:
movq -8(%rbp), %r15
imulq $34, %r15
movq %r15, -16(%rbp)
jmp .LB_if.end_140736635609664
.LB_if.end_140736635609664:
movq -16(%rbp), %r14
movq %r14, %rax
movq %rbp, %rsp
popq %rbp
retq

