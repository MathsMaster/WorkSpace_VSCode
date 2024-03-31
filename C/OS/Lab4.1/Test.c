/**
 * @file Test.c
 * @author your name (you@domain.com)
 * @brief 使用消息队列来完成三个进程之间的通讯,两个进程之间进行剪刀石头布,分别把出的结果传递给裁判进程,由裁判进程进行判断
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "Utils.h"

struct Game
{
    long Type; //
    int Round; //表示石头剪子布
    
};

/**
 * @brief 往消息队列发送消息
 *
 * @param num 消息队列的id
 */
void result_send(int msgId)
{
    struct Game game;
    game.Type = 1;
    game.Round = rand() % 3;
    printf("当前的进程pid : %d , 消息队列的msgId : %d , Round : %d \n", getpid(), msgId, game.Round);
    msgsnd(msgId, &game, sizeof(int), 0);
}

/**
 * @brief 评判出拳的结果,-1A胜,0平局,1B胜
 *
 */
int result_announce(int a, int b)
{
    if ((a + 1 == b) || (a - 3) == b)
        return -1; // a胜b
    else if (a == b)
        return 0; //平局
    else
        return 1; // a负b
}

/**
 * @brief 统计每盘的胜负结果，并存入文件
 *
 * @param result_list 存放每一局的结果, -1A胜,0平局,1B胜
 * @param len 一共有多少局
 */
void writeFile(int *result_list, int len)
{
    int count_A = 0;                      // A胜的次数
    int count_B = 0;                      // B胜的次数
    int pingju = 0;                       //平局的次数
    FILE *fin = fopen("result.txt", "w"); //以写入权限打开文件
    if (fin == NULL)
        printf("文件打开失败\n");
    int i;
    for (i = 0; i < len; i++)
    {
        switch (result_list[i])
        {
        case -1: // A胜
            count_A++;
            fprintf(fin, "NO.%d : A 赢\n", i + 1);
            printf("NO.%d : A 赢\n", i + 1);
            break;
        case 0: //平局
            pingju++;
            fprintf(fin, "NO.%d : 平局\n", i + 1);
            printf("NO.%d : 平局\n", i + 1);
            break;
        case 1: // B胜
            count_B++;
            fprintf(fin, "NO.%d : B 赢\n", i + 1);
            printf("NO.%d : B 赢\n", i + 1);
            break;
        }
    }

    printf("\n 最终的结果是 A赢次数: %ds \n B赢次数:%ds \n 平局的次数: %d \n", count_A, count_B, pingju);
    fprintf(fin, "\n 最终的结果是 A赢次数: %ds \n B赢次数:%ds \n 平局的次数: %d \n", count_A, count_B, pingju);
    fclose(fin);
}

int main()
{
    int times = 100;   //表示比赛的总轮数
    int key1 = 1234; //表示消息队列的代号
    int key2 = 5678;
    int *result_list;
    pid_t pid1, pid2;
    int msgid1, msgid2;                      //创建两消息队列的返回值
    msgid1 = msgget(key1, IPC_CREAT | 0666); //创建一个消息队列,key1表示消息队列的代号,IPC_CREAT表示创建消息队列
    if (msgid1 == -1)                        //消息队列创建失败
    {
        printf("创建 1 号消息队列失败.....\n");
        fprintf(stderr, "创建消息队列失败\n"); //往一个文件中写入字符串
        exit(EXIT_FAILURE);
    }
    msgid2 = msgget(key2, IPC_CREAT | 0666);
    if (msgid2 == -1)
    {
        printf("创建 2 号消息队列失败.....\n");
        fprintf(stderr, "创建消息队列失败\n"); //往一个文件中写入字符串
        exit(EXIT_FAILURE);
    }
    printf("游戏开始,请输入比赛的轮数 : \n");
    // scanf("%d", &times);
    result_list = (int *)malloc(times * sizeof(int)); //创建个int型数组,用于存放比赛用存放比赛用的每一轮结果
    int i = 0;

    for (i; i < times; i++)
    {
        printf("第%d轮比赛开始......\n", i);
        printf("当前进程pid : %d \n", getpid());
        //这一行代码执行后,就会有两个进程同时开始执行,一个是父进程，一个是子进程
        pid1 = fork(); //创建一个选手1的线程,并且返回pid
        printf("返回的pid1 : %d \n", pid1);
        if (pid1 == 0) //表示当前进程创建成功,但是处在子进程的执行中
        {
            printf("进入1号子进程开始执行\n");
            srand((unsigned)time(0) * 3000); //生成随机数的种子
            result_send(msgid1);             //往消息队列1发送消息，消息在发送时生成
            printf("准备退出1号子进程....\n");
            exit(-1);
            printf("退出1号子进程\n"); //这行代码基本不会被执行
        }
        printf("当前进程pid : %d \n", getpid());

        //这一行代码执行后,又会有两个进程同时开始执行,一个是父进程，一个是子进程
        pid2 = fork(); //创建一个选手2的线程,并且返回pid
        printf("返回的pid2 : %d \n", pid2);
        if (pid2 == 0) //表示当前进程创建成功,但是处在子进程的执行中
        {
            printf("进入2号子进程开始执行\n");
            srand((unsigned)time(NULL) * i); //生成随机数的种子
            result_send(msgid2);             //往消息队列2发送消息，消息在发送时生成
            printf("准备退出2号子进程....\n");
            exit(-1);
            printf("退出2号子进程\n");
        }
        printf("当前进程pid : %d \n", getpid());
        if (pid1 < 0 || pid2 < 0) //表示进程创建失败
        {
            printf("创建进程失败\n");
            fprintf(stderr, "创建进程失败\n");
        }
        else //表示进程虽然创建成功了，但是当前是父进程在执行中
        {
            printf("当前进程pid : %d \n", getpid());
            printf("等待两个子进程退出 \n");
            wait(NULL); //等待两个子进程退出
            wait(NULL);
            printf("两个子进程已经退出..... \n");
            struct Game game1;
            struct Game game2;
            //从两个消息队列中接收两个子进程的消息
            msgrcv(msgid1, &game1, sizeof(game1) - sizeof(long), 0, 0); //这表示只接收Round的属性
            msgrcv(msgid2, &game2, sizeof(game2) - sizeof(long), 0, 0); //这表示只接收Round的属性
            printf("父进程中的 msgId1 : %d ,msgId2 : %d\n", msgid1, msgid2);
            printf("父进程从消息队列中收到的数据 game1->Round : %d , game2->Round : %d \n", game1.Round, game2.Round);
            //评判出拳结果
            int j = result_announce(game1.Round, game2.Round);
            result_list[i] = j; //记录这一局的谁赢
        }
    }
    //统计每盘的胜负结果,并将比赛结果写入文件
    writeFile(result_list, times);
    //删除消息队列
    if (msgctl(msgid1, IPC_RMID, 0) == -1) //表示删除消息队列失败
    {
        fprintf(stderr, "删除1号消息队列失败\n ");
    }
    if (msgctl(msgid2, IPC_RMID, 0) == -1) //表示删除消息队列失败
    {
        fprintf(stderr, "删除2号消息队列失败\n ");
    }
    exit(EXIT_SUCCESS);
}