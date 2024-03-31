/**
 * @file Lab2.2.c
 * @author your name (you@domain.com)
 * @brief 完成OS的实验2.2
 * @version 0.1
 * @date 2022-04-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "greeting.h"
#define N 10

int main()
{
    char name[N];
    printf("your name , please : ");
    scanf("%s",name);
    greeting(name);
    exit(0);
}