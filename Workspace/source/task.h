#ifndef TASK_H
#define TASK_H
#include "./portmacro.h"

typedef struct tskTaskControlBlock
{
	volatile StackType_t *pxTopOfStack;		  // 栈顶指针
	ListItem_t xStateListItem;				  // 任务节点 用于将任务控制块挂接到链表中
	StackType_t *pxStack;					  // 任务栈起始地址
	char pcTaskName[configMAX_TASK_NAME_LEN]; // 任务名称
} tskTCB;

typedef tskTCB TCB_t;

typedef void * TaskHandle_t;

#endif