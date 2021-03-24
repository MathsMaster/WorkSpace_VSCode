/* 
    演示数据结构C语言版2.7的代码实现
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "SequentialLinearList.h"

SeqList prepareArrayData(bool isOrder, bool isFirst)
{
    //先准备好两个顺序线性表及其相关数据
    SeqList l;
    InitList(&l);
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
        ListInsert(&l, i, &arr[i]);
    }
    return l;
}

/* 
    将线性表2中的数据插入到线性表1的后面去(直接往末尾插入)，不需要有序排列
    以及在线性表1中存在的数据，就不再插入了
 */
SeqList MergeDisorderData(SeqList seqList_1, SeqList seqList_2)
{
    for (int i = 0; i < seqList_2.length; i++)
    {
        int value = getElem(&seqList_2, i);
        if (!isExist(&seqList_1, value))
            ListInsert(&seqList_1, seqList_1.length, &value);
    }
    return seqList_1;
}

/* 
    测试合并无序表的数据,使用顺序结构存储(数组)
 */
void testMergeDisorderData_Array()
{
    printf("测试合并无序表的数据,使用顺序结构存储(数组)\n");
    SeqList seqList_1 = prepareArrayData(false, true);
    printf("准备的数据1\n");
    PrintList(&seqList_1);
    SeqList seqList_2 = prepareArrayData(false, false);
    printf("准备的数据2\n");
    PrintList(&seqList_2);
    SeqList list = MergeDisorderData(seqList_1, seqList_2);
    printf("打印合并后的数据 表2往表1中插入不存在的元素\n");
    PrintList(&list);
}

/* 
    传进来两个有序线性表(从小到大排列，使用的顺序存储结构)，进行数据的合并
    将表2和表1的数据，按照从小到大的顺序排列
    思路:
        取出两个线性表的长度的值总和,作为循环的次数使用。创建一个新的线性表
        首次取出两个线性表的0索引元素比较大小,取出其中较小的元素插入新的线性表,并且其线性表的索引指向接下来的位置,
        继续比较。。。
        直到其中的一个线性表的指针长度到达末尾，然后直接将另一个线性表的剩余元素，直接插入到新的线性表中
 */
SeqList MergeOrderData(SeqList seqList_1, SeqList seqList_2)
{
    SeqList list;
    InitList(&list);
    if (isEmpty(seqList_2) && isEmpty(seqList_1))
        return list;
    if (isEmpty(seqList_2))
        return seqList_1;
    if (isEmpty(seqList_1))
        return seqList_2;
    int length = seqList_1.length + seqList_2.length;

    int index_1 = 0, index_2 = 0;
    for (int i = 0; i < length; i++)
    {
        ElemType value_1 = 0;
        ElemType value_2 = 0;
        if (index_1 >= Length(seqList_1)) //线性表1的所有元素已经全部都被插入了，接下来直接把线性表2的剩余元素给插入
        {
            value_2 = getElem(&seqList_2, index_2);
            ListInsert(&list, i, &value_2);
            index_2++;
            if (index_2 >= Length(seqList_2))
                break;
        }
        else if (index_2 >= Length(seqList_2)) //线性表2的所有元素已经全部都被插入了，接下来直接把线性表1的剩余元素给插入
        {
            value_1 = getElem(&seqList_1, index_1);
            ListInsert(&list, i, &value_1);
            index_1++;
            if (index_1 >= Length(seqList_1))
                break;
        }
        else
        {
            value_1 = getElem(&seqList_1, index_1);
            value_2 = getElem(&seqList_2, index_2);
            ListInsert(&list, i, value_1 < value_2 ? &value_1 : &value_2);
            if (value_1 < value_2) //判断大小用来确定将哪个线性表的索引自增
                index_1++;
            else
                index_2++;
        }
    }

    return list;
}

/* 
    测试合并有序表的数据,使用数组(顺序存储)
 */
void testMergeOrderData_Array()
{
    printf("测试合并有序数据，使用的顺序存储结构(s数组)\n");
    SeqList seqList_1 = prepareArrayData(true, true);
    printf("准备好的的有序数据1\n");
    PrintList(&seqList_1);
    SeqList seqList_2 = prepareArrayData(true, false);
    printf("准备好的的有序数据2\n");
    PrintList(&seqList_2);
    SeqList list = MergeOrderData(seqList_1, seqList_2);
    printf("打印合并后的数据 表1和表2的数据进行有序排列\n");
    PrintList(&list);
}

int main()
{
    // testMergeDisorderData_Array();
    testMergeOrderData_Array();
}
