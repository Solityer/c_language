#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * 第一部分: 指针基础与字节序测试
 * ============================================================ */
void test_endian_and_basic()
{
    printf("\n=== 1. 指针基础与大小端测试 ===\n");
    int a = 0x11223344;
    int *pa = &a;
    char *pc = (char *) &a; // 强制类型转换，改变看待内存的视角

    printf("int* pa = %p\n", pa);
    printf("int* pa+1 = %p (跳过4字节)\n", pa + 1);
    printf("char* pc = %p\n", pc);
    printf("char* pc+1 = %p (跳过1字节)\n", pc + 1);

    // 小端序测试 (低位存低地址)
    // 内存中预期: 44 33 22 11 (若为小端)
    if (*pc == 0x44)
    {
        printf("当前机器为: 小端存储 (Little Endian)\n");
    }
    else
    {
        printf("当前机器为: 大端存储 (Big Endian)\n");
    }
}

/* ============================================================
 * 第二部分: sizeof 与 strlen 的内存布局特训 (面试/笔试重点)
 * ============================================================ */
void test_sizeof_drills()
{
    printf("\n=== 2. sizeof 与 strlen 内存布局特训 ===\n");

    // 1. 一维整型数组
    int a1[] = {1, 2, 3, 4};
    printf("--- int a[] = {1,2,3,4} ---\n");
    printf("sizeof(a1): %zu (整个数组大小)\n", sizeof(a1));
    printf("sizeof(a1+0): %zu (首元素地址)\n", sizeof(a1 + 0));
    printf("sizeof(*a1): %zu (首元素大小)\n", sizeof(*a1));
    printf("sizeof(&a1): %zu (整个数组的地址)\n", sizeof(&a1));
    printf("sizeof(*&a1): %zu (解引用数组指针->整个数组)\n", sizeof(*&a1));
    printf("sizeof(&a1 + 1): %zu (跳过整个数组后的地址)\n", sizeof(&a1 + 1));

    // 2. 字符数组 (无\0)
    char arr_no_null[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    printf("--- char arr[] = {'a'...'f'} (无\\0) ---\n");
    printf("sizeof(arr): %zu\n", sizeof(arr_no_null));
    // strlen 在遇到 \0 前不会停止，故以下为随机值
    printf("strlen(arr): %zu (随机值)\n", strlen(arr_no_null));
    printf("strlen(&arr): %zu (随机值)\n", strlen((char *) &arr_no_null));

    // 3. 字符数组 (字符串初始化，含\0)
    char arr_str[] = "abcdef";
    printf("--- char arr[] = \"abcdef\" ---\n");
    printf("sizeof(arr): %zu (包含\\0，共7字节)\n", sizeof(arr_str));
    printf("strlen(arr): %zu (不含\\0，共6字符)\n", strlen(arr_str));

    // 4. 字符串指针
    char *p_str = "abcdef";
    printf("--- char* p = \"abcdef\" ---\n");
    printf("sizeof(p): %zu (指针变量大小)\n", sizeof(p_str));
    printf("strlen(p): %zu\n", strlen(p_str));
    printf("strlen(&p): %zu (随机值，从指针变量p本身的地址开始找\\0)\n", strlen((char *) &p_str));

    // 5. 二维数组
    int a2[3][4] = {0};
    printf("--- int a2[3][4] ---\n");
    printf("sizeof(a2): %zu (整个二维数组)\n", sizeof(a2));
    printf("sizeof(a2[0]): %zu (第一行数组的大小)\n", sizeof(a2[0]));
    printf("sizeof(a2[0] + 1): %zu (第一行第2个元素的地址)\n", sizeof(a2[0] + 1));
    printf("sizeof(a2 + 1): %zu (第二行的地址，类型是 int(*)[4])\n", sizeof(a2 + 1));
}

/* ============================================================
 * 第三部分: 指针数组 vs 数组指针
 * ============================================================ */
void print_2d_by_pointer(int (*p)[5], int r, int c)
{
    // 数组指针的使用，一般在二维数组传参时使用
    printf("--- 使用数组指针打印二维数组 ---\n");
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            // *(*(p + i) + j) 等价于 p[i][j]
            printf("%d ", *(*(p + i) + j));
        }
        printf("\n");
    }
}

