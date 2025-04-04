#include <stdio.h>

int my_strlen(char* s)
{
    int count = 0;
    if (*s != '\0')
    {
        count++;
        s++;
    }
    return 0;
}

int main()
{
    int a1 = 100;
    int arr1[10] = { 0 };
    int* pa1 = &a1; //pa是专门用来存放地址的,这里的pa就被称为指针变量
    //指针的大小在32位平台是4个字节，在64位平台是8个字节
    printf("%p\n", &a1); //0000007996fffb0c
    printf("%d\n", a1);


    //指针+-整数(指针类型的意义)
    int a2 = 0x11223344;
    //int*的指针解引用访问4个字节
    int* pa2 = &a2;   //pa2地址为44 33 22 11
    printf("%p\n", pa2); //000000933b7ffdec
    printf("%p\n", pa2 + 1); //000000933b7ffdf0
    *pa2 = 0;   //pa2地址变为00 00 00 00
    //char*的指针解引用访问1个字节
    //char* pa3 = &a2;   //44 33 22 11
    //printf("%p\n", pa3); //000000933b7ffdec
    //printf("%p\n", pa3 + 1); //000000933b7ffded
    //*pa3 = 0;   //00 33 22 11


    //野指针
    //int* p1;//局部变量指针未初始化，默认为随机值
    //int *p1 = 20;
    //指针越界访问
    int arr2[10] = { 0 };
    int* p = arr2;
    int i = 0;
    for (i = 0; i <= 11; i++)
    {
        //当指针指向的范围超出数组arr的范围时，p就是野指针
        *(p++) = i;
    }


    //指针运算
    //不使用下标访问数组
    int arr3[10] = { 0 };
    int* p3 = &arr3[0];
    int sz = sizeof(arr3) / sizeof(arr3[0]);
    for (int i = 0; i < sz; i++)
    {
        *p3 = i;
        p3++;
    }
    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr3[i]);
    }

    char arr4[] = "abcdef";
    int len = my_strlen(arr4);
    printf("%d\n", len);


    //指针和数组
    int arr5[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int sz1 = sizeof(arr5) / sizeof(arr5[0]);
    int* p4 = arr5;
    for (int i = 0; i < sz1; ++i)
    {
        printf("%p == %p\n", p4 + i, &arr5[i]);
    }


    //二级指针
    int a3 = 0;
    int* p5 = &a3; //p5是一级指针变量,指针变量也是变量,变量是在内存中开辟空间的,是变量就有地址
    int** pp5 = &p5; //pp5就是二级指针变量,二级指针变量就是用来存放一级指针变量的地址
    int*** ppp5 = &pp5;


    // 指针数组
    int arr6[] = { 1,2,3,4,5 };
    int arr7[] = { 2,3,4,5,6 };
    int arr8[] = { 3,4,5,6,7 };
    int* parr[] = { arr6,arr7,arr8 }; //模拟,可看为二维数组
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%d ", parr[i][j]); //和下句等同
            //printf("%d ",*(parr[i] + j));
        }
        printf("\n");
    }
    return 0;
}
