#include <stdio.h>
#define SIZE 10  //标识符常量
#define CH 'w'
#include "add.h"

//库函数:c语言的编译器的现成函数,直接可以使用
//scanf的作用是输入函数,数据从键盘读取到内存中
//printf的作用是输出数据,数据从内存中输出到屏幕上

int a = 2024;
extern int g_val;
void test();
enum SEX
{
    //注：枚举常量的默认是从0开始，依次向下递增1的
    MALE,
    FEMALE,
    SECRET
};
int main() {
    char ch;
    scanf("%c", &ch);
    printf("%c\n", ch);

    printf("1---> %d\n", a);
    test();
    printf("g_val = %d\n", g_val);



    //常量
    /*字面常量
    const 修饰的常变量
    #define 定义的标识符常量
    枚举常量*/
    const int a1 = 3;  //const不能被修改
    printf("%d\n", a1);

    int arr[SIZE] = { 0 }; //不报错
    printf("%c\n", CH); //w

    //枚举常量
    printf("%d\n", MALE); //0
    printf("%d\n", FEMALE); //1
    printf("%d\n", SECRET); //2




    //字符串
    char arr1[] = "bit";
    char arr2[] = { 'b', 'i', 't' };
    char arr3[] = { 'b', 'i', 't', '\0' };
    char arr4[] = { '\0','b', 'i', 't' };
    printf("%s\n", arr1);
    printf("%s\n", arr2);
    printf("%s\n", arr3);
    printf("%s\n", arr4); //不打印

    //  \为转义字符,\\为反转义字符
    printf("c:\test\text.c\n"); //c:      est     ext.c
    printf("c:\\test\\text.c\n"); //c:\test\text.c
    printf("%c\n", 'a');
    printf("%c\n", '\''); //打印单引号
    printf("%s\n", "ab");
    printf("%s\n", "\"");
    printf("\a"); //警告字符,蜂鸣
    printf("abcdef\n");
    printf("abc\bdef"); //abdef  /b退格符
    // \ddd中ddd表示1~3个八进制的数字
    printf("%c\n", '\130'); //八进制的130转换为十进制后得到88,把88作为ASCII值代码的字符输出
    // \xdd中dd表示2个十六进制数字
    printf("%c\n", '\x31');
    return 0;
}

void test()
{
    printf("2---> %d\n", a);
}