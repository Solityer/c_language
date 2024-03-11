#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void Print1(int arr[3][5], int r, int c);
void Print2(int(*p)[5], int r, int c);
void test1(int arr[5], int sz);
void test2(int* p, int sz);
void test3(int arr[3][5], int r, int c);
void test4(int(*p)[5], int r, int c);
int Add(int x, int y);

int main()
{
    //字符指针
    char ch = 'w';
    char* pc = &ch;
    printf("%p\n", pc);
    *pc = 'w';

    char arr1[] = "abcdef";
    const char* p = "abcdef"; //后面是常量字符串,需要加上const
    printf("%s\n", p);  //p放的是a的地址,从a开始以此向后打印字符串   //结果:abcdef
    printf("%c\n", *p);  //结果:a

    //面试题
    char str1[] = "hello bit.";
    char str2[] = "hello bit.";
    const char* str3 = "hello bit.";
    const char* str4 = "hello bit.";
    if (str1 == str2) //数组名是数组首元素的地址
        printf("str1 and str2 are same\n");
    else
        printf("str1 and str2 are not same\n"); //yep

    if (str3 == str4)
        printf("str3 and str4 are same\n");  //yep
    else
        printf("str3 and str4 are not same\n");




    // 指针数组
    int arr2[] = { 1,2,3,4,5 };
    int arr3[] = { 2,3,4,5,6 };
    int arr4[] = { 3,4,5,6,7 };
    int* parr1[] = { arr2,arr3,arr4 }; //模拟,可看为二维数组
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            printf("%d ", parr1[i][j]); //和下句等同
            //printf("%d ",*(parr1[i] + j));
        }
        printf("\n");
    }



    //数组指针
    /*整形指针    --  指向整形变量的指针,存放整形变量的地址的指针变量
     *浮点型指针  --  指向字符变量的指针,存放字符变量的地址的指针变量
     *数组指针    --  指向数组的指针,存放的是数组的地址的指针变量*/
     //int *p1[10];  //指针数组
     //int (*p2)[10];  //数组指针变量


     //数组名的理解
     /*数组名是首元素的地址
      *有2个例外:
      *1.sizeof(数组名),这里的数组名不是数组首元素的地址,数组名表示整个数组,sizeof(数组名)计算的是整个数组的大小,单位是字节
      *2.&数组名,这里的数组名表示整个数组,&数组名取出的是整个数组的地址
      *除此之外,所有地方的数组名都是数组是首元素的地址*/
    int arr5[10] = { 0 };
    printf("%p\n", arr5); //000000d747dffd60
    printf("%p\n", arr5 + 1); //000000d747dffd64

    printf("%p\n", &arr5[0]); //000000d747dffd60
    printf("%p\n", &arr5[0] + 1); //000000d747dffd64
    printf("%p\n", &arr5); //000000d747dffd60

    printf("%p\n", &arr5 + 1); //000000d747dffd88
    /*差28,16进制转换为十进制2*16^1+8*16^0=40,数组有10个字符,正好跳过整个数组40字节*/

    int arr6[10] = { 1,2,3,4,5,6,7,8,9 };
    //数组的地址,存储到数组指针变量
    int(*p6)[10] = &arr6; //p指针指向的是数组,用int类型定义


    int arr7[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int* p3 = arr7;
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", *(p3 + i));
    }
    int(*p4)[10] = &arr7;
    for (int i = 0; i < 10; i++)
    {
        //printf("%d ",*((*p4) + i));
        printf("%d ", (*p4)[i]);
    }



    //数组指针的使用,一般在二维数组上才方便
    /*二维数组传参,形参是二维数组的形式*/
    int arr8[3][5] = { 1,2,3,4,5,2,3,4,5,6,3,4,5,6,7 };
    Print1(arr8, 3, 5);
    Print2(arr8, 3, 5);

    //总结
    //数组参数、指针参数
    //一维数组传参，形参部分可以是数组,也可以是指针
    int arr9[5] = { 0 };
    test1(arr9, 5);
    test2(arr9, 5);
    //二维数组传参,形参部分可以是数组,也可以是指针
    char arr10[3][5] = { 0 };
    test3(arr10, 3, 5);
    test4(arr10, 3, 5);



    //函数指针
    printf("%p\n", &Add); //00007ff7dbce167e
    printf("%p\n", Add); //00007ff7dbce167e
    int (*pf)(int, int) = &Add;  //Add(x,y)
    //指针类型   x的类型  y的类型
    int arr11[10] = { 0 };
    int(*pa)[10] = &arr11; //arr是数组首元素地址,&arr是数组地址
    return 0;
}

void Print1(int arr[3][5], int r, int c)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void Print2(int(*p)[5], int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%d ", *(*(p + i) + j));
        }
        printf("\n");
    }
}

void test1(int arr[5], int sz)
{}
void test2(int* p, int sz)
{}
void test3(int arr[3][5], int r, int c)
{}
void test4(int(*p)[5], int r, int c)
{}

int Add(int x, int y)
{
    return x + y;
}