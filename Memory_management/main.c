/*动态内存管理*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>

void GetMemory1(char** p);
void Test1(void);
char* GetMemory2(void);
void Test2(void);
void GetMemory3(char** p, int num);
void Test3(void);
void Test4(void);

int main() {
    /*malloc和free*/
    //int arr[10]; //40个字节
    //malloc只分配空间,不初始化空间
    int* p1 = (int*)malloc(40);  //malloc默认指针类型是void*类型
    if (p1 == NULL)
    {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", *(p1 + i));
    }
    free(p1);  //free函数用来释放动态开辟的内存。
    p1 = NULL;


    /*calloc*/  //void* calloc (size_t num, size_t size);
    //calloc既分配空间,又初始化空间
    int* p2 = (int*)calloc(10, sizeof(int));
    if (p2 == NULL)
    {
        perror("calloc");
        return 1;
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", p2[i]);
    }
    free(p2);  //free函数用来释放动态开辟的内存。
    p2 = NULL;


    /*realloc*/   //void* realloc (void* ptr, size_t size);  将初始指针ptr增加zize字节大小
    int* p3 = (int*)malloc(40);
    if (p3 == NULL)
    {
        perror("malloc");
        return 1;
    }
    //初始化1~10
    for (int i = 0; i < 10; ++i)
    {
        p3[i] = i + 1;
    }
    printf("\n");
    //增加一些空间
    int* ptr = (int*)realloc(p3, 80);  //将p3指针增加80个字节大小
    if (ptr != NULL)
    {
        p3 = ptr;
        ptr = NULL;
    }
    else
    {
        perror("realloc");
        return 1;
    }
    for (int i = 0; i < 30; ++i)
    {
        printf("%d\n", p3[i]);
    }
    free(p3);
    p3 = NULL;



    /*笔试题目*/
    Test1();
    Test2();
    Test3();
    Test4();
    return 0;
}
void GetMemory1(char** p)
{
    //p = (char*)malloc(100);
    *p = (char*)malloc(100);
}
void Test1(void)
{
    char* str = NULL;
    GetMemory1(&str);
    strcpy(str, "hello world");
    printf(str);
    free(str);
    str = NULL;
}

char* GetMemory2(void)
{
    char p[] = "Hello world";
    return p;
}
void Test2(void)
{
    char* str = NULL;
    str = GetMemory2();  //记住了指针,但指向的空间在出局部时被销毁了,变成了野指针
    printf(str);
}

void GetMemory3(char** p, int num)
{
    *p = (char*)malloc(num);
}
void Test3(void)
{
    char* str = NULL;
    GetMemory3(&str, 100);
    strcpy(str, "hello");
    printf(str);
    free(str);
    str = NULL;
}

void Test4(void)
{
    char* str = (char*)malloc(100);
    strcpy(str, "hello");
    free(str);
    str = NULL;
    if (str != NULL)
    {
        strcpy(str, "world");
        printf(str);
    }
}