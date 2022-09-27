#include "os.h"

extern void trap_vector(void);								//中断向量表，陷入的入口
extern void uart_isr(void);
extern void timer_handler(void);
extern void schedule(void);
extern void do_syscall(struct context *cxt);

void trap_init(){
	w_mtvec((reg_t) trap_vector);							//初始化mtvec寄存器
}

reg_t trap_handler(reg_t epc, reg_t cause, struct context *cxt){					
	reg_t return_pc = epc;
	reg_t cause_code = cause & 0xfff;
	if(cause & 0x8000000000000000LL){									//如果是中断则继续执行如果是异常的话，则报错
		switch(cause_code){
			case 3:
					uart_puts("software interruption!\n");
					int id = r_mhartid();
					*(uint64_t *) CLINT_MSIP(id) = 0;
					schedule();
					break;
			case 7:
					uart_puts("timer interruption!\n");
					timer_handler();
					break;
			case 11:
					uart_puts("external interruption!\n");
					break;
			default:
					uart_puts("unknown async exception!\n");
					break;
		}
	} else {
		printf("Sync exception!, code = %d\n", cause_code);
		switch(cause_code){
			case 8:
				uart_puts("System call from U-mode!\n");
				do_syscall(cxt);
				return_pc += 4;
				break;
			default:
				panic("OOPS! what can I do!\n");
		}
	}

	return return_pc;
}

void trap_test(){
	*(int*) 0x00000001 = 100;
	uart_puts("Yeah! I'm return back from trap!\n");
}


