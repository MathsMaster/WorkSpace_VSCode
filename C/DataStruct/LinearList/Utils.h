#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "SingleLinkedList_copy.h"


LinkedList prepareListData(int i, bool isFirst)
{
    //先准备好两个顺序线性表及其相关数据
    LinkedList list = (LinkedList)malloc(sizeof(Node));
    InitList(list);
    int len = 0;
    int arr[50];
    int arr1[] = {1, 4, 6, 8, 10, 14, 17, 45, 45, 78};
    int arr1_1[] = {0, 1, 4, 8, 17, 23, 45, 48, 48, 90, 100, 110};
    //非递减的两个序列
    int arr2[] = {3, 3, 5, 6, 8, 23, 23, 45};
    int arr2_1[] = {1, 4, 4, 5, 7, 22, 23, 45, 234, 456, 657};

    int arr3[] = {3, 5, 6, 8, 23, 45};
    int arr3_1[] = {1, 4, 5, 7, 8, 23, 45, 234, 456, 657};

    int arr5[] = {-10, -8, -6, -1, 3, 5, 6, 8, 23, 45};

    int arr6[] = {-10, -8, -6, -1, 3, 5, 6, 8, 23, 45, 34};

    switch (i)
    {
    case 1:
        if (isFirst)
        {
            len = sizeof(arr1) / sizeof(int);
            memcpy(arr, arr1, len * sizeof(int));
        }
        else
        {
            len = sizeof(arr1_1) / sizeof(int);
            memcpy(arr, arr1_1, len * sizeof(int));
        }
        break;
    case 2:
        if (isFirst)
        {
            len = sizeof(arr2) / sizeof(int);
            memcpy(arr, arr2, len * sizeof(int));
        }
        else
        {
            len = sizeof(arr2_1) / sizeof(int);
            memcpy(arr, arr2_1, len * sizeof(int));
        }
        break;
    case 3:
        if (isFirst)
        {
            len = sizeof(arr3) / sizeof(int);
            memcpy(arr, arr3, len * sizeof(int));
        }
        else
        {
            len = sizeof(arr3_1) / sizeof(int);
            memcpy(arr, arr3_1, len * sizeof(int));
        }
        break;
    case 5:
        len = sizeof(arr5) / sizeof(int);
        memcpy(arr, arr5, len * sizeof(int));
        break;
    case 6:
        len = sizeof(arr6) / sizeof(int);
        memcpy(arr, arr6, len * sizeof(int));
        break;
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
