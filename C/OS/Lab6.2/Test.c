/**
 * @file Test.c
 * @author your name (you@domain.com)
 * @brief  实验目的: 理解文件存储空间的管理,文件的物理结构,目录结构,以及文件操作的实现
 *         实验内容: 实现一个简单的二级文件管理系统,可以实现常用文件目录和文件操作。（根本没涉及到树形目录结构）
 *              用户登录，列文件目录,创建文件，删除文件，打开文件，关闭文件，读文件，写文件
 *         设计思路:
 *              本文件系统采用两级目录，其中第一级对应应用账号,第二级对应应用账号下的文件（暂不考虑文件共享，文件系统安全）。
 *              设计时，先确定文件系统的数据结构，即主目录，子目录，活动文件等。主目录和子目录都以链表的形式存放，用户创建的文件以编号形式存储在磁盘上，
 *              并且需要在目录中登记。
 *          实现思路：
 *              这货根本不是基于磁盘块的逻辑来设计的，而是基于内存中的分配方式设计的。
 * @version 0.1
 * @date 2022-05-06
 *
 * @copyright Copyright (c) 2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MaxUser 100        //表示当前最多有100个用户
#define MaxDisk 512 * 1024 //表示磁盘空间总容量是512*1024 B
#define commandAmount 12   //指令数量

//按照这货的思路，这是明显把磁盘块当成内存里的分区了，而且每个磁盘块的大小不等
//开始时只有一个分区，然后不断的创建文件，每创建一个文件，就多一个分区，分区就越来越多，剩余的空分区也越来越小
typedef struct distTable //磁盘块结构体
{
    int maxlength; //表示整个磁盘分区的剩余长度
    int start;     //当前磁盘分区在整个磁盘空间的起始位置
    int useFlag;   //表示当前盘分区是否被使用了
    struct distTable *next;
} diskNode;
diskNode *diskHead; //表示整个磁盘中的各个分区链接成的表，第一个是空闲分区，后面的部分则是已经有人使用过的分区，或者是被使用过后回收释放的分区

//在二级目录里，一个FCB就是对应了一个文件，如果是在多级目录里，则可能还包含了文件夹的情况
//一个FCB到底对应了一个什么？？？？ 从书上看,一个FCB对应了一个文件(文件夹也是文件),也就是说,一个FCB里可能会包括很多FCB
//在简单的两级目录里面,文件只在最下面一层，也就是说，不会存在FCB里包含FCB的情况。
typedef struct fileTable //文件块结构体，即FCB
{
    char fileName[10];
    int start;        //文件在磁盘存储空间的起始地址
    int length;       //文件内容长度
    int maxlength;    //文件的最大长度
    char fileKind[3]; //文件的属性——读写方式
    struct tm *timeinfo;
    bool openFlag; //判断是否有进程打开了该文件
    // fileTable *next;
} fileTableN;

//一个UFD列表，相当于第二级目录，同时也是用户目录中的一项, 一个结构体对应着UFD中的一项
typedef struct user_file_directory //用户文件目录文件UFD中的一项
{
    // char fileName[10];
    struct fileTable *file;           //表示当前这一项所指向的文件(即文件控制块FCB)
    struct user_file_directory *next; //表示下一个子项的链接
} UFD;

//相当于书上的MFD对象中的一项而已, 即第一级目录中的一项而已
typedef struct master_file_directory //主文件目录MFD
{
    char userName[10];
    char password[10];
    UFD *user; //指向了第二级目录，也就是用户的文件目录
} MFD;
MFD userTable[MaxUser]; //一个MFD列表，相当于第一级目录，整个系统中唯一存在的MFD对象,而里面有很多用户的文件信息
int userNo = 0;         //表示用户编号，从0开始，依次递增

//文件管理
void fileCreate(char fileName[], int length, char fileKind[]); //创建文件
void fileWrite(char fileName[]);                               //写文件
void fileCat(char fileName[]);                                 //读文件
void fileRen(char fileName[], char rename[]);                  //重命名文件
void fileFine(char fileName[]);                                //查询文件
void fileDir(char UserName[]);                                 //显示某一用户的所有文件
void fileClose(char fileName[]);                               //关闭已打开的文件
void fileDel(char fileName[]);                                 //删除文件
void chmod(char fileName[], char kind[]);                      //修改文件的读写方式
int requestDist(int startPostion, int maxLength);              //磁盘分配查询
void initDisk();                                               //初始化磁盘
void freeDisk(int startPostion);                               //磁盘空间释放
void diskShow();                                               //显示磁盘使用情况

//用户管理
void userCreate();
int login();
int userID = -1; //用户登录的ID号，值为-1时表示没有用户登录 , 实际上就是用户的userNo

int main()
{
    //准备这么多命令用来干啥
    char order[commandAmount][10];
    strcpy(order[0], "create");
    strcpy(order[1], "rm");
    strcpy(order[2], "cat");
    strcpy(order[3], "write");
    strcpy(order[4], "fine");
    strcpy(order[5], "chmod");
    strcpy(order[6], "ren");
    strcpy(order[7], "dir");
    strcpy(order[8], "close");
    strcpy(order[9], "return");
    strcpy(order[10], "exit");
    strcpy(order[11], "df");

    char command[100];     //键盘输入的命令，中间以空格 或 换行来分割
    char command_str1[10]; //键盘输入的第一个操作命令的字符串
    char command_str2[10]; //键盘输入的第二个操作命令的字符串
    //输入创建文件命令时，后面需要的几个参数
    char command_str3[5];
    char command_str4[3];
    int i, k, j;
    int length;
    initDisk(); //初始化磁盘

    //这里假设了在MDF的列表中存在100个用户,先给每个用户的子项先建立起来，进行初始化
    for (i = 0; i < MaxUser; i++) //初始化用户UFD目录文件的头指针
    {
        userTable[i].user = (UFD *)malloc(sizeof(UFD));
        userTable[i].user->next = NULL;
    }

    //无限循环
    while (1)
    {
        printf("********************************************\n");
        printf("                  1、创建用户\n");
        printf("                  2、登录\n");
        printf("                  输入数字100退出....\n");
        printf("********************************************\n");
        printf("请选择功能键:>");
        int choice;
        scanf("%d", &choice);

        if (choice == 1)
        {
            userCreate();
        }
        else if (choice == 2)
        {
            userID = login();
        }
        else if (choice == 100)
        {
            printf("退出\n");
            break;
        }
        else
        {
            printf("您的输入有误，请重新选择\n");
            break;
        }

        while (1)
        {
            if (userID == -1)
            {
                printf("用户未登录,请登录后再操作\n");
                break;
            }
            printf("———————————————————————————————————————\n");
            printf(" create-创建 格式：create a1 1000 rw,将创建名为a1,长度为1000字节可读可写的文件\n");
            printf(" rm-删除 格式：rm a1,将删除名为a1的文件\n");
            printf(" cat-查看文件内容 格式：cat a1,显示a1的内容\n");
            printf(" write-写入  格式：write a1\n");
            printf(" fine-查询 格式：fine a1 ,将显示文件 a1的属性\n");
            printf(" chmod-修改 格式：chmod a1 r,将文件a1的权限改为只读方式\n");
            printf(" ren-重命名 格式：ren a1 b1 ,将a1改名为b1\n");
            printf(" dir-显示文件 格式：dir aaa,将显示aaa用户的所有文件\n");
            printf(" df-显示磁盘空间使用情况 格式：df\n");
            printf(" close-关闭文件 格式：close a1,将关闭文件a1\n");
            printf(" return-退出用户，返回登录界面\n");
            printf(" exit-退出程序\n");
            printf("————————————————————————————————————————\n");
            printf("请输入你的命令:>  命令之间以空格 或者 换行号来分割.....\n");
            gets(command); //从键盘中读取输入到数组中,中间以换行或者空格号来进行间隔
            //***************** 读取键盘输入的第一个操作命令 ****************
            int select;
            // command_str1字符串存储命令的操作类型
            for (i = 0; command[i] != ' ' && command[i] != '\0'; i++)
            {
                command_str1[i] = command[i]; //将输入的char挨个的赋值到command_str1中
            }
            k = i;
            command_str1[k] = '\0';
            for (i = 0; i < commandAmount; i++)
            {
                if (!strcmp(command_str1, order[i])) //比较输入的字符串，如果字符串香等
                {
                    select = i;
                    break;
                }
            }
            if (i == commandAmount) //又是通过越界来判断,这判断不方法不好👎
            {
                printf("您输入的命令有误，请重新输入\n");
                continue;
            }
            //************** 读取键盘输入的第二个操作命令,表示文件名称 ****************
            // commmand_str2字符串存储文件名或用户名
            for (i = k + 1, k = 0; command[i] != ' ' && command[i] != '\0'; i++, k++)
                command_str2[k] = command[i];
            command_str2[k] = '\0'; //在末尾添加'\0'表示字符串结束了
            k = i;

            //************** 开始进行操作处理命令 ****************
            UFD *p;
            switch (select) //选择代号0~11,分别表示create....df的命令
            {
            case 0: // create-创建文件
                //这写代码的能力,真生硬啊,差不多就相当于本4的水平
                for (i = k + 1, k = 0; command[i] != ' '; i++, k++)
                {
                    command_str3[k] = command[i];
                }
                command_str3[k] = '\0';
                k = i;
                j = 1;
                length = 0;                                     //初始化文件长度
                for (i = strlen(command_str3) - 1; i >= 0; i--) //把字符串转换为十进制
                {
                    length += (command_str3[i] - 48) * j;
                    j *= 10;
                }
                for (i = k + 1, k = 0; command[i] != ' ' && command[i] != '\0'; i++, k++)
                {
                    command_str4[k] = command[i];
                }
                command_str4[k] = '\0';
                fileCreate(command_str2, length, command_str4);
                break;
            case 1: // rm-删除
                fileDel(command_str2);
                break;
            case 2: // cat-查看文件内容
                break;
            case 3: // write-写入
                break;
            case 4: // fine-查询
                break;
            case 5: // chmod-修改
                break;
            case 6: // ren-重命名
                break;
            case 7: // dir-显示文件
                break;
            case 8: // df-显示磁盘空间使用情况
                break;
            case 9: // close-关闭文件
                break;
            case 10: // return-退出用户
                break;
            case 11: // exit-退出程序

                break;
            default:

                break;
            }
        }
    }
}

/**
 * @brief 调用系统功能，从键盘读取信息,输入信息时，不显示在屏幕上
 *
 * @return int
 */
