/*字符函数和字符串函数*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


size_t my_strlen(const char* str);
char* my_strcpy(char* dest, const char* src);
char* my_strcat(char* dest, const char* src);
int my_strcmp(const char* src, const char* dst);
char* my_strstr(const char* str1, const char* str2);
void* my_memcpy(void* dst, const void* src, size_t count);
void* my_memmove(void* dst, const void* src, size_t count);


int main()
{
	/*strlen*/
	if ((int)strlen("abc") - (int)strlen("abcdef") > 0)  //strlen返回的无符号数,不能直接相减
	{
		printf("Greater than\n");
	}
	else
	{
		printf("Less than or equal\n");
	}
	//实现strlen
	size_t sz = my_strlen("abc");
	printf("%u\n", sz);


	/*strcpy*/
	char arr1[20] = { 0 };
	char arr2[] = "hello bit";
	char arr3[20] = "xxxxx";
	char arr4[5] = { 'a','b','c','d','e' };
	char arr5[6] = { 'a','b','c','d','e','\0' };
	strcpy(arr1, arr2);
	printf("%s\n", arr1); //hello bit
	strcpy(arr3, arr4);
	printf("%s\n", arr3); //abcdeabcde
	strcpy(arr3, arr5);
	printf("%s\n", arr3); //abcde
	//实现strcpy
	my_strcpy(arr2, arr3);
	printf("%s\n", arr2); //xxxxx bit


	/*strcat*/  //连接追加字符
	char arr6[20] = "hello";
	char arr7[] = "world";
	strcat(arr6, arr7);
	printf("%s\n", arr6);
	//实现strcat
	my_strcat(arr6, arr7);
	printf("%s\n", arr6);


	/*strcmp*/  //比较对应字符的大小
	int ret1 = strcmp("abcdef", "abq");
	printf("%d\n", ret1);  //-1
	int ret2 = strcmp("abcdef", "abc");
	printf("%d\n", ret2);  //1
	int ret3 = strcmp("abc", "abc");
	printf("%d\n", ret3); //0
	//实现strcmp
	int ret4 = my_strcmp("abcdef", "abq");
	printf("%d\n", ret4);  //-1
	int ret5 = my_strcmp("abcdef", "abc");
	printf("%d\n", ret5);  //1
	int ret6 = my_strcmp("abc", "abc");
	printf("%d\n", ret6); //0



	/*strncpy*/  //多了个n,是受限制的字符函数
	char arr8[20] = "abcdef";
	char arr9[] = "xxxxxxxxxxxxx";
	strncpy(arr8, arr9, 3);
	printf("%s\n", arr8);  //xxxdef


	/*strncat*/
	char arr10[20] = "abcdef";
	char arr11[] = "xxx";
	strncpy(arr10, arr11, 5);  //arr11只有三个,追加完3个之后,添加一个\0进去
	printf("%s\n", arr10);


	/*strncmp*/
	char arr12[20] = "abcqwertyuiop";
	char arr13[] = "abcdef";
	printf("%d\n", strncmp(arr12, arr13, 3));  //0
	printf("%d\n", strncmp(arr12, arr13, 4));  //1


	/*strstr*/  //char* strstr ( const char *str1, const char * str2);
	//功能是找str2在str1中第一次出现的位置
	char arr14[] = "abcdefabcdef";
	char arr15[] = "def";
	char arr16[] = "deq";
	char* ret7 = strstr(arr14, arr15);
	printf("%s\n", ret7);  //defabcdef
	char* ret8 = strstr(arr14, arr16);
	if (ret8 != 0)
		printf("%s\n", ret8);
	else
		printf("error");
	//实现strstr
	char arr17[] = "abbbcdef";
	char arr18[] = "bbc";
	char* ret9 = my_strstr(arr17, arr18);
	if (ret9 != 0)
		printf("%s\n", ret9);
	else
		printf("error");


	/*strtok*/  //char * strtok ( char* str, const char* sep );
	char arr19[] = "pengzhihao@yeah.net";
	char sep[] = "@.";  //sep代表字符串包含的分隔符
	strtok(arr19, sep);  //会修改原字符串(分隔符会被修改为\0)
	//改进方法
	char copy[30];
	strcpy(copy, arr19);
	strtok(copy, sep);

	char arr20[] = "pengzhihao@yeah.net";
	char copy1[30];
	strcpy(copy1, arr20);
	char sep1[] = "@.";
	char* ret10 = NULL;
	for (ret10 = strtok(copy1, sep1); ret10 != NULL; ret10 = strtok(NULL, sep1))
	{
		printf("%s\n", ret10);
	}


	/*strerror*/  //c语言中会把错误码存放到errno变量中,strerror(errno)可以提示报错信息
	for (int i = 0; i < 10; i++)
	{
		printf("%d: %s\n", i, strerror(i));
	}


	/*字符函数*/
	printf("%d\n", isupper('A'));  //是大写就返回非0值,是小写就返回0
	printf("%d\n", isdigit('2'));  //是数字就返回非0值,是其他就返回0
	//字符转换
	printf("%c\n", tolower('A'));  //a
	printf("%c\n", toupper('a'));  //A




	/*memcpy*/
	int arr21[] = { 1,2,3,4,5,6,7,8,9,10 };
	int arr22[20] = { 0 };
	//将arr21中的内容拷贝到arr2中
	memcpy(arr22, arr21, 40);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr22[i]);
	}
	//实现memcpy
	my_memcpy(arr22, arr21, 20);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr22[i]);
	}

	//memcpy函数是用来处理不重叠的内存拷贝
	//如果要把arr21的12345拷贝到34567位置上,变成1 2 1 2 3 4 5 8 9 10,结果确实1 2 1 2 1 2 1 2 9 10
	my_memcpy(arr21 + 2, arr21, 20);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr21[i]);
	}


	/*memmove*/
	memmove(arr21 + 2, arr21, 20);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr21[i]);
	}
	//实现memmove
	my_memmove(arr21 + 2, arr21, 20);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr21[i]);
	}
	return 0;
}

