.text
.globl f
.type f, @function
f:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736984005712:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl g
.type g, @function
g:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736983986864:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r14
movq %r14, %rdi
callq f
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
.L.entry_140736983984800:
movq $f,-8(%rbp)
movq -8(%rbp), %r15
movq $1, %rdi
callq *%r15
movq %rax, -16(%rbp)
movq $g,-8(%rbp)
movq -8(%rbp), %r14
movq $2, %rdi
callq *%r14
movq %rax, -24(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r15
movq -24(%rbp), %r14
addq %r15, %r14
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
