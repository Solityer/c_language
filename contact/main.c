#include "contact.h"

// 打印菜单
void menu()
{
    printf("\n");
    printf("****************************************\n");
    printf("**** 1. add             2. del      ****\n");
    printf("**** 3. search          4. modify   ****\n");
    printf("**** 5. show            6. sort     ****\n");
    printf("**** 0. exit                        ****\n");
    printf("****************************************\n");
}

// 使用枚举增加代码可读性，避免使用魔术数字 (Magic Numbers)
enum Option
{
    EXIT, // 0
    ADD, // 1
    DEL, // 2
    SEARCH, // 3
    MODIFY, // 4
    SHOW, // 5
    SORT // 6
};

int main()
{
    int input = 0;

    // 创建通讯录对象
    // 此时 con 中的 data 指针未初始化，包含随机值
    Contact con;

    // 初始化：分配堆区内存，并从 contact.txt 加载数据
    InitContact(&con);

    do
    {
        menu();
        printf("请输入你的选择:>");
        scanf("%d", &input);

        // 建议：此处可以增加对 input 的校验逻辑，防止输入非数字字符导致的死循环

        switch (input)
        {
            case ADD:
                AddContact(&con);
                break;
            case DEL:
                DelContact(&con);
                break;
            case SEARCH:
                SearchContact(&con);
                break;
            case MODIFY:
                ModifyContact(&con);
                break;
            case SHOW:
                ShowContact(&con);
                break;
            case SORT:
                // 扩展思考：你可以利用 qsort 标准库函数实现排序
                // qsort 需要你自定义一个 compar 函数指针
                printf(">> 排序功能暂未实现，建议作为练习自行扩展。\n");
                break;
            case EXIT:
                // 退出前必须做两件事，这是保证数据安全和内存安全的关键：
                // 1. 保存数据到文件
                SaveContact(&con);
                // 2. 释放动态开辟的内存
                DestroyContact(&con);
                printf(">> 退出通讯录，再见。\n");
                break;
            default:
                printf(">> 选择错误，请重新选择。\n");
                break;
        }
    } while (input);

    return 0;
}
