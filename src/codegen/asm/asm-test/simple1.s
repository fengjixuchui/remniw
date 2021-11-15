.text
.globl f
.type f, @function
f:
pushq %rbp
movq %rsp, %rbp
subq $0, %rsp
.L.entry_140736561560560:
movq $1, %rax
movq %rbp, %rsp
popq %rbp
retq

.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $0, %rsp
.L.entry_140736561562848:
movq $.L.fmtstr.1, %rdi
callq f
movq %rax, %rsi
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
