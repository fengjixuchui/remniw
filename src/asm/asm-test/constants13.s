.text
.globl fn
.type fn, @function
fn:
pushq %rbp
movq %rsp, %rbp
subq $80, %rsp
.L.entry_140736558819680:
movq %rdi, -72(%rbp)
movq %rsi, -64(%rbp)
movq %rdx, -56(%rbp)
movq %rcx, -48(%rbp)
movq %r8, -40(%rbp)
movq %r9, -32(%rbp)
movq 16(%rbp), %r15
movq %r15, -24(%rbp)
movq 24(%rbp), %r14
movq %r14, -16(%rbp)
movq 32(%rbp), %r15
movq %r15, -8(%rbp)
movq -72(%rbp), %r14
movq -64(%rbp), %r15
addq %r14, %r15
movq -56(%rbp), %r14
addq %r14, %r15
movq -48(%rbp), %r14
addq %r14, %r15
movq -40(%rbp), %r14
addq %r14, %r15
movq -32(%rbp), %r14
addq %r14, %r15
movq -24(%rbp), %r14
addq %r14, %r15
movq -16(%rbp), %r14
addq %r14, %r15
movq -8(%rbp), %r14
addq %r14, %r15
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
subq $112, %rsp
.L.entry_140736558854720:
movq $1,-8(%rbp)
movq $2,-16(%rbp)
movq $3,-24(%rbp)
movq $4,-32(%rbp)
movq $5,-40(%rbp)
movq $6,-48(%rbp)
movq $7,-56(%rbp)
movq $8,-64(%rbp)
movq $9,-72(%rbp)
movq -8(%rbp), %r15
movq %r15, %rdi
movq -16(%rbp), %r14
movq %r14, %rsi
movq -24(%rbp), %r15
movq %r15, %rdx
movq -32(%rbp), %r14
movq %r14, %rcx
movq -40(%rbp), %r15
movq %r15, %r8
movq -48(%rbp), %r14
movq %r14, %r9
movq -56(%rbp), %r15
movq %r15, 0(%rsp)
movq -64(%rbp), %r14
movq %r14, 8(%rsp)
movq -72(%rbp), %r15
movq %r15, 16(%rsp)
callq fn
movq %rax, -80(%rbp)
movq $.L.fmtstr.1, %rdi
movq -80(%rbp), %r14
movq %r14, %rsi
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr.1:
.asciz "%lli\0A"
.L.fmtstr:
.asciz "%lli"
