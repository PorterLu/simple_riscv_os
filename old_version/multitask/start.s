.extern _memory_end
.global _start

_start:
	csrr t0 ,mhartid
	slli t0, t0, 13
	la sp, _memory_end
	add sp, sp, t0

	csrr a0, mhartid
	bnez a0, park

	j os_main

park:
	j park

