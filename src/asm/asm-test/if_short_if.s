.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
.L.entry_140737253927072:
movq $0,-8(%rbp)
movq $0,-16(%rbp)
movq $0,-24(%rbp)
movq -8(%rbp), %r15
cmpq $0, %r15
jne .L.if.else5_140737253923712
.L.if.then_140737253923632:
movq -16(%rbp), %r14
cmpq $0, %r14
jne .L.if.else_140737253945408
.L.if.then4_140737253945328:
movq $12,-24(%rbp)
jmp .L.if.end_140737253945872
.L.if.else_140737253945408:
movq $34,-24(%rbp)
jmp .L.if.end_140737253945872
.L.if.end_140737253945872:
jmp .L.if.end6_140737253946880
.L.if.else5_140737253923712:
jmp .L.if.end6_140737253946880
.L.if.end6_140737253946880:
movq -24(%rbp), %r15
movq %r15, %rax
movq %rbp, %rsp
popq %rbp
retq

.L.fmtstr:
.asciz "%lli"
.L.fmtstr.1:
.asciz "%lli\0A"
