//单链式线性表
#include <stdio.h>

#define OK 1
#define ERROR -1;
#define TRUE 1;
#define FALSE -1;

typedef int ElemType; //给数据类型取别名

typedef int Status; //给数据类型重命名

/* 定义单链表 */
typedef struct
{
    ElemType data;     //节点上存储数据的部分
    struct Node *next; //节点上指向下一个节点的指针索引
} Node, LinkedList;    //两个重命名,一个表示节点对象,一个表示链表对象

/* 
    初始化链表(创建空链表) 
    传进来头节点的一个空指针，在这里给他创建一个节点,但该节点仅仅作为头节点使用(不存储任何数据)
    从第一个数据节点(首元节点)才开始存储数据

    这里不能传空指针进来，否则在给指针指向的空间赋值时，就过不去
*/
Status InitList(LinkedList *list)
{
    Node headerNode;
    *list = headerNode; //创建头节点，并且给头指针赋值
    list->next = NULL;  //当前的链表只有头节点，还没有任何数据元素
    return OK;
}

/* 
    获取链表中节点中的数据 

*/
Status GetElem()
{
}

/* 根据链表中的数据元素,获取对应的节点 */
Status LocateElem()
{
}

/* 往链表中插入数据(需要创建元素) */
Status ListInsert()
{
}

/* 根据索引删除链表中的元素 */
Status ListDalete()
{
}

/* 
    使用前插法的方式创建一个链表 
    每次创建的节点,都要插入在第一个位置
    因为传进来的链表中已经拥有链头节点,所以这里需要先取出头节点,
    每次数据节点添加时,都要断开头节点的指向，指向新的节点,而新添加的节点，要指向之前的节点
*/
Status CreateList_H(LinkedList *l, int n)
{
    for (int i = 0; i < n; i++)
    {
        Node node; //不断创建新的节点
        node.data = i;
        node.next = l->next; //将头节点后面的其他节点,都挂到新的节点上
        l->next = &node;     //将新加入的节点,挂到头节点上
        printf("建立链表时打印---> 当前节点的地址 : %#X  节点中的内容 : %d  当前节点指向的下个节点的地址 : %#X \n",&node,node.data,node.next);
    }
    return OK;
}

/* 打印所有节点数据,包括头节点 */
void PrintLinkedList(LinkedList *l)
{
    if (l == NULL) //判断指针是否有指向除了NULL外的某个地址
    {
        printf("传进来的指针是NULL");
        return;
    }
    printf("头节点地址  l : %#X    &(*l) : %#X    头节点中的内容 : %d \n ", l, &(*l), (*l).data);

    Node *tempNode = NULL;
    tempNode = l->next; //通过头节点,取出首元节点的地址,赋值给临时变量
    while (1)           //只有指针才可以做判NULL操作,对象是没法来判空的
    {
        printf("指针的地址 : %#X   当前节点地址 : %#X  当前节点的内容 : %d   当前节点指向的下一个节点的地址 %#X \n",&tempNode,tempNode,tempNode->data,tempNode->next);
        tempNode = tempNode->next; //不断的取出下一个来
        if (tempNode == NULL)
            break;
    }
}

/* 
    使用后插法的方式创建一个链表
    每次创建的节点,都要插入在最后一个位置
    先是头指针指向头节点,然后才是添加数据节点,每次数据节点添加时,都是直接添加到最后面,
    并且使用一个尾指针，一直指向最后的一个节点，方便随时用来进行操作末尾的元素
*/
Status CreateList_R(LinkedList *list)
{
    return OK;
}

void testInitList();

void testSingleLinkedList();

int main()
{
    //测试初始化
    printf("\n\n测试初始化\n");
    testInitList();

    //测试单链表
    printf("\n\n测试单链表\n");
    testSingleLinkedList();

    return 0;
}

//测试初始化
void testInitList()
{
    LinkedList list; //初始化一个头节点对象
    int status = InitList(&list);
    if (status == OK)
        printf("初始化链表成功\n\n");
}

//测试单链表
void testSingleLinkedList()
{
    LinkedList *list = NULL; //先创建头指针,当前指针没指向任何地方(指针变量中没存储任何地址)
    Node headerNode;         //先创建头节点吧
    headerNode.next = NULL;
    list = &headerNode;      //修改指针的指向，使其指向头节点所在的内存

    int status = CreateList_H(list, 10);
    if (status == OK)
        printf("首插法创建链表成功\n");
    PrintLinkedList(list);
}