void test_array_pointers()
{
    printf("\n=== 3. 指针数组 vs 数组指针 ===\n");

    // 指针数组: 存放指针的数组 (模拟二维数组)
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {2, 3, 4, 5, 6};
    int arr3[] = {3, 4, 5, 6, 7};
    int *parr[] = {arr1, arr2, arr3}; // parr 是数组，每个元素是 int*

    printf("指针数组模拟二维数组:\n");
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            printf("%d ", parr[i][j]);
        }
        printf("\n");
    }

    // 数组指针: 指向数组的指针
    int arr_flat[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int (*p_array)[10] = &arr_flat; // p_array 是指针，指向一个大小为10的int数组
    printf("数组指针解引用访问: %d\n", (*p_array)[5]); // 访问下标5的元素

    // 二维数组传参
    int arr2d[3][5] = {{1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}};
    print_2d_by_pointer(arr2d, 3, 5);
}

/* ============================================================
 * 第四部分: 函数指针、回调函数与 qsort 模拟
 * ============================================================ */
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

// 通用交换函数
void swap_byte(char *buf1, char *buf2, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        char tmp = *buf1;
        *buf1 = *buf2;
        *buf2 = tmp;
        buf1++;
        buf2++;
    }
}

// 通用冒泡排序 (模拟 qsort)
// void* base: 可接收任意类型的数组
// cmp: 函数指针，实现多态比较
void bubble_sort_generic(void *base, size_t num, size_t size, int (*cmp)(const void *, const void *))
{
    for (size_t i = 0; i < num - 1; i++)
    {
        for (size_t j = 0; j < num - 1 - i; j++)
        {
            // 计算地址: (char*)base + j * size
            char *addr1 = (char *) base + j * size;
            char *addr2 = (char *) base + (j + 1) * size;
            if (cmp(addr1, addr2) > 0)
            {
                swap_byte(addr1, addr2, size);
            }
        }
    }
}

int compare_int(const void *p1, const void *p2)
{
    return (*(int *) p1 - *(int *) p2);
}

void test_func_pointers()
{
    printf("\n=== 4. 函数指针与回调函数 ===\n");

    // 函数指针数组 (转移表)
    int (*pfArr[])(int, int) = {NULL, Add, Sub, Mul, Div};
    printf("函数指针数组调用 Add(10, 20): %d\n", pfArr[1](10, 20));

    // 使用泛型冒泡排序
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int sz = sizeof(arr) / sizeof(arr[0]);
    bubble_sort_generic(arr, sz, sizeof(arr[0]), compare_int);

    printf("泛型排序结果: ");
    for (int i = 0; i < sz; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* ============================================================
 * 第五部分: 高难度指针笔试题 (阿里巴巴面试题)
 * ============================================================ */
void test_complex_pointer_puzzle()
{
    printf("\n=== 5. 高难度指针笔试题解析 ===\n");
    char *c[] = {"ENTER", "NEW", "POINT", "FIRST"};
    char **cp[] = {c + 3, c + 2, c + 1, c};
    char ***cpp = cp;

    printf("原始: cpp->cp[0], cp[0]->c[3]('FIRST')\n");

    // 1. **++cpp
    // ++cpp: cpp指向cp[1] (存的是c+2)。
    // *++cpp: 拿到c+2。 **: 拿到*(c+2)即"POINT"。
    printf("1. **++cpp = %s\n", **++cpp); // POINT

    // 2. *--*++cpp+3
    // ++cpp: cpp指向cp[2] (存的是c+1)。
    // *++cpp: 拿到c+1。
    // --: 自减操作，注意这里修改了cp[2]的内容！cp[2]原本存c+1，现在变成了c。
    // *(--): 解引用c，拿到"ENTER"。
    // +3: 字符串指针后移3，指向"ER"。
    printf("2. *--*++cpp+3 = %s\n", *--*++cpp + 3); // ER

    // 3. *cpp[-2]+3
    // cpp当前指向cp[2]。
    // cpp[-2] 即 *(cpp-2)，回退到cp[0]。
    // cp[0]存的是c+3 ("FIRST")。
    // +3: 指向 "ST"。
    printf("3. *cpp[-2]+3 = %s\n", *cpp[-2] + 3); // ST

    // 4. cpp[-1][-1]+1
    // cpp在cp[2]。cpp[-1]是cp[1]。
    // 注意：cp[1]存的是 c+2 ("POINT")。
    // 等等？cp[1]从未被修改过。
    // cp[1][-1] -> *( (c+2) - 1 ) -> *(c+1) -> "NEW"
    // +1 -> "EW"
    printf("4. cpp[-1][-1]+1 = %s\n", cpp[-1][-1] + 1); // EW
}

int main()
{
    test_endian_and_basic();
    test_sizeof_drills();
    test_array_pointers();
    test_func_pointers();
    test_complex_pointer_puzzle();
    return 0;
}
