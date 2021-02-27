/* 用于演示结构体相关的功能 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 测试C语言struct用法详解 */
void testStruct()
{
    struct Student
    {
        char *name;
        int num;
        int age;
        char group;
        float fenshu;
    } stu2, stu1 = {"Tome", 12, 34, 'B', 120.4}; //定义结构体时,定义变量
    struct Student stu3, stu4;                   //在函数内部声明变量

    stu3.name = "张三";
    stu3.num = 21;
    stu3.age = 22;
    stu3.group = 'A';
    stu3.fenshu = 100;
    printf("stu1.name : %s , stu1.num : %d , stu1.age : %d , stu1.group : %c , stu1.fenshu :%f\n", stu1.name, stu1.num, stu1.age, stu1.group, stu1.fenshu);
}

/* 测试C语言结构体数组 */
void testStructArray()
{
    struct Student
    {
        char *name;
        int num;
        int age;
        char group;
        float score;
    } students[7] = {{"Li ping", 5, 18, 'C', 145.0},
                     {"Zhang ping", 4, 19, 'A', 130.5},
                     {"He fang", 1, 18, 'A', 148.5}};
    //定义数组的两种形式
    //也可以在定义数组时直接赋值
    struct Student ss[3] = {{"Li ping", 5, 18, 'C', 145.0},
                            {"Zhang ping", 4, 19, 'A', 130.5},
                            {"He fang", 1, 18, 'A', 148.5}};

    //数组只有在定义的时候才能直接赋值,否则就只有挨个元素中，挨个成员变量的进行赋值
    /* students[0] = {{"Li ping", 5, 18, 'C', 145.0};
    students[1] = {"Z ping", 5, 18, 'C', 145.0};
    students[2] = {"P ping", 5, 18, 'C', 145.0};
    students[3] = {"D ping", 5, 18, 'C', 145.0};
    students[4] = {"S ping", 5, 18, 'C', 145.0}; */
    printf("ss[1].name : %s \n", ss[1].name);
}

struct Stu
{
    char *name;  //姓名
    int num;     //学号
    int age;     //年龄
    char group;  //所在小组
    float score; //成绩
} stu1 = {"Tom", 12, 18, 'A', 136.5}, *spointer = &stu1;

void average(struct Stu *sp, int len);

/* 测试C语言的结构体指针 */
void testStructPointer()
{
    //两种定义结构体指针的方式，一种使在定义结构体时直接定义指针变量
    struct Stu *sp = &stu1;

    //sp->num 和 (*sp).num效果一样
    printf("通过结构体指针获取对象变量 name : %s , num : %d\n", (*sp).name, (*sp).num);
    printf("通过结构体指针获取对象变量 name : %s , num : %d\n", sp->name, sp->num);

    //结构体数组指针的使用
    struct Stu ss[] = {{"A ping", 5, 18, 'C', 145.0},
                       {"B ping", 5, 18, 'C', 142.0},
                       {"C ping", 5, 18, 'C', 135.5},
                       {"D ping", 5, 18, 'C', 1235.0},
                       {"E ping", 5, 18, 'C', 148.0}};
    *sp = ss[0];
    printf("通过结构体指针获取对象变量 name : %s , num : %d\n", ss[0].name, ss[0].num);
    sp = ss;
    for (int i = 0; i < sizeof(ss) / sizeof(struct Stu); i++)
    {
        printf("通过结构体指针获取对象 %d, name : %s , num : %d,score : %f \n", i, (sp + i)->name, (sp + i)->num, (*(sp + i)).score);
    }

    //结构体指针作为函数参数的使用
    int len = sizeof(ss) / sizeof(struct Stu);
    average(ss, len);
}

void average(struct Stu *sp, int len)
{
    float average;
    float sum;
    for (int i = 0; i < len; i++)
    {
        sum += sp->score;
    }
    average = sum / len;
    printf("平均分数为 average : %f \n", average); //这里不能乱用类型转换啊
}

/* 测试C语言的枚举类型 */
void testEnum()
{
    enum Week
    {
        Mon = 1,
        Tues,
        Wed,
        Thurs
    };
    printf("Mon : %d ,Tues : %d ,Wed : %d ,Thurs : %d\n", Mon, Tues, Wed, Thurs);
}

/* 测试C语言的公用体 */
void testUnion()
{
}

int main()
{
    //10.1C语言struct用法详解
    printf("\n\n10.1C语言struct用法详解\n");
    testStruct();

    //10.2C语言结构体数组
    printf("\n\n10.2C语言结构体数组\n");
    testStructArray();

    //10.3测试C语言的结构体指针
    printf("\n\n10.3测试C语言的结构体指针\n");
    testStructPointer();

    //10.4C语言枚举类型
    printf("\n\n10.4C语言枚举类型\n");
    testEnum();

    //10.5C语言共用体
    printf("\n\n10.5C语言共用体\n");
    testUnion();

    return 0;
}