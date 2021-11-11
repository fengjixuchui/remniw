.text
.globl div
.type div, @function
div:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737072481936:
movq %rdi, -16(%rbp)
movq %rsi, -8(%rbp)
movq -16(%rbp), %r15
movq -8(%rbp), %r14
movq %r15, %rax
cqto
idivq %r14
movq %rax, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140737072457616:
movq $18,-8(%rbp)
movq -8(%rbp), %r15
movq %r15, %rax
cqto
movq $3, %r14
idivq %r14
movq %rax, %r14
addq $17, %r14
movq %r14, -16(%rbp)
movq -8(%rbp), %r15
cmpq $17, %r15
jle .L.if.else_140737072484240
.L.if.then_140737072484160:
movq $7,-8(%rbp)
leaq -8(%rbp), %r14
movq %r14, -24(%rbp)
jmp .L.if.end_140737072484848
.L.if.else_140737072484240:
movq -8(%rbp), %r15
movq %r15, %rax
cqto
movq $3, %r14
idivq %r14
movq %rax, %r14
movq %r14, -16(%rbp)
leaq -16(%rbp), %r15
movq %r15, -24(%rbp)
jmp .L.if.end_140737072484848
.L.if.end_140737072484848:
movq -24(%rbp), %r14
movq (%r14), %r15
movq %r15, -8(%rbp)
jmp .L.while.cond_140737072486560
.L.while.cond_140737072486560:
movq -8(%rbp), %r14
cmpq $5, %r14
jle .L.while.end_140737072487296
.L.while.body_140737072487216:
movq -8(%rbp), %r15
movq %r15, %rax
cqto
movq $2, %r14
idivq %r14
movq %rax, %r14
movq %r14, %rdi
movq $3, %rsi
callq div
movq %rax, -8(%rbp)
jmp .L.while.cond_140737072486560
.L.while.end_140737072487296:
movq $.L.fmtstr.1, %rdi
movq -8(%rbp), %r15
movq %r15, %rsi
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr.1:
.asciz "%lli\0A"
.L.fmtstr:
.asciz "%lli"
