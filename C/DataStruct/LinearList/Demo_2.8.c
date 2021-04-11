/* 
    创建一个链式存储结构，用来实现对稀疏多项式的相加
    先准备好两份链式存储的数据(创建链表)
    再进行对应的相加操作
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//多项式的节点
typedef struct PNode
{
    int codf; //多项式的系数
    int expn; //多项式的指数
    struct PNode *next;
} * LinkedList, PNode;

bool InitList(LinkedList list)
{
    PNode headerNode;
    *list = headerNode; //创建头节点，并且给头指针赋值
    list->next = NULL;  //当前的链表只有头节点，还没有任何数据元素
    return true;
}

/* 
    往链表中插入数据(需要创建元素)
    list 指向单链表头节点的指针
    index 元素插入位置的索引,从0开始计算，以首元节点为0
    expn 节点中的数据部分的指数
    codf 节点中的数据部分的系数
 */
bool ListInsert(LinkedList list, int index, int expn, int codf)
{
    if (index < 0)
        return false;
    if (index == 0) //如果是准备从第0个元素的位置插入
    {
        PNode *newNode = (PNode *)malloc(sizeof(PNode)); //创建新节点所需的空间
        newNode->codf = codf;
        newNode->expn = expn;
        newNode->next = list->next;
        list->next = newNode;
        return true;
    }
    else //如果是准备从其他位置开始插入节点
    {
        PNode *tempNode = list->next; //先指向首元节点
        int i = 0;
        while (true) //如果索引越界,就直接返回
        {
            if (i == index - 1) //如果当前找到了准备插入的节点位置的前一个节点,准备动手
                break;
            tempNode = tempNode->next;
            i++;
            if (tempNode == NULL) //什么时候判断是否越界比较好呢
                return false;
        }
        PNode *newNode = (PNode *)malloc(sizeof(PNode)); //创建新节点所需的空间
        newNode->codf = codf;
        newNode->expn = expn;
        newNode->next = tempNode->next;
        tempNode->next = newNode;
        return true;
    }
}

int Length(LinkedList list)
{
    if (list == NULL)
        return 0;
    int len = 0;
    PNode *node = list->next; //先拿到首元节点的指针
    while (true)
    {
        if (node != NULL)
        {
            len++;
            node = node->next;
        }
        else
        {
            break;
        }
    }
    return len;
}

PNode *GetElem(LinkedList list, int index)
{
    int i = 0;
    PNode *tempNode = list->next; //先指向首元节点
    while (true)
    {
        if (i == index)
        {
            return tempNode;
        }
        tempNode = tempNode->next;
        i++;
    }
}

LinkedList prepareListData(bool isFirst)
{
    //先准备好两个顺序线性表及其相关数据
    LinkedList list = malloc(sizeof(PNode));
    InitList(list);
    int arr0[] = {1, 3, 5, 8, 10};              //作为指数
    int arr1[] = {1, 2, 4, 6, 9};               //作为系数
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};   //作为指数
    int arr3[] = {1, 3, 4, 5, 7, 8, 9, 10, 11}; //作为系数

    if (isFirst)
    {
        for (int i = 0; i < sizeof(arr0) / sizeof(int); i++)
        {
            ListInsert(list, i, arr0[i], arr1[i]);
        }
    }
    else
    {
        for (int i = 0; i < sizeof(arr2) / sizeof(int); i++)
        {
            ListInsert(list, i, arr2[i], arr3[i]);
        }
    }

    return list;
}

/* 
    合并两个多项式(链表结构)
    一个节点中存储了某一项对应的指数和系数,只有指数相同的项才能进行相加减
    思路:
        首先，取出两个链表的首元节点，比较其指数
        如果指数相同，就将其系数进行相加，然后将结果插入到第三方的链表上(也可以直接将原有的节点直接添加到新的链表上)
        如果指数不相同，则取出其中指数较小的节点,结果插入到第三方的链表上。同时链表的指针位移
        当某一个链表已经到头后，直接将剩余节点插入到第三方链表中
 */
LinkedList MergeData(LinkedList list_1, LinkedList list_2)
{
    LinkedList list = malloc(sizeof(PNode));
    if ((list_1 == NULL || Length(list_1) == 0) && (list_2 == NULL || Length(list_2) == 0))
        return list;
    //取出两个链表的首元节点
    PNode *node_1 = list_1->next;
    PNode *node_2 = list_2->next;
    int len = 0;
    while (true)
    {
        if (node_1 == NULL) //链表1已经到头了,把链表2的剩余元素都插入到第三方链表里
        {
            len = Length(list);
            ListInsert(list, len, node_2->expn, node_2->codf);
            node_2 = node_2->next;
            if (node_2 == NULL)
                break;
        }
        else if (node_2 == NULL) //链表2已经到头了,把链表1的剩余节点插入到第三方中
        {
            len = Length(list);
            ListInsert(list, len, node_1->expn, node_1->codf);
            node_1 = node_1->next;
            if (node_1 == NULL)
                break;
        }
        else
        {
            //首先判断两个节点的指数是否相同
            if (node_1->expn < node_2->expn) //把小的指数插入到新的节点上
            {
                len = Length(list);
                ListInsert(list, len, node_1->expn, node_1->codf);
                node_1 = node_1->next;
            }
            else if (node_1->expn > node_2->expn)
            {
                len = Length(list);
                ListInsert(list, len, node_2->expn, node_2->codf);
                node_2 = node_2->next;
            }
            else //两个节点的指数相等
            {
                len = Length(list);
                int vale_codf = node_1->codf + node_2->codf;
                ListInsert(list, len, node_2->expn, vale_codf);
                node_1 = node_1->next;
                node_2 = node_2->next;
            }
        }
    }
    return list;
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
    PNode *tempNode = NULL;
    tempNode = l->next; //首先指向首元节点
    while (true)        //只有指针才可以做判NULL操作,对象是没法来判空的
    {
        printf("指针变量本身的地址 : %#X   当前节点所在的内存空间地址 : %#X  当前节点的索引 : %d  当前节点的指数 : %d  当前节点的系数 : %d \n", &tempNode, tempNode, i, tempNode->expn, tempNode->codf);
        tempNode = tempNode->next; //不断的取出下一个来
        if (tempNode == NULL)
            break;
        i++;
    }
}

//测试计算两个多项式
void testCalculate()
{
    printf("测试合并两个多项式(使用的链式存储结构)\n");
    LinkedList list_1 = prepareListData(true);
    printf("准备的数据1\n");
    PrintLinkedList(list_1);
    LinkedList list_2 = prepareListData(false);
    printf("准备的数据2\n");
    PrintLinkedList(list_2);
    LinkedList list = MergeData(list_1, list_2);
    printf("打印合并后的数据\n");
    PrintLinkedList(list);
}

int main()
{
    testCalculate();
    return 0;
}