//单链式线性表
#include <stdio.h>

#define OK 1
#define ERROR -1;
#define TRUE 1;
#define FALSE -1;

typedef struct Book{
    char no[20];
    char *name;
    float price;
} ElemType;//给数据类型取别名
typedef int Status;   //给数据类型重命名

/* 定义单链表 */

