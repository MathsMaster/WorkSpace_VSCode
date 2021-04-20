/* 
    算法设计题第6题
    建立一个循环链表队列,并且只有一个尾部指针存在，不设指向头节点的指针
    入队，出队，初始化，判空，置空队列
    思路:
        每次入队和出队时，通过尾部指针的节点的next找到头节点，然后进行出队的操作
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef int ElemType;

//节点的结构体
typedef struct
{
    ElemType data;
    struct Node *next;
} Node, *Pointer;

//循环链表队列,该队列只有尾部指针，没有头节点的指针
typedef struct
{
    Pointer rear; //只有尾部指针
} LinkedCircleQueen;

//初始化,创建头节点
bool initQueen(LinkedCircleQueen *linkQueen)
{
    if(linkQueen == NULL)
        exit(OVERFLOW);
    Node * headNode = malloc(sizeof(Node));
    linkQueen->rear = headNode;
    linkQueen->rear->next = headNode; 
    return true;
}

/* 
    入队,实际上就是不断的接到尾部节点上
    队列只有尾部指针
 */
bool enQueen(LinkedCircleQueen *linkQueen, ElemType e)
{
    if (linkQueen == NULL)
        exit(OVERFLOW);
    Node *node = malloc(sizeof(Node));
    node->data = e;
    node->next = NULL;//防止野指针

    Node * headNode = linkQueen->rear->next;//先取出头节点
    node->next = headNode;//指向头节点
    linkQueen->rear->next = node;
    linkQueen->rear = node;
}

//出队
ElemType deQueen(LinkedCircleQueen *linkQueen)
{
    if (linkQueen == NULL || linkQueen->rear == NULL)
        exit(OVERFLOW);
    Node *headNode = linkQueen->rear->next;//头节点
    if(headNode == NULL)
        return -1;
    Node * node = headNode->next;//首元节点
    headNode->next = node->next;
    ElemType e = node->data;
    free(node);
    return e;
}

/* 
    清空队列,就是把除了头节点之外，所有的元素，挨个的释放掉
 */
bool clearQueen(LinkedCircleQueen *linkQueen)
{
    if (linkQueen == NULL || linkQueen->rear == NULL)
        exit(OVERFLOW);
    Node *headNode = linkQueen->rear->next;
    if(headNode == NULL)//如果头节点为空
        return false;
    Node *node = headNode->next;//首元节点
    Node *p;
    while (node != NULL && (node != headNode))//这里因为是循环链表，将会循环到头节点上
    {
        p = node;
        node = node->next;
        free(p);
    }
    linkQueen->rear = headNode;//删除完成后，尾部指针要指向头节点，并且头节点的next要指向自己
    linkQueen->rear->next = headNode;
    return true;
}

/* 
    判断队列是否为空
    就是判断是否有首元节点存在,循环链表，首元节点不存在的话，头节点的下一个就指向了自己
 */
bool queenEmpty(LinkedCircleQueen *linkQueen)
{
    if (linkQueen == NULL || linkQueen->rear == NULL)
        exit(OVERFLOW);
    Node * headNode =linkQueen->rear->next; 
    if(headNode == NULL)
        exit(OVERFLOW);
    if(headNode->next == headNode)//循环链表，首元节点不存在时，头节点的下一个就指向了自己
        return true;
    return false;
}

void traverseQueen(LinkedCircleQueen *linkQueen)
{
    if (linkQueen == NULL || linkQueen->rear == NULL)
        exit(OVERFLOW);
    Node * headNode = linkQueen->rear->next;
    if(headNode == NULL)
        exit(OVERFLOW);
    int len = 0;
    Node *node = headNode->next;
    while (node != NULL && (node != headNode))
    {
        printf("队列元素节点[%d]: %d\n",len,node->data);
        len++;
        node = node->next;
    }
}

void test3_2_6()
{
    LinkedCircleQueen linkQueen;//创建队列的对象，里面只有尾部指针
    printf("测试链式队列的初始化。。。。。。\n");
    initQueen(&linkQueen);
    printf("测试链式队列的入队。。。。。。\n");
    for(int i = 0 ; i < 12;i++)
    {
        enQueen(&linkQueen,i*20);
    }
    traverseQueen(&linkQueen);
    printf("\n");

    printf("测试链式队列首元节点的删除。。。。。。\n");
    deQueen(&linkQueen);
    traverseQueen(&linkQueen);
    printf("\n");

    printf("测试链式队列的清空。。。。。。\n");
    clearQueen(&linkQueen);
    traverseQueen(&linkQueen);
    printf("\n");

    printf("队列是否为空 %d \n ",queenEmpty(&linkQueen));
}

int main()
{
    test3_2_6();
}