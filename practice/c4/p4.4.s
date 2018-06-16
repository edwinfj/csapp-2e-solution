	.file	"p4.4.c"
	.text
	.globl	absSum
	.type	absSum, @function
absSum:
.LFB0:
	.cfi_startproc
	testl	%esi, %esi
	je	.L6
	movl	$0, %eax
.L5:
	movl	(%rdi), %edx
	movl	%eax, %ecx
	subl	%edx, %ecx
	addl	%edx, %eax
	testl	%edx, %edx
	cmovs	%ecx, %eax
	addq	$4, %rdi
	subl	$1, %esi
	jne	.L5
	rep ret
.L6:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	absSum, .-absSum
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.4) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
