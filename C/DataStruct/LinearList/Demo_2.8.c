/* 
    创建一个链式存储结构，用来实现对稀疏多项式的相加
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

PNode* GetElem(LinkedList list, int index)
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
    int len = 0;
    int arr[50];
    int arr0[] = {3, 5, 6, 8, 3, 23, 6, 45};
    int arr1[] = {9, 4, 5, 45, 234, 456, 657, 234, 456};
    int arr2[] = {1, 4, 6, 8, 10, 14, 17, 45, 45, 78};
    int arr3[] = {0, 8, 17, 23, 45, 48, 90};

    if (isFirst)
    {
        len = sizeof(arr0) / sizeof(int);
        memcpy(arr, arr0, len * sizeof(int));
    }
    else
    {
        len = sizeof(arr1) / sizeof(int);
        memcpy(arr, arr1, len * sizeof(int));
    }

    for (int i = 0; i < len; i++)
    {
        ListInsert(list, i, arr[i]);
    }
    return list;
}

int main()
{

    return 0;
}