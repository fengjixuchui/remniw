.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140737162602448:
movq $42,-8(%rbp)
movq $43,-16(%rbp)
movq -8(%rbp), %r15
cmpq $0, %r15
je .L.if.else_140737162582144
.L.if.then_140737162585680:
movq $.L.fmtstr.1, %rdi
movq $0, %rsi
callq printf
jmp .L.if.end_140737162604400
.L.if.else_140737162582144:
movq $.L.fmtstr.1, %rdi
movq $1, %rsi
callq printf
jmp .L.if.end_140737162604400
.L.if.end_140737162604400:
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr:
.asciz "%lli"
.L.fmtstr.1:
.asciz "%lli\0A"
