#include <stdio.h>
#include <stdbool.h> // C99 标准引入，用于 bool 类型
#include <math.h>    // 用于 sqrt 函数 (Linux下编译需加 -lm)
#include <string.h>  // 用于 size_t, strlen, strcpy

// ======================================================================================
// 基础算法逻辑 (Logic & Algorithms)
// ======================================================================================

/*
 * 函数名: is_prime
 * 功能: 判断一个数是否为素数
 * 优化逻辑: 只需试除到 sqrt(n)。
 * 注意: 循环条件必须包含 sqrt(n) (即 <=)，否则如 n=9, sqrt=3 时无法进入循环判断，会误判。
 */
bool is_prime(int n)
{
    int j = 0;
    for (j = 2; j <= sqrt(n); j++)
    {
        if (n % j == 0)
            return false;
    }
    return true;
}

/*
 * 函数名: is_leap_year
 * 功能: 判断闰年
 * 规则: 能被4整除且不能被100整除，或者能被400整除。
 */
bool is_leap_year(int y)
{
    if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
        return true;
    else
        return false;
}

/*
 * 函数名: binary_search
 * 功能: 二分查找
 * 前提: 数组必须是有序的 (Monotonic functionality)
 * 核心细节: 使用 left + (right - left) / 2 防止直接相加导致的 int 溢出。
 */
int binary_search(int arr[], int k, int sz)
{
    int left = 0;
    int right = sz - 1;

    while (left <= right)
    {
        // int mid = (left + right) / 2; // 存在溢出风险
        int mid = left + (right - left) / 2; // 优化写法

        if (arr[mid] < k)
        {
            left = mid + 1; // 去右半边找
        }
        else if (arr[mid] > k)
        {
            right = mid - 1; // 去左半边找
        }
        else
        {
            return mid; // 找到了，返回下标
        }
    }
    return -1; // 找不到
}

// ======================================================================================
// 指针与函数调用 (Pointers & Function Calls)
// ======================================================================================

/*
 * 函数名: Swap1 (错误示范)
 * 问题: 传值调用 (Pass by Value)。
 * 解析: x 和 y 只是 main 中变量的临时拷贝，修改它们只会影响 Swap1 栈帧内的内存，函数结束即销毁。
 */
void Swap1(int x, int y)
{
    int z = 0;
    z = x;
    x = y;
    y = z;
}

/*
 * 函数名: Swap2 (正确示范)
 * 方式: 传址调用 (Pass by Reference / Pointer)。
 * 解析: 接收地址，通过解引用操作符 * 直接访问并修改调用者栈帧中的内存。
 */
