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

void ShellSort(SqList *L)
{
    int i, j, k = 0;
    int increment = L->length;
    do
    {
        increment = increment / 3 + 1; /* 增量序列 */
        for (i = increment + 1; i <= L->length; i++)
        {
            if (L->r[i] < L->r[i - increment]) //这里是哪个和哪个比较
            {
                L->r[0] = L->r[i]; /*  暂存在L->r[0] */
                for (j = i - increment; j > 0 && L->r[0] < L->r[j]; j -= increment)
                    L->r[j + increment] = L->r[j]; /*  记录后移，查找插入位置 */
                L->r[j + increment] = L->r[0];     /*  插入 */
            }
        }
        printf("	第%d趟排序结果: ", ++k);
        print(*L);
    } while (increment > 1);
}

int main()
{
    int d[5] = {5, 3, 4, 6, 2};
    SqList l;

    int i = 0;
    for (i = 0; i < 5; i++)
        l.r[i + 1] = d[i]; //特地留下0号位置用来干啥
    l.length = 5;
    printf("排序前:\n");
    print(l);

    printf("希尔排序:\n");
    ShellSort(&l);
    print(l);
}