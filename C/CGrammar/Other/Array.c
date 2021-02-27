//测试C语言中的数组
#include <stdio.h>
#include <string.h>

void modify(int arr[]);

void TestString();

int main()
{
    printf("Hello World!\n");
    int a = 10;
    printf("a++ : %d \n",a++);
    printf("++a : %d \n",++a);

    int arr [] ={10,11,23,45,67,56};
    printf("数组的首地址 : %#X , 元素值 : %d\n",arr , *arr);
    char str[] = "你好啊";

    char ss[] = "123456asdasdasdads";
    printf("ss[]长度 %d \n" ,strlen(ss)); 

    int array[] = {12,23,56,45,6,5,4,2,2,12,43,54};
    printf("函数外部修改前打印出来的数组array[0] : %d \n",array[0]);
    modify(array);//所谓的传递数组，实际上就是把数组的首地址传递进去了
    printf("函数外部修改后打印出来的数组array[0] : %d \n",array[0]);

    TestString();
    return 0;
}

//测试直接传数组，能否修改里面的元素
void modify(int arr[])
{
    //在函数内部获取到的数组长度实际上有误
    printf("在函数内部获取到的数组长度 : %d \n",sizeof(arr));
    if(sizeof(arr) >= 1)
    {
        arr[0] = 999;
        printf("函数内部打印出来的数组arr[0] : %d \n",arr[0]);
    }
}

void TestString()
{
    printf("\n\n\n测试字符串\n\n\n");
    char str[] = "http://c.biancheng.net";
    char *pstr = "Hello World!";
    int len = strlen(pstr);

    printf("打印字符串 pstr ");
    for(int i = 0 ; i < len ;i++)
    {
        printf("%c",*(pstr+i));
    }
    printf("\n");
    //使用pstr[i]
    printf("把字符串pstr当成数组了\n ");
    for(int i=0; i<len; i++){
        printf("%c", pstr[i]);
    }

    printf("\n");
    printf("把数组当成指针了\n ");
    int strLen = strlen(str);
    //使用*(str+i)
    for(int i=0; i<strLen; i++){
        printf("%c", *(str+i));
    }
    // printf("\n");
}