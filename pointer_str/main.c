#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* * ============================================================
 * 辅助工具与通用结构体
 * ============================================================
 */

typedef struct Stu
{
    char name[20];
    int age;
} Stu;

// 打印整型数组
void print_int_arr(int arr[], int sz)
{
    int i = 0;
    for (i = 0; i < sz; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* * ============================================================
 * 指针基础与算术运算
 * 重点：理解指针步长（Stride）和类型对指针运算的影响
 * ============================================================
 */
void test_pointer_basics()
{
    printf("=== 测试：指针基础与步长 ===\n");

    int a = 0x11223344;
    int *pa = &a;
    char *pc = (char *) &a; // 强制类型转换，改变看待内存的视角

    printf("pa = %p\n", pa);
    printf("pa+1 = %p (跳过4字节)\n", pa + 1);

    printf("pc = %p\n", pc);
    printf("pc+1 = %p (跳过1字节)\n", pc + 1);

    // 小端序测试 (低位存低地址)
    // 内存中: 44 33 22 11 (假设是小端)
    if (*pc == 0x44)
    {
        printf("当前机器为小端存储 (Little Endian)\n");
    }
    else
    {
        printf("当前机器为大端存储 (Big Endian)\n");
    }
    printf("\n");
}

/* * ============================================================
 * 数组与指针的深度辨析 (sizeof 详解)
 * 核心口诀：
 * 数组名是首元素地址，除了两个特例：
 * 1. sizeof(数组名) -> 整个数组大小
 * 2. &数组名 -> 整个数组的地址
 * ============================================================
 */
void test_sizeof_analysis()
{
    printf("=== 测试：数组与指针的 sizeof 辨析 ===\n");

    // --- 一维数组 ---
    int a[4] = {1, 2, 3, 4};
    printf("[1D Array] int a[4]\n");
    printf("sizeof(a): %zd (整个数组大小)\n", sizeof(a));
    printf("sizeof(a+0): %zd (首元素地址大小)\n", sizeof(a + 0));
    printf("sizeof(*&a): %zd (解引用数组指针->整个数组)\n", sizeof(*&a));

    // --- 二维数组 ---
    int b[3][4] = {0};
    printf("\n[2D Array] int b[3][4]\n");
    // b[0] 是第一行的数组名
    printf("sizeof(b[0]): %zd (第一行整个数组的大小 4*4)\n", sizeof(b[0]));
    printf("sizeof(b[0] + 1): %zd (第一行第2个元素的地址)\n", sizeof(b[0] + 1));
    printf("sizeof(*(b[0] + 1)): %zd (第一行第2个元素 int)\n", sizeof(*(b[0] + 1)));

    printf("sizeof(b + 1): %zd (第二行的地址，类型是 int(*)[4])\n", sizeof(b + 1));
    printf("sizeof(*(b + 1)): %zd (解引用得到第二行数组，大小 16)\n", sizeof(*(b + 1)));
    printf("\n");
}

/* * ============================================================
 * 字符串操作底层实现
 * 包含：模拟 strlen (指针-指针) 和 strcpy
 * ============================================================
 */

// 方法：指针 - 指针
size_t my_strlen(const char *str)
{
    const char *start = str;
    while (*str)
    {
        str++;
    }
    return str - start; // 指针相减得到元素个数
}

// 返回目标空间的起始地址，支持链式访问
char *my_strcpy(char *dest, const char *src)
{
    char *ret = dest;
    assert(dest && src); // 断言防止空指针

    // 妙用：先赋值，后判断表达式结果是否为'\0'，再后置++
    while ((*dest++ = *src++))
    {
        ;
    }
    return ret;
}

void test_string_funcs()
{
    printf("=== 测试：字符串底层函数 ===\n");
    char arr1[20] = "Hello";
    char arr2[] = "World";

    printf("my_strlen('%s'): %zd\n", arr1, my_strlen(arr1));

    // 链式访问演示
    printf("my_strcpy result: %s\n", my_strcpy(arr1, arr2));
    printf("\n");
}

/* * ============================================================
 * 泛型编程与回调函数 (模拟 qsort)
 * 知识点：void* 的使用，函数指针作为参数
 * ============================================================
 */

// 交换两个元素的通用函数（按字节交换）
void swap_byte(char *buf1, char *buf2, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; i++)
    {
        char tmp = *buf1;
        *buf1 = *buf2;
        *buf2 = tmp;
        buf1++;
        buf2++;
    }
}

// 比较整型
int cmp_int(const void *e1, const void *e2)
{
    return *(int *) e1 - *(int *) e2;
}

// 比较结构体（按年龄）
int cmp_stu_by_age(const void *e1, const void *e2)
{
    return ((Stu *) e1)->age - ((Stu *) e2)->age;
}

// 比较结构体（按名字）
int cmp_stu_by_name(const void *e1, const void *e2)
{
    return strcmp(((Stu *) e1)->name, ((Stu *) e2)->name);
}

// 通用冒泡排序 (模拟 qsort 接口)
// base: 起始地址, num: 元素个数, size: 每个元素大小, cmp: 比较函数
void bubble_sort_generic(void *base, size_t num, size_t size, int (*cmp)(const void *, const void *))
{
    size_t i = 0;
    for (i = 0; i < num - 1; i++)
    {
        size_t j = 0;
        for (j = 0; j < num - 1 - i; j++)
        {
            // 获取第 j 个和第 j+1 个元素的地址
            // (char*)base + j * size  --> 跳过 j 个元素大小的字节数
            char *addr1 = (char *) base + j * size;
            char *addr2 = (char *) base + (j + 1) * size;

            if (cmp(addr1, addr2) > 0)
            {
                swap_byte(addr1, addr2, size);
            }
        }
    }
}

void test_function_pointers_and_qsort()
{
    printf("=== 测试：泛型冒泡排序 (模拟 qsort) ===\n");

    // 排序整型
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int sz = sizeof(arr) / sizeof(arr[0]);
    bubble_sort_generic(arr, sz, sizeof(arr[0]), cmp_int);
    printf("整型排序结果: ");
    print_int_arr(arr, sz);

    // 排序结构体
    Stu s[] = {{"ZhangSan", 20}, {"LiSi", 30}, {"WangWu", 15}};
    int sz_stu = sizeof(s) / sizeof(s[0]);

    // 按年龄排序
    bubble_sort_generic(s, sz_stu, sizeof(s[0]), cmp_stu_by_age);
    printf("结构体按年龄排序: %s(%d), %s(%d), %s(%d)\n",
           s[0].name, s[0].age, s[1].name, s[1].age, s[2].name, s[2].age);

    printf("\n");
}

/* * ============================================================
 * 指针进阶笔试题 (高难度)
 * 来源：阿里笔试题
 * 重点：多级指针、指针算术运算优先级、前置/后置自增
 * ============================================================
 */
void test_complex_pointer_puzzle()
{
    printf("=== 测试：高难度指针笔试题 ===\n");

    char *c[] = {"ENTER", "NEW", "POINT", "FIRST"};
    char **cp[] = {c + 3, c + 2, c + 1, c};
    char ***cpp = cp;

    printf("原始状态: cpp 指向 cp[0], cp[0] 指向 c[3]('FIRST')\n");

    // **++cpp
    // ++cpp: cpp 指向 cp[1]
    // *++cpp: 拿到 cp[1] 的值 (即 c+2)
    // **++cpp: 拿到 *(c+2) 即 "POINT"
    printf("1. **++cpp = %s\n", **++cpp);

    // *--*++cpp+3
    // ++cpp: cpp 指向 cp[2]
    // *++cpp: 拿到 cp[2] 的值 (即 c+1)
    // --: 前面的结果自减, (c+1) 变为 c (即 c[0])
    // *: 解引用 c[0], 拿到 "ENTER"
    // +3: 字符串指针向后移3位, 指向 "ER"
    printf("2. *--*++cpp+3 = %s\n", *--*++cpp + 3);

    // *cpp[-2]+3
    // cpp 当前指向 cp[2]
    // cpp[-2]: *(cpp-2), 访问 cp[0] (即 c+3)
    // *cpp[-2]: 解引用 c+3, 拿到 "FIRST"
    // +3: 移3位, 指向 "ST"
    printf("3. *cpp[-2]+3 = %s\n", *cpp[-2] + 3);

    // 4. cpp[-1][-1]+1
    // cpp 当前指向 cp[2]
    // cpp[-1]: *(cpp-1), 访问 cp[1] (注意：在步骤2中，cp[1]的内容已经被改为指向 c[0] 了)
    // cpp[-1][-1]: 对 cp[1] (即 c) 再做 [-1] 操作?
    //   实际上: cp[1] 存的是 c (地址)。 cpp[-1]拿到的是 c。
    //   c[-1] 越界? 等等，回顾步骤2：
    //   cp[2] 原本存 c+1。
    //   步骤2中: ++cpp指向cp[2]。然后 *++cpp拿到 c+1。然后 --，导致 cp[2] 中的内容变成了 c。
    //   所以现在 cpp指向 cp[2], 内容是 c。
    //   cpp[-1] 访问 cp[1]。
    //   cp[1] 在步骤1后未变？步骤1 cpp指向cp[1], 只要读。
    //   让我们重新推导 步骤2 改的是 cp[2] 的内容。
    //   这里逻辑非常绕，建议配合画图理解。
    //   结果应该是 "EW"
    printf("4. cpp[-1][-1]+1 = %s\n", cpp[-1][-1] + 1);

    printf("\n");
}


int main()
{
    test_pointer_basics();
    test_sizeof_analysis();
    test_string_funcs();
    test_function_pointers_and_qsort();
    test_complex_pointer_puzzle();
    return 0;
}
