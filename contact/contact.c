#define _CRT_SECURE_NO_WARNINGS 1
#include "contact.h"

// -----------------------------------------------------------------------------
// 内部辅助函数声明
// -----------------------------------------------------------------------------
void CheckCapacity(Contact* pc); // 检查并扩容
static int FindByName(Contact* pc, char name[]); // 根据名字查找索引

// -----------------------------------------------------------------------------
// 数据持久化模块：Load & Save
// -----------------------------------------------------------------------------

// 从文件加载数据到内存
// 逻辑：读取二进制文件 -> 循环读取块 -> 检测容量自动扩容 -> 存入内存
void LoadContact(Contact* pc)
{
	FILE* pf = fopen("contact.txt", "rb"); // 以二进制读模式打开
	if (pf == NULL)
	{
		// 第一次运行可能没有文件，属于正常情况，不报错或仅提示
		// perror("LoadContact");
		return;
	}

	// 临时缓冲区
	PeoInfo tmp = { 0 };

	// fread 返回实际读取的元素个数。当返回 0 时表示文件结束
	while (fread(&tmp, sizeof(PeoInfo), 1, pf))
	{
		CheckCapacity(pc); // 确保内存足够
		pc->data[pc->sz] = tmp;
		pc->sz++;
	}

	fclose(pf);
	pf = NULL;
}

// 保存内存数据到文件
// 逻辑：以二进制写模式打开 -> 遍历内存数组 -> 写入文件
void SaveContact(Contact* pc)
{
	FILE* pf = fopen("contact.txt", "wb");
	if (pf == NULL)
	{
		perror("SaveContact"); // 只有写入失败才需要报错（如权限问题）
		return;
	}

	// 批量写入或循环写入
	// 这里采用循环写入，更稳健
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		// 指针运算 pc->data + i 等价于 &pc->data[i]
		fwrite(pc->data + i, sizeof(PeoInfo), 1, pf);
	}

	fclose(pf);
	pf = NULL;
	printf("通讯录数据已保存。\n");
}

// -----------------------------------------------------------------------------
// 初始化与销毁
// -----------------------------------------------------------------------------

// 动态版本的初始化
void InitContact(Contact* pc)
{
	assert(pc);

	pc->sz = 0;
	pc->capacity = DEFAULT_SZ;
	// calloc 会自动将内存初始化为0，适合初始化结构体
	pc->data = (PeoInfo*)calloc(pc->capacity, sizeof(PeoInfo));
	if (pc->data == NULL)
	{
		perror("InitContact->calloc");
		return;
	}

	// 初始化内存后，立即尝试加载历史数据
	LoadContact(pc);
}

// 销毁通讯录：防止内存泄漏 (Memory Leak)
// 在程序退出前必须调用
void DestroyContact(Contact* pc)
{
	free(pc->data);
	pc->data = NULL;
	pc->sz = 0;
	pc->capacity = 0;
	printf("内存资源已释放。\n");
}

// -----------------------------------------------------------------------------
// 核心功能实现
// -----------------------------------------------------------------------------

// 扩容逻辑：当 sz 达到 capacity 时触发
void CheckCapacity(Contact* pc)
{
	if (pc->sz == pc->capacity)
	{
		// realloc 调整内存块大小。注意：如果原位置后面空间不足，会在新位置开辟并拷贝数据
		PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (pc->capacity + DEFAULT_INC) * sizeof(PeoInfo));
		if (ptr != NULL)
		{
			pc->data = ptr;
			pc->capacity += DEFAULT_INC;
			printf("增容成功，当前容量: %d\n", pc->capacity);
		}
		else
		{
			perror("CheckCapacity->realloc");
			return; // 扩容失败，保持原状
		}
	}
}

// 增加联系人
void AddContact(Contact* pc)
{
	assert(pc);
	// 1. 检查容量
	CheckCapacity(pc);

	// 2. 录入信息
	printf("请输入名字:");
	scanf("%s", pc->data[pc->sz].name);
	printf("请输入年龄:");
	scanf("%d", &(pc->data[pc->sz].age));
	printf("请输入性别:");
	scanf("%s", pc->data[pc->sz].sex);
	printf("请输入电话:");
	scanf("%s", pc->data[pc->sz].tele);
	printf("请输入地址:");
	scanf("%s", pc->data[pc->sz].addr);

	pc->sz++;
	printf("增加成功\n");
}

// 显示所有联系人
void ShowContact(const Contact* pc)
{
	assert(pc);
	if (pc->sz == 0)
	{
		printf("通讯录为空，无需打印\n");
		return;
	}
	int i = 0;
	// 格式化打印：%-20s 表示左对齐，占20个字符宽度
	printf("%-20s%-5s%-5s%-12s%-30s\n", "名字", "年龄", "性别", "电话", "地址");
	for (i = 0; i < pc->sz; i++)
	{
		printf("%-20s%-5d%-5s%-12s%-30s\n",
			pc->data[i].name, pc->data[i].age, pc->data[i].sex, pc->data[i].tele, pc->data[i].addr);
	}
}

// 内部查找函数 (static 修饰，仅在本文件可见)
static int FindByName(Contact* pc, char name[])
{
	assert(pc);
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, name) == 0)
		{
			return i; // 找到返回下标
		}
	}
	return -1; // 找不到
}

// 删除联系人
// 逻辑：找到位置 -> 将后续元素前移覆盖 -> sz--
void DelContact(Contact* pc)
{
	char name[NAME_MAX];
	assert(pc);
	if (pc->sz == 0)
	{
		printf("通讯录为空，无法删除\n");
		return;
	}
	printf("输入要删除人的名字:");
	scanf("%s", name);

	int ret = FindByName(pc, name);
	if (ret == -1)
	{
		printf("要删除的人不存在\n");
		return;
	}

	// 删除操作：数据搬移
	int i = 0;
	for (i = ret; i < pc->sz - 1; i++)
	{
		pc->data[i] = pc->data[i + 1];
	}

	pc->sz--;
	printf("删除成功\n");
}

// 查找并显示
void SearchContact(Contact* pc)
{
	char name[NAME_MAX];
	assert(pc);
	printf("请输入要查找人的名字:");
	scanf("%s", name);
	int ret = FindByName(pc, name);
	if (ret == -1)
	{
		printf("要查找的人不存在\n");
		return;
	}

	printf("%-20s%-5s%-5s%-12s%-30s\n", "名字", "年龄", "性别", "电话", "地址");
	printf("%-20s%-5d%-5s%-12s%-30s\n",
		pc->data[ret].name, pc->data[ret].age, pc->data[ret].sex, pc->data[ret].tele, pc->data[ret].addr);
}

// 修改联系人
void ModifyContact(Contact* pc)
{
	char name[NAME_MAX];
	assert(pc);
	printf("请输入要修改人的名字:");
	scanf("%s", name);
	int ret = FindByName(pc, name);
	if (ret == -1)
	{
		printf("要修改的人不存在\n");
		return;
	}

	printf("开始修改信息...\n");
	printf("请输入名字:");
	scanf("%s", pc->data[ret].name);
	printf("请输入年龄:");
	scanf("%d", &(pc->data[ret].age));
	printf("请输入性别:");
	scanf("%s", pc->data[ret].sex);
	printf("请输入电话:");
	scanf("%s", pc->data[ret].tele);
	printf("请输入地址:");
	scanf("%s", pc->data[ret].addr);

	printf("修改成功\n");
}