/* 
    用来练习2.0的算法设计题
 */
#include <stdio.h>
#include "Utils.h"

//定义线性表的结构体
#define MAXSIZE 500 //定义常量

/* =============================================================================================================================== */
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SeqList;

//定义线性表的初始化函数
Status InitSeqList(SeqList *list)
{
    printf("正在初始化的SeqList的内存地址 ---->  %#X \n", list);
    list->length = 0;
    for (int i = 0; i < sizeof(list->data) / sizeof(ElemType); i++)
    {
        list->data[i] = 0;
    }
    return OK;
}

//获取线性表的长度
int LengthSeq(SeqList list)
{
    return list.length;
}

/* 
    根据元素值查找索引,并返回对应的查找到的索引
*/
ElemType LocateSeqElem(SeqList *l, int index)
{
    for (int i = 0; i < l->length; i++)
    {
        if (i == index)
        {
            return l->data[i];
        }
    }
}

//根据元素的索引来查找
ElemType getSeqElem(SeqList *l, int i)
{
    return l->data[i];
}

/*
    判断元素在线性表中是否存在
 */
bool isSeqExist(SeqList *l, ElemType value)
{
    if (l == NULL)
        return false;
    for (int i = 0; i < l->length; i++)
    {
        if (getSeqElem(l, i) == value)
        {
            return true;
        }
    }

    return false;
}

/*
    往线性表里插入元素，传进来线性表的指针l，索引i，元素e
    描述 : 插入之前先判断是否越界
        再判断是否插入到最后位置，是的话，就直接插入
        不是插入最后的位置，则要把后面元素往后移动一位
 */
Status ListSeqInsert(SeqList *l, int i, ElemType e)
{
    if (i < 0 || i >= MAXSIZE || i > l->length)
        return ERROR;

    if (i == l->length) //元素直接插入队尾,无需移动其他元素
    {
        l->data[i] = e;
        l->length++;
    }
    else //否则就需要将所有元素后移一位（要考虑最后一位元素后移时越界的情况）
    {
        for (int j = l->length - 1; j >= i; j--)
        {
            l->data[j + 1] = l->data[j];
        }
        l->data[i] = e;
        l->length++;
    }
    return OK;
}

/* 
    通过一趟遍历，就能删除掉所有元素为e的对象，时间复杂度o(n),空间复杂度o(1)
    这里的位移应该是不算在时间复杂度内的，只有比较才算时间复杂度
    思路:
        从第0个元素开始，往后进行遍历比较，如果遇到了某个元素与目标元素一样，
        将该目标元素删除，将后面的所有元素继续往前位移（在位移的过程中也进行比较）
        如果在位移的过程中进行比较时，也发现了还有目标元素存在，该目标元素也需要删除，
        同时该目标元素后的元素往前位移的步长加一
 */
bool listSeqDelete(SeqList *list, ElemType e)
{
    if (list == NULL)
        return false;
    bool isSuccess;
    int step = 0; //位移时需要选取的步长
    for (int i = 0; i < list->length; i++)
    {
        if (list->data[i] == e) //找到了目标元素，步长加1
        {
            isSuccess = true;
            list->data[i] = 0; //习惯问题，这行代码可以不用
            step++;
        }
        else
        { //后面的其他元素往前移动一个步长
            if (step > 0)
                list->data[i - step] = list->data[i];
        }
    }
    list->length -= step;
    return isSuccess;
}

SeqList prepareSeqLinearData()
{
    SeqList list;
    InitSeqList(&list);
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list.length = sizeof(arr) / sizeof(int);
    memcpy(list.data, arr, sizeof(arr));
    return list;
}

//打印线性表中的所有元素
void PrintSeqList(SeqList *l)
{
    if (l == NULL)
        return;
    for (int i = 0; i < l->length; i++)
    {
        printf("arr[%d] : %d \n", i, l->data[i]);
    }
}
/* =============================================================================================================================== */

/* =============================================================================================================================== */
const int FLAG = -111111;

