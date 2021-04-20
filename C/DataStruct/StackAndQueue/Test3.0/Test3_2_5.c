/* 
    算法设计题第五题
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* 
    判断一系列的入栈和出栈操作是否有异常
    //1表示入栈，0表示出栈
    思路:
        首先判断入栈和出栈的操作数是否相等。
        其次判断每一个出栈位置，出栈的次数是否<=入栈的次数，否则就有问题
 */
bool judgeArrayOperate(int *array, int len)
{
    int rNum = 0, oNum = 0;
    for (int i = 0; i < len; i++)
    {
        if (*(array + i) == 0) //出栈
        {
            oNum++;
            if (oNum > rNum) //出栈的次数多了
                return false;
        }
        else if (*(array + i) == 1) //入栈
        {
            rNum++;
        }
    }
    if (rNum != oNum)
        return false;
    return true;
}

void test3_2_5()
{
    int ops[] = {1, 0, 1, 1, 0, 1, 0, 0}; //1表示入栈，0表示出栈
    bool isTrue = judgeArrayOperate(&ops, sizeof(ops) / sizeof(int));
    printf("操作序列是否存在问题: %d \n", isTrue);
}

int main()
{
    test3_2_5();
}