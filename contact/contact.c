#include "contact.h"

// -----------------------------------------------------------------------------
// 内部辅助函数声明 (Static Functions)
// static 关键字限制函数作用域仅在当前文件，实现信息的“封装”与“隐藏”
// -----------------------------------------------------------------------------
void CheckCapacity(Contact *pc); // 检查容量并在必要时扩容
static int FindByName(Contact *pc, char name[]); // 根据名字查找索引，找不到返回-1

// -----------------------------------------------------------------------------
// 数据持久化模块：Load & Save
// -----------------------------------------------------------------------------

// 从文件加载数据到内存
// 逻辑：文件存在则读取 -> 循环读取块 -> 检测容量自动扩容 -> 存入内存
void LoadContact(Contact *pc)
{
    // 使用 "rb" (read binary) 模式，保证不同平台下读取的字节流一致
    FILE *pf = fopen("contact.txt", "rb");
    if (pf == NULL)
    {
        // 第一次运行可能没有文件，属于正常情况，直接返回即可
        return;
    }

    // 临时缓冲区，用于承接每次 fread 读出的数据
    PeoInfo tmp = {0};

    // fread 返回实际读取的元素个数。
    // 当文件结束或读取错误时，返回值将小于 count (此处为1)，循环结束
    while (fread(&tmp, sizeof(PeoInfo), 1, pf))
    {
        CheckCapacity(pc); // 读取过程中，如果初始容量不足，需要动态扩容
        pc->data[pc->sz] = tmp;
        pc->sz++;
    }

    fclose(pf);
    pf = NULL;
}

// 保存内存数据到文件
// 逻辑：以二进制写模式打开 -> 遍历内存数组 -> 写入文件
void SaveContact(Contact *pc)
{
    // 使用 "wb" (write binary) 模式
    FILE *pf = fopen("contact.txt", "wb");
    if (pf == NULL)
    {
        // 只有写入失败（如磁盘满、权限不足）才需要报错
        perror("SaveContact");
        return;
    }

    // 循环写入
    // 注意：此处也可以使用 fwrite(pc->data, sizeof(PeoInfo), pc->sz, pf) 一次性写入
    for (int i = 0; i < pc->sz; i++)
    {
        // 指针运算 pc->data + i 等价于 &pc->data[i]
        fwrite(pc->data + i, sizeof(PeoInfo), 1, pf);
    }

    fclose(pf);
    pf = NULL;
    printf(">> 通讯录数据已保存至本地文件。\n");
}

// -----------------------------------------------------------------------------
// 初始化与销毁
// -----------------------------------------------------------------------------

// 动态版本的初始化
void InitContact(Contact *pc)
{
    assert(pc); // 断言指针有效性，防止空指针解引用

    pc->sz = 0;
    pc->capacity = DEFAULT_SZ;

    // calloc 相比 malloc 的优势在于会自动将申请的内存初始化为0
    // 避免了后续未初始化读取导致的脏数据问题
    pc->data = (PeoInfo *) calloc(pc->capacity, sizeof(PeoInfo));
    if (pc->data == NULL)
    {
        perror("InitContact->calloc");
        return;
    }

    // 初始化内存后，立即尝试从磁盘加载历史数据
    // 这是数据持久化的关键步骤
    LoadContact(pc);
}

// 销毁通讯录
// 在程序退出前必须调用，这是 C/C++ 程序员必须养成的良好习惯
void DestroyContact(Contact *pc)
{
    assert(pc);

    free(pc->data); // 归还堆区内存给操作系统
    pc->data = NULL; // 避免悬空指针 (Dangling Pointer)
    pc->sz = 0;
    pc->capacity = 0;
    printf(">> 内存资源已释放。\n");
}

// -----------------------------------------------------------------------------
// 核心功能实现
// -----------------------------------------------------------------------------

