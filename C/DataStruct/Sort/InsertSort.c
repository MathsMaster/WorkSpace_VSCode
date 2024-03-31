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


/* 
    思路:
        0号位不存放元素，仅用于暂存数据，无序数据从1号位开始存放。
        取第二个元素和第一个元素比较
        取第三个元素和第二个元素比较
        。。。。。。
        如果后一个元素小于前一个，则将其存放在0号位上暂存

        然后从当前元素的位置上，进行到序遍历，
        分别与0号位的元素相互比较，如果比0号位的元素更大，则都向后移一位
 */
void InsertSort(SqList *L)
{
    int i, j;
    for (i = 2; i <= L->length; i++)
    {
        if (L->r[i] < L->r[i - 1]) //比较当前元素和前一个元素的大小，如果小于的话，就用0号位来暂存
        {
            L->r[0] = L->r[i];//0号保存当前元素
            for (j = i - 1; L->r[j] > L->r[0]; j--)//从对应的元素位置，往前进行到序遍历
                L->r[j + 1] = L->r[j]; //凡是小于0号位置的元素，都后移一位
            L->r[j + 1] = L->r[0];     /* 然后将0号位的元素插入到正确位置 */
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

    printf("直接插入排序:\n");
    InsertSort(&l);
    print(l);
}
