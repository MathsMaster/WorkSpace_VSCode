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
} SqList;

//定义线性表的初始化函数
Status InitList()
{
    return OK;
}

//获取线性表的长度
int Length()
{
    return OK;
}

//根据元素值查找索引
void LocateElem(SqList l, ElemType e)
{
}

//根据元素的索引来查找
void GetElem(SqList l, int i)
{
}

//往线性表里插入元素，传进来线性表的指针l，索引i，元素e
Status ListInsert()
{
    // if (i > l->length || i < 0 || l->length >= MAXSIZE)
    // {
    //     return ERROR;
    // }

    // if (i == l->length) //元素直接插入队尾
    // {
    //     l->data[i] = e;
    //     l->length++;
    // }
    // else //否则就需要将所有元素后移一位（要考虑最后一位元素后移时越界的情况）
    // {
    //     for (int j = l->length - 1; j > i; j--)
    //     {
    //         l->data[j + 1] = l->data[j];
    //     }
    //     l->data[i] = e;
    //     l->length++;
    // }
    return OK;
}

//根据索引来删除线性表中的元素，并且返回删除的值
Status ListDelete(SqList l, int i, ElemType e)
{
}

//打印线性表中的所有元素
void PrintList(SqList *l)
{
    for (int i = 0; i < l->length; i++)
    {
        printf("元素索引位置 %d : %d \n", i, l->data[i]);
    }
}

//判断整个线性表是否为空表
Status Empty(SqList l)
{
}

//销毁线性表,并释放线性表所占据的空间
void DestoryList(SqList l)
{
}

//根据传进来的线性表，以及索引，取出对应的值返回
Status getElem(SqList l, int i, ElemType *e)
{
    // if (l.length == 0 || i >= l.length || i < 0)
    //     return ERROR;

    // *e = l.data[i]; //给指针所指向的地址赋值
    return OK;
}
