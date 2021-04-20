/* 
    算法设计第8题
    设计一个两端都可以进行删除和插入的队列
    思路:
        如果是使用数组设计的话，队头和队位在越界后判断的话，稍微麻烦点
        使用链表设计的话，就需要用到双向链表，这样头节点和尾部元素都可以进行删除
 */
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node
{
    ElemType data;
    struct Node *next;
    struct Node *pre;
} Node, *Pointer;

//队列的结构体
typedef struct
{
    Pointer headPtr; //一个头指针，指向了队列的头节点
    Pointer rearPtr; //一个尾指针，指向了尾部元素节点
} LinkedDoubleQueen;

/* 
    初始化，让头节点和尾部元素节点的指针都指向头节点的空间
 */
bool initQueen(LinkedDoubleQueen *queen)
{
    if (queen == NULL)
        exit(OVERFLOW);
    queen->headPtr = malloc(sizeof(Node));
    queen->headPtr->data = 0;
    queen->headPtr->pre = NULL;
    queen->headPtr->next = NULL;
    queen->rearPtr = queen->headPtr;
    return true;
}

/* 
    头部正常插入元素
 */
bool enQueen_head(LinkedDoubleQueen *queen, ElemType e)
{
    if (queen == NULL || queen->headPtr == NULL || queen->rearPtr == NULL)
        exit(OVERFLOW);
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->pre = NULL;
    node->data = e;

    Node *headNode = queen->headPtr;           //头节点
    Node *firstEleNode = queen->headPtr->next; //相当于首元节点

    node->next = firstEleNode;
    if (firstEleNode != NULL)
        firstEleNode->pre = node;
    headNode->next = node;
    node->pre = headNode;
    return true;
}

/* 
    在队列尾部插入元素
 */
bool enQueen_rear(LinkedDoubleQueen *queen, ElemType e)
{
    if (queen == NULL || queen->headPtr == NULL || queen->rearPtr == NULL)
        exit(OVERFLOW);

    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->pre = NULL;
    node->data = e;

    queen->rearPtr->next = node;
    node->pre = queen->rearPtr;
    queen->rearPtr = node;
    return true;
}
/* 
    在头节点删除元素
 */
ElemType deQueen_head(LinkedDoubleQueen *queen)
{
    if (queen == NULL || queen->headPtr == NULL || queen->rearPtr == NULL)
        exit(OVERFLOW);
    Node *firstElemNode = queen->headPtr->next;
    if (firstElemNode == NULL)
        return -1;
    ElemType e = firstElemNode->data;

    queen->headPtr->next = firstElemNode->next;
    if (firstElemNode->next != NULL)
        firstElemNode->next->pre = queen->headPtr;

    firstElemNode->next = NULL;
    firstElemNode->pre = NULL;
    free(firstElemNode);
    return e;
}

/* 
    队列尾部删除节点
 */
ElemType deQueen_rear(LinkedDoubleQueen *queen)
{
    if (queen == NULL || queen->headPtr == NULL || queen->rearPtr == NULL)
        exit(OVERFLOW);
    Node *preRearNode = queen->rearPtr->pre; //尾部节点的上一个节点
    //如果当前尾部指针是指向头节点的话，那preRearNode就为NULL，也不用删除了
    if (preRearNode == NULL)
        return -1;
    Node *rearNode = queen->rearPtr;
    ElemType e = rearNode->data;
    preRearNode->next = NULL;
    rearNode->pre = NULL;
    free(rearNode);
    queen->rearPtr = preRearNode;
    return e;
}

void traverseQueen(LinkedDoubleQueen *queen)
{
    if (queen == NULL) //判断指针是否有指向除了NULL外的某个地址
        exit(OVERFLOW);
    Node *tempNode = queen->headPtr; //从头节点开始打印
    if (tempNode == NULL)
        exit(OVERFLOW);
    printf("头节点所在的内存空间地址 : %#X  头节点的内容 : %d   当前节点指向的下一个节点的地址 %#X  当前节点指向的上一个节点的地址 %#X \n",
           tempNode, tempNode->data, tempNode->next, tempNode->pre);

    int i = 0; //0表示首元节点
    while (true)
    {
        tempNode = tempNode->next;
        if (tempNode == NULL)
            break;

        printf("当前节点所在的内存空间地址 : %#X  [%d] : %d   当前节点指向的下一个节点的地址 %#X  当前节点指向的上一个节点的地址 %#X \n",
               tempNode, i, tempNode->data, tempNode->next, tempNode->pre);
        i++;
    }
}

void CreateList_L(LinkedDoubleQueen *queen, int len)
{
    Node *tempNode = queen->headPtr; //创建临时节点，首先就指向了头节点
    for (int i = 0; i < len; i++)
    {
        Node *newNode = malloc(sizeof(Node)); //给当前创建的节点的每一项赋值
        newNode->data = i * 30;
        newNode->next = NULL;
        newNode->pre = tempNode;

        tempNode->next = newNode; //将前驱节点的next指向当前节点

        tempNode = newNode; //最后将当前节点的地址赋予临时指针
        queen->rearPtr = newNode;
    }
}

int main()
{
    LinkedDoubleQueen queen;
    initQueen(&queen);
    CreateList_L(&queen, 5);
    traverseQueen(&queen);

    
    printf("\n\n测试双向队列的尾部删除功能\n");
    deQueen_rear(&queen);
    traverseQueen(&queen);

    printf("\n\n测试双向队列的头部删除功能\n");
    deQueen_head(&queen);
    traverseQueen(&queen);

    printf("\n\n测试双向队列的头部插入功能\n");
    enQueen_head(&queen,1000);
    traverseQueen(&queen);

    printf("\n\n测试双向队列的尾部插入功能\n");
    enQueen_rear(&queen,9999);
    traverseQueen(&queen);
}