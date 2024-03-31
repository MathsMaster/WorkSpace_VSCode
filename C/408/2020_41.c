#include <stdio.h>

#include "2020_41_utils.h"
/**
 * @brief 从三个数组中选择取出各自的值，然后经过函数的计算，计算出函数的最小值
 * 
 * @return int 
 */
int main()
{
    int array1[] = {-1,0,9};
    int array2[] = {-25,-10,10,11};
    int array3[] = {2,9,17,30,41};
    int result[3];
    int len1 = sizeof(array1)/sizeof(int);
    int len2 = sizeof(array2)/sizeof(int);
    int len3 = sizeof(array3)/sizeof(int);

    int minValue = calculate(array1,array2,array3,len1,len2,len3,result);

    printf("minValue : %d \n",minValue);
}

