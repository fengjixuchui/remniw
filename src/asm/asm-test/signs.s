.text
.globl fun
.type fun, @function
fun:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140737130551104:
movq %rdi, -8(%rbp)
movq $8,-24(%rbp)
movq $7,-16(%rbp)
jmp .L.while.cond_140737130523472
.L.while.cond_140737130523472:
movq -24(%rbp), %r15
movq -16(%rbp), %r14
cmpq %r14, %r15
jle .L.while.end_140737130524608
.L.while.body_140737130524528:
movq -24(%rbp), %r15
subq $1, %r15
movq %r15, -24(%rbp)
jmp .L.while.cond_140737130523472
.L.while.end_140737130524608:
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
.L.entry_140737130515920:
movq $10,-8(%rbp)
movq $.L.fmtstr.1, %rdi
movq -8(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $25,-8(%rbp)
movq $.L.fmtstr.1, %rdi
movq -8(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $-10,-16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $-25,-16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $-25,-16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $0,-24(%rbp)
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq -24(%rbp), %r14
imulq $5, %r14
movq %r14, -24(%rbp)
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq -24(%rbp), %r14
imulq $0, %r14
movq %r14, -32(%rbp)
movq $.L.fmtstr.1, %rdi
movq -32(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq -32(%rbp), %r14
imulq $5, %r14
movq %r14, -32(%rbp)
movq $.L.fmtstr.1, %rdi
movq -32(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $7,-40(%rbp)
movq $.L.fmtstr.1, %rdi
movq -40(%rbp), %r14
movq %r14, %rsi
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
