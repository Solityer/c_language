#pragma once

// -----------------------------------------------------------------------------
// 核心头文件：contact.h
// 设计思路：定义数据模型（Model）和操作接口（API）。
// -----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc, free, calloc, realloc

// 宏定义：增强代码的可维护性
#define NAME_MAX 20
#define SEX_MAX 5
#define TELE_MAX 12
#define ADDR_MAX 30

#define MAX 100

// 动态增长策略：默认大小与每次增量
#define DEFAULT_SZ 3
#define DEFAULT_INC 2

// -----------------------------------------------------------------------------
// 数据结构定义
// -----------------------------------------------------------------------------

// 1. 联系人个体信息
typedef struct PeoInfo
{
	char name[NAME_MAX];
	int age;
	char sex[SEX_MAX];
	char tele[TELE_MAX];
	char addr[ADDR_MAX];
} PeoInfo;

// 2. 通讯录结构体（动态内存版本）
// 相比静态数组，这里使用指针指向堆区内存，并维护 capacity 记录容量
typedef struct Contact
{
	PeoInfo* data; // 指向动态分配的内存区域
	int sz;        // 当前有效元素的个数 (size)
	int capacity;  // 当前最大容量 (capacity)，用于判断是否扩容
} Contact;

// -----------------------------------------------------------------------------
// 接口声明 (API)
// -----------------------------------------------------------------------------

// 初始化通讯录 (从文件加载数据 + 初始化内存)
void InitContact(Contact* pc);

// 增加联系人 (含自动扩容检测)
void AddContact(Contact* pc);

// 显示所有的联系人
void ShowContact(const Contact* pc);

// 删除指定联系人
void DelContact(Contact* pc);

// 查找指定联系人
void SearchContact(Contact* pc);

// 修改指定联系人
void ModifyContact(Contact* pc);

// 销毁通讯录 (释放动态内存，防止内存泄漏)
void DestroyContact(Contact* pc);

// 保存信息到文件 (持久化)
void SaveContact(Contact* pc);