/* 
    图的邻接表存储形式
    一个数组，再加上数组的每个值都引出了一条链表;
    数组的每个值表示图的一个顶点;引出的链表表示该顶点连接到的其他顶点

    在有向图中，链表中存储的就是弧头的节点；逆邻接表中，链表存储的就是弧尾的节点；
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define INFINITY 65535

typedef int VerterType; //表示顶点数据对象
typedef int EdgeType;   //边上的权值对象

/* 
    用作链表的节点(又叫边表节点),用来表示当前节点连接的其他节点；
    在有向图中，链表中存储的就是弧头的节点；逆邻接表中，链表存储的就是弧尾的节点；
 */
typedef struct EdgeNode
{
    int adjVex;
    EdgeType wight;        //表示该条边(弧)的权值
    struct EdgeNode *next; //表示链表的下个节点的指针
} EdgeNode;

/* 
    表示顶点的节点，用来存放在数组中
 */
typedef struct
{
    VerterType data;
    EdgeNode *firstEdge; //数组中指向链表的首元节点的指针
} VertexNode;

/* 
    定义图的数据结构
 */
typedef struct Graph
{
    VertexNode adjList[MAXSIZE]; //表示各个顶点的数组
    int numVertexes, numEdge;    //表示图中的顶点数，和边数(在java里的话,不需要用这个来表示吧)
} Graph;

/* 
    创建图
 */
void createGraph(Graph *g)
{
    //给顶点表中的元素赋值
    for (int i = 0; i < g->numVertexes; i++)
    {
        g->adjList[i].data = i;
        g->adjList[i].firstEdge = NULL;
    }

    int j,k;
    //建立边表
    for (int i = 0; i < g->numEdge/2; i++)
    {
        srand(i);//有向图中,j表示弧头的节点在数组中的索引,k 表示弧尾部的顶点在数组中的索引
        j = rand() % g->numVertexes;
        srand(i - 10000); //更换播种
        k = rand() % g->numVertexes;

        //之所以创建两个节点，是因为在一次循环时,创建无向图时，A连接到B点时，B也连接到A了

        EdgeNode *node = malloc(sizeof(EdgeNode));
        //使用头插法的方式创建链表
        node->adjVex = j;//表示当前的链表节点在顶点表中的索引
        node->next = g->adjList[k].firstEdge;//初始时，这里肯定为NULL
        g->adjList[k].firstEdge = node;

        //如果是创建的有向图，则没有下面的部分了
        EdgeNode *node2 = malloc(sizeof(EdgeNode));
        node2->adjVex = k;//表示当前的链表节点在顶点表中的索引
        node2->next = g->adjList[j].firstEdge;//初始时，这里肯定为NULL
        g->adjList[j].firstEdge = node;
    }
}

int main()
{
    Graph *g = malloc(sizeof(Graph));
    createGraph(g);
}