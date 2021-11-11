.text
.globl rec
.type rec, @function
rec:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737045095808:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
cmpq $0, %r15
jne .L.if.else_140737045078480
.L.if.then_140737045078400:
movq $1,-16(%rbp)
jmp .L.if.end_140737045076080
.L.if.else_140737045078480:
movq -8(%rbp), %r14
movq -8(%rbp), %r15
movq $1, %r14
subq %r15, %r14
movq %r14, %rdi
callq rec
imulq %r14, %rax
movq %rax, -16(%rbp)
jmp .L.if.end_140737045076080
.L.if.end_140737045076080:
movq -16(%rbp), %r15
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
.L.entry_140737045100080:
movq $.L.fmtstr, %rdi
movq -8(%rbp), %rsi
callq scanf
movq -8(%rbp), %r14
movq %r14, -16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -16(%rbp), %r15
movq %r15, %rdi
callq rec
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