int getch(void)
{
    char c;
    system("stty -echo");
    system("stty -icanon");
    c = getchar();
    system("stty icanon");
    system("stty echo");
    return c;
}

void userCreate()
{
    char c;
    char userName[10];
    int i;
    if (userNo < MaxUser) //用户编号userNo从0开始增长
    {
        //***********输入用户名称****************
        while (getchar() != '\n')
            ; //清空流缓冲区
        printf("请输入用户名：");
        for (i = 0; c = getch(); i++)
        {
            if (c == '\n')
                break;
            else
                userName[i] = c;
            printf("%c", c);
        }
        //***********和用户列表中已有的用户名进行比较****************
        //这个比较逻辑存在漏洞，每次都只会和前面的用户进行比较
        userName[i] = '\0';
        for (i = 0; i < userNo; i++)
        {
            //比较字符串，相同就返回0
            if (!strcmp(userTable[i].userName, userName))
            {
                printf("\n");
                printf("该用户名已存在,创建用户失败\n");
                sleep(1);
                return;
            }
        }
        strcpy(userTable[userNo].userName, userName); //进行对应的赋值
        //***********输入用户密码****************
        printf("\n");
        printf("请输入密码：");
        for (i = 0; c = getchar(); i++)
        {
            if (c == '\n')
            {
                break;
            }
            else
            {
                userTable[userNo].password[i] = c;
            }
            printf("*");
        }
        userTable[userID].password[i] = '\0'; //这一步操作是什么鬼,难道userID和userNo相等
        printf("\n");
        printf("创建用户成功\n");
        userNo++;
        sleep(1); // system("pause");
    }
    else
    {
        printf("创建用户失败，用户数量已达到上限\n");
        sleep(1); // system("pause");
    }
}

