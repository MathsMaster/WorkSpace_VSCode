# include <stdio.h>

/**
 * @file 2020_41_utils.h
 * @author xulp (you@domain.com)
 * @brief 用于计算传进来的函数的最小值
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

int calculate(int array1[], int array2[],int array3[],int len1,int len2,int len3,int result[])
{
    int minValue = 0;
    minValue = 100;
    for(int i = 0 ; i < len1;i++)
    {
        for(int j = 0 ; j < len2;j++)
        {
            for(int k = 0 ; k < len3;k++)
            {
                int v1 = array1[i] - array2[j] >= 0 ? array1[i] - array2[j] : array2[i] - array1[j];
                int v2 = array2[j] - array3[k] >= 0 ? array2[j] - array3[k] : array3[k] - array2[j];
                int v3 = array3[k] - array1[i] >= 0 ? array3[k] - array1[i] : array1[i] - array3[k];
                // int v1 = abs(array1[i] - array2[j]);
                // int v2 = abs(array2[j] - array3[k]);
                // int v3 = abs(array3[k] - array1[i]);
                if(v1 + v2+ v3 < minValue)
                {
                    printf("a : %d , b : %d , c : %d  minValue : %d \n",array1[i],array2[j],array3[k],minValue);
                    minValue = v1 + v2+ v3;
                    result[0] = array1[i];
                    result[1] = array2[j];
                    result[2] = array3[k];
                }
            }
        }
    }

    return minValue;

}
