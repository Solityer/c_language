#include <stdio.h>
#include <string.h>

/* * ------------------------------------------------------------
 * 模块 1：预处理与常量定义 (Constants & Macros)
 * ------------------------------------------------------------
 */
#define M 100
#define CH 'w'

// 宏定义：宏是替换，不是函数调用
#define ADD_MACRO(x,y) ((x)+(y))

// 枚举常量：一一列举，具有默认的整数值
enum Color
{
    RED, // 0
    GREEN, // 1
    BLUE // 2
};

enum Sex
{
    MALE = 7,
    FEMALE, // 8
    SECRET // 9
};

/* * ------------------------------------------------------------
 * 模块 2：全局变量与链接属性 (Global Variables & Linkage)
 * ------------------------------------------------------------
 */

// 全局变量：定义在{}外部
// 具有外部链接属性，决定了全局变量在多个文件之间可以互相使用
int global_a = 1000;

// static 修饰全局变量：
// 1. 将外部链接属性变成了内部链接属性
// 2. 使得该变量只能在当前的.c文件内部使用，改变了作用域
static int g_val_static = 2023;

// static 修饰函数：
// 1. 函数默认具有外部链接属性（可跨文件使用）
// 2. static修饰后变为内部链接属性，只能在当前.c文件使用
static int Add_Static(int x, int y)
{
    return x + y;
}

/* * ------------------------------------------------------------
 * 模块 3：结构体与自定义类型 (Structs & Typedef)
 * ------------------------------------------------------------
 */
typedef unsigned int uint; // 类型重命名

struct Stu
{
    char name[20];
    int age;
    float score;
};


// 测试：数据类型与大小
void test_types_and_sizeof()
{
    printf("=== 数据类型大小测试 ===\n");
    // C语言标准规定：sizeof(long) >= sizeof(int)
    printf("char: %d\n", sizeof(char));
    printf("short: %d\n", sizeof(short));
    printf("int: %d\n", sizeof(int));
    printf("long: %d\n", sizeof(long));
    printf("long long: %d\n", sizeof(long long));
    printf("float: %d\n", sizeof(float));
    printf("double: %d\n", sizeof(double));
    printf("pointer (32/64bit): %d\n", sizeof(void *));
}

// 测试：变量作用域与生命周期（含static修饰局部变量）
void test_scope_and_static()
{
    printf("\n=== 变量作用域与static修饰局部变量 ===\n");
    // 局部变量：block scope，进入创建，离开销毁
    // static修饰局部变量：
    // 1. 改变了存储位置（栈区 -> 静态区）
    // 2. 改变了生命周期（程序结束才销毁）
    // 3. 作用域不变（依然只能在函数内访问）

    static int i = 1; // 初始化只执行一次
    i++;
    printf("static i = %d (多次调用会累加)\n", i);

    int j = 1; // 普通局部变量
    j++;
    printf("local j  = %d (每次调用重置)\n", j);
}

// 测试：字符串与转义字符
void test_strings_and_escape()
{
    printf("\n=== 字符串与转义字符 ===\n");
    // 字符串隐含结尾的 \0
    char arr1[] = "abc";
    // 字符数组若无\0，strlen会继续向后读取直到遇到\0，导致随机值
    char arr2[] = {'a', 'b', 'c'};

    printf("arr1 size: %d, strlen: %d\n", sizeof(arr1), strlen(arr1)); // size=4, len=3
    printf("arr2 size: %d, strlen: %d (可能为随机值)\n", sizeof(arr2), strlen(arr2));

    // 转义字符逻辑
    // \ddd : ddd表示1-3个八进制数字。如 \130 -> 88 -> 'X'
    // \xdd : dd表示2个十六进制数字。如 \x61 -> 97 -> 'a'
    printf("Octal \\130: %c\n", '\130');
    printf("Hex \\x61: %c\n", '\x61');
    printf("File path length logic: %d\n", strlen("c:\test\111\test.c"));
    // 解析：\t(1) \111(1)
}

