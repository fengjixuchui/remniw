.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737155515072:
movq $17,-8(%rbp)
movq -8(%rbp), %r15
movq %r15, %rax
cqto
movq $3, %r14
idivq %r14
movq %rax, %r14
addq $17, %r14
movq %r14, -16(%rbp)
movq $13,-8(%rbp)
movq -8(%rbp), %r15
cmpq $17, %r15
jle .L.if.else_140737155492384
.L.if.then_140737155488848:
movq -16(%rbp), %r14
imulq $77, %r14
movq %r14, -8(%rbp)
jmp .L.if.end_140737155516448
.L.if.else_140737155492384:
movq -8(%rbp), %r15
movq %r15, %rax
cqto
movq $3, %r14
idivq %r14
movq %rax, %r14
movq %r14, -16(%rbp)
jmp .L.if.end_140737155516448
.L.if.end_140737155516448:
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r15
movq %r15, %rsi
callq printf
movq $117,-16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r14
movq %r14, %rsi
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr:
.asciz "%lli"
.L.fmtstr.1:
.asciz "%lli\0A"
