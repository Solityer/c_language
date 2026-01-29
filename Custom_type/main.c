#include <stdio.h>
#include <stddef.h> // 用于使用 offsetof 宏

/*
 * ============================================================
 * 第一部分：结构体的基础定义与初始化
 * ============================================================
 */

// 1. 标准声明
struct Student
{
    char name[20];
    int age;
    char sex[5];
    float score;
} s1, s2; // s1, s2 是全局变量

// 2. 匿名结构体 (不推荐)
// 这种写法只能在声明时创建变量，后续无法再次使用该类型定义新变量
struct
{
    char name[20];
    int age;
} anonymous_var;

// 3. 结构体的自引用
// 错误写法：
// struct Node {
//     int data;
//     struct Node n; // ERR: 结构体大小无法确定，无限递归
// };

// 正确写法：使用指针
typedef struct Node
{
    int data; // 数据域
    struct Node *next; // 指针域：存放下一个节点的地址
} Node; // typedef 重命名为 Node

/*
 * ============================================================
 * 第二部分：结构体内存对齐 (核心重点)
 * ============================================================
 *
 * 为什么要对齐？
 * 1. 平台原因(移植性)：不是所有的硬件平台都能访问任意地址上的任意数据。
 * 2. 性能原因：为了访问未对齐的内存，处理器需要作两次内存访问；而对齐的内存访问仅需要一次。
 * (以空间换时间)
 *
 * 对齐规则：
 * 1. 第一个成员在与结构体变量偏移量为0的地址处。
 * 2. 其他成员变量要对齐到某个数字（对齐数）的整数倍的地址处。
 * 对齐数 = 编译器默认的一个对齐数 与 该成员大小的较小值。
 * (VS默认对齐数是8，Linux gcc默认是对齐数是4，也就是成员自身大小)
 * 3. 结构体总大小为最大对齐数（每个成员变量都有一个对齐数）的整数倍。
 * 4. 如果嵌套了结构体，嵌套的结构体对齐到自己的最大对齐数的整数倍处，
 * 结构体的整体大小就是所有最大对齐数（含嵌套结构体的对齐数）的整数倍。
 */

// --- 案例 A: 基础对齐 ---
struct S1
{
    char c1; // 大小1, 偏移量0。当前占用: [0]
    // 填充: [1][2][3] (因为下一个成员int是对齐数4的倍数，必须从4开始)
    int i; // 大小4, 对齐数4。偏移量4。当前占用: [4][5][6][7]
    char c2; // 大小1, 对齐数1。偏移量8。当前占用: [8]
    // 结尾填充: [9][10][11] (总大小必须是最大对齐数4的倍数，所以是12)
};

// --- 案例 B: 成员顺序影响大小 ---
struct S2
{
    char c1; // [0]
    char c2; // [1] (对齐数1，直接放)
    // 填充: [2][3]
    int i; // [4][5][6][7]
    // 总大小: 8。相比S1，仅仅改变顺序就节省了空间。
};

// --- 案例 C: 嵌套结构体 ---
struct S3
{
    double d; // 8 byte
    char c; // 1 byte
    int i; // 4 byte
    // 结构体总大小：16 (8 + 1 + 3(padding) + 4)
    // S3的最大对齐数是 8 (double)
};

struct S4
{
    char c1; // 1 byte. offset 0
    // 填充: [1]...[7] (因为S3最大对齐数是8)
    struct S3 s3; // 16 bytes. offset 8. (8-23)
    double d; // 8 bytes. offset 24. (24-31)
    // 总大小 32
};

// --- 案例 D: 修改默认对齐数 ---
#pragma pack(1) // 设置默认对齐数为 1 (相当于不对齐，紧凑排列)
struct S_Packed
{
    char c1; // 1
    int i; // 4 (1与4比较，取1，所以直接挨着放)
    char c2; // 1
};
#pragma pack() // 取消设置，还原为默认

