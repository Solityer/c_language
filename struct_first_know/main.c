#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


//声明结构体类型
struct stu1
{
    //成员变量,是用来描述结构体对象的相关属性的
    char name[20];
    int age;
    char sex[5];
}s2, s3;  //s2,s3,s4就是结构体变量 --- 全局变量
struct stu1 s4 = { "zhangsan", 20,"男" };//初始化

struct AAA
{
    int a;
    char arr[10];
    int* p;
}a1 = { 100,"bit",NULL }; //结构体嵌套初始化
struct BBB
{
    char ch[10];
    struct AAA a2; //a也是结构变量
    double d;
};

struct CCC
{
    char name[20];
    int age;
};



struct S
{
    int data[1000];
    int num;
};
struct S s = { {1,2,3,4}, 1000 };
//结构体传参
void print1(struct S s)
{
    printf("%d\n", s.num);
}
//结构体地址传参
void print2(struct S* ps)
{
    printf("%d\n", ps->num);
}

//void set_CCC(struct CCC c);  //错误写法
void set_CCC(struct CCC* pc);
void print_CCC(struct CCC c);

int main() {
    struct  stu1 s1; //s1为局部变量
    //stu s5; //没有对结构体类型typeef,struct关键字不能省略
    struct AAA a3 = { .arr = "abc",.p = NULL, .a = 1 };  //.是用来找到成员变量的
    printf("%d %s %p\n", a3.a, a3.arr, a3.p); //结构成员访问操作符

    struct BBB b1 = { "hello",{20,"qqq",NULL},3.14 };
    printf("%s %d %s %p %.2lf\n", b1.ch, b1.a2.a, b1.a2.arr, b1.a2.p, b1.d);

    struct CCC c = { 0 };
    set_CCC(&c);
    print_CCC(c);



    //结构体传参
    print1(s); //传结构体
    print2(&s); //传地址

    return 0;
}

//void set_CCC(struct CCC c)  //错误写法
//{
//    c.age = 20;
//    //c.name = "zhangsan";  //错误写法
//    strcpy(c.name,"zhangsan"); //字符串拷贝
//}
void set_CCC(struct CCC* pc)
{
    (*pc).age = 20; //等同于 pc->age = 20;
    // c.name = "zhangsan";  //错误写法
    strcpy((*pc).name,"zhangsan"); //字符串拷贝
    //等同于strcpy(pc->name,"zhangsan");
}
void print_CCC(struct CCC c)
{
    printf("%s %d\n",c.name,c.age);
}