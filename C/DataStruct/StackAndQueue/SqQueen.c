/*
    顺序队列,队列和栈不同的是，栈都是在一头进行压入和删除。
    队列则是，一头用于删除，另一头用于压入。
    如果是顺序存储的队列，则会出现删除的元素过多的话，而后面压入的元素还在继续往压入，则会出现数组越界，但队列空间没用完的情况。
    为了循环利用空间，所以在数组中，一些队列尾部的元素，可能会出现对头元素的前面位置。

    判断队列是否满，或者空，以及是否空存在两种方法；
    一种是留一个空间。因为尾部索引都是指向了待插入的位置，当尾部索引+1再取模正好等于头部索引取模的值的话，就判断满了
                    因为头部元素，每次删除后，索引都会+1，如果头部元素的索引正好等于尾部索引(都是取模后的值)，则判断空了
    另一种就是使用一个专门的标志位，每次在插入或者删除时，就进行判断更新下标志位。
 */
#include <stdio.h>
#include <stdbool.h>

#define MAXSIZE 10

typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int head; //指向头的索引，最开始是指向元素的头部位置，但随着不断的删除。。。。
    int rear; //该索引一直指向了下一个待插入元素的位置(之所以指向下一个待插入元素的位置，有两个好处，1，方便取模，取出来的值就是数组中插入的位置2，方便取模后和头部元素位置进行比较)
} SqQueen;

/* 
    初始化队列,头部元素和尾部元素的索引都要归零
 */
bool initQueen(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        return false;
    sqQueen->head = 0;
    sqQueen->rear = 0;
    return true;
}

/* 
    清空队列
 */
bool clearQueen(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        return false;
    sqQueen->head = 0;
    sqQueen->rear = 0;
    return true;
}

/* 
    判断队列是否为空，使用第一种方法，留下一个专门的空间
    当尾部索引取模后，等于头部索引取模后的值，就为空
 */
bool queenEmpty(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        return true;
    if (sqQueen->head % MAXSIZE == sqQueen->rear % MAXSIZE)
        return true;
    return false;
}

/* 
    判断队列是否满了,发现这里满了和空了好像都不好判断
    使用第一种方法，当尾部索引+1取模后，等于头部索引取模后的值，就为满
 */
bool queenFull(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        return false;
    if (sqQueen->head % MAXSIZE == (sqQueen->rear + 1) % MAXSIZE)
        return true;
    return false;
}

/* 
    插入一个元素到队尾，有多种情况需要考虑
    队列没有满时，
        正常插入时，直接往当前尾部索引的位置插入，并且把尾部索引+1
        当数组的索引越界时，但因为删除了头部元素，导致还存在剩余空间时，就需要把尾部索引取模，取模的结果，就是元素待插入位置
    队列已满，不能再压入元素，
        判断队列是否满的标志，待插入位置取模后的值是否等于，头部元素的索引取模后的值
 */
bool enQueen(SqQueen *sqQueen, ElemType e)
{
    if (sqQueen == NULL)
        return false;
    if (queenFull(sqQueen)) //判断队列是否已满
        return false;
    sqQueen->data[sqQueen->rear % MAXSIZE] = e;
    sqQueen->rear++;
    return true;
}

/* 
    删除对列的头部元素，并返回值
    使用头部元素的索引取模后进行删除，删除时进行归零，删除后将头部元素的索引+1
 */
ElemType deQueen(SqQueen *sqQueen)
{
    if (sqQueen == NULL || queenEmpty(sqQueen))
        return -1;
    ElemType e = sqQueen->data[sqQueen->head % MAXSIZE];
    sqQueen->data[sqQueen->head % MAXSIZE] = 0; //java里的习惯
    sqQueen->head++;
    return e;
}

/* 
    获取队列的头部元素
 */
ElemType getHead(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        return -1;
    return sqQueen->data[sqQueen->head % MAXSIZE];
}

/* 
    获取队列长度
 */
int getQueenLength(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        return -1;
    return sqQueen->rear - sqQueen->head;
}

/* 
    从对头到队尾部，依次遍历元素
    尾部索引因为一直指向了待插入的位置,所以只需要<即可
 */
void traverseQueen(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        return;
    for (int i = sqQueen->head; i < sqQueen->rear; i++)
    {
        printf("当前打印的元素 data[%d] : %d \n", i, sqQueen->data[i%MAXSIZE]);
    }
}

int main()
{   

    printf("测试顺序队列的初始化....\n");
    SqQueen sqQueen;
    initQueen(&sqQueen);
    printf("初始化成功\n");

    printf("队列的长度 : %d \n",getQueenLength(&sqQueen));

    printf("测试顺序队列的插入数据....\n");
    for(int i = 0 ; i < 20;i++)
    {
        enQueen(&sqQueen,i*10);
    }
    printf("队列的长度 : %d \n",getQueenLength(&sqQueen));
    traverseQueen(&sqQueen);

    printf("测试顺序队列的出队....\n");
    ElemType e;
    for(int i = 0 ; i < 15;i++)
    {
        e = deQueen(&sqQueen);
        printf("出队的数据%d \n",e);
    }
    printf("队列的长度 : %d \n",getQueenLength(&sqQueen));
    traverseQueen(&sqQueen);

    printf("测试顺序队列的出队后入队....\n");
    for(int i = 0 ; i < 20;i++)
    {
        enQueen(&sqQueen,i*10);
    }
    printf("队列的长度 : %d \n",getQueenLength(&sqQueen));
    traverseQueen(&sqQueen);
}