//用户登录
int login()
{
    char name[10], psw[10];
    char c;
    int i, times;
    while (getchar() != '\n')
        ; //清空流缓冲区
    //***********输入用户名称****************
    printf("请输入用户名:\n");
    for (i = 0; c = getchar(); i++)
    {
        if (c == '\n')
            break;
        else
            name[i] = c;
        printf("%c", c);
    }
    name[i] = '\0';
    for (i = 0; i < userNo; i++)
    {
        //用户名匹配
        if (!strcmp(userTable[i].userName, name))
            break;
    }
    //这写代码的人真菜,竟然用这种方式来匹配，还不如封装成专门的匹配函数
    if (i == userNo)
    {
        printf("\n您输入的用户名不存在\n");
        sleep(1); // system("pause");
        return -1;
    }
    //***********输入用户密码****************
    for (times = 0; times < 3; times++)
    {
        // psw使用'\0'来代替
        memset(psw, '\0', sizeof(psw));
        printf("\n请输入密码:");
        for (i = 0; c = getchar(); i++)
        {
            if (c == '\n')
                break;
            else
                psw[i] = c;
            printf("*");
        }
        printf("\n");
        for (i = 0; i < userNo; i++)
        {
            //这里又有bug,将输入的用户密码和所有密码进行匹配,只要有一个能匹配上，结果就登录成功
            if (!strcmp(psw, userTable[i].password))
            {
                printf("用户登录成功\n");
                sleep(1); // system("pause");
                break;
            }
        }
        if (i == userNo)
        {
            printf("您输入的密码错误，您还有%d次输入机会\n", 2 - times);
            if (times == 2)
                exit(0);
        }
        else
        {
            break;
        }
    }
    return i; //这个 i 相当于就是 userNo
}