typedef struct
{
    ElemType data;           //节点上存储数据的部分
    struct CDNode *next;     //节点上指向下一个节点的指针索引
    struct CDNode *previous; //指向上一个节点的指针索引
} CDNode, *CDLinkedList;

/*
    创建头节点,使头指针指向该节点,并且因为是双向链表
    list 传进来的指针
 */
Status InitCDList(CDLinkedList list)
{
    CDNode headNode;
    headNode.data = FLAG;
    //因为是双向循环链表，空表时指向自己
    headNode.previous = list;
    headNode.next = list;
    *list = headNode;
    return OK;
}

/* 
    尾部插入法创建双链表,每个节点都有指向后继节点和前驱节点
    list 一个指针,指向了头节点
    len 链表中的元素的长度(不包括头节点)

 */
Status CreateCDList_L(CDLinkedList list, int len)
{
    CDNode *tempNode = list; //创建临时节点，首先就指向了头节点
    for (int i = 0; i < len; i++)
    {
        CDNode *newNode = (CDNode *)malloc(sizeof(CDNode)); //给当前创建的节点的每一项赋值
        newNode->data = i * 30;
        newNode->next = NULL;
        newNode->previous = tempNode;

        tempNode->next = newNode; //将前驱节点的next指向当前节点

        tempNode = newNode; //最后将当前节点的地址赋予临时指针
    }

    //最后需要把尾部节点和头节点连接起来
    tempNode->next = list;
    list->previous = tempNode;

    return OK;
}

/* 
    用来判断传入的链表的长度，不包含头节点
 */
int getListLength(CDLinkedList list)
{
    if (list == NULL)
        return -1;

    CDNode *tempNode = list->next; //先指向首元节点，可能为空
    int len = 0;
    while (true)
    {
        if (tempNode == NULL || tempNode->data == FLAG) //如果找到了
            return len;
        tempNode = tempNode->next;
        len++;
    }
}

void PrintCDLinkedList(CDLinkedList l)
{
    if (l == NULL) //判断指针是否有指向除了NULL外的某个地址
    {
        printf("传进来的指针是NULL");
        return;
    }

    CDNode *tempNode = l; //从头节点开始打印

    printf("头节点所在的内存空间地址 : %#X  头节点的内容 : %d   当前节点指向的下一个节点的地址 %#X  当前节点指向的上一个节点的地址 %#X \n",
           tempNode, tempNode->data, tempNode->next, tempNode->previous);

    int i = 0; //0表示首元节点
    while (true)
    {
        tempNode = tempNode->next;
        if (tempNode == NULL || tempNode->data == FLAG) //如果是循环链表，必须得想个办法跳出来
            break;

        printf("当前节点所在的内存空间地址 : %#X 当前节点的内容 : %d   当前节点指向的下一个节点的地址 %#X  当前节点指向的上一个节点的地址 %#X \n",
               tempNode, tempNode->data, tempNode->next, tempNode->previous);
    }
}
/* =============================================================================================================================== */

/* 
    根据传进来的指针，删除对应的节点对象
    因为是单链表，所以先考虑下获取到前驱节点
 */
void deleteNodeByElemType(LinkedList list, Node *node)
{
    if (list == NULL || node == NULL)
        return;

    Node *preNode = list;        //先拿到头节点
    Node *tempNode = list->next; //拿到首元节点
    while (tempNode != NULL)
    {
        if (node->data == tempNode->data) //准备进行删除
        {
            preNode->next = tempNode->next;
            break;
        }
        preNode = tempNode;
        tempNode = tempNode->next;
    }
}

/* 
    根据传进来的指针，删除对应的节点对象
    因为是单链表，所以先考虑下获取到前驱节点
 */
void deleteNode(LinkedList list, Node *node)
{
    if (list == NULL || node == NULL)
        return;

    Node *preNode = list;        //先拿到头节点
    Node *tempNode = list->next; //拿到首元节点
    while (tempNode != NULL)
    {
        if (node == tempNode) //准备进行删除
        {
            preNode->next = tempNode->next;
            break;
        }
        preNode = tempNode;
        tempNode = tempNode->next;
    }
}

