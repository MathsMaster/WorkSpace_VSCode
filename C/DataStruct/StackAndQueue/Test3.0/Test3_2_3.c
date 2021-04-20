/*
    算法设计题第三题
    一个判断回文函数的方法
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 5
typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int top;
} SqStack;

bool InitStack(SqStack *sq)
{
    if (sq == NULL)
        return false;
    sq->top = -1;
    return true;
}

/* 
    插入元素为新的栈顶元素
 */
bool push(SqStack *sq, ElemType e)
{
    if (sq == NULL)
        return false;
    sq->data[++(sq->top)] = e;
    return true;
}

/* 
    删除栈顶元素，并返回其值
 */
ElemType pop(SqStack *sq)
{
    if (sq == NULL)
        return false;
    return sq->data[sq->top--];
}

/* 
    判断是否是空栈
 */
bool stackFull(SqStack *sq)
{
    if (sq == NULL)
        return false;
    if (sq->top + 1 >= MAXSIZE)
        return true;
    return false;
}

void test3_2_3()
{
    ElemType e;
    SqStack stack;
    InitStack(&stack);
    while (true) //准备出栈
    {
        scanf("%d", &e);
        if (e == -1)
            break;
        if (stackFull(&stack))
        {
            printf("栈已满\n");
        }
        else
        {
            push(&stack, e);
        }
    }

    printf("输出栈顶数据: %d \n", pop(&stack));
}

int main()
{
    test3_2_3();
}