/**
 * @brief 初始化磁盘
 *
 */
void initDisk()
{
    //把整个磁盘当成了内存中的一个分区
    diskHead = (diskNode *)malloc(sizeof(diskNode));
    diskHead->maxlength = MaxDisk;
    diskHead->useFlag = 0;
    diskHead->start = 0;
    diskHead->next = NULL;
}

/**
 * @brief 这是把整个磁盘都当成了一个分区，每创建一个文件，就从剩余分区中切割一部分，作为一个分区，剩余分区就是空分区
 *
 * @param startPostion 表示起始位置,是表示文件在整个磁盘空间的位置
 * @param fileLength 传进来的待创建文件的长度
 * @return int
 */
int requestDist(int startPostion, int fileLength)
{
    int flag = 0;       //是否有被使用
    diskNode *p, *temp; //表示一个磁块
    diskNode *q;        //表示一个被占用的磁块
    p = diskHead;       //表示磁盘中的盘块链表的头指针
    while (p)           //按这种方式分配磁块的结果是，diskHead链表的第一块是空闲分区,后面每一块都是被占用了的
    {
        //这是指当前磁盘块的长度大于fileLength,如果要是不大于，那不就凉拌了
        //这里明显是把磁盘当成了内存中的分区了，每个分区大小不等，这里的每个磁盘块大小也不等
        if (p->useFlag == 0 && p->maxlength > fileLength) //
        {
            startPostion = p->start;
            //繁忙磁块
            q = (diskNode *)malloc(sizeof(diskNode));
            q->start = p->start;
            q->maxlength = fileLength; //文件长度就是当前磁盘块的长度
            q->useFlag = 1;            //当前磁盘块被占用了
            q->next = NULL;

            diskHead->start = p->start + fileLength;         //这个指针相当于指向了磁盘块链表的尾部了
            diskHead->maxlength = p->maxlength - fileLength; //这玩意就相当于整个磁盘块的剩余长度了
            flag = 1;
            temp = p;
            //这操作是把刚生成的繁忙磁块，链接到空闲磁块后面去
            if (diskHead->next == NULL)
            {
                diskHead->next = q; //这操作是把刚生成的繁忙磁块，链接到空闲磁块后面去
            }
            else
            {
                while (temp->next)
                    temp = temp->next;
                temp->next = q;
            }
            break;
        }
        p = p->next;
    }
    return flag;
}

/**
 * @brief 创建文件
 *
 * @param fileName 文件名
 * @param length 文件长度
 * @param fileKind 文件权限
 */
