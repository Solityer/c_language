#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>

/* ============================================================
 * 第一部分: 核心函数的模拟实现 (底层逻辑)
 * ============================================================ */

/**
 * 1. 模拟 strlen
 * 方法: 指针-指针法
 * 优势: 比计数器法更符合汇编层面的地址计算逻辑，效率较高。
 * 注意: 返回值是 size_t (unsigned int/long long)，这是后续比较时的重要考点。
 */
size_t my_strlen(const char *str)
{
    const char *start = str;
    assert(str != NULL);
    while (*str)
    {
        str++;
    }
    // 指针相减得到的是元素个数
    return str - start;
}

/**
 * 2. 模拟 strcpy
 * 原理: 逐字节拷贝，直到遇到 '\0'。
 * 返回值: 返回目标空间的起始地址，是为了支持“链式访问”（如 printf("%s", my_strcpy(buf, src))）。
 */
char *my_strcpy(char *dest, const char *src)
{
    char *ret = dest;
    assert(dest && src);
    
    // 核心技巧: 
    // 1. *dest++ = *src++ : 先赋值，再指针自增
    // 2. 赋值表达式的值即为被赋的值。当赋值 '\0' (即0) 时，循环终止
    while ((*dest++ = *src++))
    {
        ;
    }
    return ret;
}

/**
 * 3. 模拟 strcat
 * 原理: 先找到 dest 的末尾，再进行 copy。
 * 风险: dest 必须有足够的空间容纳追加的内容，否则会造成缓冲区溢出。
 */
char *my_strcat(char *dest, const char *src)
{
    char *ret = dest;
    assert(dest && src);
    
    // 1. 找到目标空间的末尾 '\0'
    while (*dest != '\0')
    {
        dest++;
    }
    // 2. 数据追加 (逻辑同 strcpy)
    while ((*dest++ = *src++))
    {
        ;
    }
    return ret;
}

/**
 * 4. 模拟 strcmp
 * 原理: 逐字节比较，直到发现不同或遇到结束符。
 * 规范: 
 * str1 > str2 -> 返回 > 0
 * str1 < str2 -> 返回 < 0
 * str1 == str2 -> 返回 0
 */
int my_strcmp(const char *str1, const char *str2)
{
    assert(str1 && str2);
    while (*str1 == *str2)
    {
        // 如果相等且都遇到 '\0'，说明完全相等
        if (*str1 == '\0')
            return 0;
        str1++;
        str2++;
    }
    // 返回字符差值 (标准库行为)
    // 这里的强转 (unsigned char*) 是一种更严谨的写法，防止扩展 ASCII 码（负数char）比较出错，
    // 但在基础学习中，直接相减也是常见实现。
    return *str1 - *str2; 
}

/**
 * 5. 模拟 strstr (朴素模式匹配算法)
 * 复杂度: O(N*M)。在实际工程中，对于超长文本可能会用 KMP 或 BM 算法优化。
 * 逻辑: 
 * cp: 记录当前在主串中尝试匹配的起始位置
 * s1, s2: 用于遍历比对的工作指针
 */
const char *my_strstr(const char *str1, const char *str2)
{
    const char *cp; 
    const char *s1; 
    const char *s2; 

    assert(str1 && str2);
    
    // 空串是任何串的子串
    if (*str2 == '\0')
        return str1;

    cp = str1;
    while (*cp)
    {
        s1 = cp;
        s2 = str2;
        // 开始匹配，且保证不越界
        while (*s1 && *s2 && *s1 == *s2)
        {
            s1++;
            s2++;
        }
        // 如果 s2 走到了末尾，说明匹配成功
        if (*s2 == '\0')
            return cp;
            
        cp++; // 匹配失败，主串起始位置后移一位
    }
    return NULL;
}

/**
 * 6. 模拟 memcpy
 * 特点: 不处理内存重叠。
 * 场景: 只要源地址和目标地址不重叠，效率很高。
 * 实现: 强制转换为 (char*) 进行单字节拷贝。
 */
void *my_memcpy(void *dest, const void *src, size_t sz)
{
    assert(dest && src);
    void *ret = dest;
    
    // 转换为 char* 因为 void* 不能进行解引用或算术运算
    char *p_dest = (char *)dest;
    const char *p_src = (const char *)src;

    while (sz--)
    {
        *p_dest++ = *p_src++;
    }
    return ret;
}

/**
 * 7. 模拟 memmove (高频考点)
 * 特点: 处理内存重叠 (Overlapping Memory)。
 * 逻辑:
 * - 当 dest < src: 从前向后拷贝 (不会覆盖还未读取的 src 数据)
 * - 当 dest >= src: 从后向前拷贝 (防止覆盖 src 后端的数据)
 * 图解:
 * [ s r c . . . ]
 * [ d e s t . . . ]  -> 此时 dest > src，如果从前向后拷，src 的后半部分会被 dest 的新值覆盖。
 */
void *my_memmove(void *dest, const void *src, size_t sz)
{
    assert(dest && src);
    void *ret = dest;
    char *p_dest = (char *)dest;
    const char *p_src = (const char *)src;

    if (p_dest < p_src)
    {
        // 情况1: 目标在源之前，或者不重叠 -> 从前向后拷贝 (同 memcpy)
        while (sz--)
        {
            *p_dest++ = *p_src++;
        }
    }
    else
    {
        // 情况2: 目标在源之后且重叠 -> 从后向前拷贝
        // 逻辑: 访问 src[sz-1] 到 src[0]
        while (sz--)
        {
            *(p_dest + sz) = *(p_src + sz);
        }
    }
    return ret;
}

