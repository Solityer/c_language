#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>

/* ============================================================
 * 第一部分: 字符分类与转换
 * ============================================================ */
void test_ctype()
{
    printf("\n=== 1. 字符分类与转换 ===\n");
    char arr[] = "Test String.\n";
    printf("原始字符串: %s", arr);

    char *p = arr;
    while (*p)
    {
        if (isupper(*p))
        {
            *p = tolower(*p); // 大写转小写
        }
        p++;
    }
    printf("转换后字符串: %s", arr);
}

/* ============================================================
 * 第二部分: 字符串函数模拟实现
 * ============================================================ */

// 1. 模拟 strlen (指针-指针法)
size_t my_strlen(const char *str)
{
    const char *start = str;
    while (*str)
        str++;
    return str - start;
}

// 2. 模拟 strcpy (链式访问)
char *my_strcpy(char *dest, const char *src)
{
    char *ret = dest;
    assert(dest && src);
    // 妙用：先赋值，后判断结果是否为\0，再自增
    while ((*dest++ = *src++))
    {
        ;
    }
    return ret;
}

// 3. 模拟 strcat (追加)
char *my_strcat(char *dest, const char *src)
{
    char *ret = dest;
    assert(dest && src);
    // 1. 找到目标空间的末尾
    while (*dest != '\0')
        dest++;
    // 2. 数据追加
    while ((*dest++ = *src++))
    {
        ;
    }
    return ret;
}

// 4. 模拟 strcmp
int my_strcmp(const char *str1, const char *str2)
{
    assert(str1 && str2);
    while (*str1 == *str2)
    {
        if (*str1 == '\0')
            return 0;
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// 5. 模拟 strstr (查找子串) - 朴素匹配算法
const char *my_strstr(const char *str1, const char *str2)
{
    const char *cp; // 记录开始匹配的位置
    const char *s1; // 遍历str1
    const char *s2; // 遍历str2

    assert(str1 && str2);
    if (*str2 == '\0')
        return str1;

    cp = str1;
    while (*cp)
    {
        s1 = cp;
        s2 = str2;
        while (*s1 && *s2 && *s1 == *s2)
        {
            s1++;
            s2++;
        }
        if (*s2 == '\0')
            return cp; // 找到子串
        cp++;
    }
    return NULL;
}

void test_string_funcs()
{
    printf("\n=== 2. 字符串函数模拟 ===\n");
    char buf[100] = "Hello";

    printf("my_strlen('Hello'): %zu\n", my_strlen(buf));

    my_strcat(buf, " World");
    printf("my_strcat结果: %s\n", buf);

    const char *sub = my_strstr(buf, "Wor");
    if (sub)
        printf("my_strstr找到子串: %s\n", sub);
    else
        printf("未找到子串\n");
}

/* ============================================================
 * 第三部分: 内存操作函数 (重要)
 * ============================================================ */

// 模拟 memcpy (不考虑内存重叠)
void *my_memcpy(void *dest, const void *src, size_t sz)
{
    assert(dest && src);
    void *ret = dest;
    while (sz--)
    {
        *(char *) dest = *(char *) src;
        dest = (char *) dest + 1;
        src = (char *) src + 1;
    }
    return ret;
}

// 模拟 memmove (考虑内存重叠)
// 01 02 03 04 05
// copy [1,2,3] to [3,4,5] -> src < dest -> 从后向前拷贝
// copy [3,4,5] to [1,2,3] -> dest < src -> 从前向后拷贝
void *my_memmove(void *dest, const void *src, size_t sz)
{
    assert(dest && src);
    void *ret = dest;

    if (dest < src)
    {
        // 前->后 (同memcpy)
        int i = 0;
        for (i = 0; i < sz; i++)
        {
            *(char *) dest = *(char *) src;
            dest = (char *) dest + 1;
            src = (char *) src + 1;
        }
    }
    else
    {
        // 后->前
        while (sz--)
        {
            *((char *) dest + sz) = *((char *) src + sz);
        }
    }
    return ret;
}

void test_memory_funcs()
{
    printf("\n=== 3. 内存函数测试 ===\n");

    // memmove 测试
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // 将 1,2,3,4,5 移动到 3,4,5,6,7 的位置 (重叠)
    my_memmove(arr + 2, arr, 20);

    printf("memmove结果(预期: 1 2 1 2 3 4 5 8...): ");
    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // memset 测试
    memset(arr, 0, 20); // 前5个int清零
    printf("memset清零后前5位: %d %d...\n", arr[0], arr[1]);
}

/* ============================================================
 * 第四部分: strtok 与 strerror
 * ============================================================ */
void test_advanced_utils()
{
    printf("\n=== 4. strtok 与 strerror ===\n");

    // strtok 分割字符串 (会修改原字符串)
    char ip[] = "192.168.23.101";
    char buf[30];
    strcpy(buf, ip); // 拷贝一份操作

    const char *sep = ".";
    char *s = NULL;
    printf("IP分割: ");
    for (s = strtok(buf, sep); s != NULL; s = strtok(NULL, sep))
    {
        printf("[%s] ", s);
    }
    printf("\n");

    // strerror 与文件操作错误
    FILE *pf = fopen("non_existent_file.txt", "r");
    if (pf == NULL)
    {
        // errno 是全局错误码
        printf("文件打开失败: %s\n", strerror(errno));
        // perror("自定义信息") 等价于 printf + strerror
    }
}

int main()
{
    test_ctype();
    test_string_funcs();
    test_memory_funcs();
    test_advanced_utils();
    return 0;
}
