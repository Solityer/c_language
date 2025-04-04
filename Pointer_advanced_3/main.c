#include <stdio.h>
#include <string.h>

int main() 
{
    //一维数组
    int a1[] = {1,2,3,4};
    printf("%d\n",sizeof(a1));  //数组长度,单位是字节  4*4=16
    printf("%d\n",sizeof(a1+0));  //数组首元素的地址,大小8个字节
    printf("%d\n",sizeof(*a1));  //数组首元素长度,大小4个字节
	printf("%d\n", sizeof(a1 + 1));  //数组第二个元素的地址,地址大小8
	printf("%d\n", sizeof(a1[1]));  //数组第二个元素的大小,4个字节
	printf("%d\n", sizeof(&a1));  //数组地址,大小8个字节
	printf("%d\n", sizeof(*&a1));  //等价与sizeof(a),16个字节
	printf("%d\n", sizeof(&a1 + 1));  //&a+1相对于&a跳过了一个数组,依然是地址,是地址就是4或8个字节
	printf("%d\n", sizeof(&a1[0]));  //数组是首元素的地址,8个字节
	printf("%d\n", sizeof(&a1[0] + 1)); //&a[0]是第一个元素,所有&a[0]+1是第二个元素地址,依然是8个字节
    
	//字符数组
	char arr[] = { 'a','b','c','d','e','f' };
	printf("%d\n", sizeof(arr));  //整个数组的大小,单位是字节,总共是6个字节
	printf("%d\n", sizeof(arr + 0));  //arr+0=arr,表示数组首元素地址,是地址就是8个字节
	printf("%d\n", sizeof(*arr));  //首元素地址,大小是1个字节
	printf("%d\n", sizeof(arr[1]));  //第二个元素地址,大小是1个字节
	printf("%d\n", sizeof(&arr));  //数组地址,8个字节
	printf("%d\n", sizeof(&arr + 1));  //跳过整个数组的地址,大小8个字节
	printf("%d\n", sizeof(&arr[0] + 1));  //第二个元素的地址,大小8个字节

	printf("%d\n", strlen(arr));  //数组中没有'\0',产生随机值
	printf("%d\n", strlen(arr + 0));  //首元素地址,无'\0',随机值
	//printf("%d\n", strlen(*arr)); //error,arr是数组首元素地址,*arr就是数组首元素,就是'a',ASCII值是97,将97作为地址传参
	//printf("%d\n", strlen(arr[1])); //error,同上
	printf("%d\n", strlen(&arr));  //数组地址,数组地址和数组首元素地址的值是一样的,随机值
	printf("%d\n", strlen(&arr + 1));
	printf("%d\n", strlen(&arr[0] + 1));  //第二个元素的地址,随机值


	char arr[] = "abcdef";  //[a b c d \0]
	printf("%d\n", sizeof(arr));  //7
	printf("%d\n", sizeof(arr + 0));  //首元素地址
	printf("%d\n", sizeof(*arr));  //首元素大小,字符是1个字节
	printf("%d\n", sizeof(arr[1]));  //第二个元素大小
	printf("%d\n", sizeof(&arr));  //数组地址,8个字节
	printf("%d\n", sizeof(&arr + 1));  //还是数组地址
	printf("%d\n", sizeof(&arr[0] + 1));  //第二个元素的地址,8个字节

	printf("%d\n", strlen(arr));  //数组长度,6
	printf("%d\n", strlen(arr + 0));  //同上
	//printf("%d\n", strlen(*arr));  //error
	//printf("%d\n", strlen(arr[1]));  //error
	printf("%d\n", strlen(&arr));  //6个
	printf("%d\n", strlen(&arr + 1));  //后面没有了,随机值
	printf("%d\n", strlen(&arr[0] + 1));  //5个


	char* p = "abcdef";
	printf("%d\n", sizeof(p));  //p是指针变量,大小就是8
	printf("%d\n", sizeof(p + 1));  //指'b'的地址,还是指针变量,大小还是8
	printf("%d\n", sizeof(*p));  //指'a',就是1个字节
	printf("%d\n", sizeof(p[0]));  //p[0] = *(p+0) = *p,还是1个字节
	printf("%d\n", sizeof(&p));  //&就是char**,还是地址,8个字节
	printf("%d\n", sizeof(&p + 1)); //8
	printf("%d\n", sizeof(&p[0] + 1));//'b'的地址,8个字节

	printf("%d\n", strlen(p));//6
	printf("%d\n", strlen(p + 1));//5
	//printf("%d\n", strlen(*p));
	//printf("%d\n", strlen(p[0]));
	printf("%d\n", strlen(&p));//0
	printf("%d\n", strlen(&p + 1));//0
	printf("%d\n", strlen(&p[0] + 1));//5


	//二维数组
	int a2[3][4] = { 0 };
	printf("%d\n", sizeof(a2));
	printf("%d\n", sizeof(a2[0][0]));
	printf("%d\n", sizeof(a2[0]));
	printf("%d\n", sizeof(a2[0] + 1));
	printf("%d\n", sizeof(*(a2[0] + 1)));
	printf("%d\n", sizeof(a2 + 1));
	printf("%d\n", sizeof(*(a2 + 1)));
	printf("%d\n", sizeof(&a2[0] + 1));
	printf("%d\n", sizeof(*(&a2[0] + 1)));
	printf("%d\n", sizeof(*a2));
	printf("%d\n", sizeof(a2[3]));
    return 0;
}