/*
 * ============================================================
 * 第三部分：位段 (Bit Field)
 * ============================================================
 * 作用：节省空间。成员必须是 int, unsigned int, signed int 或 char。
 * 格式：成员名后加冒号和比特位大小。
 */
struct BitField
{
    int _a: 2; // 占2个bit
    int _b: 5; // 占5个bit
    int _c: 10; // 占10个bit
    int _d: 30; // 占30个bit
    // 注意：_d 无法在第一个int剩余的空间放下(32-17=15 < 30)，会开辟新的空间。
    // 总大小取决于编译器实现，通常是int(4字节)的整数倍。
};

/*
 * ============================================================
 * 第四部分：枚举 (Enum)
 * ============================================================
 * 作用：增加代码可读性。
 */
enum Sex
{
    MALE = 3, // 赋初值，后续自动递增
    FEMALE, // 4
    SECRET // 5
};

/*
 * ============================================================
 * 第五部分：联合体 (Union)
 * ============================================================
 * 特点：所有成员共用同一块内存。大小至少是最大成员的大小。
 */
union Un
{
    char c; // 1 byte
    int i; // 4 bytes
    // 总大小：4 bytes
};

// 判断大小端字节序的经典面试题
// 小端(Little Endian): 低位字节排放在低地址端
// 大端(Big Endian): 低位字节排放在高地址端
int check_sys_is_little_endian()
{
    union
    {
        char c;
        int i;
    } u;
    u.i = 1;
    // 内存逻辑: 0x00000001
    // 小端存储: 01 00 00 00 (低地址存低位01)
    // 大端存储: 00 00 00 01 (低地址存高位00)
    return u.c; // 返回1则是小端，0则是大端
}

/*
 * ============================================================
 * 主函数：逻辑测试与验证
 * ============================================================
 */
int main()
{
    printf("========== 1. 结构体内存对齐测试 ==========\n");
    // 使用 offsetof 宏查看成员偏移量 (需要 <stddef.h>)
    // 验证 struct S1 { char c1; int i; char c2; };
    printf("S1 c1 offset: %zd\n", offsetof(struct S1, c1)); // 0
    printf("S1 i  offset: %zd\n", offsetof(struct S1, i)); // 4
    printf("S1 c2 offset: %zd\n", offsetof(struct S1, c2)); // 8
    printf("S1 total size: %zd\n", sizeof(struct S1)); // 12

    printf("S2 total size: %zd (优化顺序后)\n", sizeof(struct S2)); // 8
    printf("S4 total size: %zd (嵌套结构体)\n", sizeof(struct S4)); // 32
    printf("S_Packed size: %zd (pragma pack(1))\n", sizeof(struct S_Packed)); // 6

    printf("\n========== 2. 位段测试 ==========\n");
    printf("BitField size: %zd\n", sizeof(struct BitField)); // 8 (两个int空间)

    printf("\n========== 3. 枚举测试 ==========\n");
    enum Sex sex = SECRET;
    printf("MALE: %d, FEMALE: %d, SECRET: %d\n", MALE, FEMALE, SECRET);
    printf("sizeof(sex): %zd\n", sizeof(sex)); // 通常是4 (int)

    printf("\n========== 4. 联合体与大小端测试 ==========\n");
    union Un un;
    printf("union addr: %p\n", &un);
    printf("un.c addr:  %p\n", &(un.c));
    printf("un.i addr:  %p (地址相同)\n", &(un.i));

    if (check_sys_is_little_endian())
        printf("当前机器模式: 小端 (Little Endian)\n");
    else
        printf("当前机器模式: 大端 (Big Endian)\n");

    printf("\n========== 5. 传值与传址 ==========\n");
    /*
     * 经验法则：结构体传参时，尽量传址（指针）。
     * 原因：函数传参时需要压栈。如果结构体过大，传值（拷贝整个结构体）会
     * 导致系统开销大，性能下降。
     */
    struct S2 my_struct = {'A', 'B', 100};
    // print1(my_struct);  // 传值：开销大
    // print2(&my_struct); // 传址：开销小，只需传递一个指针大小(4/8字节)

    return 0;
}
