#include "platform.h"

	.equ STACK_SIZE, 1024
	
	.global _start
	
	.text
_start:
	csrr	t0, mhartid
	mv		tp, t0
	bnez	t0, park

	# Set all bytes in the BSS section to zero
	la 		a0, _bss_start
	la 		a1, _bss_end
	bgeu	a0, a1, 2f
1:
	sd 		zero, (a0)
	add		a0,	a0, 8
	bltu 	a0, a1, 1b
2:
	# Setup stacks, the stack grows from bottom to top, so we put
	# the stack pointer to the very end of the stack range
	slli 	t0, t0, 10
	la 		sp, stacks + STACK_SIZE

	add		sp, sp, t0

	j start_kernel

park:
	j park

.align 3
stacks:
	.skip STACK_SIZE * MAXNUM_CPU
	.end

