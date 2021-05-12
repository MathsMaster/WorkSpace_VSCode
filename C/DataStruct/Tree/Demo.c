#include <stdio.h>
#include <string.h>

#define MAXSIZE 100

typedef int TElemType;
/*   
    使用双亲表示法来表示树的存储结构 ，相当于把所有节点平铺在同一层，然后用索引来确定当前节点的双亲所在位置
    表示树中的节点对象
 */
typedef struct
{
    int parent;     //表示在数组中，当前节点的双亲的位置
    TElemType data; //节点数据
} PNode;

typedef struct
{
    PNode nodes[MAXSIZE];
    int root; //根在数组中的索引
    int num;  //节点总数
} PTree;



/* 
    使用孩子表示法来表示树结构;
    和双亲表示法相同的是:把所有节点平铺在同一数组中,每个节点又使用一个链表指向自己的孩子节点;并且该链表是串联的，所有兄弟都是串联在一起
 */
typedef struct BoyNode //使用链表的方式来表示孩子节点
{
    int child;
    struct BoyNode *next; //指向兄弟节点
} * ChildPter;

typedef struct //一个头指针，指向了孩子节点的第一个
{
    ChildPter firstChild; //该指针指向了第一个孩子节点
} BoxNode;

typedef struct
{
    BoxNode nodes[MAXSIZE];//整棵树的所有节点都平铺在该数组
    int root;//根节点在数组中的索引
    int num;//总的节点树
} Tree;



/* 
    孩子兄弟表示法，通过链表的方式来表示整棵树;
    思路:
        每个节点都通过指针，指向自己的第一个孩子节点和右边的第一个兄弟节点
    可以在该节点中添加一个指向双亲节点的指针，就可以用来直接查找双亲
 */
typedef struct CTNode
{
    TElemType data;
    struct CTNode *firstChild,*rightSib;
}CTNode,*CTree;







void InitTree(Tree *tree);

void destroyTree(Tree *tree);

void createTree(Tree *tree);

void clearTree(Tree *tree);

void TreeEmpty(Tree *tree);

void TreeDepth(Tree *tree);

void TreeRoot(Tree *tree);

void Value(Tree *tree, int i);

void Assign(Tree *tree);

void Parent(Tree *tree);

void InsertChild(Tree *tree);

void DeleteChild(Tree *tree);

int main()
{
    printf("算法图解\n大话数据结构\n算法第四版\n数据结构和算法分析\n");
}