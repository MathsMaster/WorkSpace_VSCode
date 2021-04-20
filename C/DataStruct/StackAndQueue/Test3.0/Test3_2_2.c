/*
    算法设计题第二题
    一个判断回文函数的方法
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 1024

typedef char ElemType;
typedef struct
{
    ElemType data[MAXSIZE];
    int top; //默认指向-1
} SqStack;

/* 
    初始化
 */
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
    判断字符串是否是回文
    思路:
        将一半的char字符入栈，然后再取另一半的字符来挨个进行比较
 */
bool judgeWord(ElemType s[])
{
    SqStack stack;
    InitStack(&stack);
    int len = strlen(s);

    for (int i = 0; i < len / 2; i++)
    {
        push(&stack, s[i]);
    }

    ElemType e;
    bool isHuiwen = true;
    if (len % 2 == 1) //字符长度为奇数
    {
        for (int i = (len / 2) + 1; i < len; i++)
        {
            if (pop(&stack) != s[i])
                isHuiwen = false;
        }
    }
    else
    { //字符长度为偶数
        for (int i = len / 2; i < len; i++)
        {
            ElemType c = s[i];
            ElemType b = pop(&stack);
            if (b != c)
                isHuiwen = false;
        }
    }
    return isHuiwen;
}

void test3_2_2()
{
    printf("输入的数据是否为回文 : %d \n", judgeWord("abcdscba"));
}

int main()
{
    test3_2_2();
}