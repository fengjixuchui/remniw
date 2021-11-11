.text
.globl inc
.type inc, @function
inc:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736860884880:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
addq $1, %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl dec
.type dec, @function
dec:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736860875984:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r14
movq $1, %r15
subq %r14, %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl ide
.type ide, @function
ide:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736860854800:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r14
movq %r14, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl foo
.type foo, @function
foo:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140736860855488:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
cmpq $0, %r15
jne .L.if.else_140736860856448
.L.if.then_140736860856368:
movq -8(%rbp), %r14
movq %r14, %rdi
callq dec
movq %rax, -16(%rbp)
jmp .L.if.end_140736860890544
.L.if.else_140736860856448:
jmp .L.if.end_140736860890544
.L.if.end_140736860890544:
movq -8(%rbp), %r15
movq %r15, %rdi
callq inc
movq %rax, -16(%rbp)
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
subq $32, %rsp
.L.entry_140736860893424:
movq $.L.fmtstr, %rdi
leaq -8(%rbp), %rsi
xorl %eax, %eax
callq scanf
movq -8(%rbp), %r15
movq %r15, -16(%rbp)
movq -16(%rbp), %r14
cmpq $0, %r14
jle .L.if.else_140736860895696
.L.if.then_140736860895616:
movq -16(%rbp), %r15
movq %r15, %rdi
callq foo
movq %rax, -24(%rbp)
jmp .L.if.end_140736860896848
.L.if.else_140736860895696:
movq -16(%rbp), %r14
movq %r14, %rdi
callq foo
movq %rax, -24(%rbp)
jmp .L.if.end_140736860896848
.L.if.end_140736860896848:
movq $.L.fmtstr.1, %rdi
movq -24(%rbp), %r15
movq %r15, %rsi
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
