/**
 * @file Test.c
 * @author
 * @brief 实现先进先出的页面置换算法 , 并且计算访问命中率

 *        我擦，理了快一天了，终于把这个思路逻辑给理清楚了
 *        需求: 一个进程有32个页面,模拟320条指令,每条指令都会涉及到随机的一个进程页面。
 *             主动设置内存中有几个可用内存块。分别模拟，在内存中只有4个可用内存块，24个可用内存块，32个可用内存块的情况下，
 *             执行320条指令时，内存和外存之间的调页情况。
 *        实现思路:
 *             1，一个数组表示总的进程页面  p1_type p1[total_vp]，表示有32个进程页面
 *             2，一个数组表示用户总的内存空间  pfc_type pfc[total_vp]，表示有32个内存块，但是可用的内存卡设置成只有4个/32个/24个
 *             3，一个数组表示320条指令  int a[total_instruction];
 *             4，一个链表表示用户内存中空闲内存块的链表 pfc_type *freepf_head
 *             5，一个链表表示用户内存中繁忙内存块的链表 pfc_type *busypf_head;
 *             6,一个数组page[total_instruction],长度为320，对应了320条指令，但是这数组中的值只有0～31，分别代表了进程对应32个页面号
 *
 * @version 0.1
 * @date 2022-05-04
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define INVALID -1
#define total_instruction 320 //总的指令数量
#define total_vp 32           //总的进程页面数量
#define clear_period 50

typedef struct //页面结构(和在内存，还是外存无关)
{
    int pn;      //对应进程中的页号
    int pfn;     //对应内存中的块号(pfn == INVALID表示在外存，否则当前进程页就在内存)
    int counter; //一个周期内访问页面的次数
    int time;    //访问时间
} p1_type;
p1_type p1[total_vp]; //表示总的进程页面

typedef struct pfc_struct //表示内存空间中的页面结构
{
    int pn;  //对应进程的页号
    int pfn; //对应的内存块号(pfn == INVALID表示在外存，否则当前进程页就在内存)
    struct pfc_struct *next;
} pfc_type;
pfc_type pfc[total_vp]; //表示总的内存空间(包含了忙的内存块，和空闲的内存块 , 还包括部分未使用的内存块)

pfc_type *freepf_head; //表示内存空间中空闲的内存块的指针
pfc_type *busypf_head; //表示内存空间中，忙的内存块的指针
pfc_type *busypf_tail; //忙内存页尾指针

int diseffect; //表示失效次数（即表示需要从外存进行调页的次数）

int a[total_instruction]; //表示随机生成的320条指令,值都在0～319之间
// page[i]:offset[j] 正好可以用来表示一条内存地址
int offset[total_instruction]; // offset[i]里的值都在0～9之间 , 这是想要模仿每个页面内的偏移地址（在这没实际意义）
int page[total_instruction];   // page[i]里的值都在0～31之间 , 这是想要模仿32个页面的索引

void initialize();
void FIFO();

int main()
{
    //随机生成320条指令, 值在0～319之间, 存储在a[i]中
    int s, i, j;
    srand(10 * getpid());
    s = (float)319 * rand() / 32767 / 32767 / 2 + 1;
    for (i = 0; i < total_instruction; i += 4) //循环80次
    {
        if (s < 0 || s > 319)
        {
            printf("当 i==%d, Error, s==%d 退出程序\n", i, s);
            exit(0);
        }
        a[i] = s;
        a[i + 1] = a[i] + 1;
        a[i + 2] = (float)a[i] * rand() / 32767 / 32767 / 2;
        a[i + 3] = a[i + 2] + 1;
        s = (float)(318 - a[i + 2]) * rand() / 32767 / 32767 / 2 + a[i + 2] + 2;
        if ((a[i + 2] > 318) || (s > 319))
            printf("a[%d+2]: %d , s==%d\n", i, a[i + 2], s);
    }
    //通过打印发现,数组a中所有数据都在0~319之间
    // for (int i = 0; i < total_instruction; i++)
    // {
    //     printf("打印随机生成的指令序列流: a[%d]:%d \n", i, a[i]);
    // }
    //指令序列变换为页面地址流
    for (i = 0; i < total_instruction; i++)
    {
        page[i] = a[i] / 10;   //这好像就是分页存储中的页面地址号
        offset[i] = a[i] % 10; //这又是每一页里面的偏移地址号
    }

    //通过打印发现,offset[i]里的值都在0～9之间,page[i]里的值都在0～31之间
    // for (int i = 0; i < total_instruction; i++)
    // {
    //     printf("打印页面地址: page[%d]:%d , offset[%d]:%d \n", i, page[i], i, offset[i]);
    // }

    //模拟内存中只有4个空闲页面时的调页动作
    printf("模拟内存中只有4个可用内存块时的调页动作......\n");
    FIFO(4);
    //模拟内存中只有24个空闲页面时的调页动作
    printf("模拟内存中只有24个可用内存块时的调页动作......\n");
    FIFO(24);
    //模拟内存中只有32个空闲页面时的调页动作
    printf("模拟内存中只有32个可用内存块时的调页动作......\n");
    FIFO(32);

    //这傻逼把这里给搞复杂了，就是模拟只有4个空闲页面的调页，和模拟只有32个空闲页面的调页之间的情况
    //用户工作区从4个页面到32个页面 ？？？？？ 这是啥意思
    // for (i = 4; i <= 32; i++)
    // {
    //     printf("%2d 页面", i);
    //     FIFO(i);
    //     printf("\n");
    // }
}

/**
 * @brief 进行初始化,将32个外存中的页面赋初值,将几个内存的空闲页面链接成表
 *
 * @param total_pf  忙内存块和空闲内存块的总的数量
 */
