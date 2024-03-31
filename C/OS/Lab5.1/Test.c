/**
 * @file Test.c
 * @author your name (you@domain.com)
 * @brief 动态分区分配算法中的首次适应算法.
 *        首次适应算法: 将内存中的所有空闲分区块，以地址从低到高，按顺序链接起来。
 *          从头至尾进行搜索，直到找到一个足够大的空闲块，并从中切割一部分下来，剩余的部分继续留在空闲链表中.
 *         实现思路:
 *              1,使用两个链表,一个表示空闲分区块的链表,一个表示已分配的分区块的链表
 *         实现思路: 这里并没有考虑 m.size - u.size < size的情况
 *              1，先将申请的内存大小和整个空闲块链表中的最大块进行比较，如果过大，则失败
 *              2, 通过循环遍历空闲分区链,找到一个不小于所申请的大小的空闲块
 *                  1》如果申请的大小和空闲块链表中的最大块相等,则直接将该内存块从空闲链表中剥离出来,并且记录空闲最大块的数量减1
 *                  将对应的空闲内存块加入到已分配的链表的末尾
 *                  2》如果申请的大小和空闲块链表中的最大块要小，则截取部分空间，将对应的空闲链表中的节点参数进行修改,并且创建一个新的新的已分配的节点，加入已分配的链表
 *              3，修改记录空闲分区链中最大空闲块的数量和大小的参数（即head->size,maxblocknum）
 *
 *        首次适应算法的回收思路:
 *          1,因为空闲分区链是按照地址，从低到高排序的, 将待回收的内存块的节点插入到空闲分区链的对应位置
 *          2,通过地址来判断,是否和空闲分区链中的上下节点连续,如果连续的话就合并。同时更改空闲分区链中最大块的数量和大小的参数（head->size，maxblocknum）
 *          3，通过遍历,删除已分配的链表中的被回收的内存块的节点，并且修改已分配链表的长度参数(heads-->size)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 640

/**
 * @brief 定义分区内存块的结构体
 *
 * @return int
 */
struct node
{
    int address, size; //当前分区的起始地址和大小（首次适应算法中，是按照地址从低到高的方式排列分区块）
    struct node *next;
};

typedef struct node RECT;

/**
 * @brief 内存分配函数
 *
 * @return int
 */
RECT *assignment(RECT *head, int application);

/**
 * @brief 针对首次自适应算法的回收分区
 *
 * @return int
 */
void firstFit(RECT *head, RECT *heada, RECT *back1);

/**
 * @brief 最佳自适应算法的回收分区
 *
 * @param head
 * @param back1
 */
void bestFit(RECT *head, RECT *back1);

/**
 * @brief 合法性检查
 *
 * @return int
 */
int backcheck();

void print(RECT *head);

//分别表示链表的头....
RECT *head;  //空闲分区链表的头节点指针(不指向分区块)，其head->size 表示整个空闲分区链表中最大的空闲内存块的大小
RECT *heada; //已经分配的分区的链表的头节点的指针, 其heada->size 表示整个已分配的链表的内存块的数量
RECT *back;
RECT *assign1; //表示刚刚分配出来的内存块所对应的节点的指针
RECT *p;       //表示空闲分区链中的第一个元素节点

int application1; //表示所申请的分区空间大小
int maxblocknum;  //表示空闲分区链表中,最大的空闲内存块的数量(一般为1)
char way;         //用于定义分配方式: f 首先适应、最佳适应、最差适应等

int main()
{
    char choose; //表示当前是选择分配内存(a)，还是回收内存(r)
    int check;
    RECT *allocated;
    head = malloc(sizeof(RECT)); //这个难道是最开始的无意义的节点,不表示实际的内存
    p = malloc(sizeof(RECT));    //这才是空闲分区表的第一个节点
    head->size = MAX;            //这玩意表示整个空闲分区链表中最大的空闲内存块的大小
    head->address = 0;
    head->next = p;
    maxblocknum = 1; //表示空闲分区链中的，最大空闲块的数量（一般为1）

    p->size = MAX;
    p->address = 0; //从地址上就可以看出,这才是第一个空闲块
    p->next = NULL;
    print(head); //输出空闲分区表的初始状态

    heada = malloc(sizeof(RECT)); //已分配的分区的头节点的指针,不表示实际的内存
    heada->size = 0;
    heada->address = 0;
    heada->next = NULL;

    way = 'f'; //表示首次自适应算法
    do
    {
        printf("请输入'a'去分配内存,输入'r'去回收内存, 或者按下其他键退出.\n");
        scanf(" %c", &choose);      //选择分配或回收
        if (tolower(choose) == 'a') // a为分配
        {
            printf("输入申请的空间大小:\n");
            scanf("%d", &application1);               //输入申请空间大小
            assign1 = assignment(head, application1); //调用分配函数分配内存
            if (assign1->address == -1)               //分配不成功
                printf("申请的内存过大! 分配失败! \n\n");
            else //分配成功
                printf("分配成功! 分区块的地址是=%5d\n", assign1->address);
            printf("\n*********还未分配的空闲分区块*************\n");
            print(head); //输出
            printf("\n*********已经分配的空闲分区块***  **********\n");
            print(heada);
        }
        else if (tolower(choose) == 'r') //回收内存
        {
            back = malloc(sizeof(RECT));
            printf("输入回收的地址和内存块的大小 :\n");
            scanf("%d%d", &back->address, &back->size); //输入回收地址和大小
            check = backcheck(head, back);              //？？？？这里进行合法性的检查是为了啥
            if (check == 1)
            {
                printf("合法性检查通过....../n");
                printf("回收地址 : %d , 回收大小 : %d \n", back->address, back->size);
                if (tolower(way) == 'f')
                    firstFit(head, heada, back); //首先适应算法回收
                printf("\n*********还未分配的空闲分区块*************\n");
                print(head); //输出
                printf("\n*********已经分配的空闲分区块***  **********\n");
                print(heada);
            }
        }
    } while (tolower(choose) == 'a' || tolower(choose) == 'r');
    exit(0);
}

