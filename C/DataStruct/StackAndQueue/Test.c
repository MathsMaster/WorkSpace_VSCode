/* 
    舞伴问题
    先准备好两个队列的数据，其中男队列11人，女队列22人
    接下来就是开始配对的问题，每次男队列和女队列各出一个人，直到其中一个队列全部出完
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"
#include "time.h"

//数据对象
typedef struct Person
{
    char sex; //0为男，1为女
    char *name;
} ElemType;

//节点对象
typedef struct
{
    ElemType data;
    struct Node *next;
} Node, *QueenPter;

//队列的两个指针
typedef struct
{
    QueenPter head, rear;
} LinkQueen;

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
        exit(OVERFLOW);
    Node *node = linkQueen->head->next;
    linkQueen->head->next = node->next; //如果当前传进来的队列中元素都用完了，则这里会出现空指针的bug
    ElemType e = node->data;
    free(node);
    return e;
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
        printf("队列元素节点[%d]: name : %s , sex : %d \n", len, node->data.name, node->data.sex);
        len++;
        node = node->next;
    }
}

/* 
    准备数据
 */
LinkQueen *prepareDancerQueen(bool isF)
{
    LinkQueen *queen = malloc(sizeof(LinkQueen));//C语言里面这样直接创建对象都很危险，创建的空间除非被指针持有，否则代码块走完,很快就会被回收
    if (isF)
    {
        initQueen(queen);
        for (int i = 0; i < 10; i++)
        {
            ElemType *e = malloc(sizeof(ElemType));
            e->name = malloc(10);
            sprintf(e->name, "%s%d", "张三", i);
            sprintf(e->name + strlen(e->name), "%d", i);
            e->sex = 0;
            enQueen(queen, *e);
        }
    }
    else
    {
        initQueen(queen);
        for (int i = 0; i < 15; i++)
        {
            ElemType *e = malloc(sizeof(ElemType));
            e->name = malloc(10);
            sprintf(e->name, "%s%d", "小翠", i);
            sprintf(e->name + strlen(e->name), "%d", i);
            e->sex = 1;
            enQueen(queen, *e);
        }
    }
    printf("创建的队列内存地址: %#x \n",queen);
    return queen;
}

/* 
    开始配对
 */
void startCollect(LinkQueen *queenPter, LinkQueen *fQueenPter)
{

    while (getQueenLength(queenPter) > 0 && getQueenLength(fQueenPter) > 0)
    {
        ElemType man = deQueen(queenPter);
        ElemType female = deQueen(fQueenPter);
        printf("配对成功一对 name : %s , %s \n",man.name,female.name);
    }

    printf("剩余未配对的人.....\n");
    traverseQueen(queenPter);
    traverseQueen(fQueenPter);
    
}

void test()
{
    LinkQueen *queenPter = prepareDancerQueen(true); //男士队列
    traverseQueen(queenPter);
    LinkQueen *fQueenPter = prepareDancerQueen(false); //女士队列
    traverseQueen(fQueenPter);
    startCollect(queenPter,fQueenPter);
}

int main()
{
    test();
}