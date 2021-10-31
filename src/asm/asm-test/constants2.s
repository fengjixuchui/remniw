.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry:
movq $27,-8(%rbp)
movq -8(%rbp), %r8
imulq $2, %r8
movq -16(%rbp), %r8
addq %r8, %r8
movq %r8, -24(%rbp)
movq -8(%rbp), %r8
movq $0, %r9
cmpq %r8, %r9
jle .LB_if.else
.LB_if.then:
movq -24(%rbp), %r8
movq $3, %r8
subq %r8, %r8
movq %r8, -16(%rbp)
jmp .LB_if.end
.LB_if.else:
movq $12,-16(%rbp)
jmp .LB_if.end
.LB_if.end:
movq -16(%rbp), %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

