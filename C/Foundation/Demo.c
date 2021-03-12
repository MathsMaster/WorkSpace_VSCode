#include <stdio.h>
#include <stdlib.h>
#include "Demo2.h"

#define PI 3.14

int calcuateArr(int arr[], int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += arr[i];
    }
    sum += (len / 2);
    printf("打印出来的数据是 : %d \n", sum);
    return sum;
}

int main()
{

    int arr1[] = {16, 18, 17, 28, 23, 15, 16};
    int arr2[] = {24, 33, 31, 36, 21, 13, 28, 14};
    int arr3[] = {24, 20, 35, 15, 21, 20, 10, 9, 13};
    int arr4[] = {9, 28, 19, 27, 22, 16, 9, 38, 11};
    int arr5[] = {16, 9, 20, 29, 43, 5, 41};
    int arr6[] = {39, 8, 20, 13, 11, 20, 22};
    int arr7[] = {13, 20, 17, 5, 15, 30, 24, 27, 11};
    int arr8[] = {10, 18, 13, 22, 7, 24, 21, 8, 7, 5, 5, 7, 38, 16, 9};
    int arr9[] = {5, 21, 19, 16, 18, 17, 26, 13, 3, 7};
    int arr10[] = {9, 13, 12, 43, 25, 20, 9, 28, 10, 26, 4, 20, 25, 3};
    int arr11[] = {8, 12, 6, 35, 12, 34, 14, 20, 26, 21, 15, 25, 3, 10, 10, 14, 1};
    int arr12[] = {36, 4, 30, 11, 10, 20, 14, 7, 24, 6, 23, 13, 9, 17, 14};
    int arr13[] = {48, 7, 11, 28, 13, 40, 36, 5, 66, 8, 1};
    int arr14[] = {11, 5, 10, 19, 38, 5, 14, 8, 14, 14, 12, 6, 16, 24, 7};
    int arr15[] = {17, 10, 9, 12, 16, 29, 5, 15, 16, 10, 14, 7, 3};
    int arr16[] = {12, 7, 23, 10, 24, 5, 14, 14, 27, 15, 6};

    int sum = 0;

    sum += calcuateArr(arr1, sizeof(arr1) / sizeof(int));
    sum += calcuateArr(arr2, sizeof(arr2) / sizeof(int));
    sum += calcuateArr(arr3, sizeof(arr3) / sizeof(int));
    sum += calcuateArr(arr4, sizeof(arr4) / sizeof(int));
    sum += calcuateArr(arr5, sizeof(arr5) / sizeof(int));
    sum += calcuateArr(arr6, sizeof(arr6) / sizeof(int));
    sum += calcuateArr(arr7, sizeof(arr7) / sizeof(int));
    sum += calcuateArr(arr8, sizeof(arr8) / sizeof(int));
    sum += calcuateArr(arr9, sizeof(arr9) / sizeof(int));
    sum += calcuateArr(arr10, sizeof(arr10) / sizeof(int));
    sum += calcuateArr(arr11, sizeof(arr11) / sizeof(int));
    sum += calcuateArr(arr12, sizeof(arr12) / sizeof(int));
    sum += calcuateArr(arr13, sizeof(arr13) / sizeof(int));
    sum += calcuateArr(arr14, sizeof(arr14) / sizeof(int));
    sum += calcuateArr(arr15, sizeof(arr15) / sizeof(int));
    sum += calcuateArr(arr16, sizeof(arr16) / sizeof(int));

    printf("总的时间时长为 %d分钟 \n约 %d小时\n约16天 \n 约平均时间时长为 %d \n", sum, sum / 60, sum / 16);

    // system("ls");//直接运行系统命令
    println();

    const int k = 20; //类似与Java中的final,没法修改(可以通过指针进行修改,不安全)

    printf("常量 const a : %d \n", k);
    printf("常量 PI  : %.2f \n", PI);

    char m = 'B';
    printf("B : %c \n", m);
    putchar('a');
    putchar('b');
    putchar('\n');

    // char c = getchar();
    // putchar(c);
    putchar('\n');
    printf("\n\n\n\n");

    // char d ;
    // scanf("%c",&d);
    // printf("scanf 输入 : %c ",d);

    int a = 10;
    int b = 20;
    printf("10 < 20 : %d \n", a < b);

    // a++;
    // ++a;
    printf("a : %d \n", a);

    // int c = a * a++;//先使用了a的值，再对a进行++
    int c = a * ++a; //先对a进行++,再使用了a的值
    printf("c : %d \n", c);
    return 0;
}