#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#define MAXNUM_CPU 8

/*
 * 0x00001000 -- boot ROM,
 * 0X02000000 -- CLINT
 * 0X0C000000 -- PLIC
 * 0X10000000 -- UART
 * 0x10001000 -- virtio disk
 * 0x80000000 -- where we load our kernel
*/
#define UART0 0x10000000L
//#define UART0 0xa00003f8L

#define CLINT_BASE 0x2000000L
#define CLINT_MSIP(hartid) (CLINT_BASE + 8 * (hartid))
#define CLINT_MTIMECMP(hartid) (CLINT_BASE + 0x4000 + 8 * (hartid))
#define CLINT_MTIME (CLINT_BASE + 0xBFF8)

#define CLINT_TIMEBASE_FREQ 0x1000000

#endif
