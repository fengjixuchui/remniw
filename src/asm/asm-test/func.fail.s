.text
.globl f
.type f, @function
f:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736770141024:
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
.L.entry_140736770112256:
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
.L.entry_140736770144240:
movq $.L.fmtstr, %rdi
movq -16(%rbp), %rsi
callq scanf
movq -16(%rbp), %r15
movq %r15, -24(%rbp)
movq $.L.fmtstr, %rdi
movq -8(%rbp), %rsi
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
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr:
.asciz "%lli"
.L.fmtstr.1:
.asciz "%lli\0A"
