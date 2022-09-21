#include <stdint.h>

#define UART 0xa00003f8 //0x10000000
#define UART_THR (uint8_t *)(UART + 0x00)
#define UART_LSR (uint8_t *)(UART + 0x05)
#define UART_LSR_EMPTY_MASK 0x40

int lib_putc(char ch){
	//while((*UART_LSR & UART_LSR_EMPTY_MASK) == 0);
	return *UART_THR = ch;
}


void lib_puts(char *s){
	while(*s) lib_putc(*s++);
}

int os_main(void){
	lib_puts("Hello OS!\n");
	while(1){}
	return 0;
}
