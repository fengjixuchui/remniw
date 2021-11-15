.text
.globl posf
.type posf, @function
posf:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737201018784:
movq %rdi, -8(%rbp)
movq $5, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl negf
.type negf, @function
negf:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737200998240:
movq %rdi, -8(%rbp)
movq $-5, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
.L.entry_140737200995760:
movq $0,-32(%rbp)
movq $-4, %rdi
callq posf
movq %rax, -8(%rbp)
movq $.L.fmtstr.1, %rdi
movq -8(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $3, %rdi
callq negf
movq %rax, -16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq -32(%rbp), %r15
cmpq $0, %r15
jle .L.if.else_140737201027344
.L.if.then_140737201027264:
movq $posf,-40(%rbp)
jmp .L.if.end_140737201027760
.L.if.else_140737201027344:
movq $negf,-40(%rbp)
jmp .L.if.end_140737201027760
.L.if.end_140737201027760:
movq -40(%rbp), %r14
movq $4, %rdi
callq *%r14
movq %rax, -24(%rbp)
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r15
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
