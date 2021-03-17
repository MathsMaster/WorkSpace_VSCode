//双链式线性表,每个节点都有两个指针,分别指向了其前驱节点和后驱节点
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0;
#define TRUE 1;
#define FALSE -1;
#define FAILED -1;

const int FLAG = -111111;

typedef int ElemType; //给数据类型取别名
typedef int Status;   //给数据类型重命名

typedef struct
{
    ElemType data;         //节点上存储数据的部分
    struct Node *next;     //节点上指向下一个节点的指针索引
    struct Node *previous; //指向上一个节点的指针索引
} Node,                    //专门用于元素节点的结构体对象
    *LinkedList;           //专门用来指向头节点的指针

/*
    创建头节点,使头指针指向该节点,并且因为是双向链表
    list 传进来的指针
 */
Status InitList(LinkedList list)
{
    Node headNode;
    headNode.data = FLAG;
    headNode.previous = NULL;
    headNode.next = NULL;
    *list = headNode;

    return OK;
}

/* 
    尾部插入法创建双链表,每个节点都有指向后继节点和前驱节点
    list 一个指针,指向了头节点
    len 链表中的元素的长度(不包括头节点)

 */
Status CreateList_L(LinkedList list, int len)
{
    Node *tempNode = list; //创建临时节点，首先就指向了头节点
    for (int i = 0; i < len; i++)
    {
        Node *newNode = malloc(sizeof(Node)); //给当前创建的节点的每一项赋值
        newNode->data = i * 30;
        newNode->next = NULL;
        newNode->previous = tempNode;

        tempNode->next = newNode; //将前驱节点的next指向当前节点

        tempNode = newNode; //最后将当前节点的地址赋予临时指针
    }

    return OK;
}

/* 
    在双向链表中删除数据
    list 一个指针，指向了链表的头节点
    index 待删除节点的索引，从0开始计数，0表示首元节点
    考虑几种特殊情况，往index< 0 , index== 0 ,index>len , index== len删除的情况
 */
Status ListDelete(LinkedList list, int index)
{
    if (list == NULL || index < 0)
        return ERROR;

    //遍历元素，找到待删除节点的前驱节点和后继节点
    Node *nextNode = NULL;
    Node *preNode = NULL;
    Node *tempNode = list->next; //找到首元节点,这里的首元节点可能是NULL

    if (tempNode == NULL) //首元节点都为空的话，也不用删除了
        return ERROR;

    int i = 0; //从首元节点开始计数
    while (true)
    {
        nextNode = tempNode->next;
        preNode = tempNode->previous;

        if (index == i) //找到待删除的节点后
        {
            preNode->next = nextNode;
            if (nextNode != NULL) //这里需要判断后继节点是否存在,假如删除的节点正好是最后一个节点
                nextNode->previous = preNode;
            break;
        }

        i++;
        tempNode = nextNode;
        if (tempNode == NULL)
            return ERROR;
    }

    return OK;
}

/* 
    用来判断传入的链表的长度，不包含头节点
 */
int getListLength(LinkedList list)
{
    if (list == NULL)
        return FAILED;

    Node *tempNode = list->next; //先指向首元节点，可能为空
    int len = 0;
    while (true)
    {
        if (tempNode == NULL || tempNode->data == FLAG) //如果找到了
            return len;
        tempNode = tempNode->next;
        len++;
    }
}

/* 
    根据索引来获取链表中的一个节点
    desNode 用来进行返回的
    index从0开始，0表示首元节点的索引
 */
bool getListNodeByIndex(LinkedList list, int index, Node *desNode)
{
    if (list == NULL)
        return false;

    int len = getListLength(list);
    if (len <= 0 || index >= len)
        return false;

    //先指向首元节点，可能为空
    Node *tempNode = list->next;
    int i = 0;
    while (true)
    {
        if (i >= len)
            return false;

        if (i == index)
        {
            desNode = tempNode;
            return true;
        }
        tempNode = tempNode->next;
        i++;
    }
}

/* 
    获取链表的最后一个节点
 */
