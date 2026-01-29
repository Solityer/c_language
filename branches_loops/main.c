#include <stdio.h>
#include <string.h>
#include <windows.h> // 用于Sleep, system
#include <stdlib.h>  // 用于rand, srand, system
#include <time.h>    // 用于time

// ------------------------------------------------------------
// 基础语句与分支结构 (If, Switch)
// ------------------------------------------------------------

// 基础语句
void demo_01_statements()
{
    printf("=== 01. 基础语句演示 ===\n");
    3 + 5; // 表达式语句
    printf("hehe\n"); // 函数调用语句
    ; // 空语句 - 有时候我们需要一条语句，但是这条语句什么都不需要做
}

// if-else 基础逻辑
void demo_02_if_basic()
{
    printf("=== 02. if-else 基础 ===\n");
    int age = 0;
    printf("请输入年龄: ");
    scanf("%d", &age);

    // 单分支
    if (age >= 18)
        printf("成年人\n");

    // 双分支
    if (age >= 18)
        printf("成年人\n");
    else
        printf("未成年人\n");
}

// 多分支与嵌套逻辑 (年龄段划分)
void demo_03_if_nested()
{
    printf("=== 03. 多分支与逻辑嵌套 ===\n");
    /*
        age<18  - 未成年
        18~30   - 青年
        31~50   - 中年
        51~70   - 中老年
        71~99   - 老年
        >99     - 老寿星
    */
    int age = 0;
    printf("请输入年龄: ");
    scanf("%d", &age);

    // 写法1：使用 else if (推荐，逻辑清晰)
    if (age < 18)
        printf("未成年\n");
    else if (age <= 30) // 隐含了 age >= 18
        printf("青年\n");
    else if (age <= 50)
        printf("中年\n");
    else if (age <= 70)
        printf("中老年\n");
    else if (age <= 99)
        printf("老年\n");
    else
        printf("老寿星\n");

    // 补充：代码块的概念
    if (age >= 18)
    {
        // 代码块：多条语句需要用大括号括起来
        printf("成年了\n");
        printf("可以对自己负责了\n");
    }
}

// 悬空else问题与代码风格
void demo_04_dangling_else()
{
    printf("=== 04. 悬空else问题 ===\n");
    int a = 0;
    int b = 2;

    // 这里的缩进具有欺骗性
    if (a == 1)
        if (b == 2)
            printf("hehe\n");
        else // 这个else其实是和最近的 if (b==2) 匹配的，而不是和 if (a==1) 匹配
            printf("haha\n");

    // 结论：else 总是和它上面最近的、未匹配的 if 匹配
    // 建议：即使只有一行代码，也尽量加上 {}，防止逻辑混淆
}

// 常见的比较错误与奇数判断
void demo_05_coding_style()
{
    printf("=== 05. 编码风格与奇数判断 ===\n");
    int a = 10;

    // 良好的编码习惯：将常量放在左边
    // if (a == 5) // 如果少写一个=，变成赋值，条件永远为真(只要不为0)
    if (5 == a)
    {
        // 此时如果少写一个=，编译器会报错，更容易发现错误
        printf("hehe\n");
    }

    // 判断奇数
    int n = 0;
    printf("请输入数字判断奇偶: ");
    scanf("%d", &n);
    if (n % 2 == 1)
        printf("YES (是奇数)\n");
    else
        printf("NO (是偶数)\n");
}

// Switch 语句详解
void demo_06_switch()
{
    printf("=== 06. Switch 语句 ===\n");
    int day = 0;
    printf("请输入星期几(1-7): ");
    scanf("%d", &day);

    // case 穿透（没有break的情况）
    switch (day)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            printf("weekday (工作日)\n");
            break; // 遇到break才停止
        case 6:
        case 7:
            printf("weekend (周末)\n");
            break;
        default:
            printf("选择错误\n");
            break;
    }
}

// Switch 嵌套逻辑练习
void demo_07_switch_nested()
{
    printf("=== 07. Switch 嵌套练习 ===\n");
    int n = 1;
    int m = 2;
    switch (n)
    {
        case 1:
            m++; // m=3
        case 2:
            n++; // n=2
        case 3:
            switch (n)
            {
                // n此时为2
                case 1:
                    n++;
                case 2:
                    m++; // m=4
                    n++; // n=3
                    break; // 跳出内部switch
            }
        case 4:
            m++; // m=5
            break; // 跳出外部switch
        default:
            break;
    }
    printf("结果: m = %d, n = %d\n", m, n);
}

// ------------------------------------------------------------
// 循环结构与控制 (While, For, Do-While)
// ------------------------------------------------------------

