#include <stdio.h>
#define mingzi 'v'
#define NAME "Xulp"
#define year 2021
#define month 02
#define day 23
int main(int argc, char const *argv[])
{
    /* code */
    int i,n,sum;
    for(i=0;i< 100;i++)
    {
        sum = sum + i;
    }
    printf("sum + %d \n",sum);
    printf("mingzi : %d \n",mingzi);
    printf("名字 : %s \n",NAME);
    printf("今日是 %d 年 %d 月 %d 日\n",year,month,day);

    for(int i = 0;i< 10;i++)
    {
        caculate(i);
    }

    return 0;

    
}

int caculate(int i)
{
    printf(" i : %d \n",i);
    return 0;
}