.text
.globl foo
.type foo, @function
foo:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737228861360:
movq %rdi, -8(%rbp)
movq -8(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl bar
.type bar, @function
bar:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737228857520:
movq $17, %rdi
callq foo
movq %rax, -8(%rbp)
movq -8(%rbp), %r14
movq %r14, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl baz
.type baz, @function
baz:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
.L.entry_140737228865264:
movq $18, %rdi
callq foo
movq %rax, -8(%rbp)
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
subq $16, %rsp
.L.entry_140737228866384:
callq bar
movq %rax, -8(%rbp)
callq baz
movq %rax, -16(%rbp)
movq $.L.fmtstr.1, %rdi
movq -8(%rbp), %r14
movq -16(%rbp), %r15
addq %r14, %r15
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
