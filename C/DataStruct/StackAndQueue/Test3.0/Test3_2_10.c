/* 
    算法设计第十题
    使用递归算法处理单链表
        1,求链表中的最大整数
            递归函数传入参数为节点指针，返回参数为节点的数据值
        2,求链表的节点个数
            递归函数，传入参数为节点指针，以及一个计数变量的指针对象，在每次递归函数进栈或者出栈时+1
        3,求所有整数的平均值
            递归函数传入参数为节点指针，以及一个计数变量的指针对象，返回参数为当前节点值和之前递归函数返回的值,
            最后求到总数后，取平均值
 */
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0;
#define TRUE 1;
#define FALSE -1;

typedef int ElemType; //给数据类型取别名

typedef int Status; //给数据类型重命名

/* 定义单链表的结构体 */
typedef struct Node
{
    ElemType data;     //节点上存储数据的部分
    struct Node *next; //节点上指向下一个节点的指针索引
} Node, *LinkedList;   //两个重命名,一个表示节点对象,一个表示链表对象

/* 
    初始化链表(创建空链表) 
    传进来头节点的一个空指针，在这里给他创建一个节点,但该节点仅仅作为头节点使用(不存储任何数据)
    从第一个数据节点(首元节点)才开始存储数据

    这里不能传空指针进来，否则在给指针指向的空间赋值时，就过不去
*/
void InitList(LinkedList list)
{
    list->next = NULL; //当前的链表只有头节点，还没有任何数据元素
}

/* 
    使用后插法创建链表
    数据都是从链表的最后一个节点衔接上
    list 一个指针,指向的是链表的头节点
    len 需要添加的数据长度
 */
Status CreateList_L(LinkedList list, int len)
{
    //创建尾指针,尾指针初时是指向头节点
    Node *lateNode = list;
    for (int i = 0; i < len; i++)
    {
        Node *node = malloc(sizeof(Node)); //开辟节点的空间,
        node->data = i * 20;
        node->next = NULL;
        lateNode->next = node;
        lateNode = node;
    }
    return OK;
}

/* 打印所有节点数据,包括头节点 */
void PrintLinkedList(LinkedList l)
{
    if (l == NULL) //判断指针是否有指向除了NULL外的某个地址
    {
        printf("传进来的指针是NULL");
        return;
    }

    int i = 0;
    Node *tempNode = NULL;
    tempNode = l->next; //首先指向首元节点
    while (true)        //只有指针才可以做判NULL操作,对象是没法来判空的
    {
        printf("[%d] : %d \n", i, tempNode->data);
        tempNode = tempNode->next; //不断的取出下一个来
        if (tempNode == NULL)
            break;
        i++;
    }
}

/* 
    递归的核心部分
 */
int getMaxData(Node *node)
{
    if (node->next == NULL) //如果遍历到了最后的节点
        return node->data;

    int e = getMaxData(node->next); //获取当前节点后面节点的最大数据
    if (e > node->data)
        return e;
    else
        return node->data;
}

/* 
    通过递归的方式求链表中的最大值
 */
void testGetMaxDataByRecursion(LinkedList l)
{
    if (l == NULL || l->next == NULL)
        return;
    int maxNum = getMaxData(l->next); //直接传首元节点进去
    printf("最大数值是 : %d \n", maxNum);
}

/* 
    递归的核心部分,获取传进去的节点以及对应的所有子节点的数据总和
 */
int getSumData(Node *node, int *num)
{
    (*num)++;
    if (node->next == NULL) //如果遍历到了最后的节点
        return node->data;

    int e = getSumData(node->next, num); //获取当前节点后面节点的最大数据
    return e + node->data;
}

/* 
    用递归的方式计算有多少个节点,同时计算出节点的平均值
 */
void testCaluate(LinkedList l)
{
    if (l == NULL || l->next == NULL)
        return;
    int num = 0;
    int sum = getSumData(l->next, &num); //直接传首元节点进去
    printf("链表的节点个数是 : %d ,链表的平均值是 : %d \n", num, sum / num);
}

Status ListInsert(LinkedList list, int index, ElemType e)
{
    if (index < 0)
        return ERROR;
    if (index == 0) //如果是准备从第0个元素的位置插入
    {
        Node *newNode = malloc(sizeof(Node)); //创建新节点所需的空间
        newNode->data = e;
        newNode->next = list->next;
        list->next = newNode;
        return OK;
    }
    else //如果是准备从其他位置开始插入节点
    {
        Node *tempNode = list->next; //先指向首元节点
        int i = 0;
        while (true) //如果索引越界,就直接返回
        {
            if (i == index - 1) //如果当前找到了准备插入的节点位置的前一个节点,准备动手
                break;
            tempNode = tempNode->next;
            i++;
            if (tempNode == NULL) //什么时候判断是否越界比较好呢
                return ERROR;
        }
        Node *newNode = malloc(sizeof(Node)); //创建新节点所需的空间
        newNode->data = e;
        newNode->next = tempNode->next;
        tempNode->next = newNode;
        return OK;
    }
}

int main()
{
    LinkedList list = malloc(sizeof(Node));
    InitList(list);
    CreateList_L(list, 10);
    ListInsert(list, 6, 1000);
    PrintLinkedList(list);

    testGetMaxDataByRecursion(list);

    testCaluate(list);
}