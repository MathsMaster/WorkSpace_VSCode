#include <stdio.h>

extern int i;
extern int y;

int max()
{
    return i > y ? i : y;//这边使用的参数，在编译时,会去其他文件查找赋值处
}