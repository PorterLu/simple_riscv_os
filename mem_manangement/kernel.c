extern void uart_init(void);
extern void uart_puts(char *s);

extern void uart_init(void);
extern void page_init(void);

void start_kernel(void){
	uart_init();
	uart_puts("Hello RVOS!\n");
	page_init();
	while(1){};
}
