//单链式线性表
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
} Node, *LinkedList;   //两个重命名,一个表示节点对象,一个表示链表对象

/* 
    初始化链表(创建空链表) 
    传进来头节点的一个空指针，在这里给他创建一个节点,但该节点仅仅作为头节点使用(不存储任何数据)
    从第一个数据节点(首元节点)才开始存储数据

    这里不能传空指针进来，否则在给指针指向的空间赋值时，就过不去
*/
Status InitList(LinkedList list)
{
    Node headerNode;
    *list = headerNode; //创建头节点，并且给头指针赋值
    list->next = NULL;  //当前的链表只有头节点，还没有任何数据元素
    return OK;
}

/* 
    单链表的取值，根据索引来取
    获取链表中节点中的数据 
    list 传进来的一个指针,指向链表的头节点
    index 传进来的索引,从0开始计数，0代表首元节点的索引
    *e 用来将查找到的数据元素，通过指针返回
*/
Status GetElem(LinkedList list, int index, ElemType *e)
{
    int i = 0;
    Node *tempNode = list->next; //先指向首元节点
    while (true)
    {
        if (i == index)
        {
            *e = tempNode->data;
            break;
        }
        tempNode = tempNode->next;
        i++;
    }
}

/* 
    根据链表中的数据元素,获取对应的节点 
    返回对应的节点的指针
    list 传进来的指针,指向了链表的头节点
*/
Node *LocateElem(LinkedList list, ElemType e)
{
    Node *tempNode = list->next; //先指向链表的首元节点
    while (tempNode != NULL)
    {
        if (tempNode->data == e)
        {
            break;
        }
        tempNode = tempNode->next;
    }
    return tempNode;
}

/* 
    往链表中插入数据(需要创建元素)
    list 指向单链表头节点的指针
    index 元素插入位置的索引
    e 等待插入的数据
 */
Status ListInsert(LinkedList list,int index,ElemType e)
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
Status CreateList_H(LinkedList l, int n)
{
    for (int i = 0; i < n; i++)
    {
        Node *node = malloc(sizeof(Node)); //不断开辟新的空间
        node->data = i * 10;
        node->next = l->next; //将头节点后面的其他节点,都挂到新的节点上
        l->next = node;       //将新加入的节点,挂到头节点上
    }
    return OK;
}

/* 打印所有节点数据,包括头节点 */
void PrintLinkedList(LinkedList l)
{
    if (l == NULL) //判断指针是否有指向除了NULL外的某个地址
    {
        printf("传进来的指针是NULL");
        return;
    }

    int i = 0;
    Node *tempNode = NULL;
    tempNode = l->next; //首先指向首元节点
    while (true)        //只有指针才可以做判NULL操作,对象是没法来判空的
    {
        printf("指针变量本身的地址 : %#X   当前节点所在的内存空间地址 : %#X  当前节点的索引 : %d  当前节点的内容 : %d   当前节点指向的下一个节点的地址 %#X \n", &tempNode, tempNode, i, tempNode->data, tempNode->next);
        tempNode = tempNode->next; //不断的取出下一个来
        if (tempNode == NULL)
            break;
        i++;
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

LinkedList testInitList();

void testSingleLinkedList();

int main()
{
    //测试初始化
    printf("\n\n测试初始化\n");
    LinkedList list = testInitList();

    //测试单链表
    printf("\n\n测试单链表\n");
    testSingleLinkedList(list);

    //测试单链表
    printf("\n\n测试单链表的查找功能\n");
    ElemType e = -1;
    GetElem(list, 5, &e);
    printf("查找到的元素 索引为 5，值为 : %d\n", e);

    //测试根据值查找节点
    printf("\n\n测试根据值查找节点\n");
    Node *tempNode = LocateElem(list, 10);
    if (tempNode == NULL)
        printf("查找到的节点为NULL \n");
    else
        printf("查找到的节点的地址空间为 %#X  数据值为 : %d\n", tempNode, tempNode->data);

    return 0;
}

//测试初始化
LinkedList testInitList()
{
    LinkedList list = malloc(sizeof(Node)); //初始化一个头节点对象
    printf("初始化头节点 开辟的内存空间大小 : %d , 开辟的空间地址为 : %#X\n", sizeof(Node), list);
    int status = InitList(list);
    if (status == OK)
        printf("初始化链表成功\n\n");

    return list;
}

//测试单链表
void testSingleLinkedList(LinkedList list)
{
    int status = CreateList_H(list, 15);
    if (status == OK)
        printf("首插法创建链表成功\n");
    PrintLinkedList(list);
}