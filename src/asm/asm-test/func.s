.text
.globl f
.type f, @function
f:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736792034144:
movq %rdi, -16(%rbp)
movq %rsi, -8(%rbp)
movq -16(%rbp), %r15
movq %r15, %rdi
movq -8(%rbp), %r14
movq %r14, %rsi
callq g
movq %rax, %rax
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
.L.entry_140736792005376:
movq %rdi, -16(%rbp)
movq %rsi, -8(%rbp)
movq -16(%rbp), %r15
movq -8(%rbp), %r14
addq %r15, %r14
movq %r14, %rax
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
.L.entry_140736792037360:
movq $.L.fmtstr, %rdi
leaq -16(%rbp), %rsi
xorl %eax, %eax
callq scanf
movq -16(%rbp), %r15
movq %r15, -24(%rbp)
movq $.L.fmtstr, %rdi
leaq -8(%rbp), %rsi
xorl %eax, %eax
callq scanf
movq -8(%rbp), %r14
movq %r14, -32(%rbp)
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r15
movq %r15, %rdi
movq -32(%rbp), %r14
movq %r14, %rsi
callq f
movq %rax, %rsi
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
