/* 
    用于第三章栈和队列里的算法设计题
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <math.h>

#define MAXSIZE 20

typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int top1;
    int top2;
} DbStack; //顺序结构的双栈

/* 
    初始化双栈
 */
bool initStack(DbStack *stack)
{
    if (stack == NULL)
        exit(OVERFLOW);
    stack->top1 = -1;
    stack->top2 = MAXSIZE;
}

/* 
    判空,通过top1，top2的索引来判断
 */
bool stackEmpty(DbStack *stack)
{
    if (stack == NULL)
        exit(OVERFLOW);
    if (stack->top1 == -1 && stack->top2 == MAXSIZE)
        return true;
    return false;
}

/* 
    判满，当top1+1 == top2时就可以判满
 */
bool stackFull(DbStack *stack)
{
    if (stack == NULL)
        exit(OVERFLOW);
    if (stack->top1 + 1 == stack->top2)
        return true;
    return false;
}

/*
    入栈
 */
bool enStack(DbStack *stack, ElemType e, int stackNumber)
{
    if (stack == NULL)
        exit(OVERFLOW);
    if (stackFull(stack))
        return false;
    switch (stackNumber)
    {
    case 1:
        stack->data[++(stack->top1)] = e;
        break;
    default:
        stack->data[--(stack->top2)] = e;
        break;
    }
    return true;
}

/* 
    出栈
 */
bool deStack(DbStack *stack, ElemType *e, int stackNumber)
{
    if (stack == NULL)
        exit(OVERFLOW);
    if (stackEmpty(stack))
        return false;
    switch (stackNumber)
    {
    case 1:
        *e = stack->data[(stack->top1)--];
        break;
    default:
        *e = stack->data[(stack->top2)++];
        break;
    }
    return true;
}

/* 
    打印双栈的所有数据,从栈顶开始打印
 */
void printAll(DbStack *stack)
{
    if (stack == NULL)
        exit(OVERFLOW);
    if (stackEmpty(stack))
    {
        printf("双栈数据为空\n");
        return;
    }

    for (int i = stack->top1; i >= 0; i--)
    {
        printf("双栈的1类数据 [%d] : %d \n", i, stack->data[i]);
    }

    for (int i = stack->top2; i < MAXSIZE; i++)
    {
        printf("双栈的2类数据 [%d] : %d \n", i, stack->data[i]);
    }
}

/* 
    双栈的问题
 */
void test3_2_1()
{
    printf("测试双栈的初始化\n");
    DbStack stack;
    initStack(&stack);
    printf("双栈是否为空 : %d \n", stackEmpty(&stack));

    printf("测试双栈的压入数据。。。。。\n");
    for (int i = 0; i < 30; i++)
    {
        printf("压入数据成功否 : %d \n", enStack(&stack, i * 20, i % 2));
    }
    printf("双栈是否为满 : %d \n", stackFull(&stack));
    printAll(&stack);

    printf("测试双栈的删除数据。。。。。\n\n");
    ElemType e;
    for (int i = 0; i < 30; i++)
    {
        printf("删除数据成功否 : %d \n", deStack(&stack, &e, i % 2));
        printf("删除数据 : %d \n", e);
    }
    printf("双栈是否为空 : %d \n", stackEmpty(&stack));
    printAll(&stack);
}

int main()
{
    test3_2_1();
}