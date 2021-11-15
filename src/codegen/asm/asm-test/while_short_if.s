.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry_140736614179280:
movq $1,-8(%rbp)
movq $0,-16(%rbp)
movq $20,-24(%rbp)
movq -8(%rbp), %r15
cmpq $1, %r15
jne .LB_if.else8_140736614185360
.LB_if.then_140736614186720:
jmp .LB_while.cond_140736614186784
.LB_while.cond_140736614186784:
movq -8(%rbp), %r14
cmpq $0, %r14
jle .LB_while.end_140736614185296
.LB_while.body_140736614184448:
movq -16(%rbp), %r15
cmpq $0, %r15
jne .LB_if.else_140736614184576
.LB_if.then5_140736614184512:
movq -24(%rbp), %r14
addq $1, %r14
movq %r14, -24(%rbp)
jmp .LB_if.end_140736614185232
.LB_if.else_140736614184576:
movq $0,-8(%rbp)
jmp .LB_if.end_140736614185232
.LB_if.end_140736614185232:
movq -8(%rbp), %r15
movq $1, %r14
subq %r15, %r14
movq %r14, -8(%rbp)
jmp .LB_while.cond_140736614186784
.LB_while.end_140736614185296:
jmp .LB_if.end9_140736614185424
.LB_if.else8_140736614185360:
jmp .LB_if.end9_140736614185424
.LB_if.end9_140736614185424:
movq -24(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

