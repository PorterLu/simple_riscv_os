#ifndef __OS_H__
#define __OS_H__

#include "riscv.h"
#include "lib.h"
#include "task.h"

extern int os_main(void);
extern void os_kernel();
extern void user_init();

#endif