/**
 * @brief 首次适应算法的内存分配函数(核心代码)
 *         实现思路: 这里并没有考虑 m.size - u.size < size的情况
 *              1，先将申请的内存大小和整个空闲块链表中的最大块进行比较，如果过大，则失败
 *              2, 通过循环遍历空闲分区链,找到一个不小于所申请的大小的空闲块
 *                  1》如果申请的大小和空闲块链表中的最大块相等,则直接将该内存块从空闲链表中剥离出来,并且记录空闲最大块的数量减1
 *                  将对应的空闲内存块加入到已分配的链表的末尾
 *                  2》如果申请的大小和空闲块链表中的最大块要小，则截取部分空间，将对应的空闲链表中的节点参数进行修改,并且创建一个新的新的已分配的节点，加入已分配的链表
 *              3，修改记录空闲分区链中最大空闲块的数量和大小的参数（即head->size,maxblocknum）
 * @param head 空闲分区分配链表的头节点的指针(头指针并没有指向真正的空闲块)
 * @param application 所申请的内存大小
 * @return RECT*
 */
RECT *assignment(RECT *head, int application)
{
    RECT *before;                  //表示头节点（表示前一个节点）
    RECT *after;                   //表示当前待处理的节点(起名字也不知道好好起)
    RECT *assign;                  //表示申请的内存块的指针
    assign = malloc(sizeof(RECT)); //申请分配空间
    assign->size = application;
    assign->next = NULL;
    if (application > head->size || application < 0) // head->size表示整个空闲分区链表中的最大空闲块的大小, 申请的超过最大块的容量,就表示失败
    {
        assign->address = -1; //申请无效
    }
    else //
    {
        before = head;                    //这里表示的就是头节点
        after = head->next;               //这里就是第一个空闲分区的节点
        while (after->size < application) //遍历空闲分区的链表，直到找到一个不小于申请大小的空闲块
        {
            before = before->next;
            after = after->next;
        }

        if (after->size == application) //若当前的空闲分区节点大小等于申请大小则完全分配
        {
            if (after->size == head->size) //如果当前节点是空闲分区链中最大的空闲块，则要把数量减1
                maxblocknum--;
            before->next = after->next;       //断开当前节点的链接
            assign->address = after->address; //
            free(after);                      //回收空闲分区链中的当前节点的空间
        }
        else //若当前节点 > 所申请的空间大小，则截取部分空间进行分配
        {
            if (after->size == head->size) ////如果当前节点是空闲分区链中最大的空闲块，则要把数量减1
                maxblocknum--;
            after->size = after->size - application; //大于申请空间则截取相应大小分配
            assign->address = after->address + after->size;
        }
        //当空闲分区链表中，最大块的空闲块被分配完后
        if (maxblocknum == 0) //修改最大数和头节点
        {
            before = head;
            head->size = 0;
            maxblocknum = 1;
            //这一部分的作用是干啥，狗逼，竟然存在着这样的逻辑,幸亏爷功底深厚，不然还看不出里面藏了这样的逻辑啊
            //逻辑就是通过不断的循环遍历,找出空闲分区链表中的最大的内存块,并且使用maxblocknum来记录其数量
            // head作为头指针，指向了头节点，head->size则表示空闲分区链表中的最大的内存块的大小
            while (before != NULL)
            {
                if (before->size > head->size)
                {
                    head->size = before->size;
                    maxblocknum = 1;
                }
                else if (before->size == head->size) //第一次循环走这了
                {
                    maxblocknum++;
                }
                before = before->next;
            }
        }
    }

    assign1 = assign; //表示新分配出来的内存块的指针

    //修改已分配分区表，添加节点
    after = heada; //表示当前待处理的节点，这个指针就相当于java里面的引用
    while (after->next != NULL)
    {
        after = after->next; //不按照地址排序,直接挂在已分配的链表的最后面
    }
    after->next = assign; //这个已分配链表的排序竟然和地址顺序无关
    heada->size++;        //

    return assign1; //返回分配给用户到地址
}

