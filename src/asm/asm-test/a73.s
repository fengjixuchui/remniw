.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry:
movq $42,-8(%rbp)
movq $43,-16(%rbp)
movq -8(%rbp), %r8
movq $1, %r9
cmpq %r8, %r9
jle .LB_if.else
.LB_if.then:
movq -8(%rbp), %r8
addq $12, %r8
movq %r8, -16(%rbp)
jmp .LB_if.end
.LB_if.else:
movq -8(%rbp), %r8
imulq $34, %r8
movq %r8, -16(%rbp)
jmp .LB_if.end
.LB_if.end:
movq -16(%rbp), %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

