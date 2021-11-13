.text
.globl bar
.type bar, @function
bar:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736602101344:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl foh
.type foh, @function
foh:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736602083264:
movq %rdi, -16(%rbp)
movq %rsi, -8(%rbp)
movq -16(%rbp), %r14
movq -8(%rbp), %r15
addq %r14, %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl baz
.type baz, @function
baz:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736602107248:
movq %rdi, -16(%rbp)
movq %rsi, -8(%rbp)
movq $4, %rdi
movq $3, %rsi
callq foh
movq -8(%rbp), %r14
movq %rax, (%r14)
movq -16(%rbp), %r15
movq (%r15), %r14
movq (%r14), %r15
movq (%r15), %r14
movq -8(%rbp), %r15
movq (%r15), %r14
imulq %r14, %r14
movq -8(%rbp), %r15
movq %r14, (%r15)
movq -8(%rbp), %r14
movq (%r14), %r15
movq %r15, %rax
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
.L.entry_140736602111216:
movq $baz,-32(%rbp)
movq $8,-8(%rbp)
leaq -8(%rbp), %r14
movq %r14, -16(%rbp)
leaq -16(%rbp), %r15
movq %r15, -24(%rbp)
movq -24(%rbp), %r14
movq -32(%rbp), %r15
leaq -24(%rbp), %rdi
leaq -8(%rbp), %rsi
callq *%r15
movq (%r14), %r14
movq %rax, (%r14)
movq -24(%rbp), %r15
movq (%r15), %r14
movq (%r14), %r15
movq $.L.fmtstr.1, %rdi
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr.1:
.asciz "%lli\0A"
.L.fmtstr:
.asciz "%lli"
