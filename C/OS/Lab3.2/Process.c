/**
 * @brief 模拟进程的动态优先调度算法
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"
#define getpch(type) (type *)malloc(sizeof(type))

/**
 * @brief 定义进程控制块的结构体,并同时定义两个指针
 *
 */
struct pcb
{
    char name[10]; //进程名字
    char state;    //进程状态'W'表就绪,'R'表正在运行态
    int nice;      //进程的优先级
    int ntime;     //需要运行的时间
    int rtime;     //已经运行的时间
    struct pcb *link;
} *ready = NULL, *p; //该指针表示指向进程队列的队首

typedef struct pcb PCB; // C语言里为什么总是喜欢各种改名字

/**
 * @brief 获取到队列尾部元素
 *
 * @return PCB*
 */
PCB *getTail()
{
    PCB *pr = ready;
    PCB *tial = NULL;
    while (pr != NULL)
    {
        tial = pr;
        pr = pr->link;
    }
    return tial;
}

/**
 * @brief 判断元素是否存在队列中，存在就返回1，不存在就返回0
 *
 */
int isExist(PCB *p)
{
    PCB *pr = ready;
    while (pr != NULL)
    {
        if (p == pr)
            return 1;
        pr = pr->link;
    }
    return 0;
}

/**
 * @brief 进程优先级的排序函数,对传进来的进程对象进行排序,并生成就绪队列
 *        这个排序算法有问题啊，动不动就崩溃了
 *        这写书的人水平不行啊;
 *        这里要考虑两个重要问题,一个就是插入新的元素;一个是对旧的元素重新进行排序
 *
 * @return char
 */
void sort(PCB *p)
{
    int i = isExist(p); //判断是否存在
    //对新插入的元素进行排序
    if (i == 0) //表示不存在,是待新插入的元素
    {
        PCB *first = NULL, *second = NULL; //准备两个指针,用于指向链表的第一个，第二个元素
        PCB *tail = getTail();             //指向了队列尾部元素
        if (ready == NULL)                 //当队列是空的时候
        {
            p->link = ready;
            ready = p;
        }
        else if ((p->nice >= ready->nice)) //和队首元素比较,比队头优先级高就插入队头
        {
            p->link = ready;
            ready = p;
        }
        else if (p->nice <= tail->nice) //和队列尾部元素比较,比队尾优先级低,就插入队尾
        {
            tail->link = p;
            tail = p;
        }
        else //和队列的中间部分元素比较
        {
            first = ready;
            second = first->link;
            while (second == NULL)
            {
                if (p->nice > second->nice) //如果传进来的进程,优先级在first和second之间,可以进行插入
                {
                    p->link = second;
                    first->link = p;
                    break;
                }
                else //如果不在,就准备继续循环
                {
                    first = first->link;
                    second = second->link;
                }
            }
        }
    }
    else if (i == 1) //表示已经存在了，需要启动内部排列
    {
        //找到其中序列不对的那一个，如果存在的话，就扔出来进行排序
        PCB *previous = NULL;
        PCB *current = ready;
        PCB *next = current->link;
        while (next != NULL)
        {
            if (current->nice >= next->nice) //当前这个大于下一个表示正常
            {
                previous = current;
                current = next;
                next = next->link;
            }
            else
            {
                break;
            }
        }

        //当前队列中只存在一个元素,并且正是要传入的那个,那就直接返回
        if (previous == NULL && current == ready)
        {
            return;
        }
        else //当前队列中存在多个元素,进行切割后进行一次排列
        {
            previous->link = next;
            current->link = NULL;
            sort(current);
        }
    }
}

/**
 * @brief 输入各个进程参数，建立进程控制块,并排序生成就绪队列
 *
 * @return char
 */
char input()
{
    PCB *p = NULL;

    int i, num;
    printf("请输入进程数量: \n");
    scanf("%d", &num);
    for (i = 0; i < num; i++)
    {
        printf("进程号: %d \n", i);
        //同一个指针指向了多个不同的空间实体,就不怕搞出事吗
        p = getpch(PCB); //相当于 p = (PCB*)malloc(sizeof(PCB))
        printf("输入进程名称:\n");
        scanf("%s", p->name);
        printf("输入进程的优先级:\n");
        scanf("%d", &p->nice);
        printf("输入进程的运行时间(以秒为单位):\n");
        scanf("%d", &p->ntime);
        printf("\n");
        p->rtime = 0;   //已经运行的时间初始化
        p->state = 'W'; //创建时就为就绪态度
        p->link = NULL;
        sort(p); //对进程队列进行排序
    }
}

/**
 * @brief 进程撤销函数(进程运行结束,撤销进程),销毁占用空间
 *
 * @return char
 */
char destroy(PCB *p)
{
    printf(" 进程 [%s] 已经运行完成 \n", p->name);
    free(p);
}

/**
 * @brief 建立进程就绪函数(进程运行时间到,设置进程处于就绪状态)
 *
 * @return char
 */
char running(PCB *p)
{
    (p->rtime)++;
    if (p->rtime == p->ntime) //如果进程已经运行的时间，等于需要运行的时间，就准备销毁
    {
        destroy(p);
    }
    else
    {
        (p->nice)--;    //降低进程优先级
        p->state = 'W'; //进程状态切换成就绪态
        sort(p);        //重新往队列中进行排序
    }
}

/**
 * @brief 链表中节点个数的统计函数
 *
 * @return int
 */
int space()
{
    int l = 0;
    PCB *pr = ready;
    while (pr != NULL)
    {
        l++;
        pr = pr->link;
    }
    return l;
}

/**
 * @brief 进程显示函数,用于显示当前进程
 *
 * @param pr
 * @return char
 */
char disp(PCB *pr)
{
    printf("\n qname \t state \t nice \tndtime\truntime \n");
    printf("%s\t", pr->name);
    printf("%c\t", pr->state);
    printf("%d\t", pr->nice);
    printf("%d\t", pr->ntime);
    printf("%d\t", pr->rtime);
    printf("\n");
}

/**
 * @brief 进程查看函数
 *
 * @return char
 */
char check(PCB *p)
{
    PCB *pr;
    printf("\n  当前正在运行的进程是 : %s \n", p->name);
    disp(p);
    pr = ready;
    if (pr != NULL)
    {
        printf("\n当前就绪队列为 : ");
    }
    else
    {
        printf("\n当前就绪队列为 : 空 \n");
    }

    while (pr != NULL)
    {
        disp(pr);
        pr = pr->link;
    }
}

int main()
{
    int len, flag;
    input();       //进行输入,创建进程
    len = space(); //统计链表中的节点个数
    printf("\n 按0键继续......");
    while ((len != 0) && (ready != NULL))
    {
        scanf("%d", &flag);
        if (flag == 0)
        {
            p = ready;//把进程取出来,准备重新进行排序
            ready = p->link;
            p->link = NULL;
            p->state = 'R';
            check(p);
            running(p);
            printf("\n 按0键继续......");
        }
    }
    printf("\n\n 所有进程已经运行完成! \n");
    return 0;
}