void Swap2(int* p1, int* p2)
{
    int tmp = 0;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

/*
 * 函数名: Increment
 * 功能: 演示函数副作用
 * 解析: 必须传入指针才能修改外部变量的状态。
 */
void Increment(int* p)
{
    *p = *p + 1; // 等价于 (*p)++
}

// ======================================================================================
// 递归与迭代 (Recursion & Iteration)
// ======================================================================================

/*
 * 模拟 strlen - 方式 A: 迭代法
 * 优点: 效率高，栈开销小。
 */
size_t my_strlen_iterative(char* str)
{
    size_t count = 0;
    while (*str != '\0') // 字符串以 '\0' 结尾
    {
        count++;
        str++; // 指针后移
    }
    return count;
}

/*
 * 模拟 strlen - 方式 B: 递归法
 * 特点: 不创建临时变量 (计数器)。
 * 逻辑: 长度 = 1 + 剩余字符串的长度。
 */
size_t my_strlen_recursive(char* str)
{
    if (*str == '\0')
        return 0;
    else
        return 1 + my_strlen_recursive(str + 1);
}

/*
 * 函数名: PrintDigit
 * 功能: 递归打印数字的每一位 (1234 -> 1 2 3 4)
 * 核心思想:
 * 1. 递推: 如果 n > 9，说明还有高位，先处理 n/10。
 * 2. 回归: 打印当前位的模 (n % 10)。
 * 这实现了“先进后出”的逻辑，从而正序打印。
 */
void PrintDigit(int n)
{
    if (n > 9)
    {
        PrintDigit(n / 10);
    }
    printf("%d ", n % 10);
}

/*
 * 函数名: Fac_Recursive
 * 功能: 阶乘计算
 */
int Fac_Recursive(int n)
{
    if (n <= 1)
        return 1;
    else
        return n * Fac_Recursive(n - 1);
}

/*
 * 函数名: Fib_Iterative
 * 功能: 斐波那契数列 (迭代解法)
 * 比较: 递归解法代码简洁但存在大量重复计算 (O(2^N))。
 * 迭代解法效率更高 (O(N))，适合计算较大数值。
 */
int Fib_Iterative(int n)
{
    int a = 1;
    int b = 1;
    int c = 1;

    if (n <= 2) return 1;

    while (n >= 3)
    {
        c = a + b;
        a = b;
        b = c;
        n--;
    }
    return c;
}

int main()
{
    // ---------------------------------------------------------
    // 算法逻辑
    // ---------------------------------------------------------
    printf("\n=== Module 1: Algorithms Test ===\n");

    // 素数测试
    int count = 0;
    printf("[Prime] 100-200之间的素数: ");
    for (int i = 101; i <= 200; i += 2) // 偶数除2外不是素数，步长设为2优化
    {
        if (is_prime(i))
        {
            printf("%d ", i);
            count++;
        }
    }
    printf("\n[Prime] 总数: %d\n", count);

    // 二分查找测试
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int k = 7;
    int sz = sizeof(arr) / sizeof(arr[0]);
    int index = binary_search(arr, k, sz);

    if (index != -1)
        printf("[Binary Search] 找到数字 %d，下标: %d\n", k, index);
    else
        printf("[Binary Search] 未找到数字 %d\n", k);


    // ---------------------------------------------------------
    // 指针与内存
    // ---------------------------------------------------------
    printf("\n=== Module 2: Pointers & Memory Test ===\n");

    int num1 = 10;
    int num2 = 20;
    printf("交换前: num1 = %d, num2 = %d\n", num1, num2);

    // 错误交换
    Swap1(num1, num2);
    printf("Swap1(传值)后: num1 = %d, num2 = %d (未变)\n", num1, num2);

    // 正确交换
    Swap2(&num1, &num2);
    printf("Swap2(传址)后: num1 = %d, num2 = %d (成功)\n", num1, num2);

    // 副作用测试
    Increment(&num1);
    printf("Increment后 num1: %d\n", num1);


    // ---------------------------------------------------------
    // 递归与迭代
    // ---------------------------------------------------------
    printf("\n=== Module 3: Recursion & Iteration Test ===\n");

    // 字符串长度
    char str_arr[] = "Hello ZKP";
    printf("[Strlen] 原始字符串: \"%s\"\n", str_arr);
    printf("[Strlen] 长度(迭代): %zd\n", my_strlen_iterative(str_arr));
    printf("[Strlen] 长度(递归): %zd\n", my_strlen_recursive(str_arr));

    // 递归打印
    int num_print = 1234;
    printf("[Recursion] 按位打印 %d: ", num_print);
    PrintDigit(num_print);
    printf("\n");

    // 阶乘与斐波那契
    int fac_n = 5;
    printf("[Math] %d! = %d\n", fac_n, Fac_Recursive(fac_n));
    printf("[Math] Fib(10) = %d\n", Fib_Iterative(10));


    // ---------------------------------------------------------
    // 库函数特性 (Trick & Chain)
    // ---------------------------------------------------------
    printf("\n=== Module 4: Library Functions Test ===\n");

    // printf 链式调用
    // printf 返回打印字符的个数
    // 逻辑:
    //   Inner: printf("43") -> 打印"43", 返回2
    //   Mid:   printf("%d", 2) -> 打印"2", 返回1
    //   Outer: printf("%d", 1) -> 打印"1"
    //   Result: 4321
    printf("[Printf Chain] 链式访问测试: ");
    printf("%d", printf("%d", printf("43")));
    printf("\n");

    // strcpy 与 strlen 链式调用
    // strcpy 返回目标空间的起始地址，因此可以直接作为 strlen 的参数
    char buffer[20] = {0};
    char source[] = "abc";
    printf("[Chain Call] strcpy后立即测长: %zd\n", strlen(strcpy(buffer, source)));

    return 0;
}