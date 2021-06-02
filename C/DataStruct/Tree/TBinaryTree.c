/* 
    线索二叉树
    线索二叉树的原理是，二叉树的每个节点都具有指向左子树节点的指针，和指向右子树的节点指针；
    当二叉树的某个节点的左指针或者右指针不存在时，就会造成浪费。
    如果能够让该为NULL的左指针，或右指针指向在中序遍历时的，前驱节点，或者是后继节点。
    
    这就相当于将节点的链表变成了双向链表。
 */
#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    Link,
    Thread
} PointerTag; //用来标示该指针，是指向了自己的子节点，还是指向了遍历时的前驱或者后继节点

typedef int TElemType;

/* 
    定义线索二叉树的节点对象
 */
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lChild, *rChild; //分别指向左子树和右子树的指针(也是用来指向前驱节点和后继节点)
    PointerTag lTag;                   //表示左指针是指向了前驱节点，还是 左子节点
    PointerTag rTag;                   //表示右指针是指向了后继节点，还是 右子节点
} BiThrNode, *BiThrTree;

BiThrNode *pre; //一个成员变量，用来指向前驱节点
/* 
    对一棵二叉树进行线索化，就是将二叉树中的空指针全找出来，用来指向其前驱还是后继节点
    思路:
        在中序遍历的过程中进行的线索化; 
        使用一个特殊的树，如每个节点都只有左子节点的树，来进行遍历很容易理解代码;
        使用每个节点都只有右子节点的树，来进行遍历也很容易理解代码;
 */
void inThreading(BiThrTree tree)
{
    if (tree != NULL)
    {
        inThreading(tree->lChild); //初始化左子树,如果左子树不存在，会直接返回
        if (tree->lChild == NULL)  //如果左子树不存在，则进行标志位的修改，以及左指针指向前驱节点
        {
            //在中序遍历时，第一次走到这一步时，表明当前节点已经是最左边的一个节点了;此时,该前驱节点是空；也就是说第一个节点的前驱节点为NULL
            tree->lChild = pre;
            tree->lTag = Thread;
        }
        if (pre != NULL && pre->rChild == NULL)  //第一次走到这一步时，表明当前节点已经是最左边的一个节点了;此时,该前驱节点是空，不做判断会崩的
        {
            pre->rChild = tree;//走到这一步时，表明已经得到了前驱节点;可以将前驱节点的右指针，指向当前节点了，也就是其后继节点
            pre->lTag = Thread;
        }
        pre = tree;//递归的过程中，前驱节点的这个量在不断更新；把当前的节点作为前驱节点赋值给成员变量
        inThreading(tree->rChild);//没有这行代码的话，整个代码的逻辑看起来清晰易懂
    }
}

/* 
    遍历线索二叉树
    思路:
        这里传进去的是一个使用中序遍历线索化后的二叉树;并且还给该树增加了一个头节点
 */
bool inOrderTraverse(BiThrTree tree)//传进去的是原二叉树的最左边的节点
{
    
}


int main()
{

}