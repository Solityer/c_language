#define _CRT_SECURE_NO_WARNINGS
//文件操作
#include <stdio.h>

struct S
{
    int a;
    float s;
};
struct S1
{
    int a;
    float s;
    char str[10];
};

int main() {
    /*字符的输入输出函数*/
    //打开文件  //FILE * fopen ( const char * filename, const char * mode );
    FILE* pf1 = fopen("..\\data1.txt", "r");  //绝对路径
    if (pf1 == NULL)
    {
        perror("fopen");
        return 1;
    }
    //写文件   //顺序写,依次往后追加写入
    for (int i = 0; i < 26; ++i)
    {
        fputc('a' + i, pf1);
    }
    //读文件  //fgetc只有当fopen中mode为"r"时候才能输出读取
    int ch = fgetc(pf1);  //传入的是指针,从文件中读
    printf("%c\n", ch);
    ch = fgetc(pf1);
    printf("%c\n", ch);
    ch = fgetc(pf1);
    printf("%c\n", ch);
    ch = fgetc(pf1);
    printf("%c\n", ch);
    //关闭文件  //int fclose ( FILE * stream );
    fclose(pf1);
    pf1 = NULL;



    /*文本的输入输出函数*/
    FILE* pf2 = fopen("..\\data2.txt", "r");
    if (pf2 == NULL)
    {
        perror("fopen");
        return 1;
    }
    //    //写文件 ---- 写一行
    //    fputs("hello bit\n",pf2);
    //    fputs("hello solity\n",pf2);
    //    fputs("hello pengzhihao\n",pf2);
        //读文件 ---- 读一行
    char arr2[30] = { 0 };
    fgets(arr2, 30, pf2);  //只能读取MaxCount-1个字符,要么读够,要么读到换行位置
    printf("%s", arr2);
    fgets(arr2, 30, pf2);  //只能读取MaxCount-1个字符,要么读够,要么读到换行位置
    printf("%s", arr2);
    fgets(arr2, 30, pf2);  //只能读取MaxCount-1个字符,要么读够,要么读到换行位置
    printf("%s", arr2);
    //关闭文件
    fclose(pf2);
    pf2 = NULL;



    /*格式化输入输出函数*/
    FILE* pf3 = fopen("..\\data3.txt", "r");
    if (pf3 == NULL)
    {
        perror("fopen");
        return 1;
    }
    //    //写文件
    //    struct S s = {100,3.14f};
    //    fprintf(pf3,"%d %f",s.a,s.b);
        //读文件
    struct S s = { 0 };
    fscanf(pf3, "%d %f", &(s.a), &(s.s));
    printf("%d %f", s.a, s.s);
    //关闭文件
    fclose(pf3);
    pf3 = NULL;

    //了解sprintf
    char arr[30] = { 0 };
    struct S1 s1 = { 100,3.14f,"hehe" };
    struct S1 tmp1 = { 0 };
    //写入数据
    //将后面的数据按中间的格式打印到arr里(将格式化的数据转换成字符串)
    sprintf(arr, "%d %f %s\n", s1.a, s1.s, s1.str);
    printf("%s\n", arr);
    //提取数据
    //从arr里按中间的格式读取到tmp1里(从字符串中读取格式化的数据)
    sscanf(arr, "%d %f %s\n", &(tmp1.a), &(tmp1.s), tmp1.str);
    printf("%d %f %s\n", tmp1.a, tmp1.s, tmp1.str);



    /*二进制输入和输出函数*/
    FILE* pf4 = fopen("..\\data4.txt", "rb");
    if (pf4 == NULL)
    {
        perror("fopen");
        return 1;
    }
    //    struct S1 s2 = {100,3.14f,"bit"};
    //    //写文件
    //    fwrite(&s2,sizeof(struct S1),1,pf4);  //从s2中读取1个大小为sizeof(struct S1)的内容到pf4指向的文件中
    struct S1 s3 = { 0 };
    fread(&s3, sizeof(struct S1), 1, pf4);  //从pf4中读取一个大小为sizeof(struct S1)的内容存放s3中
    printf("%d %f %s\n", s3.a, s3.s, s3.str);
    //关闭文件
    fclose(pf4);
    pf4 = NULL;



    /*文件的随机读写*/
    //fseek
    FILE* pf5 = fopen("..\\data5.txt", "r");
    if (pf5 == NULL)
    {
        perror("fopen");
        return 1;
    }
    //读文件
    //定位文件指针
    fseek(pf5, 5, SEEK_SET); //初始位置
    int ch1 = fgetc(pf5);
    printf("%c\n", ch1);

    fseek(pf5, -4, SEEK_END); //末尾位置
    int ch2 = fgetc(pf5);
    printf("%c\n", ch2);

    int ch3 = fgetc(pf5);
    ch3 = fgetc(pf5);
    fseek(pf5, 3, SEEK_CUR); //当前位置
    int ch4 = fgetc(pf5);
    printf("%c\n", ch3);


    //ftell 根据文件指针的位置和偏移量来定位文件指针
    int ch5 = fgetc(pf5);
    ch5 = fgetc(pf5);
    int pos = ftell(pf5);
    printf("%d\n", pos);
    //rewind 让文件指针回到起始位置
    rewind(pf5);
    int ch6 = fgetc(pf5);
    printf("%c\n", ch6);
    fclose(pf5);
    pf5 = NULL;
    return 0;
}
