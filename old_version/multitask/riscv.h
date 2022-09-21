#ifndef __RISCV_H__
#define __RISCV_H__

#include <stdint.h>

#define reg_t uint64_t

#define UART 0x10000000
#define UART_THR (uint8_t*)(UART+0x00)
#define UART_LSR (uint8_t*)(UART+0x05)
#define UART_LSR_EMPTY_MASK 0x40

struct context{
	reg_t ra;
	reg_t sp;

	reg_t s0;
	reg_t s1;
	reg_t s2;
	reg_t s3;
	reg_t s4;
	reg_t s5;
	reg_t s6;
	reg_t s7;
	reg_t s8;
	reg_t s9;
	reg_t s10;
	reg_t s11;
};


#endif