void initialize(int total_pf)
{
    int i;
    diseffect = 0; //表示在每一轮的调页中,调出外存的次数
    //给进程的32个页面赋初始值，初始时,默认所有进程页都在外存
    for (i = 0; i < total_vp; i++)
    {
        p1[i].pn = i;        //对应进程中的页号
        p1[i].pfn = INVALID; //对应内存中的块号(初始状态下 , p1[i].pfn = INVALID 默认就是表示在外存了)
        p1[i].counter = 0;   //一个周期内访问页面的次数
        p1[i].time = -1;     //访问时间
    }
    //给进程的4个页面赋初始值，初始时,默认这4个进程页在内存
    for (i = 0; i < 4; i++)
    {
        p1[i].pn = i;        //对应进程中的页号
        p1[i].pfn = i; //修改其中的4个进程页，默认初始是在内存之中
        p1[i].counter = 0;   //一个周期内访问页面的次数
        p1[i].time = -1;     //访问时间
    }

    // 表示内存空间空闲的内存块,依次链接成链表，这里每一轮调用时，都会重新链接成表
    //对用户内存空间中的页面赋初值 , 前后页面相连, 形成页表
    for (i = 0; i < total_pf - 1; i++) //依次使用4个空闲页面链接成页表...24个...32个
    {
        pfc[i].next = &pfc[i + 1];
        pfc[i].pfn = i;
    }
    pfc[total_pf - 1].next = NULL;
    pfc[total_pf - 1].pfn = total_pf - 1;
    freepf_head = &pfc[0]; //指向了用户的内存空间中的空闲页表的头部
}

/**
 * @brief 当前模拟的是只有几个可用内存块时的调页（可用内存块的数量:包含了空闲内存块 和 忙内存块）
 *
 * @param total_pf  忙内存块和空闲内存块的总的数量
 */
void FIFO(int total_pf)
{
    int i, j;
    //又用来从内存的繁忙链表中取值,将其从繁忙的内存页面里，调入到外存中
    pfc_type *p; //一个临时性的变量,既用来从内存的空闲链表中取值,将其变更成繁忙链表的一部分。
    initialize(total_pf);
    busypf_head = busypf_tail = NULL;
    // i表示1条指令，page[i] 表示该指令需要用到的进程页号
    for (i = 0; i < total_instruction; i++)
    {
        //表示执行到当前指令了，而当前指令需要用到 page[i]的进程页,并且该进程页还在外存,所以准备启动往内存调页的功能
        // page[i]的值在0～31之间，表示对应进程中的页号
        if (p1[page[i]].pfn == INVALID) //表示当前页面在外存，准备将其调入内存
        {
            diseffect += 1;          //每轮调用FIFO时,每一轮的失效次数，每一次初始化时，这里都会归零
            if (freepf_head == NULL) //当循环了多次后,内存里的空闲内存块已经用完后，这里就为NULL了
            {
                //表示将繁忙的内存页面, 调入到外存,进而腾出一个空闲内存块加入空闲链表
                p = busypf_head->next;
                p1[busypf_head->pn].pfn = INVALID; //表示调往外存了
                freepf_head = busypf_head;         //释放忙页面的第一个页面,使其进入到内存的空闲链表
                freepf_head->next = NULL;
                busypf_head = p;
            }
            //进行调入内存的操作，需要消耗掉一个空闲内存块
            //将freepf_head指向的链表的第一个节点给断开 , 准备处理这断开的第一个节点
            p = freepf_head->next; //按FIFO方式调入新页面到内存页面
            freepf_head->next = NULL;
            //处理这断开的空闲链表的第一个节点
            freepf_head->pn = page[i];          //将进程的页号赋值
            p1[page[i]].pfn = freepf_head->pfn; //更改对应的内存块号,这一步相当于在执行调入内存的操作 p1[page[i]].pfn != -1 表示当前进程页在内存中
            //将刚才的内存中空闲页面链表的节点，加入到内存的繁忙页面节点的链表里去
            if (busypf_tail == NULL)
                busypf_head = busypf_tail = freepf_head;
            else
            {
                busypf_tail->next = freepf_head; //空闲页面减少一个，加入到繁忙页面链表
                busypf_tail = freepf_head;
            }
            freepf_head = p;
        }
    }
    printf("总的可用内存块数量 %d 时, FIFO访问命中率 :%6.4f \n\n", total_pf, 1 - (float)diseffect / 320);
}