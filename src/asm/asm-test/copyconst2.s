.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $64, %rsp
.L.entry_140736935699760:
movq $.L.fmtstr.1, %rdi
movq $123, %rsi
xorl %eax, %eax
callq printf
movq $87, %rdi
callq f
movq %rax, -8(%rbp)
movq -8(%rbp), %r15
movq %r15, -16(%rbp)
movq -8(%rbp), %r14
addq $1, %r14
movq %r14, -24(%rbp)
movq -8(%rbp), %r15
movq %r15, %rdi
callq f
movq %rax, -56(%rbp)
movq -56(%rbp), %r14
movq %r14, %rdi
callq g
movq %rax, -56(%rbp)
movq $123, %rdi
callq g
movq %rax, -64(%rbp)
movq -64(%rbp), %r15
movq %r15, -64(%rbp)
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
leaq -8(%rbp), %rdi
movq -24(%rbp), %r15
movq %r15, %rsi
leaq -64(%rbp), %rdx
callq Deref
movq %rax, -64(%rbp)
movq -24(%rbp), %r14
cmpq $0, %r14
je .L.if.else_140736935707712
.L.if.then_140736935707632:
movq -8(%rbp), %r15
movq %r15, -32(%rbp)
movq -16(%rbp), %r14
movq %r14, %rdi
callq f
movq %rax, -40(%rbp)
movq -24(%rbp), %r15
movq %r15, -48(%rbp)
jmp .L.if.end_140736935709456
.L.if.else_140736935707712:
movq $1, %rdi
callq g
movq %rax, -32(%rbp)
movq $2,-40(%rbp)
movq $1,-48(%rbp)
jmp .L.if.end_140736935709456
.L.if.end_140736935709456:
movq $.L.fmtstr.1, %rdi
movq -8(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $.L.fmtstr.1, %rdi
movq -32(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $.L.fmtstr.1, %rdi
movq -40(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $.L.fmtstr.1, %rdi
movq -48(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $.L.fmtstr.1, %rdi
movq -56(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $.L.fmtstr.1, %rdi
movq -64(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq $0, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl f
.type f, @function
f:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736935722960:
movq %rdi, -8(%rbp)
movq $555, %rax
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
.L.entry_140736935723936:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r14
movq %r14, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl h
.type h, @function
h:
pushq %rbp
movq %rsp, %rbp
subq $0, %rsp
.L.entry_140736935724544:
movq $1234, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl Deref
.type Deref, @function
Deref:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140736935725792:
movq %rdi, -24(%rbp)
movq %rsi, -16(%rbp)
movq %rdx, -8(%rbp)
movq -24(%rbp), %r15
movq (%r15), %r14
movq -16(%rbp), %r15
addq %r14, %r15
movq -8(%rbp), %r14
movq (%r14), %r14
addq %r14, %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr.1:
.asciz "%lli\n"
.L.fmtstr:
.asciz "%lli"