size_t my_strlen(const char* str)
{
	int count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}

char* my_strcpy(char* dest, const char* src)
{
	char* ret = dest;
	assert(dest != NULL);
	assert(src != NULL);

	while (*dest++ = *src++)
	{
		;
	}
	return ret;
	//    //第二种写法
	//    while (*src != '\0')
	//    {
	//        *dest = *src;
	//        dest++;
	//        src++;
	//    }
}

char* my_strcat(char* dest, const char* src)
{
	assert(dest != NULL);
	assert(src != NULL);
	char* ret = dest;
	//1.找到空间中的'\0'
	while (*dest != '\0')
	{
		dest++;
	}
	while (*dest++ = *src++)
	{
		;
	}
	return ret;
}

int my_strcmp(const char* str1, const char* str2)
{
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
			return 0;
		str1++;
		str2++;
	}
	if (*str1 > *str2)
		return 1;
	else
		return -1;
}

char* my_strstr(const char* str1, const char* str2)
{
	char* cp = (char*)str1;  //cp是记录原字符串的开始查找的位置
	char* s1, * s2;  //s1,s2是工作指针
	if (!*str2)
		return((char*)str1);
	while (*cp)
	{
		s1 = cp;
		s2 = (char*)str2;
		while (*s1 && *s2 && !(*s1 - *s2))
			s1++, s2++;
		if (!*s2)  //等同于 *s2 == '\0';
			return(cp);
		cp++;
	}
	return NULL;
}

void* my_memcpy(void* dst, const void* src, size_t count)
{
	void* ret = dst;
	assert(dst);
	assert(src);
	while (count--)
	{
		*(char*)dst = *(char*)src;
		dst = (char*)dst + 1;
		src = (char*)src + 1;
	}
	return(ret);
}

void* my_memmove(void* dst, const void* src, size_t count)
{
	void* ret = dst;
	if (dst <= src || (char*)dst >= ((char*)src + count))
	{
		//从前向后
		while (count--)
		{
			*(char*)dst = *(char*)src;
			dst = (char*)dst + 1;
			src = (char*)src + 1;
		}
	}
	else
	{
		//从后向前
		dst = (char*)dst + count - 1;
		src = (char*)src + count - 1;
		while (count--)
		{
			*(char*)dst = *(char*)src;
			dst = (char*)dst - 1;
			src = (char*)src - 1;

		}
	}
	return(ret);
}
