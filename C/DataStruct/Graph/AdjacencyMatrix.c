/* 
    使用邻接矩阵的方式来表示图
    一个矩阵存储所有的边，行表示边的尾，列表示边的头;该点如array[1][2] = 1就表示1号节点指向2号节点的边，存在
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define INFINITY 65535

typedef int VerterType; //表示顶点数据对象
typedef int EdgeType;   //边上的权值对象

/* 
    对于有向图来说，二维数组的第一个索引表示边(弧)的尾，第二个索引表示边(弧)的头
 */
typedef struct
{
    VerterType vexs[MAXSIZE];       //用来存放有多少个顶点的顶点表,如果是在java里的话，是先知道了有多少个顶点，然后才去开辟的空间
    EdgeType arc[MAXSIZE][MAXSIZE]; //一个二维数组作为矩阵,矩阵的行和边对应着图的弧
    int numVertexes, numEdges;      //表示有多少个顶点，多少个边
} MGraph;

/* 
    使用邻接矩阵创建一个无向图
    如果传进来的边数比顶点数所构建的最大边数 n*(n-1)/2还大，则需要进行判断
 */
void createMGraph(MGraph *g, int numVertexes, int numEdges)
{
    for (int i = 0; i < numVertexes; i++) //先建立一维的顶点表
    {
        g->vexs[i] = i;
    }

    for (int i = 0; i < numVertexes; i++) //再建立二维的邻接矩阵
    {
        for (int j = 0; j < numVertexes; j++)
        {
            g->arc[i][j] = INFINITY; //进行矩阵的初始化
        }
    }

    int maxEdgeNum = numVertexes * (numVertexes - 1) / 2; //由顶点所能构成的最大边数量
    if (numEdges > maxEdgeNum)
        numEdges = maxEdgeNum;
    int colmIndex, rowIndex;
    for (int i = 0; i < numEdges; i++) //开始对邻接矩阵中对应的边开始赋值
    {
        //利用随机数,随机生成对应的行和列的索引值
        srand(i);
        colmIndex = rand() % numVertexes;
        srand(i - 10000); //更换播种
        rowIndex = rand() % numVertexes;
        g->arc[colmIndex][rowIndex] = i % 2;//这里的权值暂时只有0和1
    }
}

int main()
{
    MGraph *g = malloc(sizeof(MGraph));
    createMGraph(g, 20, 10); //创建20个顶点，10条边
}