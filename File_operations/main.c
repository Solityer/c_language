#include <stdio.h>

// 定义测试用的结构体
struct S
{
    int a;
    float s;
};

struct S1
{
    int a;
    float s;
    char str[10];
};

int main()
{
    /* ============================================================ */
    /* 模块一：字符的输入输出函数 (fgetc / fputc)                   */
    /* ============================================================ */
    printf("========== 测试模块一：字符读写 ==========\n");

    // 1.1 写文件演示 (Write)
    // 必须使用 "w" (write) 模式打开才能写入。注意："w" 会清空原文件内容，若文件不存在则创建。
    FILE *pf1_write = fopen("..\\data1.txt", "w");
    if (pf1_write == NULL)
    {
        perror("fopen data1.txt for write"); // 打印错误详情
        return 1;
    }

    // 顺序写: 依次往后追加写入26个小写字母
    for (int i = 0; i < 26; ++i)
    {
        fputc('a' + i, pf1_write);
    }
    // 写完后必须关闭，缓冲区内容才会刷新到磁盘
    fclose(pf1_write);
    pf1_write = NULL;

    // 1.2 读文件演示 (Read)
    // 使用 "r" (read) 模式打开进行读取
    FILE *pf1 = fopen("..\\data1.txt", "r");
    if (pf1 == NULL)
    {
        perror("fopen data1.txt for read");
        return 1;
    }

    // fgetc: 从流中读取一个字符，返回字符的ASCII码 (int)，如果失败或结束返回 EOF
    int ch;
    printf("读取前4个字符: \n");
    ch = fgetc(pf1);
    printf("%c\n", ch);
    ch = fgetc(pf1);
    printf("%c\n", ch);
    ch = fgetc(pf1);
    printf("%c\n", ch);
    ch = fgetc(pf1);
    printf("%c\n", ch);

    // 关闭文件
    fclose(pf1);
    pf1 = NULL;


    /* ============================================================ */
    /* 模块二：文本行的输入输出函数 (fgets / fputs)                 */
    /* ============================================================ */
    printf("\n========== 测试模块二：文本行读写 ==========\n");

    // 2.1 准备数据 (通常用于初始化测试文件，此处演示写操作逻辑)
    FILE *pf2_write = fopen("..\\data2.txt", "w");
    if (pf2_write != NULL)
    {
        fputs("hello bit\n", pf2_write);
        fputs("hello solity\n", pf2_write);
        fputs("hello pengzhihao\n", pf2_write);
        fclose(pf2_write);
    }

    // 2.2 读文件演示
    FILE *pf2 = fopen("..\\data2.txt", "r");
    if (pf2 == NULL)
    {
        perror("fopen data2.txt");
        return 1;
    }

    // fgets(buf, n, stream):
    // 读取逻辑: 最多读取 n-1 个字符，或者读到换行符 '\n' 为止 (换行符也会被读入)，末尾自动补 '\0'
    char arr2[30] = {0};

    printf("逐行读取内容: \n");
    if (fgets(arr2, 30, pf2) != NULL)
        printf("%s", arr2); // 第1行
    if (fgets(arr2, 30, pf2) != NULL)
        printf("%s", arr2); // 第2行
    if (fgets(arr2, 30, pf2) != NULL)
        printf("%s", arr2); // 第3行

    fclose(pf2);
    pf2 = NULL;


    /* ============================================================ */
    /* 模块三：格式化输入输出函数 (fscanf / fprintf)                */
    /* ============================================================ */
    printf("\n========== 测试模块三：格式化读写 ==========\n");

    // 3.1 写文件 (格式化写入)
    FILE *pf3_write = fopen("..\\data3.txt", "w");
    if (pf3_write != NULL)
    {
        struct S temp_s = {100, 3.14f};
        // fprintf: 类似于 printf，但输出目标是文件流
        fprintf(pf3_write, "%d %f", temp_s.a, temp_s.s);
        fclose(pf3_write);
    }

    // 3.2 读文件 (格式化读取)
    FILE *pf3 = fopen("..\\data3.txt", "r");
    if (pf3 == NULL)
    {
        perror("fopen data3.txt");
        return 1;
    }

    struct S s = {0};
    // fscanf: 类似于 scanf，但从文件流中读取
    // 注意: 浮点数在内存中可能存在精度差异
    fscanf(pf3, "%d %f", &(s.a), &(s.s));
    printf("读取结构体数据: %d %f\n", s.a, s.s);

    fclose(pf3);
    pf3 = NULL;


    /* ============================================================ */
    /* 模块四：字符串缓冲区的格式化 (sprintf / sscanf)              */
    /* 注意：此模块不涉及文件IO，而是内存中的字符串转换                */
    /* ============================================================ */
    printf("\n========== 测试模块四：字符串格式化转换 ==========\n");

    char arr[50] = {0}; // 扩大缓冲区防止溢出
    struct S1 s1 = {100, 3.14f, "hehe"};
    struct S1 tmp1 = {0};

    // 4.1 sprintf: 将各种类型数据格式化打印到字符串(buffer)中
    // 作用: 将结构体数据序列化为字符串
    sprintf(arr, "%d %f %s\n", s1.a, s1.s, s1.str);
    printf("序列化后的字符串: %s", arr);

    // 4.2 sscanf: 从字符串(buffer)中格式化提取数据
    // 作用: 从字符串反序列化回结构体数据
    sscanf(arr, "%d %f %s\n", &(tmp1.a), &(tmp1.s), tmp1.str);
    printf("反序列化后的数据: %d %f %s\n", tmp1.a, tmp1.s, tmp1.str);


    /* ============================================================ */
    /* 模块五：二进制输入和输出函数 (fread / fwrite)                */
    /* ============================================================ */
    printf("\n========== 测试模块五：二进制读写 ==========\n");

    // 5.1 写文件 (二进制模式 "wb")
    FILE *pf4_write = fopen("..\\data4.txt", "wb");
    if (pf4_write != NULL)
    {
        struct S1 s2 = {100, 3.14f, "bit"};
        // fwrite(buffer, size, count, stream)
        // 从 s2 地址开始，写入 1 个大小为 sizeof(struct S1) 的数据块到文件
        fwrite(&s2, sizeof(struct S1), 1, pf4_write);
        fclose(pf4_write);
    }

    // 5.2 读文件 (二进制模式 "rb")
    FILE *pf4 = fopen("..\\data4.txt", "rb");
    if (pf4 == NULL)
    {
        perror("fopen data4.txt");
        return 1;
    }

    struct S1 s3 = {0};
    // fread(buffer, size, count, stream)
    // 从文件读取 1 个大小为 sizeof(struct S1) 的数据块到 s3
    fread(&s3, sizeof(struct S1), 1, pf4);
    printf("二进制读取结果: %d %f %s\n", s3.a, s3.s, s3.str);

    fclose(pf4);
    pf4 = NULL;


    /* ============================================================ */
    /* 模块六：文件的随机读写 (fseek / ftell / rewind)              */
    /* ============================================================ */
    printf("\n========== 测试模块六：文件随机读写 ==========\n");

    // 准备测试数据: "abcdef..."
    FILE *pf5_init = fopen("..\\data5.txt", "w");
    if (pf5_init != NULL)
    {
        for (int i = 0; i < 26; i++)
            fputc('a' + i, pf5_init);
        fclose(pf5_init);
    }

    FILE *pf5 = fopen("..\\data5.txt", "r");
    if (pf5 == NULL)
    {
        perror("fopen data5.txt");
        return 1;
    }

    // 6.1 fseek: 根据偏移量定位文件指针
    // int fseek ( FILE * stream, long int offset, int origin );
    // origin 选项: SEEK_SET(起始), SEEK_CUR(当前), SEEK_END(末尾)

    // 案例A: 相对起始位置偏移5 (读取第6个字符 'f')
    fseek(pf5, 5, SEEK_SET);
    int ch1 = fgetc(pf5);
    printf("SEEK_SET(5) 读取: %c\n", ch1); // 预期输出 'f'

    // 案例B: 相对末尾位置偏移-4 (倒数第4个字符)
    // 注意: 如果文件是以文本模式打开，SEEK_END的行为在某些系统可能未定义，但在二进制流中是精确的。此处用于演示。
    fseek(pf5, -4, SEEK_END);
    int ch2 = fgetc(pf5);
    printf("SEEK_END(-4) 读取: %c\n", ch2); // 'w' ('a'...'z'中倒数第四个是w)

    // 案例C: 相对当前位置偏移
    // 当前指针在读完 ch2 后自动后移一位。
    // 我们先读两个字符来改变位置，再测试 SEEK_CUR
    rewind(pf5); // 先回到开头 'a'
    fgetc(pf5); // 读 'a', 指针->'b'
    fgetc(pf5); // 读 'b', 指针->'c'
    // 此时在 'c' 处。
    fseek(pf5, 3, SEEK_CUR); // 从 'c' 向后跳3个: d, e, f -> 指向 'g'
    int ch4 = fgetc(pf5);
    printf("SEEK_CUR(3) 后读取: %c\n", ch4); // 预期输出 'g'

    // 6.2 ftell: 返回当前文件指针相对于起始位置的偏移量 (字节数)
    int pos = ftell(pf5);
    printf("当前文件指针位置 (ftell): %d\n", pos);

    // 6.3 rewind: 让文件指针回到起始位置
    rewind(pf5);
    int ch6 = fgetc(pf5);
    printf("rewind后读取首字符: %c\n", ch6); // 预期输出 'a'

    fclose(pf5);
    pf5 = NULL;

    return 0;
}