Node *getListLastNode(LinkedList list)
{
    if (list == NULL)
        return NULL;

    //先指向首元节点，可能为空
    Node *preNode = list->next;
    Node *tempNode = list->next;
    while (true)
    {
        if (tempNode == NULL || tempNode->data == FLAG) //如果找到了
            return preNode;
        preNode = tempNode; //用来持有之前的一个节点
        tempNode = tempNode->next;
    }
}

/* 
    在双向链表中插入数据
    list 一个指针，指向了链表的头节点
    index 待插入节点的索引,从0开始计数，0表示首元节点
    e 数据元素
    考虑几种特殊情况，往index< 0 , index== 0 ,index>len , index== len插入的情况
 */
Status ListInsert(LinkedList list, int index, ElemType e)
{
    if (list == NULL || index < 0)
        return ERROR;

    //获取到链表长度,判断插入位置的索引
    int len = getListLength(list);
    if (index >= 0 && index <= len)
    {
        //找到待插入位置的前驱节点和后继节点
        Node *preNode = NULL;
        Node *nextNode = NULL;
        Node *tempNode = NULL;

        //有可能插入的位置就在首元节点处
        if (index == 0)
        {
            preNode = list;           //因为插入的就在首元节点位置,前驱节点就是头节点
            nextNode = preNode->next; //后继节点可能为空
            tempNode = malloc(sizeof(Node));
            tempNode->data = e;
            tempNode->next = NULL;
            tempNode->previous = NULL;

            preNode->next = tempNode;
            tempNode->previous = preNode;
            tempNode->next = nextNode;
            nextNode->previous = tempNode;
        }
        else if (index == len) //插入位置在最后面
        {
            Node *lastNode = getListLastNode(list);
            preNode = lastNode;
            tempNode = malloc(sizeof(Node));
            tempNode->data = e;
            tempNode->next = NULL;
            tempNode->previous = NULL;

            preNode->next = tempNode;
            tempNode->previous = preNode;
        }
        else //插入位置在中间
        {
            bool isExist = getListNodeByIndex(list, index, preNode);
            if (isExist)
            {
                nextNode = preNode->next; //后继节点可能为空
                tempNode = malloc(sizeof(Node));
                tempNode->data = e;
                tempNode->next = NULL;
                tempNode->previous = NULL;

                preNode->next = tempNode;
                tempNode->previous = preNode;
                tempNode->next = nextNode;
                nextNode->previous = tempNode;
            }
            else
            {
                return ERROR;
            }
        }
    }
    else
    {
        return ERROR;
    }
}

/* 
    打印所有节点数据,包括头节点,同时打印出每个节点的前驱节点和后继节点的地址空间
    0索引表示首元节点
    l 传进来的一个指针,指向了链表的头节点
 */
void PrintLinkedList(LinkedList l)
{
    if (l == NULL) //判断指针是否有指向除了NULL外的某个地址
    {
        printf("传进来的指针是NULL");
        return;
    }

    Node *tempNode = l; //从头节点开始打印

    printf("头节点所在的内存空间地址 : %#X  头节点的内容 : %d   当前节点指向的下一个节点的地址 %#X  当前节点指向的上一个节点的地址 %#X \n",
           tempNode, tempNode->data, tempNode->next, tempNode->previous);

    int i = 0; //0表示首元节点
    while (true)
    {
        tempNode = tempNode->next;
        if (tempNode == NULL || tempNode->data == FLAG) //如果是循环链表，必须得想个办法跳出来
            break;

        printf("当前节点所在的内存空间地址 : %#X  当前节点的索引 : %d  当前节点的内容 : %d   当前节点指向的下一个节点的地址 %#X  当前节点指向的上一个节点的地址 %#X \n",
               tempNode, i, tempNode->data, tempNode->next, tempNode->previous);
        i++;
    }
}

int main()
{
    //测试初始化,先开辟好头节点的空间
    LinkedList l = malloc(sizeof(Node));
    InitList(l);
    PrintLinkedList(l);

    //测试尾插法创建双向链表
    printf("\n\n测试尾插法创建双向链表\n");
    CreateList_L(l, 15);
    PrintLinkedList(l);

    //测试双向链表的删除操作
    printf("\n\n测试双向链表的删除操作\n");
    int status = ListDelete(l, 15);
    if (status)
        printf("删除操作成功\n");
    else
        printf("删除操作失败\n");
    PrintLinkedList(l);
}
