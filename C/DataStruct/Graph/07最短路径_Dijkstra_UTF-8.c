#include "stdio.h"    
#include "stdlib.h"   
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 20
#define MAXVEX 20
#define GRAPH_INFINITY 65535

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 


typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

typedef int Patharc[MAXVEX];    /* 用于存储最短路径下标的数组 */
typedef int ShortPathTable[MAXVEX];/* 用于存储到各点最短路径的权值和 */

/* 创建图 */
void CreateMGraph(MGraph *G)
{
	int i, j;

	//边数为9，顶点数为5
	G->numEdges=9;
	G->numVertexes=5;
	
	/* 顶点数组赋值 */
	G->vexs[0]=1;
	G->vexs[1]=2;
	G->vexs[2]=3;
	G->vexs[3]=4;
	G->vexs[4]=5;

	//初始化边
	for (i = 0; i < G->numVertexes; i++)
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			if (i==j)
				G->arc[i][j]=0;//对角线直接赋值0
			else
				G->arc[i][j] = G->arc[j][i] = GRAPH_INFINITY;//邻接矩阵里的，所有的点的权值都设为无限远，表示不可达到
		}
	}

	//G->vexs[i] = {1,2,3,4,5},
	//顶点1指向点2,3,5
	G->arc[0][1]=26;
	G->arc[0][2]=3;
	G->arc[0][4]=6;

	//顶点2没有指向的点

	//顶点3指向2
	G->arc[2][1]=22; 
	//顶点4指向2,3 
	G->arc[3][1]=1; 
	G->arc[3][2]=6; 
	//顶点5指向2，3，4
	G->arc[4][1]=15;
	G->arc[4][2]=6;
	G->arc[4][3]=8; 

}

/*  Dijkstra算法，求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v] */    
/*  P[v]的值为前驱顶点下标,D[v]表示v0到v的最短路径长度和 */  
/**
 * @brief 算法的思路是:传进来一个图,一个起始顶点的索引,一个数组D用于记录该点到各个顶点的最短距离，一个数组P用于记录到哪些顶点存在最短距离（也就是顶点可到）
 * 
 * @param G 
 * @param startNodeIndex 表示开始的顶点在顶点数组中的索引，计算开始顶点到某个顶点的最短路径
 * @param P 
 * @param D 用于记录当前顶点到对应顶点的最短路径之和
 * 顶点数组 [1,2,3,4,5]
*  邻接矩阵 「0 ,26,3 ,0 ,6
 * 			0 ,0 ,0 ,0 ,0
 * 			0 ,22,0 ,0 ,0
 * 			0 ,1 ,6 ,0 ,0
 * 			0 ,15,6 ,8 ,0」
 */
void ShortestPath_Dijkstra(MGraph G, int startNodeIndex, Patharc *P, ShortPathTable *D)
{    
	int index;//表示数组索引
	int w;
	int k;
	int min;    
	int final[MAXVEX];/* final[w]=1 表示求得起始点startNodeIndex至vw的最短路径 */
	for(index=0; index<G.numVertexes; index++)    /* 初始化数据 */
	{        
		final[index] = 0;			/* 表示起始点startNodeIndex到其他点的最短距离都没求出来 */
		/* 使用各条边的权值给ShortPathTable数组中的元素赋值，作为该点到各个点的初始最短路径 */
		(*D)[index] = G.arc[startNodeIndex][index];
		(*P)[index] = -1;				/* 初始化路径数组P为-1  */       
	}

	(*D)[startNodeIndex] = 0;  /* v0至v0路径为0 */
	final[startNodeIndex] = 1;    /* v0至v0不需要求路径,不需要求路径的话，应该标记为0才对啊 */        
	/* 开始主循环，每次求得起始顶点到某个v顶点的最短路径 */   
	for(index=1; index<G.numVertexes; index++)//循环一次，表示求出了起始点到一个点的最短距离
	{
		min=GRAPH_INFINITY;    /* 当前所知离v0顶点的最近距离 */        
		for(w=0; w<G.numVertexes; w++) /* 寻找离v0最近的顶点 */    
		{            
			if(!final[w] && (*D)[w]<min)             
			{                   
				k=w;                    
				min = (*D)[w];    /* w顶点离v0顶点更近 */            
			}        
		}        
		final[k] = 1;    /* 将目前找到的最近的顶点置为1 */
		for(w=0; w<G.numVertexes; w++) /* 修正当前最短路径及距离 */
		{
			/* 如果经过v顶点的路径比现在这条路径的长度短的话 */
			if(!final[w] && (min+G.arc[k][w]<(*D)[w]))   
			{ /*  说明找到了更短的路径，修改D[w]和P[w] */
				(*D)[w] = min + G.arc[k][w];  /* 修改当前路径长度 */               
				(*P)[w]=k;        
			}       
		}   
	}
}

int main(void)
{
	int i,j,v0;
	MGraph G;
	Patharc P;
	ShortPathTable D; /* 求某点到其余各点的最短路径，因为从起始点，到各个点的最短距离不一样，所以需要使用数组进行存储 */   
	v0=0;
	
	CreateMGraph(&G);
	
	ShortestPath_Dijkstra(G, v0, &P, &D);  

	printf("最短路径倒序如下:\n");    
	for(i=1;i<G.numVertexes;++i)   
	{       
		printf("v%d - v%d : ",v0,i);
		j=i;
		while(P[j]!=-1)
		{
			printf("%d ",P[j]);
			j=P[j];
		}
		printf("\n");
	}    
	printf("\n源点到各顶点的最短路径长度为:\n");  
	for(i=1;i<G.numVertexes;++i)        
		printf("v%d - v%d : %d \n",G.vexs[0],G.vexs[i],D[i]);     
	return 0;
}