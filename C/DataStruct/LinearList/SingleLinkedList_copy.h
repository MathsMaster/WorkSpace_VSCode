//单链式线性表
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OK 1
#define ERROR 0;
#define TRUE 1;
#define FALSE -1;

typedef int ElemType; //给数据类型取别名

typedef int Status; //给数据类型重命名

/* 定义单链表的结构体 */
typedef struct Node
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

int Length(LinkedList list)
{
    if (list == NULL)
        return 0;
    int len = 0;
    Node *node = list->next; //先拿到首元节点的指针
    while (true)
    {
        if (node != NULL)
        {
            len++;
            node = node->next;
        }
        else
        {
            break;
        }
    }
    return len;
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
    判断链表中是否已经存在相同的数据了
 */
bool isExist(LinkedList list, ElemType e)
{
    if (list == NULL)
        return false;
    if (LocateElem(list, e) != NULL)
        return true;
    else
        return false;
}

/* 
    判断链表中是否已经存在相同的数据了
 */
bool isExistByPointer(LinkedList list, Node * node)
{
    if (list == NULL || node == NULL)
        return false;
    if (LocateElem(list, node->data) != NULL)
        return true;
    else
        return false;
}

/* 
    往链表中插入数据(需要创建元素)
    list 指向单链表头节点的指针
    index 元素插入位置的索引,从0开始计算，以首元节点为0
    e 等待插入的数据
 */
Status ListInsert(LinkedList list, int index, ElemType e)
{
    if (index < 0)
        return ERROR;
    if (index == 0) //如果是准备从第0个元素的位置插入
    {
        Node *newNode = (Node *)malloc(sizeof(Node)); //创建新节点所需的空间
        newNode->next = NULL;
        newNode->data = e;
        newNode->next = list->next;
        list->next = newNode;
        return OK;
    }
    else //如果是准备从其他位置开始插入节点
    {
        Node *tempNode = list->next; //先指向首元节点
        int i = 0;
        while (true) //如果索引越界,就直接返回
        {
            if (i == index - 1) //如果当前找到了准备插入的节点位置的前一个节点,准备动手
                break;
            tempNode = tempNode->next;
            i++;
            if (tempNode == NULL) //什么时候判断是否越界比较好呢
                return ERROR;
        }
        Node *newNode = (Node *)malloc(sizeof(Node)); //创建新节点所需的空间
        newNode->next = NULL;
        newNode->data = e;
        newNode->next = tempNode->next;
        tempNode->next = newNode;
        return OK;
    }
}

/* 
    根据索引删除链表中的元素 
    list 一个指针,指向了链表的头节点
    index 索引所在位置从0开始,从首元节点开始计算
*/
Status ListDelete(LinkedList list, int index)
{
    if (index < 0) //针对小于0的情况
        return ERROR;
    Node *tempNode = list->next; //先指向首元节点
    if (index == 0)              //针对等于0的情况, 如果删除的就是头节点,将首元节点的下一个直接链接到头节点上
    {
        list->next = tempNode->next;
        return OK;
    }

    int i = 0;
    while (true) //从索引1开始查找的节点
    {
        if (i == index - 1) //找到待删除节点的前驱节点
            break;
        tempNode = tempNode->next;
        i++;
        if (tempNode == NULL) //出现了越界的情况
            return ERROR;
    }

    Node *deleteNode = tempNode->next; //找到待删除的节点指针
    if (deleteNode == NULL)            //如果要删除的是最后一个元素的后面一个就直接返回
        return ERROR;
    tempNode->next = deleteNode->next; //将待删除节点的后驱节点，和待删除元素前驱节点链接起来
    return OK;
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
        Node *node = (Node *)malloc(sizeof(Node)); //不断开辟新的空间
        node->next = NULL;
        node->data = i * 10;
        node->next = l->next; //将头节点后面的其他节点,都挂到新的节点上
        l->next = node;       //将新加入的节点,挂到头节点上
    }
    return OK;
}
/* 
    使用后插法创建链表
    数据都是从链表的最后一个节点衔接上
    list 一个指针,指向的是链表的头节点
    len 需要添加的数据长度
 */
Status CreateList_L(LinkedList list, int len)
{
    //创建尾指针,尾指针初时是指向头节点
    Node *lateNode = list;
    for (int i = 0; i < len; i++)
    {
        Node *node = (Node *)malloc(sizeof(Node)); //开辟节点的空间,
        node->data = i * 20;
        node->next = NULL;
        lateNode->next = node;
        lateNode = node;
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

LinkedList testInitList();

void testSingleLinkedList();

void testTailCreateSingleLinkedList(LinkedList);

void mainTest()
{
    //测试初始化
    printf("\n\n测试初始化\n");
    LinkedList list = testInitList();

    // //测试单链表
    // printf("\n\n测试头插法创建单链表\n");
    // testSingleLinkedList(list);

    //测试尾部插法创建单链表
    printf("\n\n测试尾部插法创建单链表\n");
    testTailCreateSingleLinkedList(list);

    //测试单链表的查找功能
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

    //插入新的节点元素
    printf("\n\n测试插入新的节点元素\n");
    int status = ListInsert(list, 15, 9999999);
    if (status)
        printf("插入元素成功\n");
    else
        printf("插入元素失败\n");
    PrintLinkedList(list);

    //删除节点元素
    printf("\n\n删除节点元素\n");
    status = ListDelete(list, 0);
    if (status)
        printf("删除节点元素成功\n");
    else
        printf("删除节点元素失败\n");
    PrintLinkedList(list);
}

//测试初始化
LinkedList testInitList()
{
    LinkedList list = (LinkedList)malloc(sizeof(Node)); //初始化一个头节点对象
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

//测试尾插法创建单链表
void testTailCreateSingleLinkedList(LinkedList list)
{
    int status = CreateList_L(list, 15);
    if (status == OK)
        printf("尾部插入法创建链表成功\n");
    PrintLinkedList(list);
}