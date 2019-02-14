# day08

```
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <math.h>

/*

day01：
	i++、 ++i、 --i、 i--
	逗号运算符
	课后题

day02:
	本题要求编写程序读入1个学生的百分制成绩，百分制成绩到五分制成绩的转换规则：
		大于等于90分为A；
		小于90且大于等于80为B；
		小于80且大于等于70为C；
		小于70且大于等于60为D；
		小于60为E。



	算法	概念：
		五个特点
			有穷性
			确定性
			可行性
			有输入
			有输出
		算法的评价标准
			正确性
			可读性
			健壮性(鲁棒性)
			高效率(时间短)
			低存储量需求(占用内存小)

	程序的基本结构
		顺序结构
		选择结构 if (else if) else | if  else | if (else if) | ? : | switch
		循环结构 for | while | do while
*/
void day02() {
	char level;
	int socre = 0;
	// 接收一个学生成绩
	scanf("%d", &socre);
	// 对学生成绩进行判断
	if (socre >= 90)	{
		level = 'A';
	}
	else if (socre >= 80) {
		level = 'B';
	}
	else if (socre >= 70) {
		level = 'C';
	}
	else if (socre >= 60) {
		level = 'D';
	}
	else {
		level = 'E';
	}
	// 打印转换后的级别
	printf("转化后的学生等级为：%c\n", level);
}

void day03(){
	/*
	 && ||
	 短路与 &&：左右都为真，结果为真，其他为假
		条件表达式1 && 条件表达式2
		假设：条件表达式1为假，则不会去计算表达式2的结果，因为条件1已经为假了
	没必要计算条件2

	 短路或 ||：左右只要有一个为真，表达式结果为真。
		条件表达式1 || 条件表达式2
		假设：条件表达式1为真，则不会计算表达式2的结果，因为条件1已经为真了
	没必要去计算条件2
	*/
	int i = 0;
	int j = 2;
	int k = 12;
	k = ((i = 1) && (j = 3)); // 赋值语句的返回值是它赋值的值, 1 && 3 ===> 真
	// i = 1 j = 3 k = 1
	//printf("i = %d, j = %d, k = %d\n", i, j, k);

	i = 0; j = 2;
	k = ((i = 0) && (j = 3)); // 赋值语句的返回值是它赋值的值, 0 && _ ===> 假，发生短路
	// i = 0 j = 2 k = 0
	//printf("i = %d, j = %d, k = %d\n", i, j, k);

	i = 0; j = 2;
	k = ((i = 0) || (j = 3)); // i = 0 || j = 3 ==>  0 || (j = 3) ==> 0 || 3 ==> 1
	// i = 0 j = 3 k = 1
	printf("i = %d, j = %d, k = %d\n", i, j, k);

	i = 0; j = 2;
	k = ((i = 1) || (j = 3)); // 1 || (j = 3) ==> 1
	// i = 1 j = 2 k = 1
	printf("i = %d, j = %d, k = %d\n", i, j, k);


	/*
		异或：不同为1
		1 ^ 0 ==> 1
		0 ^ 1 ==> 1
		0 ^ 0 ==> 0
		1 ^ 1 ==> 0
	*/

	// 条件表示式 ? 语句1 : 语句2 ==》 三目运算符
	// 条件表达式为真：执行语句1
	// 条件表达式为假：执行语句2
	// 相当于 if(){} else {} 语句


	if (1) {

	}
	if (1) {

	}
	else { // 和上面最近的未匹配else的语句匹配

	}
}

void swap(int *, int*); // 函数的声明
void swap(int * a, int * b) { // 函数体的实现
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
	printf("swap funcation: *a = %d , *b = %d\n", *a, *b);
}

void day04() {
	int arr[100]; // 数组的寻址范围为：[0, 99] 或者 [0, 100)
	/*
	int:表示数组每个是整形变量
	arr:数组名，指向第一个数组元素的地址
	[100]:表示数组的大小为100个 int 类型空间

	几维数组的数组名就是几级指针
	*/
	// 访问元素：方式一
	arr[90];
	//方式二
	*(arr + 10);


	// 二维数组定义
	int array[100][100];


	/*
	函数：
		三要素：返回值、函数、形式参数

		参数传递的注意事项：函数参数传递是值传递
			int swap(int a, int b); 	
	*/
	int a = 3, b = 4;
	swap(&a, &b);
	printf("a = %d , b = %d\n", a, b);

	strcpy("", "");
}

void day05() {
	// enum weekday{ sun, mon = 7, tue, wed, thu, fri, sat };
	// enum weekday{ sun, mon, tue, wed, thu, fri, sat };
	enum weekday{ sun, mon, tue = 1, wed, thu, fri, sat };
	/*
		不写默认从0开始
		当前值的数值是它前面的值+1
	*/
	printf("tue = %d\n", sun);  // 0 0 0
	printf("tue = %d\n", mon);	// 7 1 1
	printf("tue = %d\n", tue);	// 8 2 1
	printf("tue = %d\n", wed);	// 9 3 2
}

// 打印数组
void Print(int * arr, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
// 冒泡排序
void Bubble_sort(int * arr, int size)
{
	int i = 0, j = 0, tmp = 0;
	for (i = size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
}
// 选择排序
void Selection_sort(int * arr, int size)
{
	int i = 0, j = 0, index_max = 0, tmp = 0;
	for (i = size - 1; i > 0; i--)
	{
		index_max = 0;
		for (j = 1; j <= i; j++)
		{
			if (arr[j] > arr[index_max])
				index_max = j;
		}
		if (index_max != i)
		{
			tmp = arr[index_max];
			arr[index_max] = arr[i];
			arr[i] = tmp;
		}
	}
}
// 插入排序
void Insertion_sort(int * arr, int size)
{
	int i = 0, j = 0, tmp = 0;
	for (i = 1; i < size; i++)
	{
		tmp = arr[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (tmp < arr[j])
				arr[j + 1] = arr[j];
			else
				break;
		}
		if (i != j)
			arr[j + 1] = tmp;
	}
}
void day06() {


	// 冒泡和选择至少掌握一个

	int arr1[8] = { 2, 1, 4, 7, 4, 8, 3, 6 };
	int arr2[8] = { 2, 1, 4, 7, 4, 8, 3, 6 };
	int arr3[8] = { 2, 1, 4, 7, 4, 8, 3, 6 };

	// 冒泡排序 *
	Bubble_sort(arr1, 8);
	Print(arr1, 8);

	// 选择排序 *
	Selection_sort(arr2, 8);
	Print(arr2, 8);

	// 插入排序
	Insertion_sort(arr3, 8);
	Print(arr3, 8);


}

void test1(){
	int i = 6, j = 3, k = 4;
	int m, n;
	m = i / j; // m = 6 / 3 = 2
	n = i / k; // n = 6 / 4 = 1
	// printf("m = %d, n = %d\n", m, n);

	i = 1; j = 1;
	m = i++; // m = 1
	// i++，先用i，再++ ==> 先用i= 1，再++ ，i = 2
	n = ++i; // n = 3
	// ++i，先++，再用i ==> 先++ i = 3 ,再用i ， n = 3
	// printf("m = %d, n = %d\n", m, n);


	// 数组名是数组第一个元素的地址
	int arr[5] = { 1, 2, 3, 4, 5 };
	int * p = arr;
	i = *p++; // ++ 和 * 谁的优先级高 ？
	// 先p++ 再 *p
	Print(arr, 5);
	printf("i = %d, *p = %d\n", i, *p); // 1 , 2

	p = arr;
	i = *++p; // ++ 和 * 谁的优先级高 ？
	// 先++p 再 *p
	printf("i = %d, *p = %d\n", i, *p); // 2 , 2
}



// 宏函数
#define MULT1(x, y) x*y
#define MULT2(x, y) (x)*(y)
// 宏定义只会机械的替换值
void test2() {
	
	int result1 = MULT1(1 + 2, 3 + 4); // 1 + 2 * 3 + 4 = 11
 	int result2 = MULT2(1 + 2, 3 + 4); // (1 + 2)*(3 + 4) = 21

	printf("result = %d\n", result1);
	printf("result = %d\n", result2);
}


struct  student
{
	char name[32];	// 姓名
	int age;		// 年龄
};

void test3() {
	// [0, 4] ==> 0, 1, 2, 3, 4
	struct  student s[5] = {
		{"张三", 12},
		{"李四", 11},
		{"王五", 15},
		{"小明", 21},
		{"小红", 5}
	};

	for (int i = 0; i < 5; i++)
		printf("name = %s, age = %d\n", s[i].name, s[i].age);

	// 冒泡排序
	for (int i = 4; i > 0; i--)
	// for (int i = 5; i > 0; i--) // 错误, [0, 4]
	{

		// for (int j = 0; j <= i; j++) // 错误 j ==> [0, i]
		for (int j = 0; j < i; j++) // j ==> [0, i)
		{
			// 比较年龄排序
			// if (s[j].age > s[j + 1].age) { // j <==> j + 1交换数据，升序
			if (s[j].age < s[j + 1].age) { // j <==> j + 1交换数据，降序
				struct student tmp;
				tmp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = tmp;
			}
			// j <==> j + 1交换数据
			//  错误 j ==> [0, i] ==> [0, j + 1] ==> [0, i + 1] ==> [0, 5] 越界
			//  j ==> [0, i) ==> [0, j + 1) ==> [0, i + 1) ===> [0, i] 没有越界
		}
	}
	printf("排序后的结果为：\n");
	for (int i = 0; i < 5; i++)
		printf("name = %s, age = %d\n", s[i].name, s[i].age);

}

void test4() {
	// 素数的概念：除过1和它本身没有别的因子，整数即取余的结果为0
	int n = 500;
	int i, j;
	for (i = 2; i < n; i++)
	{
		for (j = 2; j < i; j++)
		{
			if (i % j == 0)
				break;
		}
		if (i == j)
		{
			printf("%5d", i);
		}
	}

}

void test5() {
	int i = 012; // 8^1 * 1 + 8^0 * 2 = 10
	int j = 0x12; // 16^1 * 1 + 16^0 * 2 = 18
	//printf("i = %d\n", i);
	//printf("j = %d\n", j);
	
	int k = (i = 12, j = 23, 1);
	//printf("i = %d\n", i); // 12
	//printf("j = %d\n", j); // 23
	//printf("k = %d\n", k); // 1

	k = (12, 13), i = 10;
	/*
	k = (13), i = 10
	k = 13, i = 10
	i = 10
	*/
	//printf("i = %d\n", i); // 10
	//printf("j = %d\n", j); // 23
	//printf("k = %d\n", k); // 13

	k = ((12, 13), i = 11);
	/*
	k = ((13), i = 10)
	k = (13, i = 10)
	k = 10
	*/
	printf("i = %d\n", i); // 11
	printf("j = %d\n", j); // 23
	printf("k = %d\n", k); // 11

}


void test6() {
	typedef int myint; // 给类型名起别名
	myint i = 32;
	int j = 54;
	i = j;
}
int main()
{
	// day02();
	// day03();
	// day04();
	// day05();
	// day06();
	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	system("pause");
	return 0;
}
```

