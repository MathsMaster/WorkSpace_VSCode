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
    第一轮，从第0个元素开始，找到最小的元素，和第0个元素交换位置
    第二轮，从第1个元素开始，找到最小的元素，和第一个元素交换位置
    第二轮，从第2个元素开始，找到最小的元素，和第二个元素交换位置
    。。。。。
 */
void SelectSort(SqList *L)
{
	int i,j,min;
	for(i=1;i<L->length;i++)
	{ 
		min = i;						/* 将当前下标定义为最小值下标 */
		for (j = i+1;j<=L->length;j++)/* 循环之后的数据 */
        {
			if (L->r[min]>L->r[j])	/* 如果有小于当前最小值的关键字 */
                min = j;				/* 将此关键字的下标赋值给min */
        }
		if(i!=min)						/* 若min不等于i，说明找到最小值，交换 */
			swap(L,i,min);				/* 交换L->r[i]与L->r[min]的值 */
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

    printf("简单选择排序:\n");
    SelectSort(&l);
    print(l);
}