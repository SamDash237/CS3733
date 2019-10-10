	.file	"main.c"
	.text
.globl add
	.type	add, @function
add:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	popl	%ebp
	ret
	.size	add, .-add
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$24, %esp
	movl	$4, 4(%esp)
	movl	$3, (%esp)
	call	add
	movl	%eax, -8(%ebp)
	cmpl	$0, -8(%ebp)
	jle	.L4
	movl	$1, -8(%ebp)
	jmp	.L5
.L4:
	cmpl	$0, -8(%ebp)
	jns	.L6
	movl	$-1, -8(%ebp)
	jmp	.L5
.L6:
	movl	$0, -8(%ebp)
.L5:
	movl	$0, %eax
	addl	$24, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.3.3-5ubuntu4) 4.3.3"
	.section	.note.GNU-stack,"",@progbits
