#include <stdio.h>
#include <stdlib.h> // 标准头文件，包含 malloc, free, calloc, realloc
#include <string.h>
#include <limits.h>

/* =====================================================================================
   Part 1: 基础 API 使用演示 (malloc, calloc, realloc)
   ===================================================================================== */

void Demo_Malloc(void)
{
    printf("\n=== [Demo_Malloc] Start ===\n");

    // malloc(size_t size): 只负责在堆区分配指定大小的字节，不会初始化内容
    // 此时内存中的值是随机的（垃圾值）
    int *p = (int *) malloc(10 * sizeof(int)); // 申请存放10个int的空间

    // 1. 检查有效性：动态内存申请可能失败（如内存耗尽），必须检查 NULL
    if (p == NULL)
    {
        perror("malloc failed");
        return;
    }

    // 2. 使用内存
    for (int i = 0; i < 10; i++)
    {
        *(p + i) = i; // 指针运算访问
    }

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", p[i]); // 数组下标形式访问
    }
    printf("\n");

    // 3. 释放内存
    free(p); // 归还空间给操作系统

    // 4. 避免野指针：释放后 p 仍然指向那块地址，但已无权访问，必须置空
    p = NULL;
    printf("=== [Demo_Malloc] End ===\n");
}

void Demo_Calloc(void)
{
    printf("\n=== [Demo_Calloc] Start ===\n");

    // calloc(size_t num, size_t size): 分配 num * size 字节
    // 特性：自动将分配的内存初始化为 0 (按位清零)
    int *p = (int *) calloc(10, sizeof(int));

    if (p == NULL)
    {
        perror("calloc failed");
        return;
    }

    // 验证是否初始化为0
    printf("Verify calloc init: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");

    free(p);
    p = NULL;
    printf("=== [Demo_Calloc] End ===\n");
}

void Demo_Realloc(void)
{
    printf("\n=== [Demo_Realloc] Start ===\n");

    // 1. 先申请小块内存
    int *p = (int *) malloc(5 * sizeof(int));
    if (p == NULL)
    {
        perror("malloc failed");
        return;
    }
    for (int i = 0; i < 5; ++i)
    {
        p[i] = i + 1;
    }

    // 2. 空间不够，希望扩容到 10 个 int
    // realloc(void* ptr, size_t size):
    // - 情况A (原地扩容): 原内存块后面有足够空间，直接延长，返回原地址。
    // - 情况B (异地扩容): 后面空间不够，在堆区找新空间，拷贝原数据，自动释放原空间，返回新地址。
    // - 失败: 返回 NULL，原数据不丢失。

    printf("Expanding memory...\n");
    int *ptr = (int *) realloc(p, 10 * sizeof(int));

    if (ptr != NULL)
    {
        p = ptr; // 只有扩容成功，才更新指针 p
        ptr = NULL;
    }
    else
    {
        perror("realloc failed");
        // 这里不能直接退出，因为 p 指向的原内存还在，需要后续处理或释放
    }

    // 初始化新增的部分
    for (int i = 5; i < 10; i++)
    {
        p[i] = i + 100;
    }

    for (int i = 0; i < 10; ++i)
    {
        printf("%d ", p[i]);
    }
    printf("\n");

    // 特殊用法：realloc(NULL, size) 等同于 malloc(size)

    free(p);
    p = NULL;
    printf("=== [Demo_Realloc] End ===\n");
}

/* =====================================================================================
   Part 2: 经典笔试题解析 (考察指针传递、栈内存销毁、野指针)
   ===================================================================================== */

// ---------------- 题目 1: 值传递 vs 地址传递 ----------------

// 错误写法示意：
// void GetMemory_Wrong(char* p) { p = (char*)malloc(100); }
// 解释：如果传入 char* str，这里 p 是 str 的一份拷贝。
// 修改 p 的指向（指向堆内存），并不会改变外面的 str（依然是 NULL）。
// 结果：str 仍为 NULL，且 malloc 的内存泄漏。

// 正确写法：使用二级指针
void GetMemory1(char **p)
{
    *p = (char *) malloc(100); // 解引用 p，直接修改外部的指针变量
}

void Test1(void)
{
    printf("\n--- Test1: Pass by Reference ---\n");
    char *str = NULL;
    GetMemory1(&str); // 传址
    if (str != NULL)
    {
        strcpy(str, "hello world");
        printf("%s\n", str);
        free(str);
        str = NULL;
    }
}

// ---------------- 题目 2: 返回栈空间地址 ----------------

char *GetMemory2(void)
{
    // p 是数组，存储在栈区(Stack)
    char p[] = "Hello world";
    return p;
    // 函数结束，栈帧销毁，p 所属的内存被系统回收。
    // 此时返回的地址虽然没变，但里面的内容已经是不确定的了。
}

