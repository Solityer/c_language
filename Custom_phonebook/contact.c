#define _CRT_SECURE_NO_WARNINGS
#include "contact.h"

void InitContact(Contact* pc)
{
    assert(pc);
    memset(pc->data, 0, sizeof(pc->data));
    pc->sz = 0;
}

void AddContact(Contact* pc)
{
    assert(pc);
    if (pc->sz == 100)
    {
        printf("The address book is full and cannot be added!\n");//通讯录已满,无法添加
        return;
    }
    printf("please enter name:");  //请输入名字
    scanf("%s", pc->data[pc->sz].name);
    //    printf("please enter age:");  //请输入年龄
    //    scanf("%d",pc->data[pc->sz].age);
    printf("please enter sex:");  //请输入性别
    scanf("%s", pc->data[pc->sz].sex);
    printf("please enter tele:");  //请输入电话
    scanf("%s", pc->data[pc->sz].tele);
    printf("please enter addr:");  //请输入地址
    scanf("%s", pc->data[pc->sz].addr);
    pc->sz++;
    printf("Successfully added contact information\n"); //成功增加联系人信息
}

void ShowContact(const Contact* pc)
{
    assert(pc);
    int i = 0;
    printf("%-10s\t%-4s\t%-5s\t%-12s\t%-30s\n", "name", "age", "sex", "tele", "addr");
    for (i = 0; i < pc->sz; ++i)
    {
        ;
    }
    for (i = 0; i < pc->sz; i++)
    {
        printf("%-10s\t%-4d\t%-5s\t%-12s\t%-30s\n", pc->data[i].name,
            pc->data[i].age,
            pc->data[i].sex,
            pc->data[i].tele,
            pc->data[i].addr);
    }
}

int FindByName(const Contact* pc, char name[])
{
    int i = 0;
    for (i = 0; i < pc->sz - 1; i++)
    {
        if (strcmp(pc->data[i].name, name) == 0)
        {
            return i; //找到了
        }
    }
    return -1; //没找到
}

void DelContact(Contact* pc)
{
    if (pc->sz == 0)
    {
        printf("The address book is empty and cannot be deleted!\n"); //通讯录为空,无法删除
        return;
    }
    char name[MAX_NAME] = { 0 };
    assert(pc);
    printf("Please enter the name of the person you want to delete:"); //请输入要删除的人的名字
    scanf("%s", name);
    //找到要删除的人
    int del = FindByName(pc, name);
    if (del == -1)
    {
        printf("The person who needs to be deleted does not exist!\n");  //需要删除的人不存在
        return;
    }
    //删除坐标位del的人
    int i = 0;
    for (i = del; i < pc->sz - 1; i++)
    {
        pc->data[i] = pc->data[i + 1];
    }
    pc->sz--;
    printf("The contact was deleted successfully!\n");//成功删除联系人
}

void SearchContact(const Contact* pc)
{
    char name[MAX_NAME] = { 0 };
    printf("Please enter the name of the person you want to search:"); //请输入要查找的人的名字
    scanf("%s", name);
    int pos = FindByName(pc, name);
    if (pos == -1)
    {
        printf("The person who needs to be search does not exist!\n");
    }
    else
    {
        printf("%-10s\t%-4s\t%-5s\t%-12s\t%-30s\n", "name", "age", "sex", "tele", "addr");
        printf("%-10s\t%-4d\t%-5s\t%-12s\t%-30s\n", pc->data[pos].name,
            pc->data[pos].age,
            pc->data[pos].sex,
            pc->data[pos].tele,
            pc->data[pos].addr);
    }
}

void ModifyContact(Contact* pc)
{
    assert(pc);
    char name[MAX_NAME] = { 0 };

    printf("Please enter the name of the person you want to modify:"); //请输入要删除的人的名字
    scanf("%s", name);
    //找到要删除的人
    int pos = FindByName(pc, name);
    if (pos == -1)
    {
        printf("The person who needs to be modify does not exist!\n");  //需要删除的人不存在
    }
    else
    {
        printf("please enter name:");  //请输入名字
        scanf("%s", pc->data[pos].name);
        //    printf("please enter age:");  //请输入年龄
        //    scanf("%d",pc->data[pos].age);
        printf("please enter sex:");  //请输入性别
        scanf("%s", pc->data[pos].sex);
        printf("please enter tele:");  //请输入电话
        scanf("%s", pc->data[pos].tele);
        printf("please enter addr:");  //请输入地址
        scanf("%s", pc->data[pos].addr);
        printf("Success modify!\n");
    }
}