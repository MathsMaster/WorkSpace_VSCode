#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef char String[MAXSIZE + 1];

/* 通过计算返回子串T的next数组。 */
// void get_next(String T, int *next) 
// {
// 	int i,k;
//   	i=1;
//   	k=0;
//   	next[1]=0;
//   	while (i<T[0])  /* 此处T[0]表示串T的长度 */
//  	{
//     	if(k==0 || T[i]== T[k])                                                                                                                         
// 		{
//       		++i;  
// 			++k;  
// 			next[i] = k;
//     	} 
// 		else 
// 			k= next[k];	/* 若字符不相同，则k值回溯 */
//   	}
// }

/* 通过计算返回子串T的next数组。 */
void get_next(String T, int next[])
{
    int j = 0, k = -1;
    next[0] = -1;
    int len = strlen(T);
    while (j < len - 1)
    {
        if (k == -1 || T[j] == T[k])
        {
            j++;
            k++;
            next[j] = k;
        }
        else
            k = next[k]; //此语句是这段代码最反人类的地方，如果你一下子就能看懂，那么请允许我称呼你一声大神！
    }
}


int main()
{

    String ss = "abcdabd";
    int next[255];
    get_next(ss, next);
    for (int i = 0; i < strlen(ss); i++)
    {
        printf("arr[%d] : %d \n", i, next[i]);
    }
    // char * ss = "Hello World!";
    // printf("获取到的数据 : %s \n",ss +3);
    // char sss[] = {'q','a','s','d','c','s','d'};
    // printf("获取到的数据 : %s \n",sss);
}