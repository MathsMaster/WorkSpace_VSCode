/* 演示C语言的头文件相关 */
#include <stdio.h>
#include "test.h"

int max();//这里很像Java中的接口啊

/* 测试C语言的头文件关键值extern */
void testExtern()
{
    int result = max();//这里使用的参数在编译时，会去查找对应的实现处
    printf("max() : %d \n",result);

    //也就是说，如果在变量定义之前要使用该变量，则应在使用之前加 extern 声明变量，使作用域扩展到从声明开始到本文件结束。
    extern int i; //在这里进行声明,等运行时，使用下面的赋值
    extern int y;

    printf("i : %d , y : %d \n", i, y);
}

int main()
{
    //15.1测试C语言的头文件关键值extern
    printf("\n\n15.1测试C语言的头文件关键值extern\n");
    testExtern();

    return 0;
}

int i = 100;
int y = 200;