/* 
    算法设计题第九题
    递归算法
    竟然是阿克曼函数。。。。。搞不定了
    
 */
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

int ack(int m, int n)
{
    if (m == 0)
    {
        return n + 1;
    }
    else
    {
        if (n == 0)
        {
            return ack(m - 1, 1);
        }
        else
        {
            return ack(m - 1, ack(m, n - 1));
        }
    }
}

int main()
{
    printf("ack : %d \n", ack(4, 3));
}