/**
 * @brief 针对首次自适应算法的回收分区,不同的分配方案,还得使用不同的回收方案
 *         实现思路:
 *          1,因为空闲分区链是按照地址，从低到高排序的, 将待回收的内存块的节点插入到空闲分区链的对应位置
 *          2,通过地址来判断,是否和空闲分区链中的上下节点连续,如果连续的话就合并。同时更改空闲分区链中最大块的数量和大小的参数（head->size，maxblocknum）
 *          3，通过遍历,删除已分配的链表中的被回收的内存块的节点，并且修改已分配链表的长度参数(heads-->size)
 * @param head 表示空闲分区链表的头指针
 * @param heada 表示已分配的链表的头指针
 * @param back1 表示待回收的内存块
 * @return int
 */
void firstFit(RECT *head, RECT *heada, RECT *back1)
{
    RECT *after;  //表示空闲分区链表中当前节点的指针
    RECT *before; //表示空闲分区链表中前一个节点的指针
    RECT *back2;  //表示待回收的内存块的指针,在从已分配的链表中删除时,用到
    back2 = malloc(sizeof(RECT));
    back2->address = back1->address;
    back2->size = back1->size;
    back2->next = back1->next;
    before = head;
    after = head->next;
    int insert = 0;
    while (!insert) //将回收区插入空闲区链表中
    {
        //表示空闲分区链表中当前节点不为NULL,并且待回收块的地址 < 当前节点地址，并且 > 前一个节点的地址
        //因为空闲分区链表的节点地址，是由从低往高排序的
        if ((after == NULL) || ((back1->address <= after->address) && (back1->address >= before->address)))
        {
            before->next = back1;
            back1->next = after;
            insert = 1;
        }
        else
        {
            before = before->next;
            after = after->next;
        }
    }

    //通过判断back1->address == before->address + before->size是否在内存上连续, 将回收后的空闲块,与上一块进行合并
    if (back1->address == before->address + before->size)//before是back1空间的前面空闲块
    {
        before->size = before->size + back1->size;
        before->next = back1->next;
        free(back1);
        back1 = before;
    }

    //先判断地址在内存上是否连续 , 将回收后的空闲块,与下一块进行合并
    if ((after != NULL) && (after->address == back1->address + back1->size))//after是back1后面的空闲块
    {
        back1->size = back1->size + after->size;
        back1->next = after->next;//这里依旧有其他指针指向了after
        free(after);
    }
    //修改空闲分区块中，最大块的值和最大块个数，存放进行head->size和maxblocknum中
    if (head->size < back1->size)
    {
        head->size = back1->size;
        maxblocknum = 1;
    }
    else if (head->size == back1->size)
    {
        maxblocknum++;
    }

    //修改已分配链表，删除相应节点
    before = heada;
    after = heada->next;
    int del = 0;
    while (!del || after != NULL) //将回收区从已分配分区表中删除
    {
        if ((after->address == back2->address) && (after->size == back2->size))
        {
            before->next = after->next;
            after = NULL;
            free(after);
            del = 1;
        }
        else
        {
            before = before->next;
            after = after->next;
        }
    }
    heada->size--; //表示整个已分配的链表的节点个数
}

/**
 * @brief 最佳自适应算法的回收分区
 *
 * @param head
 * @param back1
 */
void bestFit(RECT *head, RECT *back1)
{
}

/**
 * @brief 检查回收块的合法性，back1为要回收到节点的指针
 *
 * @return int
 */
int backcheck(RECT *head, RECT *back1)
{
    int check = 1;
    if (back1->address < 0 || back1->size < 0)
        check = 0; //地址和大小不能为负数
    RECT *before;
    before = head->next;
    while ((before != NULL) && check) //地址不能和空闲区表中节点出现重叠
    {
        //从地址上判断，回收块的初始地址和结束地址,正好和空闲分区链里面的节点有重合的部分，所以不合法
        if (((back1->address < before->address) && (back1->address + back1->size > before->address)) || ((back1->address >= before->address) && (back1->address < before->address + before->size)))
        {
            check = 0;
        }
        else
        {
            before = before->next;
        }
    }

    if (check == 0)
        printf("合法性检查, 不合法!\n");
    return check;
}
/**
 * @brief 输出空闲分区链表里的每一个分区的信息
 *
 * @param output 空闲分区表的起始地址
 */
void print(RECT *output)
{
    RECT *current;
    int index;
    current = output->next; //第一个有意义的节点
    index = 0;
    if (output->next == NULL)
        printf("NO part for print!\n");
    else
    {
        printf("index ** address ** end *** size *** \n");
        while (current != NULL)
        {
            printf("------------------------------------\n");
            printf(" %-9d%- 9d%- 9d%- 9d\n", index, current->address, current->address + current->size - 1, current->size);
            printf("-------------------------------------\n");
            index++;
            current = current->next;
        }
    }
}
