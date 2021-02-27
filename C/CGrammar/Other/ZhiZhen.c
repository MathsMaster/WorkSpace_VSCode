#include <stdio.h>
#include <string.h>
#define Name "xulp" //定义常量（宏）

void main()
{
    //这样看的话，指针和变量很相似
    //指针  持有的地址   地址所指向的值
    //变量  持有的地址   地址所指向的值

    printf("My name is %s \n", Name);

    char a = 'V';//86

    char *p = &a; //取出a对应的地址,赋值给指针p(这里的指针就是地址，相当于Java中的引用)
    printf("修改之前的 a : %d \n", a);
    printf("修改之前的 *p : %d \n", *p); //这里的*p指的是取出指针p地址对应的值;(一个符号表示了两个不同的意思，果然设计之初就不严谨)
    printf("修改之前的p : %d \n", p);    //这里打印出来的就是指针P存放的地址
    printf("修改之前的&a : %d \n", &a);  //和P中的地址一样

    *p = 'c';//99 //这里是给指针p所指向的地址赋值

    printf("\n\n");
    printf("给*p赋值后...................... \n\n");

    printf("a : %d \n", a);
    printf("*p : %d \n", *p);
    printf("p : %d \n", p);   //这里打印出来的就是指针P存放的地址
    printf("&a : %d \n", &a); //和P中的地址一样

    char i = 'i';
    *p = i;
    printf("\n\n");
    printf("再次修改指针P的地址.............. \n\n");

    printf("a : %d \n", a);
    printf("*p : %d \n", *p);
    printf("p : %d \n", p);   //这里打印出来的就是指针P存放的地址
    printf("&a : %d \n", &a); //和P中的地址一样
}