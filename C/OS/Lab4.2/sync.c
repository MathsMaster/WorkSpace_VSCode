/**
 * @file sync.c
 * @author your name (you@domain.com)
 * @brief 模拟一个生产者，一个消费者，同时往共享的内存里进行读写操作的问题。使用信号量的机制来进行线程同步
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define MAX 256

typedef int sem_t; //看来只能自定义信号量了
sem_t empty = 10;
sem_t full = 0;
sem_t mutex = 1;
int sem_init(sem_t *s, int i, unsigned int value)
{
    return 0;
}
int sem_wait(sem_t *s)
{
    while ((*s) <= 0)
        ;
    (*s)--;
}
int sem_post(sem_t *s)
{
    (*s)++;
}

int sem_destroy(sem_t *s)
{
    (*s) = 0;
}

char *buffer;
sem_t empty; //定义同步信号量
sem_t full;  //定义同步信号量
sem_t mutex; //定义户次信号量

void *producer()
{
    printf("线程producer开始执行....\n");
    printf("producer wait前empty : %d \n ", empty);
    printf("producer wait前mutex : %d \n ", mutex);
    //对两个信号量进行P操作,如果资源都>0,就直接往下走，否则当前线程就阻塞了
    sem_wait(&empty); // empty初值为10
    printf("producer wait后empty : %d \n ", empty);
    sem_wait(&mutex); // mutex初值为1
    printf("producer wait后mutex : %d \n ", mutex);
    printf("请输入一些东西进缓存里....\n");
    buffer = (char *)malloc(MAX);
    fgets(buffer, MAX, stdin); //从文件流中读取MAX个数据到buffer中
    //相当于把这两个信号量都+1
    sem_post(&mutex);
    sem_post(&full);
    printf("producer post后full : %d \n ", full);
    printf("producer post后mutex : %d \n ", mutex);
    printf("线程producer执行完毕....\n");
}

void *consumer()
{
    printf("线程consumer开始执行....\n");
    printf("consumer wait前full : %d \n ", full);
    printf("consumer wait前mutex : %d \n ", mutex);
    //对两个信号量进行P操作,如果资源都>0,就直接往下走，否则当前线程就阻塞了
    sem_wait(&full); // full初值为0
    printf("consumer wait后full : %d \n ", full);
    sem_wait(&mutex); // mutex初值为1
    printf("consumer wait后mutex : %d \n ", mutex);
    printf("从内存中读取产品  buffer : %s \n", buffer);
    memset(buffer, 0, MAX); //使用0来填充buffer
    //相当于把这两个信号量都+1
    sem_post(&mutex);
    sem_post(&empty);
    printf("consumer post后empty : %d \n ", empty);
    printf("consumer post后mutex : %d \n ", mutex);
    printf("线程consumer执行完毕....\n");
}

//这里使用的是POSIX信号量机制
int main()
{
    pthread_t id_producer;
    pthread_t id_consumer;
    int ret;
    //设置三个信号量的初始值

    ret = sem_init(&empty, 0, 10); //设置empty初值为10
    ret = sem_init(&full, 0, 0);   //设置full初值为0
    ret = sem_init(&mutex, 0, 1);  //设置mutex初值为1

    printf("创建线程之前 ret : %d \n", ret);
    //创建生产者进程和消费者进程
    ret = pthread_create(&id_producer, NULL, producer, NULL);
    ret = pthread_create(&id_consumer, NULL, consumer, NULL);
    printf("创建线程之后 ret : %d \n", ret);
    printf("join线程...\n");
    pthread_join(id_producer, NULL); //阻塞等待对应线程结束
    pthread_join(id_consumer, NULL);
    printf("删除信号量...\n");
    //删除三个信号量
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    printf("end...");
}