// 扩容逻辑：当 sz 达到 capacity 时触发
void CheckCapacity(Contact *pc)
{
    assert(pc);
    if (pc->sz == pc->capacity)
    {
        // realloc 调整内存块大小。
        // 1. 如果原内存块后有足够空间，直接扩展。
        // 2. 如果不足，开辟新空间，拷贝数据，释放旧空间，返回新地址。
        PeoInfo *ptr = (PeoInfo *) realloc(pc->data, (pc->capacity + DEFAULT_INC) * sizeof(PeoInfo));

        if (ptr != NULL)
        {
            pc->data = ptr;
            pc->capacity += DEFAULT_INC;
            printf(">> 增容成功，当前容量: %d\n", pc->capacity);
        }
        else
        {
            perror("CheckCapacity->realloc");
            // 扩容失败可以根据策略处理，这里选择打印错误并返回，不做崩溃处理
            return;
        }
    }
}

// 增加联系人
void AddContact(Contact *pc)
{
    assert(pc);
    // 1. 检查并确保有足够容量
    CheckCapacity(pc);

    // 2. 录入信息
    printf("请输入名字: ");
    scanf("%s", pc->data[pc->sz].name);
    printf("请输入年龄: ");
    scanf("%d", &(pc->data[pc->sz].age));
    printf("请输入性别: ");
    scanf("%s", pc->data[pc->sz].sex);
    printf("请输入电话: ");
    scanf("%s", pc->data[pc->sz].tele);
    printf("请输入地址: ");
    scanf("%s", pc->data[pc->sz].addr);

    pc->sz++;
    printf(">> 增加成功\n");
}

// 显示所有联系人
void ShowContact(const Contact *pc)
{
    assert(pc);
    if (pc->sz == 0)
    {
        printf("通讯录为空，无需打印\n");
        return;
    }

    // 格式化打印：%-20s 表示左对齐，占20个字符宽度
    printf("%-20s%-5s%-5s%-12s%-30s\n", "名字", "年龄", "性别", "电话", "地址");
    for (int i = 0; i < pc->sz; i++)
    {
        printf("%-20s%-5d%-5s%-12s%-30s\n",
               pc->data[i].name, pc->data[i].age, pc->data[i].sex, pc->data[i].tele, pc->data[i].addr);
    }
}

// 内部查找函数
static int FindByName(Contact *pc, char name[])
{
    assert(pc);
    for (int i = 0; i < pc->sz; i++)
    {
        if (strcmp(pc->data[i].name, name) == 0)
        {
            return i; // 找到返回下标
        }
    }
    return -1; // 找不到
}

// 删除联系人
void DelContact(Contact *pc)
{
    char name[NAME_MAX];
    assert(pc);
    if (pc->sz == 0)
    {
        printf("通讯录为空，无法删除\n");
        return;
    }
    printf("输入要删除人的名字: ");
    scanf("%s", name);

    int ret = FindByName(pc, name);
    if (ret == -1)
    {
        printf("要删除的人不存在\n");
        return;
    }

    // 删除操作：数据搬移
    // 将 ret 位置之后的数据整体向前挪动一位
    // 边界处理：i 最大只能取到 sz-2，因为要访问 i+1
    for (int i = ret; i < pc->sz - 1; i++)
    {
        pc->data[i] = pc->data[i + 1];
    }

    pc->sz--;
    printf(">> 删除成功\n");
}

// 查找并显示
void SearchContact(Contact *pc)
{
    char name[NAME_MAX];
    assert(pc);
    printf("请输入要查找人的名字: ");
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
void ModifyContact(Contact *pc)
{
    char name[NAME_MAX];
    assert(pc);
    printf("请输入要修改人的名字: ");
    scanf("%s", name);
    int ret = FindByName(pc, name);
    if (ret == -1)
    {
        printf("要修改的人不存在\n");
        return;
    }

    printf("开始修改信息 (当前不支持修改名字)...\n");
    // 如果需要修改名字，需要额外处理，避免名字修改后导致逻辑问题（如重复）
    printf("请输入新的名字: ");
    scanf("%s", pc->data[ret].name);
    printf("请输入新的年龄: ");
    scanf("%d", &(pc->data[ret].age));
    printf("请输入新的性别: ");
    scanf("%s", pc->data[ret].sex);
    printf("请输入新的电话: ");
    scanf("%s", pc->data[ret].tele);
    printf("请输入新的地址: ");
    scanf("%s", pc->data[ret].addr);

    printf(">> 修改成功\n");
}
