.text
.globl main
.p2align	4, 0x90
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736926046256:
movq $.L.fmtstr, %rdi
leaq -8(%rbp), %rsi
movb $0, %al
callq __isoc99_scanf
movq -8(%rbp), %r15
movq %r15, -16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r14
movq %r14, %rsi
movb $0, %al
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr.1:
.asciz "%lli\0A"
.L.fmtstr:
.asciz "%lli"
