/* 
    演示数据结构C语言版2.7的代码实现
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "SingleLinkedList_copy.h"

LinkedList prepareListData(bool isOrder, bool isFirst)
{
    //先准备好两个顺序线性表及其相关数据
    LinkedList list = malloc(sizeof(Node));
    InitList(list);
    int len = 0;
    int arr[50];
    int arr0[] = {3, 5, 6, 8, 3, 23, 6, 45};
    int arr1[] = {9, 4, 5, 45, 234, 456, 657, 234, 456};
    int arr2[] = {1, 4, 6, 8, 10, 14, 17, 45, 45, 78};
    int arr3[] = {0, 8, 17, 23, 45, 48, 90};
    if (isOrder)
    {
        if (isFirst)
        {
            len = sizeof(arr2) / sizeof(int);
            memcpy(arr, arr2, len * sizeof(int));
        }
        else
        {
            len = sizeof(arr3) / sizeof(int);
            memcpy(arr, arr3, len * sizeof(int));
        }
    }
    else
    {
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
    }

    for (int i = 0; i < len; i++)
    {
        ListInsert(list, i, arr[i]);
    }
    return list;
}

/* 
    将线性表2中的数据插入到线性表1的后面去(直接往末尾插入)，不需要有序排列
    直接将线性表2中的节点取出来，判断是否在线性表1中存在相同的数据，如果不存在，就直接往表1的末尾插入节点
 */
LinkedList MergeDisorderData(LinkedList list_1, LinkedList list_2)
{
    if (list_2 == NULL && list_1 == NULL)
        return NULL;
    if (list_2 == NULL)
        return list_1;
    if (list_1 == NULL)
        return list_2;

    Node *node_2 = list_2->next; //先拿到线性表2的首元节点
    int index = 0;
    while (true)
    {
        if (node_2 != NULL)
        {
            ElemType value = node_2->data;
            if (!isExist(list_1, value))
            {
                index = Length(list_1);
                ListInsert(list_1, index, value);
            }
            node_2 = node_2->next;
        }
        else
        {
            break;
        }
    }
    return list_1;
}

/* 
    用来测试合并有序的线性表(链式结构)
    比较两个线性表中的元素后，往第三个表中进行插入，如果其中一个已经到头了，就直接将另一个都插入
    思路:
        使用两个指针，分别指向两个链表的首元节点
        取出两个节点的元素，比较大小后，将小的一方元素插入到第三方链表,同时链表的指针后移
        直到某一个指针已经指向了空节点了，将另一方的剩余节点元素都插入到第三方链表中
 */
LinkedList MergeOrderData(LinkedList list_1, LinkedList list_2)
{
    LinkedList list = malloc(sizeof(Node));
    if (list_2 == NULL && list_1 == NULL)
        return list;
    if (list_2 == NULL)
        return list_1;
    if (list_1 == NULL)
        return list_2;

    //创建两个指针
    Node *node_1 = list_1->next;
    Node *node_2 = list_2->next;

    while (true)
    {
        if (node_1 == NULL) //先判断线性表1或者表2是否到头了,将表2剩余数据全部插入第三方表
        {
            ElemType value = node_2->data;
            int index = Length(list);
            ListInsert(list, index, value);
            node_2 = node_2->next;
            if (node_2 == NULL)
                break;
        }
        else if (node_2 == NULL) //先判断线性表1或者表2是否到头了,将表1剩余数据全部插入第三方表
        {
            ElemType value = node_1->data;
            int index = Length(list);
            ListInsert(list, index, value);
            node_1 = node_1->next;
            if (node_1 == NULL)
                break;
        }
        else //没有到头的情况下，继续获取元素，比较大小，并插入第三方表
        {
            ElemType value = node_1->data < node_2->data ? node_1->data : node_2->data;
            if (node_1->data < node_2->data) //如果线性表1元素小,将其插入第三方链表
            {
                int index = Length(list);
                ListInsert(list, index, value);
                node_1 = node_1->next;
            }
            else //如果线性表2元素小
            {
                int index = Length(list);
                ListInsert(list, index, value);
                node_2 = node_2->next;
            }
        }
    }

    return list;
}

/* 
    测试合并无序表的数据,使用链表
 */
void testMergeDisorderData_LinkedList()
{
    printf("测试合并无序线性表(使用的链表)\n");
    LinkedList list_1 = prepareListData(false, true);
    printf("准备好的数据1\n");
    PrintLinkedList(list_1);
    LinkedList list_2 = prepareListData(false, false);
    printf("准备好的数据2\n");
    PrintLinkedList(list_2);
    //测试合并无序线性表的数据
    LinkedList list = MergeDisorderData(list_1, list_2);
    printf("合并后的数据\n");
    PrintLinkedList(list);
}

/* 
    测试合并有序表的数据,使用链表
 */
void testMergeOrderData_LinkedList()
{
    printf("测试合并有序线性表(使用的链表)\n");
    LinkedList list_1 = prepareListData(true, true);
    printf("准备好的数据1\n");
    PrintLinkedList(list_1);
    LinkedList list_2 = prepareListData(true, false);
    printf("准备好的数据2\n");
    PrintLinkedList(list_2);
    //测试合并有序线性表的数据
    LinkedList list = MergeOrderData(list_1, list_2);
    printf("合并后的数据\n");
    PrintLinkedList(list);
}

int main()
{
    //合并无序线性表
    // testMergeDisorderData_LinkedList();
    //合并有序线性表
    testMergeOrderData_LinkedList();
}
