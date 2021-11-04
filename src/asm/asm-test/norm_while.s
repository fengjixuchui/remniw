.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.LB_entry:
movq $10,-8(%rbp)
leaq -8(%rbp), %r9
movq %r9, -16(%rbp)
jmp .LB_while.cond
.LB_while.cond:
movq -16(%rbp), %r8
movq (%r8), %r9
cmpq $0, %r9
jle .LB_while.end
.LB_while.body:
movq -16(%rbp), %r8
movq (%r8), %r9
movq $1, %r8
subq %r8, %r9
movq -16(%rbp), %r8
movq %r9, (%r8)
jmp .LB_while.cond
.LB_while.end:
movq -8(%rbp), %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

