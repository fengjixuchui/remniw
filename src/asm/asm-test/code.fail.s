.text
.globl g
.type g, @function
g:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737233510016:
movq %rdi, -8(%rbp)
movq $11, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl succ
.type succ, @function
succ:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737233483920:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
addq $1, %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl h
.type h, @function
h:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737233480448:
movq %rdi, -16(%rbp)
movq %rsi, -8(%rbp)
movq -16(%rbp), %r14
movq -8(%rbp), %r15
movq %r15, %rdi
callq *%r14
movq %rax, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl f
.type f, @function
f:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140737233484944:
movq %rdi, -8(%rbp)
movq $3,-16(%rbp)
movq -8(%rbp), %r14
movq -16(%rbp), %r15
addq %r14, %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl test
.type test, @function
test:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737233517632:
movq %rdi, -8(%rbp)
jmp .L.while.cond_140737233518016
.L.while.cond_140737233518016:
movq -8(%rbp), %r14
cmpq $0, %r14
jle .L.while.end_140737233518752
.L.while.body_140737233518672:
movq $.L.fmtstr.1, %rdi
movq -8(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq -8(%rbp), %r14
subq $1, %r14
movq %r14, -8(%rbp)
jmp .L.while.cond_140737233518016
.L.while.end_140737233518752:
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
subq $16, %rsp
.L.entry_140737233521280:
movq $17,-8(%rbp)
movq -8(%rbp), %r15
cmpq $17, %r15
jle .L.if.else_140737233522128
.L.if.then_140737233522048:
movq $13,-8(%rbp)
jmp .L.if.end_140737233522512
.L.if.else_140737233522128:
movq $19,-8(%rbp)
jmp .L.if.end_140737233522512
.L.if.end_140737233522512:
movq $.L.fmtstr.1, %rdi
movq $.L.succ, %rdi
movq $17, %rsi
callq h
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
