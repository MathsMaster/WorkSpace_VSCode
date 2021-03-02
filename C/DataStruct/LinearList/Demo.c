/* 用于演示线性表一章中的各种数据结构 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinearList.h"
#include "SequentialLinearList.h"

void test_2_2_3_13();

/* 演示线性表 */
void testLinearList()
{
    SqlList_01 list;
    list.data = malloc(sizeof(int) * InitSize);
    printf("sizeof(int)*InitSize : %long \n", sizeof(int) * InitSize);
    printf("list.data 指针地址 : %#X \n", list.data);
}

/* 演示顺序线性表 */
void testSequentialLinearList()
{
    int arr[4] = {1, 2, 3, 4};
    printf("打印数组 arr : %#X \n", arr); //数组不管是否使用&,打印出来的都是数组首地址
    printf("打印数组 &arr : %#X \n", &arr);

    SeqList seqList; //结构体这里直接打印seqList，取出来的并不是内存地址
    printf("初始化前的结构体对象地址 seqList :  %#X \n", seqList);
    printf("初始化前的结构体对象地址 &seqList :  %#X \n", &seqList);

    InitList(&seqList); //这里和java不同，java可以直接传递对象进去，这里传递的结构体会被复制一份作为局部变量传递进去
    printf("初始化后的线性表的大小 : %d \n", seqList.length);

    char *bookNames[] = {"斗罗大陆", "鬼吹灯", "狂神", "让你爱的人爱上你", "亲昵关系", "雪鹰领主", "斗破苍穹", "猛龙过江", "拆弹专家1", "特种部队1", "特种部队2", "哪吒"};
    for (int i = 0; i < 12; i++)
    {
        ElemType element = {"123123123", bookNames[i], 12.3 + i * 2}; //指针和数组还没法直接相互赋值
        ListInsert(&seqList, i, &element);
    }

    //插入元素
    ElemType elem = {"123", "无限恐怖", 200.45};
    ListInsert(&seqList, 8, &elem);
    PrintList(&seqList);

    //根据值查找对应的元素
    int a = -1;
    LocateElem(&seqList, &elem, &a);
    printf("查找到的元素索引为 : %d \n", a);

    //删除对应的元素
    int i = 10;
    ElemType el;
    ListDelete(&seqList, i, &el);
    printf("删除的元素是 i : %d , name : %s \n", i, el.name);
    PrintList(&seqList);
}

int main()
{
    //线性表的演示
    printf("\n\n线性表的演示\n");
    testLinearList();

    //给顺序线性表增加各种函数
    printf("\n\n给顺序线性表增加各种函数\n");
    testSequentialLinearList();

    //求解2.2.3的第13题
    printf("\n\n求解2.2.3的第13题\n");
    test_2_2_3_13();

    return 0;
}

/* 
    构建一个2N的数组，将其中元素在其中拍好序；
    如果
 */
void lookMinInteger(int *arr, int len, int *a)
{
}

/* 
    根据传进来的数组，先找到其中最小正整数，和最大正整数，查找的时间复杂度 为o(n)
    根据最大正整数和最小整数之间的差值，建立一个数组；
    然后再将对应的正整数放置在数组中，根据数组中第一个空置的元素，来查找需要的最小正整数
    时间复杂度为o(n),空间复杂度则取决于数组中的最大正整数和最小正整数
 */
void lookMinInteger3(int *arr, int len, int *a)
{
}

/* 
    根据传进来的数组，找出其中未出现过的最小正整数
    思路 : 
        1,用1去与数组中每个数进行比较,看是否有与他相等的数;没有相等的数，就返回1;
            有的话,就自增1,再进行比较 ,直到找到没有与之相等的数。
        这种算法的时间复杂度为o(n^2),空间复杂度为o(n)
*/
void lookMinInteger2(int *arr, int len, int *a)
{
    int i = 1;   //用作查找的因子
    char isSame; //表示在当前一轮的查找中，是否存在相同的数值

    for (int b = 0; b < i; b++)
    {
        isSame = 0; //每一轮循环之前，都进行初始化
        for (int j = 0; j < len; j++)
        {
            if (i == arr[j])
            {
                isSame = 1; //表示这一次循环中，找到了相同元素
                break;
            }
        }

        if (isSame == 1) //表示这一次循环中，找到了相同元素;准备结束当前选择，开始下一轮查找
        {
            i++;
        }
        else //表示这一轮查找中，没有找到对应的值;用作查找的因子i就是等待返回的值
        {
            *a = i;
            break;
        }
    }
}

/* 
    用来测试2.2.3中的第13题
    描述 : 设计一个函数，根据传进来的数组，找出其中未出现过的最小正整数
 */
void test_2_2_3_13()
{
    int arr[] = {-1, 4, 6, -4, 6, 8, 9, 3, 67, 1, 2, 4, 4, 5, 7, 8, 21, 45, -43};
    int a = -1;
    lookMinInteger(arr, sizeof(arr) / sizeof(int), &a);
    printf("未曾出现过的最小正整数是 a : %d \n", a);
}
