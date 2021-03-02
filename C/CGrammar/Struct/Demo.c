/* 用于演示结构体相关的功能 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

/* 
    从测试结果来看,直接传递结构体对象,参数这里实际上也是复制了一份新的数据,使用的新的内存地址
 */
void modifyParam(struct Stu stu)
{
    printf("内部函数打印出的结构体对象地址  : %#X \n",&stu);
    stu.name = "小明";
    stu.age = 500;
    stu.score = 30000000.000;
    printf("内部函数修改后 ..... \n");
    printf("内部函数取值  stu.name : %s   stu.age : %d   stu.score %f \n",stu.name,stu.age,stu.score);
}

void modifyParamByPointer(struct Stu *stu)
{
    printf("内部函数打印出的结构体对象地址  : %#X \n",stu);
    stu->name = "小明";
    stu->age = 500;
    stu->score = 30000000.000;
    printf("内部函数修改后 ..... \n");
    printf("内部函数取值  stu->name : %s   stu->age : %d   stu->score %f \n",stu->name,stu->age,stu->score);
}

/* 
    测试结构体对象不使用指针的情况下;
    作为参数传递时，在函数中能取到值吗，同时在函数中直接修改能有效吗
 */
void testStructParam()
{
    struct Stu stu;
    printf("外部函数打印出的结构体对象地址  : %#X \n",&stu);
    printf("赋值前 ..... \n");
    printf("外部函数  stu.name : %s   stu.age : %d   stu.score %f \n",stu.name,stu.age,stu.score);
    stu.name = "Hello World";
    stu.age = 22;
    stu.score = 120;
    printf("赋值后 ..... \n");
    printf("外部函数  stu.name : %s   stu.age : %d   stu.score %f \n",stu.name,stu.age,stu.score);
    modifyParamByPointer(&stu);
    printf("外部函数取值 stu.name : %s   stu.age : %d   stu.score %f \n",stu.name,stu.age,stu.score);
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
    //C语言里竟然没法直接对字符数组赋值

    //定义结构体，并在其中定义共用体
    struct
    {
        char name[20];
        int num;
        char sex;
        char profession;
        union
        {
            float score;
            char course[20];
            char *miaosu;
        } sc;
    } boys[2] = {{"xiaohong", 123, 'a', 'd'}, {"lanlan", 123, 'a', 'd'}};

    //共用体里面的变量,都是占据的同一块内存,修改其中一个变量,会影响另一个变量的值
    boys[0].sc.score = 123;
    printf("name : %s , sc.score : %f \n", boys[0].name, boys[0].sc.score);
    strcpy(boys[1].sc.course, "Hello World!");
    printf("name : %s , sc.course : %s \n", boys[1].name, boys[1].sc.course);
    boys[1].sc.miaosu = "asdasdasdasdasdasdasd";
    printf("miaosu : %s , sc.course : %s \n", boys[1].sc.miaosu, boys[1].sc.course);
}

/* C语言位域（位段） */
void testWeiYu()
{
    //一种只有几个bit长度的变量
    struct BS
    {
        unsigned m;
        unsigned n : 4;
        unsigned char ch : 6;
    };

    struct BS b = {0xad, 0x0d, '1'};
    printf("m :  %#X , n : %#X , ch : %c \n", b.m, b.n, b.ch);
}

/* 用来测试typedef的用法 */
void testTypedef()
{
    //给基本数据类型起别名
    typedef int INTEGER;
    //给数组取别名
    typedef char array[20]; //array就是char[20]数组了

    //给结构体取别名
    typedef struct stu
    {
        char name[20];
        int age;
        char sex;
    } STU;
    typedef struct
    {
        char name[20];
        int age;
        char sex;
    } SSTU;

    int(*p)[4]; //二维数组的指针
    //为二维数组指针类型取别名
    typedef int(*ppp)[4]; //给二维数组的指针int (*p)[4],取别名 ppp

    //为函数指针类型定义别名
    typedef int (*PTR_TO_FUNC)(int, int);
}

/* C语言const的用法 */
void testConst()
{
    //类似于Java中的final,定义后不能修改
    const int MAX = 100;
    // MAX = 12;

    //这两种使用const实际上修饰的是 指针所指向的数据空间，指向的数据没法修改，但指针却可以指向别的空间
    const int *p1;
    int const *p2;
    //这种则是const 修饰的指针本身，指针的地址没法修改，也就是说没法在指向别的空间了，但指向的数据却可以修改
    int *const p3;

    //指针本身指向的数据不能被修改，指针的指向也不能别修改
    const int *const p4;
    int const *const p5;
}


/* 测试C语言的随机数 */
void testRandom()
{
    int i = rand();//这个随机数有问题，每次的值都一样，因为生成随机数的种子都是一样的
    printf("获取一个随机数 i ： %d\n",i);

    srand(time(NULL));//传进去一个新的种子,种子就是当前时间的值

    int a = rand();//
    printf("修改种子后再次获取一个随机数 a ： %d\n",a);
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

    //10.3.1测试C语言的结构体作为参数传递的效果
    printf("\n\n10.3.1测试C语言的结构体作为参数传递的效果\n");
    testStructParam();

    //10.4C语言枚举类型
    printf("\n\n10.4C语言枚举类型\n");
    testEnum();

    //10.5C语言共用体
    printf("\n\n10.5C语言共用体\n");
    testUnion();

    //10.7C语言位域（位段）
    printf("\n\n10.7C语言位域（位段）\n");
    testWeiYu();

    //11.1用来测试typedef的用法
    printf("\n\n11.1用来测试typedef的用法\n");
    testTypedef();

    //11.2C语言const的用法
    printf("\n\n11.2C语言const的用法\n");
    testConst();

    //11.3C语言的随机数
    printf("\n\n11.3C语言的随机数\n");
    testRandom();

    return 0;
}