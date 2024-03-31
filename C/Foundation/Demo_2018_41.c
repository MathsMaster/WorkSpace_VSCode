#include <stdio.h>
/**
 * @brief 传进去一个int数组，找出其中没出现过的最小正整数
 * 思路:
 *      首先判断 1是否在数组中出现过
 *          没有出现的话，1就是所求的结果；
 *          如果1出现在数组中的话，就判断2是否在数组中,2没出现的话，就直接返回，2出现的话一次++，用3去判断，直到没有对应的数出现为止
 * 
 * @return int 
 */

int judgeExist(int i,int * arr,int len)//判断对应的值是否在数组中出现过
{
    for(int j = 0 ; j < len;j++)//遍历数组中的元素，判断是否在该值是否在代码中出现过
    {
        if(i == arr[j])
        {
            return 1;//出现过返回1
        }  
    }
    return 0;//未出现过返回0
}

int getResult(int * arr,int len)
{
    int n = sizeof(arr);//数组长度
    printf("n : %d \n",n);
    for(int i = 1 ; i <= len+1;i++)
    {
        int flag = judgeExist(i,arr,len);
        if(flag == 0)//表示不存在
            return i;
    }
}

int main()
{
    // int arr [] = {-1,-2,-3,-4,-5,-6,-7};
    // int arr[] = {4,7,9,10,4,6,3};
    // int arr [] = {1,2,3,4,5,6,7};
    int arr [] = {1,2,3,4, 6,7};
    int n = sizeof(arr)/sizeof(int);//数组长度
    printf("n : %d \n",n);
    
    int value = getResult(arr,n);
    printf("未出现过的最小值是 : %d \n",value);

}