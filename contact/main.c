#define _CRT_SECURE_NO_WARNINGS 1
// 测试通讯录的基本功能 - 业务逻辑层

#include "contact.h"

void menu()
{
    printf("\n********************************\n");
    printf("**** 1. add        2. del   ****\n");
    printf("**** 3. search     4. modify****\n");
    printf("**** 5. show       6. sort  ****\n");
    printf("**** 0. exit                ****\n");
    printf("********************************\n");
}

// 使用枚举增加代码可读性
enum Option
{
    EXIT,   // 0
    ADD,    // 1
    DEL,    // 2
    SEARCH, // 3
    MODIFY, // 4
    SHOW,   // 5
    SORT    // 6
};

int main()
{
    int input = 0;
    // 创建通讯录对象
    Contact con;

    // 初始化：分配内存并加载文件
    InitContact(&con);

    do
    {
        menu();
        printf("请输入你的选择:>");
        scanf("%d", &input);
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
                // 扩展思考：可以使用 qsort 函数实现按名字或年龄排序
                printf("排序功能暂未实现，可使用 qsort 扩展。\n");
                break;
            case EXIT:
                // 退出前必须做两件事：
                // 1. 保存数据
                SaveContact(&con);
                // 2. 释放动态开辟的内存
                DestroyContact(&con);
                printf("退出通讯录\n");
                break;
            default:
                printf("选择错误，重新选择\n");
                break;
        }
    } while (input);

    return 0;
}