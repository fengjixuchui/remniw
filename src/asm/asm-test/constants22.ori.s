	.text
	.file	"constants22.ll"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	$27, 16(%rsp)
	movq	$7, (%rsp)
	movq	$61, 8(%rsp)
	movb	$1, %al
	testb	%al, %al
	jne	.LBB0_2
# %bb.1:                                # %if.then
	movq	8(%rsp), %rax
	addq	$-3, %rax
	movq	%rax, (%rsp)
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	movq	$12, (%rsp)
.LBB0_3:                                # %if.end
	movq	(%rsp), %rsi
	movl	$.Lfmtstr.1, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	addq	$24, %rsp
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