/* 
    过滤自身的重复元素
 */
void filterSelfRepeatNode(LinkedList list)
{
    if (list == NULL)
        return;
    Node *node = list->next; //先指向首元节点
    Node *anthorNode = NULL;
    while (node != NULL)
    {
        anthorNode = node->next; //指向第二个元素节点，准备用来进行比较
        while (anthorNode != NULL)
        {
            if (node->data == anthorNode->data)
            {
                deleteNode(list, node);
                break;
            }
            anthorNode = anthorNode->next;
        }
        node = node->next;
    }
}

/* 
    过滤彼此之间的重复元素,不考虑自身的重复元素
 */
void filterEachOtherRepeatNode(LinkedList list_1, LinkedList list_2)
{
    if (list_2 == NULL || list_1 == NULL)
        return;
    Node *node_1 = list_1->next;
    Node *node_2 = NULL;

    while (node_1 != NULL)
    {
        node_2 = list_2->next;
        while (node_2 != NULL)
        {
            if (node_1->data == node_2->data)
            {
                deleteNode(list_2, node_2);
                break;
            }
            node_2 = node_2->next;
        }
        node_1 = node_1->next;
    }
}

/* 
    剔除两个链表的重复元素,包括自身的重复元素
 */
void filterAllRepeatNode(LinkedList list_1, LinkedList list_2)
{
    //先过滤掉自身以及彼此之间的重复元素
    filterSelfRepeatNode(list_1);
    filterSelfRepeatNode(list_2);
    filterEachOtherRepeatNode(list_1, list_2);
}

/* 
    进行链表的合并(此时已经不需要考虑重复元素了)
    使用指针1，指针2分别指向list_1,list_2首元节点,使用链表1作为被比较对象。
    取list_2节点，进行比较，如果list_2的节点小，就取出该节点，插入到list_1节点之前，同时list_2指针后移。
    如果list_2的节点大，那么list_1的节点后移一步，然后两边继续比较。。。。。。
    直到list_2节点比list_1节点小，然后插入list_1节点之前,同时list_2指针后移。
    如果list_2先到终点，则退出。如果list_1先到终点,则将list_2剩余元素接入到list_1末尾
 */
LinkedList mergeList(LinkedList list_1, LinkedList list_2)
{
    if (list_1 == NULL)
        return list_2;
    if (list_2 == NULL)
        return list_1;
    Node *preNode_1 = list_1;
    Node *node_1 = list_1->next; //先取出首元节点
    Node *preNode_2 = list_2;
    Node *node_2 = list_2->next;
    while (true)
    {
        if (node_2 == NULL) //链表2已经到头，表示list_2所有节点都进行了比较,已经插入了list_1
        {
            break;
        }
        else if (node_1 == NULL) //链表1到头了，需要把链表2的剩余元素全都链接到List_1的尾部
        {
            preNode_1->next = node_2;
            preNode_2->next = NULL; //链表2的剩余元素已经被接入链表1了，所以链表2的头节点需要断开
            node_2 = NULL;
        }
        else if (node_2->data < node_1->data) //先考虑list_2节点小的情况，往list_1中插入,同时node_2指针后移,这里要进行5步操作
        {
            preNode_2->next = node_2->next;
            node_2->next = node_1;
            preNode_1->next = node_2;
            node_2 = preNode_2->next;
            preNode_1 = preNode_1->next;
        }
        else if (node_2->data > node_1->data) //再考虑list_2节点大的情况,因为进行了重复剔除，所以不需要考虑相等的情况
        {
            preNode_1 = node_1;
            node_1 = node_1->next; //当node_1是链表1的最后一个元素时,这里就会变成NULL
        }
    }

    return list_1;
}

