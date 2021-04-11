/* 
    顺序存储结构的栈
    用于演示数组实现的栈的函数功能

 */
#include <stdio.h>
#include <stdbool.h>

#define SUCCESS 100
#define ERROR -1
#define MAXSIZE 100

typedef int Status;
typedef int ElemType;

typedef struct
{
    int top; //指向当前栈顶元素的索引,默认-1
    ElemType data[MAXSIZE];
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
    清空栈，实际上就是把指向栈顶的索引，修改成-1
 */
bool clearStack(SqStack *sq)
{
    if (sq == NULL)
        return false;
    sq->top = -1;
    return true;
}

/* 
    判断是否是空栈
 */
bool stackEmpty(SqStack *sq)
{
    if (sq == NULL)
        return false;
    if (sq->top == -1)
        return true;
    return false;
}

/* 
    获取栈的元素长度
 */
int getStackLength(SqStack *sq)
{
    if (sq == NULL)
        return -1;
    return sq->top + 1;
}

/* 
    获取栈顶部元素
 */
ElemType getTop(SqStack *sq)
{
    if (sq == NULL || sq->top == -1)
        return -1;

    return sq->data[sq->top];
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
    打印栈中的每个元素
 */
void stackTraverse(SqStack *sq)
{
    if (sq == NULL)
        return;
    for (int i = 0; i < getStackLength(sq); i++)
    {
        printf("sq.data[%d] : %d \n",i,sq->data[i]);
    }
}

int main()
{
    printf("测试初始化\n");
    //测试初始化
    SqStack sqStack;
    InitStack(&sqStack);

    printf("测试压入栈\n");
    for(int i = 0 ; i < 10 ; i ++)
    {
        push(&sqStack,i);
    }

    stackTraverse(&sqStack);

    printf("栈的长度 %d \n",getStackLength(&sqStack));
    ElemType e = getTop(&sqStack);
    printf("getTop取出的栈顶部元素为 : %d \n",e);
    printf("栈的长度 %d \n",getStackLength(&sqStack));
    e = pop(&sqStack);
    printf("pop取出的栈顶部元素为 : %d \n",e);
    printf("栈的长度 %d \n",getStackLength(&sqStack));
}