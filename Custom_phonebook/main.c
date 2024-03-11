#define _CRT_SECURE_NO_WARNINGS
//通讯录功能实现
#include <stdio.h>
#include "contact.h"

void menu();
void test();

int main() {
    test();
    return 0;
}

void menu()
{
    printf("*****************************\n");
    printf("******1.add       2.del******\n");
    printf("******3.search    4.modify***\n");
    printf("******5.show      6.sort*****\n");
    printf("******      0.exit      *****\n");
    printf("*****************************\n");
}
void test()
{
    int input = 0;
    //首先要有通讯录存放的地方
    Contact con;
    //初始化通讯录
    InitContact(&con);
    do
    {
        menu();
        printf("please select num:");
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
            break;
        case EXIT:
            printf("Exit Contacts"); //退出通讯录
            break;
        default:
            break;
        }
    } while (input);
}