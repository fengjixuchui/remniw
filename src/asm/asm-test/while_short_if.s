.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry:
movq $1,-8(%rbp)
movq $0,-16(%rbp)
movq $20,-24(%rbp)
movq -8(%rbp), %r8
cmpq $1, %r8
jne .LB_if.else8
.LB_if.then:
jmp .LB_while.cond
.LB_while.cond:
movq -8(%rbp), %r8
cmpq $0, %r8
jle .LB_while.end
.LB_while.body:
movq -16(%rbp), %r8
cmpq $0, %r8
jne .LB_if.else
.LB_if.then5:
movq -24(%rbp), %r8
addq $1, %r8
movq %r8, -24(%rbp)
jmp .LB_if.end
.LB_if.else:
movq $0,-8(%rbp)
jmp .LB_if.end
.LB_if.end:
movq -8(%rbp), %r8
movq $1, %r8
subq %r8, %r8
movq %r8, -8(%rbp)
jmp .LB_while.cond
.LB_while.end:
jmp .LB_if.end9
.LB_if.else8:
jmp .LB_if.end9
.LB_if.end9:
movq -24(%rbp), %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

