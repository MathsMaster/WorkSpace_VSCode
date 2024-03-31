#include <stdio.h>
/**
 * @brief C语言和C++的区别
 *
 * @return int
 */
/*
struct Student
{
    char *name;
    int age;
    float score;
};

void display(Student stu)
{
    printf("%s的年龄 : %d , 成绩是 : %f \n", stu.name, stu.age, stu.score);
}

int main()
{
    Student stu1 ;
    stu1.name = "小明";
    stu1.age = 15;
    stu1.score = 12.4;
    display(stu1);
}
*/



class Student{
    public:
        char *name;
        int age;
        float score;
        void say()
        {
            printf("%s的年龄是 %d, score: %f\n",name,age,score);
        }

};

int main()
{
    Student stu;
    stu.name = "小明";
    stu.age = 15;
    stu.score = 23.45;
    stu.say();
}