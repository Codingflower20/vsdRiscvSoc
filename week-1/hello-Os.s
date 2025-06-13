	.file	"hello.c"
	.option nopic
	.attribute arch, "rv32i2p1_m2p0_a2p1_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-16
	li	a4,10
	sw	a4,4(sp)
	li	a4,20
	sw	a4,8(sp)
	lw	a4,4(sp)
	lw	a3,8(sp)
	li	a0,0
	add	a4,a4,a3
	sw	a4,12(sp)
	addi	sp,sp,16
	jr	ra
	.size	main, .-main
	.ident	"GCC: (g04696df096) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