/* ============================================================
 * 第二部分: 单元测试与知识点验证
 * ============================================================ */

// 知识点 A: strlen 的返回值是 size_t (无符号型) 的陷阱
void test_strlen_trap()
{
    printf("\n=== Test A: strlen 无符号数陷阱 ===\n");
    // 逻辑分析: 
    // strlen("abc") = 3, strlen("abcdef") = 6
    // 3 - 6 = -3
    // 但由于是 size_t (unsigned int)，-3 会被解析为一个巨大的正整数 (补码)
    // 所以 (3 - 6) > 0 恒为真
    if ((int)strlen("abc") - (int)strlen("abcdef") > 0) 
    {
         // 错误的分支（如果未强转 int）
         printf("错误理解: 3 - 6 > 0 (因为是无符号数运算)\n");
    }
    else
    {
         // 正确的分支（如果强转了 int）
         printf("正确处理: (int)3 - (int)6 < 0\n");
    }

    // 原始 main1.c 中的演示逻辑
    if (strlen("abc") - strlen("abcdef") > 0)
    {
        printf("结论: 未经转换直接相减，结果 > 0 (Unsigned Wrap-around)\n");
    }
}

// 知识点 B: 基础字符串操作 (Copy & Cat)
void test_string_basic_ops()
{
    printf("\n=== Test B: 字符串拷贝与追加 ===\n");
    char buf[50] = "Hello";
    char src[] = " World";

    // 1. 测试 my_strlen
    printf("my_strlen('%s'): %zu\n", buf, my_strlen(buf));

    // 2. 测试 my_strcat
    my_strcat(buf, src);
    printf("my_strcat 结果: %s\n", buf);

    // 3. 测试 my_strcpy
    char buf2[50];
    my_strcpy(buf2, "New String");
    printf("my_strcpy 结果: %s\n", buf2);

    // 4. 安全版本演示 (strncpy/strncat) - 来自 main1.c
    // strncpy 并不总会添加 \0，除非源串长度 < n
    char arr8[20] = "abcdef";
    char arr9[] = "xxxxxxxxxxxxx";
    strncpy(arr8, arr9, 3); // 只拷前3个
    // 结果预期: xxxdef (注意没有自动加 \0 截断后续)
    printf("strncpy(..., 3) 结果: %s (预期 xxxdef)\n", arr8);
}

// 知识点 C: 查找与分割
void test_search_and_token()
{
    printf("\n=== Test C: 查找与分割 ===\n");
    
    // 1. my_strstr 测试
    const char *haystack = "abbbcdef";
    const char *needle = "bbc";
    const char *res = my_strstr(haystack, needle);
    if (res)
        printf("my_strstr 找到子串: %s\n", res);
    else
        printf("my_strstr 未找到\n");

    // 2. strtok 测试 (会修改原字符串，务必操作副本)
    char ip_raw[] = "192.168.0.1";
    char ip_copy[32];
    strcpy(ip_copy, ip_raw);
    
    const char *sep = ".";
    char *token = NULL;
    
    printf("strtok 分割 IP: ");
    // 初始化调用传 buf，后续调用传 NULL
    for (token = strtok(ip_copy, sep); token != NULL; token = strtok(NULL, sep))
    {
        printf("[%s] ", token);
    }
    printf("\n");

    // 3. strerror 测试 (错误码转换)
    // 尝试打开不存在的文件
    FILE *pf = fopen("not_exist.txt", "r");
    if (pf == NULL)
    {
        // errno 被自动设置
        printf("文件打开失败原因 (strerror): %s\n", strerror(errno));
    }
}

// 知识点 D: 内存操作与重叠处理
void test_memory_overlap()
{
    printf("\n=== Test D: 内存重叠 (memmove vs memcpy) ===\n");
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 场景: 将 1,2,3,4,5 拷贝到 3,4,5,6,7 的位置 (下标 2 开始)
    // 源区间: [0, 4], 目标区间: [2, 6] -> 重叠！
    // 如果从前向后拷:
    // arr[2] = arr[0] (1) -> {1,2,1,4,5...}
    // arr[3] = arr[1] (2) -> {1,2,1,2,5...}
    // arr[4] = arr[2] (此时arr[2]已经是1了!) -> {1,2,1,2,1...} -> 数据损坏
    
    my_memmove(arr + 2, arr, 20); // 20 bytes = 5 ints

    printf("my_memmove 结果: ");
    for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
    printf("\n(预期: 1 2 1 2 3 4 5 8 9 10)\n");

    // 简单清零测试
    memset(arr, 0, 8); // 8 bytes = 2 ints
    printf("memset(..., 0, 8) 后前两位: %d %d\n", arr[0], arr[1]);
}

// 知识点 E: 字符分类与转换 (ctype.h)
void test_char_type()
{
    printf("\n=== Test E: 字符处理 ===\n");
    char c = 'A';
    if (isupper(c))
    {
        printf("'%c' 是大写，转小写: '%c'\n", c, tolower(c));
    }
    printf("isdigit('2')? %s\n", isdigit('2') ? "Yes" : "No");
}

int main()
{
    test_char_type();       // 1. 字符类型判断与转换
    test_strlen_trap();     // 2. size_t 的无符号陷阱 (重要!)
    test_string_basic_ops();// 3. 基础字符串操作及安全版本
    test_search_and_token();// 4. 字符串查找、分割与错误报告
    test_memory_overlap();  // 5. 内存重叠处理 (memmove核心)

    return 0;
}