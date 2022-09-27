#include "os.h"

extern void switch_to(struct context *next);

#define MAX_TASK 10																//最多支持10个线程
#define STACK_SIZE 1024
uint8_t task_stack[MAX_TASK][STACK_SIZE] __attribute__ ((aligned (8)));;	//申请10个栈空间，供线程使用
struct context ctx_task[MAX_TASK];												//上下文结构体，同于保存线程的上下文

static int _top = 0;													
static int _current = -1;

void sched_init(){
	w_mscratch(0);
	w_mie(r_mie() | MIE_MSIE);
}

void schedule(){
	if(_top <= 0){
		panic("Num of task should be greater than zero!");
		return ;
	}

	_current = (_current + 1) % _top;										//top表示现在的线程数量，current表示正在运行的线程
	struct context *next = &(ctx_task[_current]);
	switch_to(next);
}

int task_create(void (*start_routin)(void)){
	if(_top < MAX_TASK){
		ctx_task[_top].sp = (reg_t) (&(task_stack[_top][STACK_SIZE - 1]) + 1);		//注册堆栈指针
		ctx_task[_top].pc = (reg_t) start_routin;							//加入函数指针
		_top++;
		return 0;
	} else {
		return -1;
	}
}

void task_yield(){															//用yield进行封装，不过现在还没有实现系统调用
	int id = r_mhartid();
	*(uint64_t*)CLINT_MSIP(id) = 1;
}

void task_delay(volatile int count){										//用于delay一段时间，之后再进行线程调度
	count *= 5000;
	while(count--);
}
