.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140737016801488:
movq $.L.fmtstr, %rdi
leaq -8(%rbp), %rsi
xorl %eax, %eax
callq scanf
movq -8(%rbp), %r15
movq %r15, -16(%rbp)
movq $1,-24(%rbp)
movq -16(%rbp), %r14
cmpq $0, %r14
jle .L.if.else_140737016777840
.L.if.then_140737016777760:
movq -24(%rbp), %r15
movq -16(%rbp), %r14
imulq %r15, %r14
movq %r14, -24(%rbp)
movq -16(%rbp), %r15
subq $1, %r15
movq %r15, -16(%rbp)
jmp .L.if.end_140737016802576
.L.if.else_140737016777840:
jmp .L.if.end_140737016802576
.L.if.end_140737016802576:
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
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
