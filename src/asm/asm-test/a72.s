.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry_140736583822016:
movq $42,-8(%rbp)
movq $43,-16(%rbp)
jmp .LB_if.else_140736583819808
.LB_if.then_140736583822144:
movq -8(%rbp), %r15
addq $12, %r15
movq %r15, -16(%rbp)
jmp .LB_if.end_140736583819872
.LB_if.else_140736583819808:
movq -8(%rbp), %r14
imulq $34, %r14
movq %r14, -16(%rbp)
jmp .LB_if.end_140736583819872
.LB_if.end_140736583819872:
movq -16(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