// 测试：操作符逻辑（自增/自减，逻辑运算，逗号表达式）
void test_operators()
{
    printf("\n=== 操作符逻辑 ===\n");
    // 自增自减
    int a = 5;
    int b = a++; // 后置++：先使用，后+1。 b=5, a=6
    int c = ++a; // 前置++：先+1，后使用。 a=7, c=7
    printf("a=%d, b=%d, c=%d\n", a, b, c);

    // 逻辑运算短路特性
    // C语言中，0表示假，非0表示真
    int x = 0;
    if (!x)
        printf("!0 is True\n");

    // 逗号表达式：从左向右执行，整个表达式的结果是最后一个表达式的结果
    int m = 3, n = 4, p = 1;
    int q = (m = 2 + p, n = m - 1, p = m + n);
    // m=3, n=2, p=3+2=5. q=5
    printf("Comma Op Result: %d\n", q);
}

// 测试：输入输出与EOF处理
void test_io_control()
{
    printf("\n=== 输入输出与循环控制 ===\n");
    printf("请输入一个数字 (输入Ctrl+Z或非数字结束):\n");
    int iq = 0;
    // scanf返回值：成功读取的项数。失败返回EOF(-1)。
    // 这种写法常用于算法竞赛(OJ)的多组输入
    if (scanf("%d", &iq) != EOF)
    {
        if (iq >= 140)
            printf("Genius\n");
        else
            printf("Keep learning\n");
    }

    // 清理缓冲区，防止影响后续输入
    while (getchar() != '\n');
}

// 测试：指针基础（C语言的核心）
void test_pointers()
{
    printf("\n=== 指针基础逻辑 ===\n");
    /*
     * 核心逻辑总结：
     * 1. 内存被划分为以字节为单位的内存单元。
     * 2. 每个单元都有编号，编号 = 地址 = 指针。
     * 3. 变量创建即申请内存空间。
     * 4. &a 取出的是首字节地址（低地址）。
     * 5. 指针变量用于存放地址。
     */

    int a = 10;
    int *pa = &a; // int* 说明pa是指向int的指针

    printf("Address of a: %p\n", pa);
    printf("Value of a: %d\n", *pa); // * 解引用：通过地址找到对象

    *pa = 20; // 本质是远程修改a
    printf("New Value of a: %d\n", a);

    // 指针大小探讨
    // 指针变量存放的是地址，地址的位数取决于CPU寻址能力(32位/64位)
    // 32位系统 -> 4字节; 64位系统 -> 8字节
    printf("Size of int*: %d\n", sizeof(int *));
    printf("Size of char*: %d\n", sizeof(char *));
}

// 测试：结构体使用
void test_structs()
{
    printf("\n=== 结构体测试 ===\n");
    struct Stu s1 = {"ZhangSan", 20, 88.0f};
    struct Stu *ps = &s1;

    // 访问方式 1：结构体变量.成员
    printf("Struct Access (.): %s, %d\n", s1.name, s1.age);

    // 访问方式 2：结构体指针->成员
    printf("Struct Access (->): %s, %d\n", ps->name, ps->age);
}

// main函数是程序的入口，有且仅有一个
// 标准写法：int main() 或 int main(int argc, char* argv[])
int main()
{
    // 1. 测试数据类型与大小
    test_types_and_sizeof();

    // 2. 测试作用域与Static (建议多次调用观察static效果)
    test_scope_and_static();
    test_scope_and_static();
    test_scope_and_static();

    // 3. 测试常量与枚举
    printf("\n=== 常量测试 ===\n");
    printf("Enum MALE: %d, FEMALE: %d\n", MALE, FEMALE);
    printf("Macro ADD: %d\n", ADD_MACRO(2, 3));

    // 4. 测试字符串与转义
    test_strings_and_escape();

    // 5. 测试操作符
    test_operators();

    // 6. 测试指针核心逻辑
    test_pointers();

    // 7. 测试结构体
    test_structs();

    // 8. 输入输出测试 (放在最后，避免阻塞)
    // test_io_control();

    return 0;
}
