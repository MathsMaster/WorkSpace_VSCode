/* 
    线索二叉树
    线索二叉树的原理是，二叉树的每个节点都具有指向左子树节点的指针，和指向右子树的节点指针；
    当二叉树的某个节点的左指针或者右指针不存在时，就会造成浪费。
    如果能够让该为NULL的左指针，或右指针指向在中序遍历时的，前驱节点，或者是后继节点。
    
    这就相当于将节点的链表变成了双向链表。
 */
#include <stdio.h>

typedef enum {Link,Thread} PointerTag;//用来标示该指针，是指向了自己的子节点，还是指向了遍历时的前驱或者后继节点

typedef int TElemType;

/* 
    定义线索二叉树的节点对象
 */
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lChild,*rChild;//分别指向左子树和右子树的指针(也是用来指向前驱节点和后继节点)
    PointerTag lTag;//表示左指针是指向了前驱节点，还是 左子节点
    PointerTag rTag;//表示右指针是指向了后继节点，还是 右子节点
} BiThrNode,*BiThrTree;

/* 
    对一棵二叉树进行线索化，就是将二叉树中的空指针全找出来，用来指向其前驱还是后继节点
 */
void inThreading(BiThrTree tree)
{
    
}


int main()
{
    
}