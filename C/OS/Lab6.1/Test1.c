/**
 * @file Test.c
 * @author your name (you@domain.com)
 * @brief 使用C语言中简单的文件操作函数,来实现对source.dat的读写复制功能
 *        再使用linux的函数,来实现对文件的读写复制功能
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    char buf;
    FILE *source, *backup;
    printf("当前项目的文件功能是基于 C Library....\n");
    //竟然不会像Java一样抛出异常来
    source = fopen("./source.dat", "r"); //以只读的权限打开文件
    backup = fopen("./target.dat", "w"); //以只写的权限打开文件

    if (source == NULL)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    if (backup == NULL)
    {
        printf("创建写入文件时失败\n");
        exit(1);
    }
    //进行文件的读写操作
    while (fread(&buf, sizeof(buf), 1, source) == 1)
    {
        //每读一个字节,就写入一个字节
        if (fwrite(&buf, sizeof(buf), 1, backup))
        {
            // printf("写入文件成功\n");
        }
        else
        {
            printf("写入文件失败\n");
        }
    }

    if (fclose(source) == 0)//关闭流成功，返回0，否则返回-1
    {
        printf("关闭输入流成功\n");
    }
    else
    {
        printf("关闭输入流失败\n");
    }

    if (fclose(backup) == 0)
    {
        printf("关闭输出流成功\n");
    }
    else
    {
        printf("关闭输出流失败\n");
    }
}