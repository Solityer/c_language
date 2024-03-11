#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Add(int x, int y);
int Sub(int x, int y);
int Mul(int x, int y);
int Div(int x, int y);
void Menu();
void Calc(int (*pf5)(int, int));

void qsort
(
    void* base,  //指向了需要排序的第一个元素
    size_t num,  //排序元素的个数
    size_t size,  //一个元素的大小,单位是字节
    int (*compar)(const void*, const void*)  //函数指针类型--这个函数指针指向的函数,能够base指向数组中的两个元素
);

void print(int arr[], int sz);

void test1();  //测试qsort排序整型
int compare_int(const void* p1, const void* p2);
/*void*指针 ---- 无具体类型的指针
 *这种类型的指针是不能直接解引用操作的,也不能直接进行指针运算
 *void*可以接收任何类型的地址*/

void test2();  //测试qsort排序结构体数据
struct Stu
{
    char name[20];
    int age;
};
int compare_stu_by_age(const void* p1, const void* p2);
void test3();
int compare_stu_by_name(const void* p1, const void* p2);

int main() {
    //函数指针的数组
    int (*pf1)(int, int) = Add;
    int (*pf2)(int, int) = Sub;
    int (*pf3)(int, int) = Mul;
    int (*pf4)(int, int) = Div;  //函数指针
    int (*pfarr[])(int, int) = { NULL,Add,Sub,Mul,Div }; //函数指针数组

    int x = 0;
    int y = 0;
    int ret = 0;
    /*常规写法*/
    int input1 = 0;
    do
    {
        Menu();
        printf("please select sum:");
        scanf("%d", &input1);
        switch (input1)
        {
        case 1:
            printf("please input two sum:");
            scanf("%d %d", &x, &y);
            ret = Add(x, y);
            printf("ret = %d\n", ret);
            break;
        case 2:
            printf("please input two sum:");
            scanf("%d %d", &x, &y);
            ret = Sub(x, y);
            printf("ret = %d\n", ret);
            break;
        case 3:
            printf("please input two sum:");
            scanf("%d %d", &x, &y);
            ret = Mul(x, y);
            printf("ret = %d\n", ret);
            break;
        case 4:
            printf("please input two sum:");
            scanf("%d %d", &x, &y);
            ret = Div(x, y);
            printf("ret = %d\n", ret);
            break;
        case 0:
            printf("Exit calculator!!\n");
            break;
        default:
            printf("Select error!!\n");
            break;
        }
    } while (input1);

    /*改进写法*/
    int input2 = 0;
    do
    {
        Menu();
        printf("please select sum:");
        scanf("%d", &input2);
        if (input2 >= 1 && input2 <= 4)
        {
            printf("please input two sum:");
            scanf("%d %d", &x, &y);
            ret = pfarr[input2](x, y);
            printf("ret = %d\n", ret);
        }
        else if (input2 == 0)
        {
            printf("Exit calculator!!\n");
            break;
        }
        else
        {
            printf("Select error!!\n");
        }
    } while (input2);


    //int (*(*p)[])(int, int) = &pfarr;  //p是指向函数指针数组的指针



    //回调函数
    int x3 = 0;
    int y3 = 0;
    int ret3 = 0;
    int input3 = 0;
    do
    {
        Menu();
        printf("please select sum:");
        scanf("%d", &input3);
        switch (input3)
        {
        case 1:
            Calc(Add);
            break;
        case 2:
            Calc(Sub);
            break;
        case 3:
            Calc(Mul);
            break;
        case 4:
            Calc(Div);
            break;
        case 0:
            printf("Exit calculator!!\n");
            break;
        default:
            printf("Select error!!\n");
            break;
        }
    } while (input3);


    //实例:冒泡排序
    int arr[10] = { 9,8,7,6,5,4,3,2,1,0 };
    int sz = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < sz - 1; i++)
    {
        for (int j = 0; j < sz - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    for (int i = 0; i < sz; i++)
    {
        printf("%d ", arr[i]);
    }

    /*qsot函数的特点:
     *1.快速排序的方法
     *2.适合与任何类型数据的排序*/
    test1();
    test2();
    test3();
    return 0;
}

int Add(int x, int y)
{
    return x + y;
}
int Sub(int x, int y)
{
    return x - y;
}
int Mul(int x, int y)
{
    return x * y;
}
int Div(int x, int y)
{
    return x / y;
}
void Menu()
{
    printf("****************************\n");
    printf("********1.add  2.sub********\n");
    printf("********3.mul  4.div********\n");
    printf("*********  0.exit  *********\n");
    printf("****************************\n");
}
void Calc(int (*pf5)(int, int))
{
    int x = 0;
    int y = 0;
    int ret = 0;
    printf("please input two sum:");
    scanf("%d %d", &x, &y);
    ret = pf5(x, y);
    printf("ret = %d\n", ret);
}
void print(int arr[], int sz)
{
    for (int i = 0; i < sz; i++)
    {
        printf("%d ", arr[i]);
    }
}
void test1()
{
    int arr[10] = { 3,1,5,2,4,7,9,6,8,0 };
    int sz = sizeof(arr) / sizeof(arr[0]);
    qsort(arr, sz, sizeof(arr[0]), compare_int);
    print(arr, sz);
}
int compare_int(const void* p1, const void* p2)
{
    return (*(int*)p1 - *(int*)p2);
}
void test2()
{
    struct Stu arr[] = { {"zhangsan",20},{"lisi",50},{"wangwu",15} };
    int sz = sizeof(arr) / sizeof(arr[0]);
    qsort(arr, sz, sizeof(arr[0]), compare_stu_by_age);
}
int compare_stu_by_age(const void* p1, const void* p2)
{
    (((struct Stu*)p1)->age - ((struct Stu*)p2)->age);
    return 0;
}
void test3()
{
    struct Stu arr[] = { {"zhangsan",20},{"lisi",50},{"wangwu",15} };
    int sz = sizeof(arr) / sizeof(arr[0]);
    qsort(arr, sz, sizeof(arr[0]), compare_stu_by_name);
}
int compare_stu_by_name(const void* p1, const void* p2)
{
    return strcmp(((struct Stu*)p1)->name, ((struct Stu*)p2)->name);
}