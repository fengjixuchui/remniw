.text
.globl fib
.type fib, @function
fib:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
.L.entry_140736329661536:
movq %rdi, -8(%rbp)
movq $1,-16(%rbp)
movq $1,-24(%rbp)
movq -8(%rbp), %r15
movq %r15, -32(%rbp)
jmp .L.while.cond_140736329637104
.L.while.cond_140736329637104:
movq -32(%rbp), %r14
cmpq $1, %r14
jle .L.while.end_140736329632960
.L.while.body_140736329632880:
movq -16(%rbp), %r15
movq -24(%rbp), %r14
addq %r15, %r14
movq %r14, -40(%rbp)
movq -24(%rbp), %r15
movq %r15, -16(%rbp)
movq -40(%rbp), %r14
movq %r14, -24(%rbp)
movq -32(%rbp), %r15
movq $1, %r14
subq %r15, %r14
movq %r14, -32(%rbp)
jmp .L.while.cond_140736329637104
.L.while.end_140736329632960:
movq -24(%rbp), %r15
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
subq $16, %rsp
.L.entry_140736329666560:
movq $.L.fmtstr, %rdi
movq -8(%rbp), %rsi
callq scanf
movq -8(%rbp), %r14
movq %r14, -16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r15
movq %r15, %rdi
callq fib
movq %rax, %rsi
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr.1:
.asciz "%lli\0A"
.L.fmtstr:
.asciz "%lli"
