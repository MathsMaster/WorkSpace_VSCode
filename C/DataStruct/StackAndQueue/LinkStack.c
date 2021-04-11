/* 
    使用链表实现的栈
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXSIZE 20

typedef int ElemType;

//定义链表的节点对象
typedef struct
{
    ElemType data;
    struct StackNode *next;
} StackNode;

//定义栈的结构体对象
typedef struct
{
    StackNode *top; //指向栈顶的指针,但栈为NULL时，这里指向NULL
    int count;
} LinkStack;

bool initStack(LinkStack *linkStack)
{
    if (linkStack == NULL) //传进来的对象指向了NULL
        return false;
    linkStack->count = 0;
    linkStack->top = NULL;
    return true;
}

bool clearStack(LinkStack *linkStack)
{
    if (linkStack == NULL) //传进来的对象指向了NULL
        return false;
    StackNode *node, *p; //因为C语言没有内存回收机制，所以需要手动是否内存
    node = linkStack->top;
    while (node != NULL)
    {
        p = node;
        node = node->next;
        free(p);
    }
    linkStack->count = 0;
    linkStack->top = NULL;
    return true;
}

int getLinkStackLength(LinkStack *linkStack)
{
    if (linkStack == NULL) //传进来的对象指向了NULL
        return -1;
    return linkStack->count;
}

/* 
    获取栈顶对象
 */
ElemType getTop(LinkStack *linkStack)
{
    if (linkStack == NULL) //传进来的对象指向了NULL
        return -1;
    return linkStack->top->data;
}

/* 
    将元素压入栈顶
 */
bool push(LinkStack *linkStack, ElemType e)
{
    if (linkStack == NULL) //传进来的对象指向了NULL
        return false;
    StackNode *node = malloc(sizeof(StackNode));
    node->data = e;
    node->next = linkStack->top;
    linkStack->top = node;
    linkStack->count++;
    return true;
}

/* 
    移除栈顶部元素
 */
ElemType pop(LinkStack *linkStack)
{
    if (linkStack == NULL) //传进来的对象指向了NULL
        return -1;
    StackNode *topNode = linkStack->top;
    int e = topNode->data;
    linkStack->top = topNode->next;
    topNode->next = NULL;
    free(topNode);
    linkStack->count--;
    return e;
}

void stackTraverse(LinkStack *linkStack)
{
    if (linkStack == NULL)
        return;

    StackNode *node = linkStack->top;
    int i = 0;
    while (node != NULL)
    {
        printf("sq.data[%d] : %d \n", i, node->data);
        node = node->next;
        i++;
    }
}

/* 
    这是一个递归函数，用于计算阶乘
    N! = 1*2*3*4*.....*N;
 */
int fact(int n)
{
    if (n == 1)
        return 1;
    return n * (fact(n - 1));
}

/* 
    使用递归来遍历一个链表
 */
void traverseList(StackNode *top)
{
    if (top == NULL)
        return;
    printf("当前遍历的链表数据1 : %d \n", top->data);
    traverseList(top->next);
    printf("当前遍历的链表数据 : %d \n", top->data);
}

int main()
{
    printf("测试初始化\n");
    //测试初始化
    LinkStack linkStack;
    bool isSuccess = initStack(&linkStack);
    printf("初始化成功\n");
    stackTraverse(&linkStack);

    printf("测试压入栈\n");
    for (int i = 0; i < 10; i++)
    {
        push(&linkStack, i * 10);
    }
    printf("链栈的长度 %d \n", getLinkStackLength(&linkStack));
    stackTraverse(&linkStack);

    ElemType e = getTop(&linkStack);
    printf("getTop取出的栈顶部元素为 : %d \n", e);
    printf("栈的长度 %d \n", getLinkStackLength(&linkStack));
    e = pop(&linkStack);
    printf("pop取出的栈顶部元素为 : %d \n", e);
    printf("链栈的长度 %d \n", getLinkStackLength(&linkStack));
    e = pop(&linkStack);
    printf("pop取出的栈顶部元素为 : %d \n", e);
    printf("链栈的长度 %d \n", getLinkStackLength(&linkStack));

    int result = fact(5);
    printf("递归计算阶乘的结果 %d \n", result);

    traverseList(linkStack.top);
}