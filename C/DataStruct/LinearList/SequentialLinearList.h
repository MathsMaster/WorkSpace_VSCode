//顺序线性表
#include <stdio.h>

#define OK 1
#define ERROR -1;
#define TRUE 1;
#define FALSE -1;

//定义线性表的结构体
#define MAXSIZE 50    //定义常量
typedef int ElemType; //给数据类型取别名
typedef int Status;   //给数据类型重命名

typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SeqList;

//定义线性表的初始化函数
Status InitList(SeqList *list)
{
    printf("正在初始化的SeqList的内存地址 ---->  %#X \n", list);
    list->length = 0;
    return OK;
}

//获取线性表的长度
int Length(SeqList list)
{
    return list.length;
}

/* 
    根据元素值查找索引,并返回对应的查找到的索引
*/
void LocateElem(SeqList *l, ElemType e, int *index)
{
    for(int i = 0 ; i < l->length;i++)
    {
        if(l->data[i] == e)
        {
            *index = i;
            break;
        }
    }
}

//根据元素的索引来查找
void GetElem(SeqList l, int i)
{
}

/*
    往线性表里插入元素，传进来线性表的指针l，索引i，元素e
    描述 : 插入之前先判断是否越界
        再判断是否插入到最后位置，是的话，就直接插入
        不是插入最后的位置，则要把后面元素往后移动一位
 */
Status ListInsert(SeqList *l, int i, ElemType e)
{
    if (i < 0 || i >= MAXSIZE || i > l->length)
        return ERROR;

    if (i == l->length) //元素直接插入队尾,无需移动其他元素
    {
        l->data[i] = e;
        l->length++;
    }
    else //否则就需要将所有元素后移一位（要考虑最后一位元素后移时越界的情况）
    {
        for (int j = l->length - 1; j >= i; j--)
        {
            l->data[j + 1] = l->data[j];
        }
        l->data[i] = e;
        l->length++;
    }
    return OK;
}

/* 
    根据索引来删除线性表中的元素，并且返回删除的值
    e就是用来返回对应的值的
    描述 : 删除之前先判断是否越界
        再判断是否删除的最后位置，是的话，就直接删除
        不是删除最后的位置，则要把后面元素往后移动一位
 */
Status ListDelete(SeqList *l, int i, ElemType *e)
{
    if (i < 0 || i >= MAXSIZE || i >= l->length)
        return ERROR;

    *e = l->data[i];
    if (i == l->length - 1) //删除的队尾元素,无需移动其他元素
    {
        l->length--;
    }
    else //待删除的元素在其他位置
    {
        for (int j = i; j < l->length; j++)
        {
            l->data[j] = l->data[j + 1];
        }
        l->length--;
    }
    return OK;
}

//打印线性表中的所有元素
void PrintList(SeqList *l)
{
    for (int i = 0; i < l->length; i++)
    {
        printf("元素索引位置 %d : %d \n", i, l->data[i]);
    }
}

//打印线性表中的所有元素
void printList(SeqList l)
{
    for (int i = 0; i < l.length; i++)
    {
        printf("元素索引位置 %d : %d \n", i, l.data[i]);
    }
}

//判断整个线性表是否为空表
Status Empty(SeqList l)
{
}

//销毁线性表,并释放线性表所占据的空间
void DestoryList(SeqList l)
{
}