void fileCreate(char fileName[], int length, char fileKind[])
{
    printf("创建文件 filename : %s , length : %d , fileKind : %s \n", fileName, length, fileKind);
    time_t rawtime; //一个long型数据,表示文件权限
    int startPos;
    UFD *fileNode;
    UFD *p; //表示第二级目录,也就是用户目录的头指针
    //******************** 判断传进来的文件名称,与当前用户目录下的所有文件名称进行比较 **************************
    for (p = userTable[userID].user->next; p != NULL; p = p->next)
    {
        if (!strcmp(p->file->fileName, fileName)) //和当前用户下的所有文件名进行比较
        {
            printf("文件重名，创建文件失败\n");
            sleep(1); // system("pause");
            return;
        }
    }

    //  这破玩意根本不是在按照固定磁块大小的方式，进行文件分配的。
    if (requestDist(startPos, length))
    {
        //相当是用户目录下的一项
        fileNode = (UFD *)malloc(sizeof(UFD));
        //这玩意相当于是是一个文件
        fileNode->file = (fileTableN *)malloc(sizeof(fileTableN)); //这一步必不可少，因为fileNode里面的指针也需要申请地址，否则fileNode->file指向会出错
        strcpy(fileNode->file->fileName, fileName);
        strcpy(fileNode->file->fileKind, fileKind);
        fileNode->file->maxlength = length;
        fileNode->file->start = startPos;
        fileNode->file->openFlag = false;
        time(&rawtime);
        fileNode->file->timeinfo = localtime(&rawtime);
        fileNode->next = NULL;
        if (userTable[userID].user->next == NULL)
            userTable[userID].user->next = fileNode;
        else
        {
            p = userTable[userID].user->next;
            while (p->next)
                p = p->next;
            p->next = fileNode;
        }
        printf("创建文件成功\n");
        sleep(1); // system("pause");
    }
    else
    {
        printf("磁盘空间已满或所创建文件超出磁盘空闲容量，磁盘空间分配失败\n");
        sleep(1); // system("pause");
    }
}

/**
 * @brief 磁盘空间释放, 找到对应的磁盘分区块，直接将其useFlag改为false
 *
 * @param startPostion 表示文件在整个磁盘空间中的起始位置
 */
void freeDisk(int startPostion)
{
    diskNode *p;
    for (p = diskHead; p != NULL; p = p->next)
    {
        if (p->start == startPostion)
            break;
    }
    p->useFlag = false;//找到对应的磁盘分区块，直接将其改为
}

/**
 * @brief 删除文件
 *
 * @param fileName
 */
void fileDel(char fileName[])
{
    UFD *p, *temp;
    UFD *q; 
    q = userTable[userID].user;//表示用户目录的头指针
    p = q->next;//表示用户目录下第二项
    //先找到对应的文件
    while (p)
    {
        if (!strcmp(p->file->fileName, fileName))
            break;
        else
        {
            p = p->next;
            q = q->next;
        }
    }
    //找到文件后进行操作
    if (p)
    {
        if (p->file->openFlag != true) //先判断是否有进程打开该文件
        {
            temp = p;
            q->next = p->next;//从用户目录的链表中进行删除
            freeDisk(temp->file->start); //磁盘空间回收
            free(temp);
            printf("文件删除成功\n");
            sleep(1); // system("pause");
        }
        else
        {
            printf("该文件已被进程打开,删除失败\n");
            sleep(1); // system("pause");
        }
    }
    else
    {
        printf("没有找到该文件,请检查输入的文件名是否正确\n");
        sleep(1); // system("pause");
    }
}
/**
 * @brief 读文件
 *
 * @param fileName
 */
void fileCat(char fileName[])
{
}

void fileWrite(char fileName[])
{
}

/**
 * @brief 查询文件
 *
 * @param fileName
 */
void fileFine(char fileName[])
{
}
/**
 * @brief 修改文件的读写方式
 *
 * @param fileName
 * @param kind
 */
void chmod(char fileName[], char kind[])
{
}
/**
 * @brief 重命名文件
 *
 * @param fileName
 * @param name
 */
void fileRen(char fileName[], char name[])
{
}
/**
 * @brief 显示某一用户的所有文件
 *
 * @param userName
 */
void fileDir(char userName[])
{
}

/**
 * @brief 显示磁盘使用情况
 *
 */
void diskShow()
{
    diskNode *p;
    int i = 0, unusedDisk = 0;
    printf("***************************************************************************\n");
    printf("  盘块号    起始地址       容量(byte)   是否已被使用\n");
    for (p = diskHead; p != NULL; p = p->next, i++)
    {
        if (p->useFlag == false)
            unusedDisk += p->maxlength;
        printf("   %d         %d              %d          %d     \n", i, p->start, p->maxlength, p->useFlag);
    }
    printf("***************************************************************************\n");
    printf("磁盘空间总容量：512*1024Bytes  已使用：%dBytes   末使用：%dBytes\n\n", MaxDisk - unusedDisk,
           unusedDisk);
    sleep(1); // system("pause");
}
/**
 * @brief 关闭已打开的文件
 *
 * @param fileName
 */
void fileClose(char fileName[])
{
}
