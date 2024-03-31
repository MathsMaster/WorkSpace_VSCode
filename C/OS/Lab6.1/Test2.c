/**
 * @file Test2.c
 * @author
 * @brief 使用Linux的系统函数open,read,write,close，来完成文件的读写操作
 * @version 0.1
 * @date 2022-05-06
 */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAXSIZE 1024 //定义常量

int main()
{
    char buf[MAXSIZE];
    int source, backup; //
    int size;
    printf("当前项目是基于 Linux system calls.\n");
    //打开文件，返回一个文件描述符,失败就返回-1
    source = open("./source.dat", O_RDONLY); //以只读权限打开文件
    backup = open("./target.dat", O_WRONLY | O_CREAT, 0644);
    if (source == -1)
    {
        printf("打开源文件失败\n");
        exit(1);
    }
    if (backup == -1)
    {
        printf("打开目标文件失败\n");
        exit(1);
    }

    //返回值size表示实际读入的长度
    while((size = read(source,buf,MAXSIZE)) >0)
    {
        //返回值为实际写入的长度
        if(write(backup,buf,size) != size)
        {
            printf("写入文件时出现错误 \n");
			exit(1);
        }else{
            printf("写入数据成功 \n");
        }
    }

    if(size < 0)
    {
        printf("读取源文件失败 \n");
    }else{
        printf("读取源文件成功 \n");
    }

    //关闭失败就返回-1，成功就返回0
    if(close(source) == 0)
    {
        printf("关闭源文件成功 \n");
    }else{
        printf("关闭源文件失败 \n");
    }

    if(close(backup) == 0)
    {
        printf("关闭目标文件成功 \n");
    }else{
        printf("关闭目标文件失败 \n");
    }
}