/* 
    用来测试合并有序的线性表(链式结构),同时要求不开辟新的空间,同时合并后的表中不允许出现重复数据
    思路:
        这里有两个功能，一个是剔除重复元素。一个是进行有序合并。
        先进行重复元素的剔除，然后合并来简化难度。

        剔除重复元素，先剔除自身链表的重复元素，从第一个元素和后面每个元素进行遍历
        再使用当前自己的元素与对方链表进行遍历

        再进行链表的合并(此时已经不需要考虑重复元素了)
 */
LinkedList MergeOrderData(LinkedList list_1, LinkedList list_2)
{
    //直接过滤掉重复元素
    filterAllRepeatNode(list_1, list_2);
    printf("剔除重复元素后的数据1\n");
    PrintLinkedList(list_1);
    printf("剔除重复元素后的数据2\n");
    PrintLinkedList(list_2);
    return mergeList(list_1, list_2); //现在传进来的数据已经是有序,且不存在重复元素了
}

/* 
    测试合并有序表的数据,使用链表
 */
void testMergeOrderData_LinkedList()
{
    printf("测试第二章第二大题的第一小题: 合并两个有序线性表,不开辟新的空间\n");
    LinkedList list_1 = prepareListData(1, true);
    printf("准备好的数据1\n");
    PrintLinkedList(list_1);
    LinkedList list_2 = prepareListData(1, false);
    printf("准备好的数据2\n");
    PrintLinkedList(list_2);
    //测试合并有序线性表的数据
    LinkedList list = MergeOrderData(list_1, list_2);
    printf("合并后的数据\n");
    PrintLinkedList(list);
}

/* 
    遍历list_1，找到其中比node节点大的数据，然后插入前面
    node 传进来的一个单独节点的指针，既没有前置节点，也没有后置节点
 */
void insertList(LinkedList list_1, Node *node)
{
    if (list_1 == NULL || node == NULL)
        return;
    Node *preNode = list_1;
    Node *currentNode = list_1->next; //首元节点
    while (currentNode != NULL)
    {
        if (currentNode->data > node->data) //如果比node大，则插入前面
        {
            preNode->next = node;
            node->next = currentNode;
            return;
        }
        preNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == NULL)
    {
        preNode->next = node;
    }
}

/* 
    因为可以允许存在重复元素，所以不需要再进行元素的剔除了
    因为都是非递减序列，所以合并的关节就在在于，每次取list_2的元素去往list_1中遍历找到比他大的数，就往前一个进行插入,
    因为每次都遍历，所以效率会低点

    简单思路:
        以list_1作为参照标准.
        遍历list_2中的元素，因为都是非递减排列的，所以直接取List_2的的元素(注意在取的时候，需要断开前置节点和后置节点),往list_1中插入
        插入的元素从头往后进行遍历，直到找到比当前元素大的值，然后插入该位置的前面。
        如果list_1中不存在比当前元素大的值，则表示list_2的剩余元素都比该值大，可以直接把list_2的剩余元素链接到list_1后面
    复杂思路:
        简单思路就是每个元素都是在list_1中插入时，进行的从头遍历
        这里可以记住要当前插入的索引，等下次再插入时，从这里接着遍历
 */
LinkedList MergeNotDecreasingDataOrderData(LinkedList list_1, LinkedList list_2)
{
    if (list_2 == NULL)
        return list_1;
    if (list_1 == NULL)
        return list_2;

    Node *preNode = list_2;
    Node *tempNode = list_2->next; //首元节点
    preNode->next = tempNode->next;
    tempNode->next = NULL;
    while (true)
    {
        insertList(list_1, tempNode);
        tempNode = preNode->next;
        if (tempNode == NULL)
            break;
        preNode->next = tempNode->next;
        tempNode->next = NULL;
    }
    return list_1;
}

/* 
    拆分元素，0以上的放在A表，0以下的元素放在B表
    思路:
        先创建两个头节点，并准备好两个尾指针。
        将List的第一个元素取出来(取的时候要断开和后面的链接),挂到两个头节点的某一个上，并且对应的尾指针后移
 */
