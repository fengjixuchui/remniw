.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.LB_entry:
movq $123,-8(%rbp)
movq $1,-16(%rbp)
movq -8(%rbp), %r8
cmpq $0, %r8
jle .LB_if.else
.LB_if.then:
movq -16(%rbp), %r9
movq -8(%rbp), %r8
imulq %r9, %r8
movq %r8, -16(%rbp)
movq -8(%rbp), %r9
movq $1, %r8
subq %r9, %r8
movq %r8, -8(%rbp)
jmp .LB_if.end
.LB_if.else:
jmp .LB_if.end
.LB_if.end:
movq -16(%rbp), %r8
movq %r8, %rax
movq %rbp, %rsp
popq %rbp
retq

