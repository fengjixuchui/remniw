.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.LB_entry_140736736574224:
movq $123,-8(%rbp)
movq $1,-16(%rbp)
movq -8(%rbp), %r15
cmpq $0, %r15
jle .LB_if.else_140736736574128
.LB_if.then_140736736572304:
movq -16(%rbp), %r14
movq -8(%rbp), %r15
imulq %r14, %r15
movq %r15, -16(%rbp)
movq -8(%rbp), %r14
movq $1, %r15
subq %r14, %r15
movq %r15, -8(%rbp)
jmp .LB_if.end_140736736574288
.LB_if.else_140736736574128:
jmp .LB_if.end_140736736574288
.LB_if.end_140736736574288:
movq -16(%rbp), %r14
movq %r14, %rax
movq %rbp, %rsp
popq %rbp
retq