void splitList(LinkedList list)
{
    if (list == NULL)
        return;

    LinkedList list_1 = malloc(sizeof(Node));
    Node *tailNode1 = list_1; //尾指针
    LinkedList list_2 = malloc(sizeof(Node));
    Node *tailNode2 = list_2;

    Node *node = list->next; //首元节点
    list->next = node->next; //取出来之后就赶紧断开和后面的链接，否则之后会弄出些问题
    node->next = NULL;
    while (node != NULL)
    {
        if (node->data > 0)
        {
            tailNode1->next = node;
            tailNode1 = node; //尾部指针后移
        }
        else if (node->data < 0)
        {
            tailNode2->next = node;
            tailNode2 = node;
        }

        node = list->next;
        if (node == NULL)
            break;
        list->next = node->next;
        node->next = NULL; ////取出来之后就赶紧断开和后面的链接，否则之后会弄出些问题
    }

    printf("拆分后的数据1\n");
    PrintLinkedList(list_1);
    printf("拆分后的数据2\n");
    PrintLinkedList(list_2);
}

/* 
    合并两个链表的差集合(即仅在list1出现，而不在list2中出现的元素)，使用list_1返回
    思路:
        把list_2中的元素，一个个的取出来，在list_1中进行比对，然后删除list1中对应的元素
 */
int mergeTwoListDifference(LinkedList list_1, LinkedList list_2)
{
    if (list_2 == NULL)
        return 0;
    if (list_1 == NULL)
        return 0;

    Node *node = list_2->next;
    while (node != NULL)
    {
        if (isExistByPointer(list_1, node))
        {
            deleteNodeByElemType(list_1, node);
        }
        node = node->next;
    }

    return Length(list_1);
}

/* 
    合并两个链表的交集，使用list_1返回
    思路:
        把list_1中的元素挨个取出来，在list_2中进行比对，如果在list_2中存在，就留下，否则就直接从list_1中删除
 */
LinkedList mergeTwoListIntersection(LinkedList list_1, LinkedList list_2)
{
    if (list_2 == NULL)
        return list_1;
    if (list_1 == NULL)
        return list_2;

    Node *node = list_1->next;
    while (node != NULL)
    {
        if (!isExistByPointer(list_2, node))
        {
            deleteNode(list_1, node); //删除list_2中的节点元素
        }
        node = node->next;
    }

    return list_1;
}

void testMergeNotDecreasingData_LinkedList()
{
    printf("测试第二章第二大题的第2小题: 合并两个非递减的有序列表,允许重复元素存在不开辟新的空间\n");
    LinkedList list_1 = prepareListData(2, true);
    printf("准备好的数据1\n");
    PrintLinkedList(list_1);
    LinkedList list_2 = prepareListData(2, false);
    printf("准备好的数据2\n");
    PrintLinkedList(list_2);
    //测试合并有序线性表的数据
    LinkedList list = MergeNotDecreasingDataOrderData(list_1, list_2);
    printf("合并后的数据\n");
    PrintLinkedList(list);
}

/* 
    通过一趟遍历找到最大值
    思路:
        
 */
int lookMaxValue(LinkedList list)
{
    if (list == NULL || list->next == NULL)
        return 0;
    Node *node = list->next;
    int value = node->data;
    while (node != NULL)
    {
        if (value < node->data)
        {
            value = node->data;
        }
        node = node->next;
    }

    return value;
}

/* 
    获取到当前节点之前的一个节点
 */
Node *getPreNode(LinkedList list, Node *node)
{
    if (list == NULL || list->next == NULL)
        return NULL;
    Node *preNode = list; //头节点
    while (preNode->next != NULL)
    {
        if (preNode->next == node)
        {
            break;
        }
        preNode = preNode->next;
    }
    return preNode;
}

Node *getLastNode(LinkedList list)
{
    if (list == NULL || list->next == NULL)
        return NULL;
    Node *node = list->next; //首元节点
    while (node->next != NULL)
    {
        node = node->next;
    }

    return node;
}

