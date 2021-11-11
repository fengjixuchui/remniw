.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
.L.entry_140736385297312:
movq $.L.fmtstr, %rdi
leaq -24(%rbp), %rsi
xorl %eax, %eax
callq scanf
movq -24(%rbp), %r15
movq %r15, -32(%rbp)
movq $.L.fmtstr, %rdi
leaq -16(%rbp), %rsi
xorl %eax, %eax
callq scanf
movq -16(%rbp), %r14
movq %r14, -40(%rbp)
movq $.L.fmtstr, %rdi
leaq -8(%rbp), %rsi
xorl %eax, %eax
callq scanf
movq -8(%rbp), %r15
movq %r15, -48(%rbp)
movq -32(%rbp), %r14
cmpq $0, %r14
jne .L.if.else12_140736385304944
.L.if.then_140736385304864:
movq -40(%rbp), %r15
cmpq $0, %r15
jne .L.if.else_140736385305520
.L.if.then8_140736385305440:
movq $.L.fmtstr.1, %rdi
movq -48(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
jmp .L.if.end_140736385306800
.L.if.else_140736385305520:
movq $.L.fmtstr.1, %rdi
movq -32(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
jmp .L.if.end_140736385306800
.L.if.end_140736385306800:
jmp .L.if.end13_140736385308688
.L.if.else12_140736385304944:
jmp .L.if.end13_140736385308688
.L.if.end13_140736385308688:
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr:
.asciz "%lli"
.L.fmtstr.1:
.asciz "%lli\0A"
