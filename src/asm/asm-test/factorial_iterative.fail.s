.text
.globl ite
.type ite, @function
ite:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736635508240:
movq %rdi, -8(%rbp)
movq $1,-16(%rbp)
jmp .L.while.cond_140736635487376
.L.while.cond_140736635487376:
movq -8(%rbp), %r15
cmpq $0, %r15
jle .L.while.end_140736635485216
.L.while.body_140736635485136:
movq -16(%rbp), %r14
movq -8(%rbp), %r15
imulq %r14, %r15
movq %r15, -16(%rbp)
movq -8(%rbp), %r14
movq $1, %r15
subq %r14, %r15
movq %r15, -8(%rbp)
jmp .L.while.cond_140736635487376
.L.while.end_140736635485216:
movq -16(%rbp), %r14
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
subq $16, %rsp
.L.entry_140736635512112:
movq $.L.fmtstr, %rdi
movq -8(%rbp), %rsi
callq scanf
movq -8(%rbp), %r15
movq %r15, -16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r14
movq %r14, %rdi
callq ite
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