// While 与 For 循环基础
void demo_08_loops()
{
    printf("=== 08. 循环基础 (奇数打印) ===\n");

    // While 循环打印 1-100 奇数
    printf("While循环输出: ");
    int i = 1;
    while (i <= 20)
    {
        // 缩小范围演示
        if (i % 2 == 1)
            printf("%d ", i);
        i++;
    }
    printf("\n");

    // For 循环 (C99标准支持在for内定义变量)
    // 语法: for(初始化; 判断; 调整)
    printf("For循环输出:   ");
    for (int j = 1; j <= 20; j++)
    {
        if (j % 2 == 1)
            printf("%d ", j);
    }
    printf("\n");
}

// Break 与 Continue 的区别
void demo_09_break_continue()
{
    printf("=== 09. Break 与 Continue 辨析 ===\n");

    // 1. While 中的 break/continue
    printf("[While - Continue]: ");
    int i = 1;
    while (i <= 10)
    {
        if (i == 5)
        {
            i++; // 注意：如果这里不调整，直接continue，会造成死循环
            continue; // 跳过本次循环后边的代码，直接去判断部分
        }
        printf("%d ", i); // 不会打印 5
        i++;
    }
    printf("\n");

    printf("[While - Break]:    ");
    i = 1;
    while (i <= 10)
    {
        if (i == 5)
            break; // 永久终止循环
        printf("%d ", i); // 只打印 1 2 3 4
        i++;
    }
    printf("\n");

    // 2. For 中的 break/continue
    printf("[For - Continue]:   ");
    for (int j = 1; j <= 10; j++)
    {
        if (j == 5)
            continue; // 跳过后面代码，直接去 j++ (调整部分)
        printf("%d ", j);
    }
    printf("\n");
}

// Do-While 循环
void demo_10_do_while()
{
    printf("=== 10. Do-While 循环 ===\n");
    int i = 1;
    do
    {
        if (i == 5)
        {
            i++;
            continue;
        }
        printf("%d ", i);
        i++;
    } while (i <= 10);
    printf("\n");
    // do-while 特点：至少执行一次循环体
}

// ------------------------------------------------------------
// 输入输出缓冲区深入 (getchar/putchar)
// ------------------------------------------------------------

// getchar/putchar基础与EOF
void demo_11_getchar_basic()
{
    printf("=== 11. getchar/putchar 基础 ===\n");
    printf("请输入字符 (Ctrl+Z 结束):\n");
    int ch = 0;
    // getchar 读取字符成功时返回ASCII码，失败或遇到文件末尾返回 EOF (-1)
    // windows 环境按 Ctrl+Z 触发 EOF
    while ((ch = getchar()) != EOF)
    {
        putchar(ch);
    }
}

// 缓冲区清理（模拟密码确认场景）
void demo_12_buffer_clear()
{
    printf("=== 12. 缓冲区清理逻辑 (重点) ===\n");
    char password[20];
    printf("请输入密码:>");
    // scanf 读取字符串时，遇到空格或回车就停止读取，但回车符(\n)还留在缓冲区里
    scanf("%s", password);

    /* 如果不清理缓冲区，下面的 getchar() 会直接读取刚才剩下的 '\n'，
     导致 ch 变成 '\n'，直接进入 else 分支输出 "确认失败"。
    */

    // 清理缓冲区逻辑：循环读取直到读走 '\n'
    int temp = 0;
    while ((temp = getchar()) != '\n')
    {
        ; // 空语句，只为了消耗字符
    }

    printf("请确认(Y/N):");
    int ch = getchar(); // 这次才能正确读取用户输入的新字符

    if ('Y' == ch)
        printf("确认成功\n");
    else
        printf("确认失败\n");
}

// ------------------------------------------------------------
// 常用算法实践
// ------------------------------------------------------------

// 阶乘计算 (1! + ... + n!)
void demo_13_factorial()
{
    printf("=== 13. 阶乘累加计算 ===\n");
    int n = 0;
    int i = 0;
    int ret = 1;
    int sum = 0;

    // 计算 1!+2!+3!
    for (n = 1; n <= 3; n++)
    {
        ret *= n; // 不需要每次从头乘，利用上一轮的阶乘结果
        sum += ret;
    }
    printf("1!+2!+3! = %d\n", sum);
}

