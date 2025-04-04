#pragma once

#include <stdio.h>
#include <string.h>  //包含memset函数
#include <assert.h>
#define MAX 100
#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDR 30

enum OPTION
{
    EXIT,  //0
    ADD, //1
    DEL,  //2
    SEARCH,  //3
    MODIFY,  //4
    SHOW,  //5
    SORT  //6
};

/*函数类型的声明*/

typedef struct PeoInfo
{
    char name[MAX_NAME];
    int age;
    char sex[MAX_SEX];
    char tele[MAX_TELE];
    char addr[MAX_ADDR];
}PeoInfo;
//通讯录
typedef struct Contact
{
    PeoInfo data[MAX];
    int sz;  //用来记录通讯录的人数
}Contact;

/*函数声明*/
//初始化通讯录
void InitContact(Contact* pc);
//增加联系人
void AddContact(Contact* pc);
//展示通讯录人员信息
void ShowContact(const Contact* pc);
//查找联系人
int FindByName(const Contact* pc, char name[]);
//删除指定联系人
void DelContact(Contact* pc);
//查找指定联系人
void SearchContact(const Contact* pc);
//修改指定联系人
void ModifyContact(Contact* pc);




