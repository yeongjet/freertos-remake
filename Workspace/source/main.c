#include "./portmacro.h"
#include "./task.h"

#define TASK1_STACK_SIZE 128
StackType_t Task1Stack[TASK1_STACK_SIZE];
#define TASK2_STACK_SIZE 128
StackType_t Task2Stack[TASK2_STACK_SIZE];

int main(void)
{
    TCB_t Task1TCB;
    TCB_t Task2TCB;
}

void delay(uint32_t count)
{
    for (; count != 0; count--)
        ;
}

void Task1_Entry(void *p_arg)(1)
{
    for (;;)
    {
        flag1 = 1;
        delay(100);
        flag1 = 0;
        delay(100);
    }
}

void Task2_Entry(void *p_arg)(2)
{
    for (;;)
    {
        flag2 = 1;
        delay(100);
        flag2 = 0;
        delay(100);
    }
}