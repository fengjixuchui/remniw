.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140736307789040:
movq $.L.fmtstr, %rdi
leaq -8(%rbp), %rsi
xorl %eax, %eax
callq scanf
movq -8(%rbp), %r15
movq %r15, -16(%rbp)
jmp .L.while.cond_140736307759888
.L.while.cond_140736307759888:
movq -16(%rbp), %r14
cmpq $1, %r14
jle .L.while.end_140736307760624
.L.while.body_140736307760544:
movq -16(%rbp), %r15
movq %r15, %rax
cqto
movq $2, %r14
idivq %r14
movq %rax, %r14
movq %r14, -24(%rbp)
movq -24(%rbp), %r15
cmpq $3, %r15
jle .L.if.else_140736307789568
.L.if.then_140736307789488:
movq -16(%rbp), %r14
movq -24(%rbp), %r15
subq %r15, %r14
movq %r15, -16(%rbp)
jmp .L.if.end_140736307790208
.L.if.else_140736307789568:
jmp .L.if.end_140736307790208
.L.if.end_140736307790208:
movq -16(%rbp), %r14
subq $4, %r14
movq %r14, -32(%rbp)
movq -32(%rbp), %r15
cmpq $0, %r15
jle .L.if.else14_140736307791856
.L.if.then11_140736307791776:
movq -16(%rbp), %r14
movq %r14, %rax
cqto
movq $2, %r15
idivq %r15
movq %rax, %r15
movq %r15, -16(%rbp)
jmp .L.if.end15_140736307792464
.L.if.else14_140736307791856:
jmp .L.if.end15_140736307792464
.L.if.end15_140736307792464:
movq -32(%rbp), %r14
subq $1, %r14
movq %r14, -32(%rbp)
jmp .L.while.cond_140736307759888
.L.while.end_140736307760624:
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr:
.asciz "%lli"
.L.fmtstr.1:
.asciz "%lli\0A"