/* 
    逆转一个链表，将头节点外的其他节点指向方向都逆转过来
    思路:
        写一个函数，每次都取出链表的最后一个元素，以及前面的一个元素节点，将取出来的元素节点，连成链
        最后取出头节点，将头节点链接在最前面
 */
void transposeList(LinkedList list)
{
    //获取到链表的最后一个节点
    Node *lastNode = getLastNode(list);
    Node *preNode = getPreNode(list, lastNode);
    lastNode->next = preNode;
    preNode->next = NULL;

    Node *tailNode = lastNode; //先保存下最后的节点，等下准备链接到头节点上

    while (preNode != list) //只要没有获取到头节点，就继续
    {
        lastNode = getLastNode(list);
        preNode = getPreNode(list, lastNode);
        if (preNode != list) //如果找到了头节点，不要链接上去
            lastNode->next = preNode;
        preNode->next = NULL;
    }
    list->next = tailNode; //这里变成了一个循环节点
}

/* 
    修改传进来的双向循环链表中，节点和前置节点的位置
    思路:
        先取到四个有关的节点

 */
void changeNodes(CDLinkedList list, CDNode *node)
{
    if (list == NULL || node == NULL)
    {
        return;
    }

    CDNode *nextNode = node->next;
    CDNode *preNode = node->previous;       //前置节点
    CDNode *prepreNode = preNode->previous; //前置节点的前置节点

    //先断开几个节点的相关链接
    node->previous = NULL;
    node->next = NULL;
    preNode->previous = NULL;
    preNode->next = NULL;
    prepreNode->next = NULL;
    nextNode->previous = NULL;

    prepreNode->next = node;
    node->previous = prepreNode;
    node->next = preNode;
    preNode->previous = node;
    preNode->next = nextNode;
    nextNode->previous = preNode;
}

/* 
    删除链表中介于min和max之间的节点
 */
void deleteNodes(LinkedList list, int min, int max)
{
    if (list == NULL)
        return;

    Node *preNode = list;
    Node *node = list->next;
    while (node != NULL)
    {
        if (node->data > min && node->data < max)
        {
            //删除对应节点
            preNode->next = node->next;
            node->next = NULL;
            node = preNode->next;
            continue;
        }
        preNode = node;
        node = node->next;
    }
}

void testLookMax()
{
    printf("测试第二章第二大题的第6小题: 通过一趟遍历找到单链表中的最大值\n");
    LinkedList list_1 = prepareListData(6, true);
    printf("准备好的数据1\n");
    PrintLinkedList(list_1);
    //测试合并有序线性表的数据
    int value = lookMaxValue(list_1);
    printf("合并后的数据\n");
    printf("查找到的最大值 : %d \n", value);
}

void testTransposeList()
{
    printf("测试第二章第二大题的第7小题: 逆转一个链表\n");
    LinkedList list_1 = prepareListData(6, true);
    printf("准备好的数据1\n");
    PrintLinkedList(list_1);
    //逆转链表的数据
    transposeList(list_1);
    printf("逆转后的数据\n");
    PrintLinkedList(list_1);
}

void testDeleteNodes()
{

    printf("测试第二章第二大题的第8小题: 删除一个链表中的部分数据\n");
    LinkedList list_1 = prepareListData(6, true);
    printf("准备好的数据1\n");
    PrintLinkedList(list_1);
    //逆转链表的数据
    deleteNodes(list_1, -6, 23);
    printf("清除后的数据\n");
    PrintLinkedList(list_1);
}

/* 
    测试顺序线性表中删除指定的一些元素
 */
void testLinearDeleteNodes()
{
    printf("测试第二章第二大题的第10小题: 删除线性表中的一些指定数据\n");
    SeqList list = prepareSeqLinearData();
    printf("准备好的数据\n");
    PrintSeqList(&list);
    bool isSuccess = listSeqDelete(&list, 3);
    printf("清除数据 %s\n", isSuccess ? "成功" : "失败");
    PrintSeqList(&list);
}

