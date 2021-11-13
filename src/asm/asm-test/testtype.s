.text
.globl posf
.type posf, @function
posf:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736794762624:
movq %rdi, -8(%rbp)
movq $5, %rax
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
.L.entry_140736794754800:
movq %rdi, -8(%rbp)
movq $-5, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl doref
.type doref, @function
doref:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736794733088:
movq %rdi, -8(%rbp)
movq %rbp, %rsp
popq %rbp
retq

.text
.globl deref
.type deref, @function
deref:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736794733664:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
movq (%r15), %r14
movq %r14, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl doublederef
.type doublederef, @function
doublederef:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736794739072:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
movq (%r15), %r14
movq (%r14), %r15
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
subq $80, %rsp
.L.entry_140736794734496:
movq $0,-32(%rbp)
movq $-4, %rdi
callq posf
movq %rax, -8(%rbp)
movq $.L.fmtstr.1, %rdi
movq -8(%rbp), %r14
movq %r14, %rsi
xorl %eax, %eax
callq printf
movq $3, %rdi
callq negf
movq %rax, -16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r15
movq %r15, %rsi
xorl %eax, %eax
callq printf
movq -32(%rbp), %r14
cmpq $0, %r14
jle .L.if.else_140736794775456
.L.if.then_140736794775376:
movq $posf,-40(%rbp)
jmp .L.if.end_140736794775840
.L.if.else_140736794775456:
movq $negf,-40(%rbp)
jmp .L.if.end_140736794775840
.L.if.end_140736794775840:
movq -40(%rbp), %r15
movq $4, %rdi
callq *%r15
movq %rax, -24(%rbp)
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r14
movq %r14, %rsi
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
