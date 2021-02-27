/*
    该Demo用来演示关于C语言中的指针的各种特性
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    返回较长的字符串
 */
char *getLongStr(char *str1, char *str2)
{
    if (strlen(str1) > strlen(str2))
    {
        return str1;
    }
    else
    {
        return str2;
    }
}

/* 
    返回函数中的一个局部变量对应的地址,也就是返回一个指针
 */
int *func()
{
    int n = 100;
    return &n;
}

/* 测试二级指针 */
void testSecondLevelPointer()
{
    int a = 100;
    int *p1 = &a;
    int **p2 = &p1;
    printf("a的地址 %#X , a的内容数据 %d \n", &a, a);
    printf("P1的地址 %#X, P1的内容 %#X , P1的内容所指向的数据 %d \n", &p1, p1, *p1);
    printf("P2的地址 %#X, P2的内容 %#X , P2的内容所指向的数据 %#X, P2的内容所指向的最终数据 %d\n", &p2, p2, *p2, **p2);
}

/* 测试NULL指针和void指针 */
void testNullVoidPointer()
{
    char *str = NULL;
    printf("str的地址 %#X, str的内容 %#X , str的内容所指向的数据 %#X \n", &str, str, *str);

    char *ss = (char *)malloc(sizeof(char) * 30);
    printf("ss的地址 %#X, ss的内容 %#X , ss的内容所指向的数据 %s \n", &ss, ss, *ss);
}

/* 测试数组和指针绝不等价,数组是另一种类型 */
void testArrayAndPointer()
{
    int arr[6] = {1, 2, 3, 4, 5, 6};
    int *p = arr;
    printf("数组arr的地址 : %#X \n", arr);
    printf("通过指针去取数组的元素 : %d,%d,%d,%d,%d,%d\n", *p, *p + 1, *p + 2, *p + 3, *p + 4, *p + 5, *p + 6);

    int len_arr = sizeof(arr) / sizeof(int);
    int len_p = sizeof(*p) / sizeof(int);
    printf("数据类型int 的长度 : %d , 指针类型 int*的长度 %d \n", sizeof(int),sizeof(int*));
    printf("数组arr的长度 : %d  , 指针的长度 %d \n", len_arr,len_p);
}

/* 测试数组和指针的转化
    当数组名作为数组定义的标识符（也就是定义或声明数组时）、sizeof 或 & 的操作数时，它才表示整个数组本身，
    在其他的表达式中，数组名会被转换为指向第 0 个元素的指针（地址）。
 */
void testArraySwitchPointer()
{
    int  arr[] = {0,1,2,3,4,5};
    int *p ;
    p = arr;//把数组首地址，赋值到指针的空间中
    printf("arr[] : %d\n",sizeof(arr));
    printf("p : %d\n",sizeof(p));
    for(int i = 0 ; i < sizeof(arr)/sizeof(int);i++)
    {
        printf("通过指针取数组元素 p[%d] : %d \n",i,p[i]);
    }

    for(int i = 0 ; i < sizeof(arr)/sizeof(int);i++)
    {
        printf("用指针换种方式取数组元素 p + %d : %d \n",i,*(p+i));
    }

    for(int i = 0 ; i < sizeof(arr)/sizeof(int);i++)
    {
        p = arr + i;
        printf("再换种方式取数组元素 p = arr + %d , *p : %d \n",i,*p);
    }

    printf("把数组首地址，赋值到指针的空间后 指针P的内容中的值 : %#X ,指针P所指向的空间的数据 %d\n",p,*p);
    *p = arr;//把数组的首地址 作为数据赋值到 指针P所指向的空间
    printf("把数组的首地址 作为数据赋值到 指针P所指向的空间后 指针P的内容中的值 : %#X ,指针P所指向的空间的数据 %#X\n",p,*p);
}

/* 用来测试指针数组，数组中存放的都是指针 */
void testPointerArray()
{
    int a = 18,b = 12,c = 10;
    //定义个指针数组，里面每个元素都是指针
    int *arr[] = {&a,&b,&c};
    //定义一个二级指针，用来指向指针数组的首地址
    int **p = &arr;//这样写，表示此时的arr是个数组，这是取出其首地址
    // int **p = arr;//这样写，表示此时的arr是个地址（指针）
    printf("指针数组中的三个元素 %#X , %#X ,%#X \n",arr[0],arr[1],arr[2]);
    printf("指针数组中的三个元素最终指向的值 %d , %d ,%d \n",*arr[0],*arr[1],*arr[2]);
    printf("用二级指针的方式取出指针数组中的三个元素最终指向的值 %d , %d ,%d \n",**(p+0),**(p+1),**(p+2));

    printf("\n\n");
    //指针数组和字符串数组结合使用  //指针数组ss中每个元素存放的都是字符串的首地址
    char *ss[] = {"zxcvb","Hello WOrld!","123456","qsxcadqwe"};
    printf("%s \n%s \n%s \n%s \n",ss[0],ss[1],ss[2],ss[3]);
    printf("打印字符串数组的首地址 %#X , %#X , %#X ,%#X \n",&ss[0],&ss[1],&ss[2],&ss[3]);
}

/* 测试二维数组的指针（指向二维数组的指针） */
void testTwoWeiArrayPointer()
{
    int arr[3][4] = { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} };
    int p = arr;

    printf("这里的p :    %#X \n",p);  
}

int main()
{    
    //9.8C语言指针作为函数的返回值
    printf("\n\n9.8C语言指针作为函数的返回值\n");
    char *str1 = "12345678";
    char *str2 = "1234";
    printf("较长的一个字符串是 %s\n ", getLongStr(str1, str2));

    //验证函数结束时，里面的数据被回收掉，指针依然指向以回收到的数据的异常
    printf("\n\n验证函数结束时，里面的数据被回收掉\n");
    int *p = func(); //这里的*p是指地址
    printf("立刻获取到的局部变量 n %d \n", *p);
    printf("Hello World!\n");
    int i = *p; //这里的*p是指相应的地址对应的元素值
    printf("稍后获取到的局部变量 n %d \n", i);

    //9.9测试指向指针的指针
    printf("\n\n9.9测试指向指针的指针\n");
    testSecondLevelPointer();

    //9.10测试null指针和Void指针
    // printf("\n\n9.10测试null指针和Void指针\n");
    // testNullVoidPointer();

    //9.11数组和指针绝不等价，数组是另外一种类型
    printf("\n\n9.11数组和指针绝不等价，数组是另外一种类型\n");
    testArrayAndPointer();


    //9.12数组到底在什么时候会转换为指针
    printf("\n\n9.12数组到底在什么时候会转换为指针\n");
    testArraySwitchPointer();

    //9.13指针数组
    printf("\n\n9.13指针数组，数组中存放的都是指针\n");
    testPointerArray();

    //9.15二维数组的指针（指向二维数组的指针）
    printf("\n\n9.15二维数组的指针（指向二维数组的指针）\n");
    testTwoWeiArrayPointer();



    return 0;
}