void testChangeNodes()
{

    printf("测试第二章第二大题的第9小题: 修改传进去的一个节点以及该节点的前置节点的位置\n");
    CDLinkedList list = malloc(sizeof(CDNode));
    InitCDList(list);
    CreateCDList_L(list, 15);
    printf("准备好的数据\n");
    PrintCDLinkedList(list);
    changeNodes(list, list);
    printf("清除后的数据\n");
    PrintCDLinkedList(list);
}

/* 
    拆分一个链表
 */
void testSplit()
{
    printf("测试第二章第二大题的第5小题: 拆分一个链表\n");
    LinkedList list_1 = prepareListData(5, true);
    printf("准备好的数据1\n");
    PrintLinkedList(list_1);
    //测试合并有序线性表的数据
    splitList(list_1);
}

/* 
    过滤两个两个链表的差集
 */
void testFilterTwoListDifference()
{
    printf("测试第二章第二大题的第4小题: 过滤两个链表的差集\n");
    LinkedList list_1 = prepareListData(3, true);
    printf("准备好的数据1\n");
    PrintLinkedList(list_1);
    LinkedList list_2 = prepareListData(3, false);
    printf("准备好的数据2\n");
    PrintLinkedList(list_2);
    //测试合并有序线性表的数据
    int len = mergeTwoListDifference(list_1, list_2);
    printf("合并差集后的数据长度 : %d \n", len);
    PrintLinkedList(list_1);
}

/* 
    过滤两个两个链表的交集
 */
void testFilterTwoListIntersection()
{
    printf("测试第二章第二大题的第3小题: 过滤两个链表的交集\n");
    LinkedList list_1 = prepareListData(3, true);
    printf("准备好的数据1\n");
    PrintLinkedList(list_1);
    LinkedList list_2 = prepareListData(3, false);
    printf("准备好的数据2\n");
    PrintLinkedList(list_2);
    //测试合并有序线性表的数据
    LinkedList list = mergeTwoListIntersection(list_1, list_2);
    printf("合并后的数据\n");
    PrintLinkedList(list);
}

/* 
    测试第二章第二大题的第一小题: 合并两个有序线性表,不开辟新的空间
 */
void test2_2_1()
{
    testMergeOrderData_LinkedList();
}

/* 
    测试第二章第二大题的第一小题: 合并两个非递减的有序列表,允许重复元素存在不开辟新的空间
 */
void test2_2_2()
{
    testMergeNotDecreasingData_LinkedList();
}

/* 

 */
void test2_2_3()
{
    testFilterTwoListIntersection();
}

void test2_2_4()
{
    testFilterTwoListDifference();
}

void test2_2_5()
{
    testSplit();
}

void test2_2_6()
{
    testLookMax();
}

void test2_2_7()
{
    testTransposeList();
}

void test2_2_8()
{
    testDeleteNodes();
}

void test2_2_9()
{
    testChangeNodes();
}

void test2_2_10()
{
    testLinearDeleteNodes();
}

int main()
{
    // test2_2_1();
    // test2_2_2();
    // test2_2_3();
    // test2_2_4();
    // test2_2_5();
    // test2_2_6();
    // test2_2_7();
    // test2_2_8();
    // test2_2_9();
    test2_2_10();

    // int array[30];
    // array[0] = 100;
    // array[1] = 200;
    // array[2] = 300;

    // int * pointer = array;

    // printf("数组第一个元素 %d ,其地址为: %#X \n",array[0],&array[0]);
    // printf("数组第二个元素 %d ,其地址为: %#X \n",array[1],&array[1]);
    // printf("指针获取到的数组第一个元素 %d ,以及指针的地址: %#X \n",*pointer,pointer);
    // printf("指针获取到的数组第2个元素 %d ,以及指针的地址: %#X \n",*(pointer+1),pointer+1);
}
