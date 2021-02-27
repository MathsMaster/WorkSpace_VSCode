#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    char str[] = "Hell World!";
    printf("sizeof字符串长度为 : %d \n", sizeof(str));
    printf("strlen字符串长度为 : %d \n", strlen(str));
    int a;
    printf("开始输入 \n");
    scanf("%d", &a);
    printf("输入的结果 a : %d \n", a);

    //拷贝字符串
    char str1[] = "第一窜字符串";
    char str2[] = "第2窜字符串";
    char str3[100];

    strcpy(str3,"这是复制进来的数据");
    strcpy(str1,str2);
    printf("输入的结果 st1 : %s \n", str1);
    printf("输入的结果 st2 : %s \n", str2);
    printf("输入的结果 st3 : %s \n", str3);
    return 0;
}
