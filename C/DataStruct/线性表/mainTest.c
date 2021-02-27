#include <stdio.h>
#include "SequentialLinearList.h" //导入顺序线性表
#include "StaticLinkedList.h"     //导入静态链式线性表
#include "SingleLinkedList.h"     //导入单链式线性表
#include "DoubleLinkedList.h"     //导入双链式线性表
#include "CircularSingleLinkedList.h"//导入循环单链式线性表
#include "CircularDoubleLinkedList.h"//导入循环双链式线性表

int main()
{
    //测试顺序线性表
    SqList l;//C语言中就这样直接定义个结构体对象
    InitList(&l);//初始化
    ListInsert(&l,0,23445);
    PrintList(&l);//打印顺序线性表

    return 0;
}