// 二分查找 (Binary Search)
void demo_14_binary_search()
{
    printf("=== 14. 二分查找算法 ===\n");
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 0;
    int sz = sizeof(arr) / sizeof(arr[0]); // 计算数组元素个数

    printf("有序数组: 1-10，请输入要查找的数字: ");
    scanf("%d", &k);

    int left = 0;
    int right = sz - 1;
    int flag = 0;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // 防止 (left+right) 溢出
        if (arr[mid] < k)
        {
            left = mid + 1;
        }
        else if (arr[mid] > k)
        {
            right = mid - 1;
        }
        else
        {
            printf("找到了，下标是：%d\n", mid);
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        printf("找不到\n");
}

// 字符串两端汇聚动画
void demo_15_string_animation()
{
    printf("=== 15. 字符串动态汇聚 ===\n");
    char arr1[] = "welcome to bit!!!!!!!";
    char arr2[] = "*********************";

    int left = 0;
    int right = strlen(arr1) - 1;

    while (left <= right)
    {
        arr2[left] = arr1[left];
        arr2[right] = arr1[right];
        printf("%s\n", arr2);

        Sleep(1000); // 暂停1000毫秒 (windows.h)
        // system("cls"); // 清空屏幕，为了便于查看历史记录，这里暂时注释掉

        left++;
        right--;
    }
    printf("最终结果: %s\n", arr2);
}

// 模拟用户登录 (限制次数)
void demo_16_login()
{
    printf("=== 16. 模拟用户登录 (限制3次) ===\n");
    int i = 0;
    char password[20] = {0};
    for (i = 0; i < 3; i++)
    {
        printf("请输入密码(正确为123456):>");
        scanf("%s", password);

        // strcmp: 字符串比较。相等返回0
        if (strcmp(password, "123456") == 0)
        {
            printf("登录成功\n");
            break;
        }
        else
        {
            printf("密码错误\n");
        }
    }
    if (i == 3)
        printf("三次密码错误，退出程序\n");
}

// ------------------------------------------------------------
// 综合游戏与系统命令
// ------------------------------------------------------------

// 猜数字游戏辅助函数
void game_logic()
{
    // 1. 生成1~100的随机数
    // rand函数生成伪随机数，范围 0~RAND_MAX(32767)
    int ret = rand() % 100 + 1;
    int guess = 0;
    while (1)
    {
        printf("请猜数字:>");
        scanf("%d", &guess);
        if (guess < ret)
            printf("猜小了\n");
        else if (guess > ret)
            printf("猜大了\n");
        else
        {
            printf("恭喜你，猜对了\n");
            break;
        }
    }
}

// 猜数字游戏 (do-while与switch综合)
void demo_17_guess_game()
{
    printf("=== 17. 猜数字游戏 ===\n");
    int input = 0;
    // 设置随机数生成器，使用时间戳作为种子，确保每次运行随机数不同
    srand((unsigned int) time(NULL));
    do
    {
        printf("**************************\n");
        printf("****** 1. play     ******\n");
        printf("****** 0. exit     ******\n");
        printf("**************************\n");
        printf("请选择>:");
        scanf("%d", &input);
        switch (input)
        {
            case 1:
                game_logic();
                break;
            case 0:
                printf("退出游戏\n");
                break;
            default:
                printf("选择错误，重新选择\n");
                break;
        }
    } while (input);
}

// Goto 语句与关机恶作剧
void demo_18_goto_shutdown()
{
    printf("=== 18. Goto与关机程序 ===\n");
    // 提示：system("shutdown -s -t 60") 会在60秒后关机
    // system("shutdown -a") 取消关机
    // 为了防止测试时真的关机，仅做逻辑演示，实际执行代码已注释

    /*
    char input[20] = { 0 };
    system("shutdown -s -t 60");
    again:
        printf("你的电脑在1分钟内就会关机，如果输入：我是猪，就取消关机\n");
        scanf("%s", input);
        if (strcmp(input, "我是猪") == 0) {
            system("shutdown -a");
            printf("你很配合，已经取消关机\n");
        } else {
            goto again; // 跳转回去
        }
    */

    printf("由于涉及系统关机命令，代码已在 demo_18 中注释保护，请查看源码学习逻辑。\n");
    printf("goto 语句通常尽量少用，但在多层嵌套跳出或错误处理时有奇效。\n");
}


int main()
{
    // --- 第一部分：基础与分支 ---
    demo_01_statements();
    demo_02_if_basic();
    demo_03_if_nested();
    demo_04_dangling_else();
    demo_05_coding_style();
    demo_06_switch();
    demo_07_switch_nested();

    // --- 第二部分：循环控制 ---
    demo_08_loops();
    demo_09_break_continue();
    demo_10_do_while();

    // --- 第三部分：缓冲区 ---
    demo_11_getchar_basic();
    demo_12_buffer_clear();

    // --- 第四部分：算法实践 ---
    demo_13_factorial();
    demo_14_binary_search();
    demo_15_string_animation();
    demo_16_login();

    // --- 第五部分：综合 ---
    demo_17_guess_game(); // <--- 经典小游戏
    demo_18_goto_shutdown();

    return 0;
}
