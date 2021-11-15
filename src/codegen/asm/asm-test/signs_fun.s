.text
.globl idf
.type idf, @function
idf:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736693258752:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl posf
.type posf, @function
posf:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736693253264:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r14
movq %r14, %rax
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
.L.entry_140736693235808:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
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
.L.entry_140736693234400:
movq $0,-32(%rbp)
movq $5, %rdi
callq idf
movq %rax, -24(%rbp)
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $-4, %rdi
callq idf
movq %rax, -24(%rbp)
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $5, %rdi
callq posf
movq %rax, -8(%rbp)
movq $.L.fmtstr.1, %rdi
movq -8(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $7, %rdi
callq posf
movq %rax, -8(%rbp)
movq $.L.fmtstr.1, %rdi
movq -8(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $-4, %rdi
callq negf
movq %rax, -16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $-8, %rdi
callq negf
movq %rax, -16(%rbp)
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
