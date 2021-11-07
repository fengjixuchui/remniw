.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry_140737051507456:
movq $42,-8(%rbp)
movq $43,-16(%rbp)
movq -8(%rbp), %r15
movq $1, %r14
cmpq %r15, %r14
jle .LB_if.else_140737051505248
.LB_if.then_140737051507584:
movq -8(%rbp), %r15
addq $12, %r15
movq %r15, -16(%rbp)
jmp .LB_if.end_140737051505312
.LB_if.else_140737051505248:
movq -8(%rbp), %r14
imulq $34, %r14
movq %r14, -16(%rbp)
jmp .LB_if.end_140737051505312
.LB_if.end_140737051505312:
movq -16(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