void Test2(void)
{
    printf("\n--- Test2: Return Stack Memory (Bug Demo) ---\n");
    char *str = NULL;
    str = GetMemory2();
    // str 变成了野指针。打印它可能乱码，也可能侥幸显示原值（取决于栈是否被覆盖），
    // 但这是极度危险的未定义行为。
    printf("Result (Undefined Behavior): %s\n", str);
}

// ---------------- 题目 3: 内存泄漏隐患 ----------------

void GetMemory3(char **p, int num)
{
    *p = (char *) malloc(num);
}

void Test3(void)
{
    printf("\n--- Test3: Good logic but check leaks ---\n");
    char *str = NULL;
    GetMemory3(&str, 100);
    if (str != NULL)
    {
        strcpy(str, "hello");
        printf("%s\n", str);

        // 记得释放
        free(str);
        str = NULL;
    }
}

// ---------------- 题目 4: 释放后使用 (Use After Free) ----------------

void Test4(void)
{
    printf("\n--- Test4: Use After Free (Bug Demo) ---\n");
    char *str = (char *) malloc(100);
    strcpy(str, "hello");
    free(str); // str 指向的内存已归还
    str = NULL; // 这是一个好习惯，置空防止误用

    if (str != NULL)
    {
        // 如果上面没有 str = NULL，这里就会发生非法访问
        strcpy(str, "world");
        printf(str);
    }
    else
    {
        printf("Safe! str is NULL, prevented illegal access.\n");
    }
}

/* =====================================================================================
   Part 3: 常见内存错误合集 (Crash 演示)
   注意：这些函数包含严重错误，实际运行时会导致程序崩溃或未定义行为。
   ===================================================================================== */

// 错误1: 对 NULL 指针解引用
void Error_NullPointerDereference(void)
{
    printf("Running Error: Null Pointer Dereference...\n");
    // 申请巨大空间导致 malloc 失败返回 NULL (模拟失败)
    // int* p = (int*)malloc(INT_MAX);
    // 或者直接模拟：
    int *p = (int *) malloc(INT_MAX * 4);

    // 如果不判断 if (p == NULL) 直接使用：
    *p = 20; // CRASH! 写入访问权限冲突
    free(p);
}

// 错误2: 动态内存越界访问
void Error_OutOfBounds(void)
{
    printf("Running Error: Out Of Bounds...\n");
    int *p = (int *) malloc(10 * sizeof(int));
    if (p == NULL)
        return;

    // 申请了 10 个，下标是 0-9
    for (int i = 0; i <= 10; i++)
    {
        // i=10 时越界
        p[i] = i; // 当 i=10，这属于堆溢出(Heap Overflow)，可能破坏 malloc 的头部信息
    }

    // free 时通常会检查头部信息，如果越界破坏了头部，free 也会报错
    free(p);
}

// 错误3: free 释放非动态开辟的内存
void Error_FreeStackMemory(void)
{
    printf("Running Error: Free Stack Memory...\n");
    int a = 10;
    int *p = &a;
    free(p); // CRASH! 栈内存不能由 free 管理
}

// 错误4: free 释放动态内存的一部分 (指针位置不对)
void Error_FreePartMemory(void)
{
    printf("Running Error: Free Part of Memory...\n");
    int *p = (int *) malloc(100);
    if (p == NULL)
        return;

    p++; // 指针移动了

    // 此时 p 不再指向内存块的起始位置。
    // free 需要读取指针偏移量之前的元数据(metadata)来知道释放多少大小。
    // 指针不对，读到的元数据是错的。
    free(p); // CRASH!
}

// 错误5: 对同一块内存多次释放 (Double Free)
void Error_DoubleFree(void)
{
    printf("Running Error: Double Free...\n");
    int *p = (int *) malloc(100);
    free(p);

    // ... 代码执行一段时间 ...

    free(p); // CRASH! 释放已经被释放的内存
    // 解决方法: free(p) 后立即 p = NULL; free(NULL) 是安全的（什么都不做）。
}

// 错误6: 内存泄漏 (Memory Leak)
void Error_MemoryLeak(void)
{
    printf("Running Error: Memory Leak...\n");
    int *p = (int *) malloc(100);
    if (1)
    {
        return; // 函数直接返回，p 丢失，堆内存 100 字节永远无法被回收，直到程序结束
    }
    free(p);
}

int main()
{
    /* 1. 基础用法 */
    Demo_Malloc();
    Demo_Calloc();
    Demo_Realloc();

    /* 2. 笔试题目解析 */
    Test1(); // 传址调用，正确
    Test2(); // 返回栈地址，野指针
    Test3(); // 正常逻辑
    Test4(); // Use after free 保护

    /* 3. 常见错误演示
       警告: 以下函数包含致命错误。
    */

    // Error_NullPointerDereference();
    // Error_OutOfBounds();
    // Error_FreeStackMemory();
    // Error_FreePartMemory();
    // Error_DoubleFree();
    // Error_MemoryLeak(); // 实际上这个不会 Crash，只是会导致内存占用增加
    return 0;
}
