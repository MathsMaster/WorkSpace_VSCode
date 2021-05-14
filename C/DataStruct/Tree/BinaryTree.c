/* 
    演示二叉树
    因为二叉树，每个节点最多只能有两个子节点，所以可以用数组来实现，直接放在同一个数组中就行
    另一种方式就是直接使用链表来实现
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int treeIndex=1;
typedef char String[6]; /*  0号单元存放串的长度 */
String str;

typedef char TElemType;
/* 
    二叉树的顺序存储结构
    二叉树的顺序存储结构一般只使用于满二叉树和完全二叉树；其他二叉树使用的话，可能会导致空间的浪费
 */

/* 
    二叉树的链式存储结构(二叉链表),和孩子兄弟表示法类似
 */
typedef struct BinaryNode
{
    TElemType data;
    struct BiTNode *lChild, *rChild;
} BinaryNode, *Tree ,*BiTree,BiTNode;

/* 
    二叉树的前序遍历递归算法
    思路:
        当二叉树只有三个节点时，顺序为  根节点-->左子节点-->右子节点
        当遍历到左子节点时，发现下面还存在子节点时，依次  根节点(前左子节点)-->左子节点-->右子节点。。。。。。
 */
void preOrdertraverse(Tree tree)
{
    if (tree == NULL)
        return;
    //打印节点数据
    printf("前序遍历  当前节点数据 : %c \n", tree->data);
    //遍历左子节点
    preOrdertraverse(tree->lChild);
    //遍历右子节点
    preOrdertraverse(tree->rChild);
}

/* 
    二叉树的中序遍历算法
    思路:
        首先进来，就通过一路遍历左子树到到最下层的左子树上去
        首先找到二叉树的最下面一层的左子节点,顺序是 左子节点-->根节点-->右子节点
        当遍历了右子节点后，在上面一层的节点中又把
 */
void inOrdertraverse(Tree tree)
{
    if (tree == NULL)
        return;
    inOrdertraverse(tree->lChild); //遍历左子树
    //打印当前节点的数据
    printf("中序遍历  当前节点数据 : %c \n", tree->data);
    inOrdertraverse(tree->rChild); //遍历右子树
}

/* 
    二叉树的后序遍历算法
    思路:
        首先进来，就通过一路遍历左子树到到最下层的左子树上去
        首先找到二叉树的最下面一层的左子节点,顺序是 左子节点-->右子节点-->根节点
 */
void postOrdertraverse(Tree tree)
{
    if (tree == NULL)
        return;
    postOrdertraverse(tree->lChild); //遍历左子树
    postOrdertraverse(tree->rChild); //遍历右子树
    //打印当前节点的数据
    printf("后序遍历  当前节点数据 : %c \n", tree->data);
}

/* 
    使用键盘输入的方式，按照前序顺序来构造二叉树,
    这个创建二叉树的代码有问题
 */
void CreateBiTree(BiTree *T)//这里传进来的是个二级指针
{
    // if (i >= sizeof(str)/sizeof(char))
    //     return;
    // tree = malloc(sizeof(BinaryNode));
    // tree->data = str[i];
    // i++;
    // createTree(tree->lChild);
    // createTree(tree->rChild);
    if(treeIndex > 16)
        return;

	TElemType ch;
	
	scanf("%c",&ch);
	ch=str[treeIndex++];

	if(ch=='#') 
		*T=NULL;
	else
	{
		*T=(BiTree)malloc(sizeof(BiTNode));
		if(!*T)
			exit(OVERFLOW);
		(*T)->data=ch; /* 生成根结点 */
		CreateBiTree(&(*T)->lChild); /* 构造左子树 */
		CreateBiTree(&(*T)->rChild); /* 构造右子树 */
	}
}

int main()
{
    //测试创建二叉树
    // Tree tree = malloc(sizeof(BinaryNode)); //创建头指针所指向的内存空间
    BiTree T;
    CreateBiTree(&T);
    preOrdertraverse(T);
}