/* 
    算法设计的第7题
    一个顺序存储的数组形式的队列
    只不过该队列的判空和判满和之前不同，这次不是以空一格的方式，而是用个标志位来判断
    思路:
        因为头部索引始终指向了头元素所在的位置，为尾部索引始终指向了待插入的位置。
        当插入后，每次都判断下尾部索引取模后，是否等于头部索引取模后的值；如果相等，就表示满了，否则就没满
        当删除后，每次都判断下头部索引取模后，是否等于尾部索引取模后的值；如果相等，就表示空了，否则就没空
 */
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAXSIZE 10

typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int head;   //指向头的索引，最开始是指向元素的头部位置，但随着不断的删除。。。。
    int rear;   //该索引一直指向了下一个待插入元素的位置(之所以指向下一个待插入元素的位置，有两个好处，1，方便取模，取出来的值就是数组中插入的位置2，方便取模后和头部元素位置进行比较)
    int isFull; //0表示空了，1表示满，2表示不空也不满
} SqQueen;

/* 
    初始化队列,头部元素和尾部元素的索引都要归零
 */
bool initQueen(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        exit(OVERFLOW);
    sqQueen->head = 0;
    sqQueen->rear = 0;
    return true;
}

/* 
    判断队列是否为空，使用第一种方法，留下一个专门的空间
    当尾部索引取模后，等于头部索引取模后的值，并且还需要依靠标志位来判断
 */
bool queenEmpty(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        exit(OVERFLOW);
    return sqQueen->isFull == 0;
}

bool queenFull(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        exit(OVERFLOW);
    return sqQueen->isFull == 1;
}

/* 
    插入一个元素到队尾
    插入前，判断是否满了，没有满才能继续插入，
        没有满时，直接往当前尾部索引的位置插入，并且把尾部索引+1
        当数组的索引越界时，但因为删除了头部元素，导致还存在剩余空间时，就需要把尾部索引取模，取模的结果，就是元素待插入位置
        在插入完成后，还需要判断当前头部索引取模后与尾部索引取摸后是否相等，
            如果相等就判断已经满了
            如果没有满的话，标志位要置为2
    如果已满，就直接返回
 */
bool enQueen(SqQueen *sqQueen, ElemType e)
{
    if (sqQueen == NULL)
        exit(OVERFLOW);
    if (queenFull(sqQueen)) //判断队列是否已满
        return false;
    sqQueen->data[sqQueen->rear % MAXSIZE] = e;
    sqQueen->rear++;
    if (sqQueen->rear % MAXSIZE == sqQueen->head % MAXSIZE)
        sqQueen->isFull = 1; //表示已满
    else
        sqQueen->isFull = 2; //表示不满也不空
    return true;
}

/* 
    删除对列的头部元素，并返回值
    使用头部元素的索引取模后进行删除，删除时进行归零，删除后将头部元素的索引+1
    并且删除完成后，还需要判断队列是否为NULL
 */
ElemType deQueen(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        exit(OVERFLOW);
    if (queenEmpty(sqQueen))
        return false;
    ElemType e = sqQueen->data[sqQueen->head % MAXSIZE];
    sqQueen->data[sqQueen->head % MAXSIZE] = 0; //java里的习惯
    sqQueen->head++;
    if (sqQueen->rear % MAXSIZE == sqQueen->head % MAXSIZE)
        sqQueen->isFull = 0; //表示已经空了
    else
        sqQueen->isFull = 2; //表示不满也不空
    return e;
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

/* 
    获取队列长度
 */
int getQueenLength(SqQueen *sqQueen)
{
    if (sqQueen == NULL)
        return -1;
    return sqQueen->rear - sqQueen->head;
}

int main()
{
    printf("测试顺序队列的初始化....\n");
    SqQueen sqQueen;
    initQueen(&sqQueen);
    printf("初始化成功\n");

    printf("队列的长度 : %d \n",getQueenLength(&sqQueen));

    printf("\n");

    printf("测试顺序队列的插入数据....\n");
    for(int i = 0 ; i < 20;i++)
    {
        enQueen(&sqQueen,i*10);
    }
    printf("队列的长度 : %d \n",getQueenLength(&sqQueen));
    traverseQueen(&sqQueen);

    printf("\n");

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