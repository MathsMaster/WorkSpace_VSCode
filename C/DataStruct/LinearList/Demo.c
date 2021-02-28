/* 用于演示线性表一章中的各种数据结构 */
#include <stdio.h>
#include <stdlib.h>
#include "LinearList.h"


int main()
{
    printf("Hell\n");

    SqlList_01 list;
    list.data = malloc(sizeof(int)*InitSize);
    printf("sizeof(int)*InitSize : %d \n",sizeof(int)*InitSize); 
    printf("list.data 指针地址 : %#X \n",&list.data);

    return 0;

}