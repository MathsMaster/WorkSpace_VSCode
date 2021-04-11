/* 
    链式队列的实现
    需要两个指针，一个指向头节点，一个指向尾节点，一个专门用于出队，一个专门用于入队
    这里的链队为什么喜欢弄个头节点出来,而链栈就不弄出个头节点来
    难道就因为是用来，在初始化时，让头指针和尾指针能指向个共同的空间吗
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "math.h"
#include "time.h"

typedef int ElemType;

//节点对象的结构体
typedef struct
{
    ElemType data;
    struct Node *next;
} Node, *QueenPointer;

//队列的结构体对象
typedef struct
{
    QueenPointer head; //指向头节点的指针
    QueenPointer rear; //指向尾节点的指针
} LinkQueen;

/* 
    初始化队列,就是创建头节点，然后让头节点和尾节点都指向该空间
 */
bool initQueen(LinkQueen *linkQueen)
{
    printf("开始初始化.... \n");
    if (linkQueen == NULL)
        exit(OVERFLOW);                                       //直接退出程序
    linkQueen->rear = linkQueen->head = malloc(sizeof(Node)); //开始时都指向了头节点
    if (linkQueen->head == NULL)                              //如果没法开辟空间
        exit(OVERFLOW);                                       //直接退出程序
    linkQueen->head->next = NULL;
    linkQueen->rear->next = NULL;
    return true;
}

/* 
    入队,实际上就是不断的接到尾部节点上
 */
bool enQueen(LinkQueen *linkQueen, ElemType e)
{
    if (linkQueen == NULL)
        exit(OVERFLOW);
    Node *node = malloc(sizeof(Node));
    node->data = e;
    node->next = NULL;

    linkQueen->rear->next = node;
    linkQueen->rear = node;
}

/* 
    出队,头指针不变(C语言里就喜欢专门搞个头节点,浪费空间,java就不干这事)
    直接删除头节点下面的元素
    如果是在java里面，头节点就是第一个元素的节点
    但是在C语言里面，头节点是不作为存储元素的，接下来的一个节点才是第一个元素节点
 */
ElemType deQueen(LinkQueen *linkQueen)
{
    if (linkQueen == NULL || linkQueen->head == NULL)
        return -1;
    Node *node = linkQueen->head->next;
    linkQueen->head->next = node->next;
    ElemType e = node->data;
    free(node);
    return e;
}

/* 
    清空队列,就是把除了头节点之外，所有的元素，挨个的释放掉
 */
bool clearQueen(LinkQueen *linkQueen)
{
    if (linkQueen == NULL || linkQueen->head == NULL)
        return false;
    Node *node = linkQueen->head->next;
    Node *p;
    while (node != NULL)
    {
        p = node;
        node = node->next;
        free(p);
    }
    linkQueen->head->next = NULL;
    linkQueen->rear = linkQueen->head;
    return true;
}

/* 
    判断队列是否为空
 */
bool queenEmpty(LinkQueen *linkQueen)
{
    if (linkQueen == NULL || linkQueen->head == NULL)
        exit(OVERFLOW);
    if (linkQueen->head == linkQueen->rear)
        return true;
    return false;
}

/* 
    获取队列的首元节点的元素
 */
ElemType getHead(LinkQueen *linkQueen)
{
    if (linkQueen == NULL || linkQueen->head == NULL || linkQueen->head->next == NULL)
        return -1;
    Node *node = linkQueen->head->next;
    return node->data;
}

/* 
    获取队列长度
 */
int getQueenLength(LinkQueen *linkQueen)
{
    if (linkQueen == NULL || linkQueen->head == NULL)
        exit(OVERFLOW);
    int len = 0;
    Node *node = linkQueen->head->next;
    while (node != NULL)
    {
        len++;
        node = node->next;
    }
    return len;
}

/* 
    从对头到队尾部，依次遍历元素
    尾部索引因为一直指向了待插入的位置,所以只需要<即可
 */
void traverseQueen(LinkQueen *linkQueen)
{
    if (linkQueen == NULL || linkQueen->head == NULL)
        exit(OVERFLOW);
    int len = 0;
    Node *node = linkQueen->head->next;
    while (node != NULL)
    {
        printf("队列元素节点[%d]: %d\n",len,node->data);
        len++;
        node = node->next;
    }
}

int main()
{
    LinkQueen linkQueen;//创建队列的对象，里面只有两个节点指针
    printf("测试链式队列的初始化。。。。。。\n");
    initQueen(&linkQueen);
    printf("队列的长度 : %d \n",getQueenLength(&linkQueen));
    printf("测试链式队列的入队。。。。。。\n");
    for(int i = 0 ; i < 12;i++)
    {
        enQueen(&linkQueen,i*20);
    }
    printf("队列的长度 : %d \n",getQueenLength(&linkQueen));
    traverseQueen(&linkQueen);

    printf("测试链式队列首元节点的删除。。。。。。\n");
    deQueen(&linkQueen);
    printf("队列的长度 : %d \n",getQueenLength(&linkQueen));
    printf("队列的首元节点 : %d \n",getHead(&linkQueen));

    printf("测试链式队列的清空。。。。。。\n");
    clearQueen(&linkQueen);
    printf("队列的长度 : %d \n",getQueenLength(&linkQueen));
    printf("队列的首元节点 : %d \n",getHead(&linkQueen));
    traverseQueen(&linkQueen);

    printf("队列是否为空 %d \n ",queenEmpty(&linkQueen));
}