//创建循环单链表
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0;
#define TRUE 1;
#define FALSE -1;
const int FLAG = -111111;

typedef int ElemType; //给数据类型取别名
typedef int Status;   //给数据类型重命名

typedef struct
{
    ElemType data;     //节点上存储数据的部分
    struct Node *next; //节点上指向下一个节点的指针索引
} Node,                //专门用于元素节点的结构体对象
    *LinkedList;       //专门用来指向头节点的指针

/* 
    初始化循环单链表,为
 */
Status InitList(LinkedList list)
{
    //创建头节点对象,放入头节点的空间中
    Node headNode;
    headNode.data = FLAG;
    *list = headNode;
    list->next = list; //最后使头节点的next指向自己
    return OK;
}

/* 
    尾部插入法创建链表
    list 一个指针,指向了头节点
    len 链表中的元素的长度(不包括头节点)
 */
Status CreateList_L(LinkedList list, int len)
{
    Node *tempNode = list; //创建个临时节点的指针,先指向头节点
    for (int i = 0; i < len; i++)
    {
        Node *newNode = malloc(sizeof(Node));
        newNode->data = i * 20;
        tempNode->next = newNode; //将其挂到前面的一个节点后面
        newNode->next = list;     //再使当前节点指向头节点

        tempNode = newNode; //最后使临时节点的指针,指向该新加入的节点
    }
}

/* 
    打印所有节点数据,包括头节点
    l 传进来的一个指针,指向了链表的头节点
 */
void PrintLinkedList(LinkedList l)
{
    if (l == NULL) //判断指针是否有指向除了NULL外的某个地址
    {
        printf("传进来的指针是NULL");
        return;
    }

    int i = 0;
    Node *tempNode = l; //从头节点开始打印
    while (true)        //只有指针才可以做判NULL操作,对象是没法来判空的
    {
        printf("临时指针变量本身的地址 : %#X   当前节点所在的内存空间地址 : %#X  当前节点的索引 : %d  当前节点的内容 : %d   当前节点指向的下一个节点的地址 %#X \n",
               &tempNode, tempNode, i, tempNode->data, tempNode->next);
        tempNode = tempNode->next;  //不断的取出下一个来
        if (tempNode->data == FLAG) //因为是循环链表，必须得想个办法跳出来
        {
            break;
        }
        i++;
    }
}

int main()
{
    //测试初始化
    printf("\n\n测试初始化\n");
    LinkedList list = malloc(sizeof(Node)); //先为头节点开辟空间
    int status = InitList(list);
    if (status)
        printf("初始化成功!\n");
    else
        printf("初始化失败!\n");
    PrintLinkedList(list);

    //测试初始化
    printf("\n\n测试尾部插入法创建循环链表\n");
    CreateList_L(list, 10);
    PrintLinkedList(list);


    return 0;
}