#include <stdio.h>
#include <stdlib.h>

void printTag(char *year, char *num);
//指针和数组经常能通用
void run2020_41(int arr1[], int arr2[], int arr3[], int len1, int len2, int len3);

int main()
{
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr2[] = {2, 3, 6, 8};
    int arr3[] = {-3, 5, 6, 8, 10};
    printf("arr1的首地址 %#x \n", arr1);
    printf("arr2的首地址 %#x \n", arr2);
    printf("arr3的首地址 %#x \n", arr3);
    printf("arr1的长度 %d \n", sizeof(arr1)); //这里获取的是数组长度
    printf("arr2的长度 %d \n", sizeof(arr2));
    printf("arr3的长度 %d \n", sizeof(arr3)); //这里这样获取的只是指针变量的长度
    run2020_41(arr1, arr2, arr3, sizeof(arr1) / sizeof(int), sizeof(arr2) / sizeof(int), 5);
}

void printTag(char *year, char *num)
{
    printf("==========================计算机408的%s的第%s题===========================\n", year, num);
}

/*
    对于输入的任意三个数组，找到每个数组中的一个值，使三个值的运算结果最小
*/
void run2020_41(int arr1[], int arr2[], int arr3[], int len1, int len2, int len3)
{
    printTag("2020", "41");

    printf("arr1的首地址 %#x \n", arr1);
    printf("arr2的首地址 %#x \n", arr2);
    printf("arr3的首地址 %#x \n", arr3);

    printf("Hello World!\n len : %d ",len1);

    int minValue = arr1[0] + arr2[0] + arr3[0];
    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            for (int k = 0; k < len3; k++)
            {
                int v1 = arr1[i] - arr2[j] > 0 ? arr1[i] - arr2[j] : arr2[i] - arr1[j];
                int v2 = arr2[j] - arr3[k] > 0 ? arr2[j] - arr3[k] : arr3[k] - arr2[j];
                int v3 = arr3[k] - arr1[i] > 0 ? arr3[k] - arr1[i] : arr1[i] - arr3[k];
                if (v1 + v2 + v3 < minValue)
                    minValue = v1 + v2 + v3;
            }
        }
    }
    printf("最小的距离是  %d \n", minValue);
}