#include <stdio.h>
#include <stddef.h>
#pragma pack(1)  //设置默认对齐数为1

struct SN
{
    char c; int i;
}sn1 = { 'q',100 }, sn2 = { .i = 200, .c = 'w' }; //声明类型的同时定义变量sn1 sn2,为全局变量

struct S
{
    double d;
    struct SN sn;
    int arr[10];
    int b;
};

struct S1
{
    char c1;
    int i;
    char c2;
};
struct S2
{
    int i;
    char c1;
    char c2;
};
struct S3
{
    double d; //8
    char c;  //1
    int c1;  //4
};
struct S4
{
    char c1;
    struct S3 s3;  //8 1 4中的最大值8
    double d;
};

struct S5
{
    char c1;
    int a;
    char c2;
};

struct S6
{
    int data[100];
    int num;
};
void print1(struct S6 tmp);
void print2(struct S6* ps6);


struct A
{
    int _a : 2; //位段,数字表示二进制位,单位是比特
    int _b : 5;
    int _c : 10;
    int _d : 30;
};

struct S7
{
    char a : 3;
    char b : 4;
    char c : 5;
    char d : 4;
};


enum Color
{
    RED,
    GREEN,
    BLUE
};  //枚举变量的声明


union Un  //联合类型的声明
{
    char c;
    int i;
};

int main() {
    /*结构体*/
    struct SN sn3; //定义结构体变量sn3,为局部变量
    printf("%c %d\n", sn2.c, sn2.i);

    //初始化：定义变量的同时赋初值
    struct S s = { 3.14,{'a',99},{1,2,3} };
    printf("%lf %c %d\n", s.d, s.sn.c, s.sn.i);
    for (int i = 0; i < 10; ++i)
    {
        printf("%d ", s.arr[i]);
    }

    //结构体内存对齐
    printf("%d\n", sizeof(struct S1));  //12?
    printf("%d\n", sizeof(struct S2));  //8?
    /* offsetof()可以计算结构体成员相较于结构体起始位置的偏移量*/
    printf("%d\n", offsetof(struct S1, c1)); //0
    printf("%d\n", offsetof(struct S1, i)); //4
    printf("%d\n", offsetof(struct S1, c2)); //8
    /*结构体内存对齐的规则:
     * 1.结构体的第一个成员永远放在相较于结构体变量起始位置的偏移量为0的位置
     * 2.从第二个成员开始往后的每个成员都要对齐到某个对齐数的整数倍处。
     *   对齐数:结构体成员自身的大小和默认对齐数的较小值.
     *   vs上默认对齐数是8.
     *   gcc没有默认对齐数,对齐数就是结构体成员的自身大小.
     * 3.结构体的总大小,必须是最大对齐数的整数倍
     *   最大对齐数:所有成员的对齐数中的最大值
     * 4.如果嵌套了结构体的情况，嵌套的结构体对齐到自己的最大对齐数的整数倍处,
     *   结构体的整体大小就是所有最大对齐数（含嵌套结构体的对齐数）的整数倍.
     * 总结:偏移是对齐数的最小值,结果是对齐数的最大值的整数倍*/
    printf("%d\n", sizeof(struct S3));  //16
    printf("%d\n", sizeof(struct S4));  //32
    printf("%d\n", sizeof(struct S5));  //设置默认对齐数后变成了6

    struct S6 s6 = { {1,2,3},100 };
    print1(s6);
    print2(&s6);


    /*位段*/
    printf("%d\n", sizeof(struct A));

    struct S7 s7 = { 0 };  //地址:00 00 00
    s7.a = 10;  //地址:02 00 00
    s7.b = 12;  //地址:62 00 00
    s7.c = 3;  //地址:62 03 00
    s7.d = 4;  //地址:62 03 04


    /*枚举*/
    enum Color c = GREEN; //枚举变量的创建和赋值
    printf("%d\n", RED);
    printf("%d\n", GREEN);
    printf("%d\n", BLUE);


    /*联合(共用体)*/
    //联合也是一种特殊的自定义类型,这种类型定义的变量也包含一系列的成员
    //特征是这些成员公用同一块空间(所以联合也叫共用体),所以地址是一样的
    printf("%d\n", sizeof(union Un));
    union Un un = { 0 };
    printf("%p\n", &un);
    printf("%p\n", &(un.i));
    printf("%p\n", &(un.c));


    return 0;
}

void print1(struct S6 tmp)
{
    printf("%d\n", tmp.num);
}
void print2(struct S6* ps6)
{
    printf("%d\n", ps6->num);
}
