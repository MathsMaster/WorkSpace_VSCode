/*  */
#include <stdio.h>

#define MaxSize 50

//一种定义顺序表的方式
typedef struct
{  
    int data[MaxSize];
    int length;

} SqlList;

#define InitSize 100
//另一种定义顺序表的方式
typedef struct
{
    int *data;
    int maxSize,length;
} SqlList_01;

