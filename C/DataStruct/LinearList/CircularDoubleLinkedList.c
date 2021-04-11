//双向循环链表
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
    struct CDNode *next;     //节点上指向下一个节点的指针索引
    struct CDNode *previous; //指向上一个节点的指针索引
} CDNode, *CDLinkedList;

/*
    创建头节点,使头指针指向该节点,并且因为是双向链表
    list 传进来的指针
 */
Status InitCDList(CDLinkedList list)
{
    CDNode headNode;
    headNode.data = FLAG;
    //因为是双向循环链表，空表时指向自己
    headNode.previous = list;
    headNode.next = list;
    *list = headNode;
    return OK;
}


/* 
    尾部插入法创建双链表,每个节点都有指向后继节点和前驱节点
    list 一个指针,指向了头节点
    len 链表中的元素的长度(不包括头节点)

 */
Status CreateCDList_L(CDLinkedList list, int len)
{
    CDNode *tempNode = list; //创建临时节点，首先就指向了头节点
    for (int i = 0; i < len; i++)
    {
        CDNode *newNode = (CDNode *)malloc(sizeof(CDNode)); //给当前创建的节点的每一项赋值
        newNode->data = i * 30;
        newNode->next = NULL;
        newNode->previous = tempNode;

        tempNode->next = newNode; //将前驱节点的next指向当前节点

        tempNode = newNode; //最后将当前节点的地址赋予临时指针
    }

    //最后需要把尾部节点和头节点连接起来
    tempNode->next = list;
    list->previous = tempNode;

    return OK;
}

/* 
    用来判断传入的链表的长度，不包含头节点
 */
int getListLength(CDLinkedList list)
{
    if (list == NULL)
        return FAILED;

    CDNode *tempNode = list->next; //先指向首元节点，可能为空
    int len = 0;
    while (true)
    {
        if (tempNode == NULL || tempNode->data == FLAG) //如果找到了
            return len;
        tempNode = tempNode->next;
        len++;
    }
}

void PrintCDLinkedList(CDLinkedList l)
{
    if (l == NULL) //判断指针是否有指向除了NULL外的某个地址
    {
        printf("传进来的指针是NULL");
        return;
    }

    printf("传进来的链表长度(不包括头节点) : %d \n", getListLength(l));

    CDNode *tempNode = l; //从头节点开始打印

    printf("头节点所在的内存空间地址 : %#X  头节点的内容 : %d   当前节点指向的下一个节点的地址 %#X  当前节点指向的上一个节点的地址 %#X \n",
           tempNode, tempNode->data, tempNode->next, tempNode->previous);

    int i = 0; //0表示首元节点
    while (true)
    {
        tempNode = tempNode->next;
        if (tempNode == NULL || tempNode->data == FLAG) //如果是循环链表，必须得想个办法跳出来
            break;

        printf("当前节点所在的内存空间地址 : %#X 当前节点的内容 : %d   当前节点指向的下一个节点的地址 %#X  当前节点指向的上一个节点的地址 %#X \n",
               tempNode, tempNode->data, tempNode->next, tempNode->previous);
    }
}

// int main()
// {
//     LinkedList l = (LinkedList)malloc(sizeof(Node));
//     InitCDList(l);
//     PrintLinkedList(l);

//     printf("\n\n测试尾插法创建双向循环链表\n");
//     CreateCDList_L(l, 15);
//     PrintLinkedList(l);
// }