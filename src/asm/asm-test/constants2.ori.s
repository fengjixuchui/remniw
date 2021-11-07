	.text
	.file	"constants2.ori.ll"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	$27, 24(%rsp)
	leaq	32(%rsp), %rsi
	movl	$.Lfmtstr, %edi
	xorl	%eax, %eax
	callq	scanf@PLT
	movq	32(%rsp), %rax
	movq	%rax, 8(%rsp)
	movq	24(%rsp), %rcx
	leaq	(%rax,%rcx,2), %rax
	movq	%rax, 16(%rsp)
	testq	%rcx, %rcx
	jns	.LBB0_2
# %bb.1:                                # %if.then
	movq	16(%rsp), %rax
	addq	$-3, %rax
	movq	%rax, 8(%rsp)
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	movq	$12, 8(%rsp)
.LBB0_3:                                # %if.end
	movq	8(%rsp), %rsi
	movl	$.Lfmtstr.1, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.Lfmtstr,@object                # @fmtstr
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lfmtstr:
	.asciz	"%lli"
	.size	.Lfmtstr, 5

	.type	.Lfmtstr.1,@object              # @fmtstr.1
.Lfmtstr.1:
	.asciz	"%lli\n"
	.size	.Lfmtstr.1, 6

	.section	".note.GNU-stack","",@progbits
