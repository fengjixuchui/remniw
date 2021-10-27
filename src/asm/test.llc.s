	.text
	.file	"test.ll"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	movq	$1, -8(%rsp)
	movl	$10, %eax
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
