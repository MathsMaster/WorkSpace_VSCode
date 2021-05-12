/* 
    演示二叉树
 */
#include <stdio.h>
#include <string.h>

typedef int TElemType;
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
    struct BinaryNode *lChild, *rChild;
} Node, *Tree;


/* 
    二叉树的前序遍历递归算法
    思路:
        当二叉树只有三个节点时，顺序为  根节点-->左子节点-->右子节点
        当遍历到左子节点时，发现下面还存在子节点时，依次  根节点(前左子节点)-->左子节点-->右子节点。。。。。。
 */
void preOrdertraverse(Tree tree)
{
    if(tree == NULL)
        return;
    //打印节点数据
    printf("当前节点数据 : %d ",tree->data);    
    //遍历左子节点
    preOrdertraverse(tree->lChild);
    //遍历右子节点
    preOrdertraverse(tree->rChild);
}

/* 
    二叉树的中序遍历算法
    思路:
        首先就要进入到最下层去
        首先找到二叉树的最下面一层的左子节点,顺序是 左子节点-->根节点-->右子节点
        当遍历了右子节点后，在上面一层的节点中又把
 */
void inOrdertraverse(Tree tree)
{

}


int main()
{

}