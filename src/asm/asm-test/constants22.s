.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140737063150208:
movq $27,-8(%rbp)
movq $7,-16(%rbp)
movq -8(%rbp), %r15
imulq $2, %r15
movq -16(%rbp), %r14
addq %r15, %r14
movq %r14, -24(%rbp)
movq -8(%rbp), %r15
movq $0, %r14
cmpq %r15, %r14
jle .L.if.else_140737063150864
.L.if.then_140737063150784:
movq -24(%rbp), %r15
movq $3, %r14
subq %r15, %r14
movq %r14, -16(%rbp)
jmp .L.if.end_140737063151488
.L.if.else_140737063150864:
movq $12,-16(%rbp)
jmp .L.if.end_140737063151488
.L.if.end_140737063151488:
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r15
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
