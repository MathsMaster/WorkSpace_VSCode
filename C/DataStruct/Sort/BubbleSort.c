#include <stdio.h>
#define MAXSIZE 10000 /* 用于要排序数组个数最大值，可根据需要修改 */
typedef struct
{
    int r[MAXSIZE + 1]; /* 用于存储要排序数组，r[0]用作哨兵或临时变量 */
    int length;         /* 用于记录顺序表的长度 */
} SqList;

void print(SqList L)
{
    int i;
    for (i = 1; i < L.length; i++)
        printf("%d,", L.r[i]);
    printf("%d", L.r[i]);
    printf("\n");
}

/* 交换L中数组r的下标为i和j的值 */
void swap(SqList *L,int i,int j) 
{ 
	int temp=L->r[i]; 
	L->r[i]=L->r[j]; 
	L->r[j]=temp; 
}

/**
 思路:
    将第0个元素依次与后面的元素相互比较,如果比后面的元素小，则相互交换位置
    如果比后面的元素大，则使用后面的元素，依次与后面的元素相互比较，直到最小的元素出现在顶部
 */
void BubbleSort(SqList *L)
{ 
	int i,j;
	for(i=1;i<L->length;i++)
	{
		for(j=L->length-1;j>=i;j--)  /* 注意j是从后往前循环 */
		{
			if(L->r[j]>L->r[j+1]) /* 若前者大于后者（注意这里与上一算法的差异）*/
			{
				 swap(L,j,j+1);/* 交换L->r[j]与L->r[j+1]的值 */
			}
		}
	}
}

int main()
{
    int d[5] = {5, 3, 4, 6, 2};
    SqList l;

    int i = 0;
    for (i = 0; i < 5; i++)
        l.r[i + 1] = d[i];//特地留下0号位置用来干啥
    l.length = 5;
    printf("排序前:\n");
    print(l);

    printf("冒泡排序:\n");
    BubbleSort(&l);
    print(l);
}