/*
    算法设计题第四题
    输入一个后缀表达式，计算其值
    后缀表达式因为没有运算符的优先级，所以比起算数表达式要简单的多
    后缀表达式计算思路(不需要判断各种运算符的优先级):
        先开辟一个栈，用于存储数字
        从左往右，挨个读取输入的字符，如果是数字，就直接压入数字栈
        如果是运算符，就数字栈中弹出顶部的两个数字，然后使用该运算符进行计算，将结果压入数字栈，同时该运算符可以抛弃了。
        然后继续读取下一个字符，如果是数字就压入数字栈，如果是运算符，就如上计算。
        直到读取到了结束符号，就可以退出了
    算数表达式计算思路(无括号的情况):
        先开辟两个栈，一个用于存储数字，一个用于存储运算符
        从左往右，挨个读取输入的字符，如果是数字，就直接压入数字栈。
        如果是运算符，判断判断符栈里面的运算符优先级，是否大于待入栈的运算符：
            如果符栈的顶部运算符优先级小，则该运算符可以入栈;
            如果符栈的顶部运算符优先级大，就从数字栈里取出顶部的两个元素计算结果，结果入数字栈,同时符栈顶部的运算符可以抛弃了
                继续待入栈的运算符，用来继续和符栈顶部运算符比较，如上。。。。
        直到读取到终止符为止。
    算数表达式计算思路(有括号的情况):
        和无括号的情况类似，不同的是，括号的优先级判断有点麻烦；
            如果是"("要入符号栈时，该"("大于任何运算符的优先级，可以直接入栈，
            但是在"("后入栈的运算符优先级又都比"("大, 可以直接入栈, 直到运算符")"出现，该")"的优先级又比任何运算符优先级小,
            ")"要入符号栈时，就会把"("和")"之间的符号清掉，同时结果入数字栈

 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int top; //指向栈顶的索引(初始状态下指向-1)
} SqStack;

/* 
    初始化
 */
bool InitStack(SqStack *sq)
{
    if (sq == NULL)
        return false;
    sq->top = -1;
    return true;
}

/* 
    插入元素为新的栈顶元素
 */
bool push(SqStack *sq, ElemType e)
{
    if (sq == NULL)
        return false;
    sq->data[++(sq->top)] = e;
    return true;
}

/* 
    删除栈顶元素，并返回其值
 */
ElemType pop(SqStack *sq)
{
    if (sq == NULL)
        return false;
    return sq->data[sq->top--];
}

/* 
    测试版只支持输入简单的后缀表达式 23 34 + 2 * $
 */
void test3_2_4()
{
    SqStack stack;
    InitStack(&stack);
    char *str = malloc(100);
    int num_1, num_2;
    while (true)
    {
        scanf("%s", str);
        if (strcmp(str, "$") == 0)
            break;
        // printf("这是输入的字符串: %s \n",str);
        if (strcmp(str, "+") == 0) //是运算符+
        {
            num_2 = pop(&stack);
            num_1 = pop(&stack);
            push(&stack, num_1 + num_2);
            printf("进入了循环 +\n");
        }
        else if (strcmp(str, "-") == 0) //是运算符-
        {
            num_2 = pop(&stack);
            num_1 = pop(&stack);
            push(&stack, num_1 - num_2);
            printf("进入了循环 -\n");
        }
        else if (strcmp(str, "*") == 0) //是运算符*
        {
            num_2 = pop(&stack);
            num_1 = pop(&stack);
            push(&stack, num_1 * num_2);
            printf("进入了循环 * \n");
        }
        else if (strcmp(str, "/") == 0) //是运算符/
        {
            num_2 = pop(&stack);
            num_1 = pop(&stack);
            push(&stack, num_1 / num_2);
            printf("进入了循环 / \n");
        }
        else
        { //其余的都当成数字处理
            printf("进入了else\n");
            int num = atoi(str);
            printf("这是输入的字符串转成的数字 %d \n", num);
            push(&stack, num);
        }
    }
    printf("最后计算出的结果 : %d \n", pop(&stack));
}

int main()
{
    test3_2_4();
    // char ss[100];
    // gets(ss);
    // printf("输入的数据 : %s \n",ss);

    // char * str = malloc(100);
    // while(strcmp(str,"$") != 0)
    // {
    //     scanf("%s",str);
    //     printf("输入数据 %s \n",str);
    // }
}