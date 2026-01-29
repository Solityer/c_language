#pragma once
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // 包含 malloc, free, calloc, realloc 等内存管理函数

// 宏定义：增强代码的可维护性，避免由于数组越界导致的缓冲区溢出风险
#define NAME_MAX 20
#define SEX_MAX 5
#define TELE_MAX 12
#define ADDR_MAX 30

// 动态增长策略：
// DEFAULT_SZ: 初始开辟的元素个数
// DEFAULT_INC: 每次扩容增加的元素个数
#define DEFAULT_SZ 3
#define DEFAULT_INC 2

// -----------------------------------------------------------------------------
// 数据结构定义
// -----------------------------------------------------------------------------

// 1. 联系人个体信息结构体
// 使用定长数组存储字符串，内存布局紧凑，适合二进制读写
typedef struct PeoInfo
{
    char name[NAME_MAX];
    int age;
    char sex[SEX_MAX];
    char tele[TELE_MAX];
    char addr[ADDR_MAX];
} PeoInfo;

// 2. 通讯录管理结构体（动态内存版本）
// 核心差异：静态版本直接使用 PeoInfo data[100]，而这里使用指针维护堆区内存
typedef struct Contact
{
    PeoInfo *data; // 指向堆区动态分配的连续内存块
    int sz; // 当前已存储的有效元素个数 (Size)
    int capacity; // 当前内存块能容纳的最大元素个数 (Capacity)
} Contact;

// -----------------------------------------------------------------------------
// 接口声明 (API)
// -----------------------------------------------------------------------------

// 初始化通讯录
// 功能：初始化结构体成员，并从文件加载历史数据
void InitContact(Contact *pc);

// 增加联系人
// 逻辑：检查容量(CheckCapacity) -> 扩容(realloc) -> 写入数据
void AddContact(Contact *pc);

// 显示所有的联系人
void ShowContact(const Contact *pc);

// 删除指定联系人
// 逻辑：查找 -> 内存搬移(覆盖) -> 修正sz
void DelContact(Contact *pc);

// 查找指定联系人
void SearchContact(Contact *pc);

// 修改指定联系人
void ModifyContact(Contact *pc);

// 销毁通讯录
// 功能：释放堆区内存，防止内存泄漏 (Critical for C/C++)
void DestroyContact(Contact *pc);

// 保存信息到文件
// 功能：将内存中的数据序列化写入磁盘
void SaveContact(Contact *pc);
