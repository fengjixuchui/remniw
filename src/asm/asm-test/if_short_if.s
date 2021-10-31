.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
.LB_entry:
movq $0,-8(%rbp)
movq $0,-16(%rbp)
movq $0,-24(%rbp)
movq -8(%rbp), %r8
cmpq $0, %r8
jne .LB_if.else5
.LB_if.then:
movq -16(%rbp), %r8
cmpq $0, %r8
jne .LB_if.else
.LB_if.then4:
movq $12,-24(%rbp)
jmp .LB_if.end
.LB_if.else:
movq $34,-24(%rbp)
jmp .LB_if.end
.LB_if.end:
jmp .LB_if.end6
.LB_if.else5:
jmp .LB_if.end6
.LB_if.end6:
movq -24(%rbp), %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

