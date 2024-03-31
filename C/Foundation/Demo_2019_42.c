/**
 * @file Demo_2019_42.c
 * @author 
 * @brief 创建一个循环队列
 * @version 0.1
 * @date 2021-11-05
 * 
 * @copyright Copyright (c) 2021
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "math.h"
#include "time.h"

typedef int ElemType;

//节点对象的结构体
typedef struct
{
    ElemType data;
    struct Node *next; //指向下个节点的指针
} Node;

//单链表的结构体
typedef struct
{
    Node *first; //指向队列的第一个元素,当链表中没元素时，指针就指向NULL了
} SingleLink;

//队列的结构体
typedef struct
{
    Node *first; //指向队列的第一个元素
    Node *end;   //指向队列的最后一个元素，当队列中没元素时，两指针就指向NULL了
} Queen;

//初始化队列
void initQueen(Queen *queen)
{
    if (queen == NULL)
        return;
    queen->first = NULL;
    queen->end = NULL;
}

//初始化单链表
void initLink(SingleLink *link)
{
    if (link == NULL)
        return;
    link->first = NULL;
}

//入队的操作
void enQueen(Queen *queen, ElemType e)
{
    if (queen == NULL)
        return;
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = e;
    node->next = NULL;

    if (queen->end == NULL && queen->first == NULL) //第一个添加进来的元素
    {
        queen->end = node;
        queen->first = node;
    }
    else
    {
        queen->end->next = node;
        queen->end = node;
        queen->end->next = queen->first;
    }
}

//出队的操作
Node *outQueen(Queen *queen)
{
    if (queen == NULL || queen->first == NULL)
        return NULL;
    Node *node = queen->first;
    if (queen->end == queen->first) //最后一个出队的元素
    {
        queen->end = NULL;
        queen->first = NULL;
    }
    else
    {
        queen->end->next = queen->first->next;
        queen->first->next = NULL;
        queen->first = queen->end->next;
    }
    return node;
}

//队列空了的标志
bool isQueenEmpty(Queen *queen)
{
    if (queen == NULL)
        return true;
    if (queen->first == NULL && queen->end == NULL)
        return true;
    return false;
}

//遍历队列的操作
void travseQueen(Queen *queen)
{
    if (queen == NULL || queen->first == NULL)
        return;
    Node *node = queen->first;
    int i = 0;
    while (node != NULL)
    {
        printf("队列中的元素 : %d \n", node->data);
        node = node->next;
        if (node == queen->first && i != 0)
            break;
        i++;
    }
}

//遍历队列的操作
void travseQueen2(Queen *queen)
{
    if (queen == NULL || queen->first == NULL)
        return;
    while (!isQueenEmpty(queen))
    {
        Node *node = outQueen(queen);
        printf("队列中的元素 : %d \n", node->data);
    }
}

int main()
{
    SingleLink link;
    initLink(&link);

    Queen queen;       //这里直接开辟出了空间
    initQueen(&queen); //对队列的头尾元素直接初始化为NULL

    enQueen(&queen, 1);
    enQueen(&queen, 20);
    enQueen(&queen, 3);
    enQueen(&queen, 5);
    enQueen(&queen, 7);
    enQueen(&queen, 12);
    enQueen(&queen, 1);
    enQueen(&queen, 11);

    // travseQueen(&queen);
    travseQueen2(&queen);
}