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

#ifdef CONFIG_SYSCALL
	li 		t0, 0xffffffff
	csrw	pmpaddr0, t0
	li 		t0, 0xf
	csrw 	pmpcfg0, t0
#endif
 
	# At the end of start_kernel, schedule() will call MRET to switch
	# to the first task, se we prepare the mstatus here.
	# Notice: default mstatus is 0
	# Set mstatus.MPP to 3, so we still run in Machine mode after MRET.
	# Set mstatus.MPIE to 1, so MRET will enable the interrupt.

#ifdef CONFIG_SYSCALL
	li 		t0, 1 << 7
#else
	li 		t0, 3 << 11 | 1 << 7
#endif

	csrr	a1, mstatus			
	or 		t0, t0, a1
	csrw	mstatus, t0

	j start_kernel

park:
	j park

.align 3
stacks:
	.skip STACK_SIZE * MAXNUM_CPU
	.end

