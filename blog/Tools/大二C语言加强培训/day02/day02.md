# day02

>   编程练习题

## 第一题

### 题目：分数转换

*   题目

    >   本题要求编写程序读入N个学生的百分制成绩，统计五分制成绩的分布，百分制成绩到五分制成绩的转换规则：

    *   大于等于90分为A；
    *   小于90且大于等于80为B；
    *   小于80且大于等于70为C；
    *   小于70且大于等于60为D；
    *   小于60为E。

*   输入格式

    >   输入在第一行中给出一个正整数N(≤ 1000)，即学生人数；第二行给出N个学生的百分制成绩，其间以空格分隔。

*   输出格式

    >   在一行输出A、B、C、D、E对应的五分制成绩的人数分布，数字间以空格分隔，行末不得有多余空格。

### 代码

```
#include <stdio.h>


int main()
{
    int i = 0;
    int N = 0;
    int score[1000] = { 0 };
    int level[5] = { 0 };

    // 从键盘输入学生个数
    printf("Please input num of student:");
    scanf("%d", &N);

    // 根据学生个数接收N个学生的成绩
    printf("Please input student score:");
    for (i = 0; i < N; i++)
    {
        scanf("%d", &score[i]);
    }

    // 遍历学生成绩score，将百分制转换成五分制，并且进行统计个数
    for (i = 0; i < N; i++)
    {
        if (score[i] < 60)       //小于60分      ===》 即为 1 分
            level[0] += 1;
        else if (score[i] < 70)  //小于70分      ===》 即为 2 分
            level[1] += 1;
        else if (score[i] < 80)  //小于80分      ===》 即为 3 分
            level[2] += 1;
        else if (score[i] < 90)  //小于90分      ===》 即为 4 分
            level[3] += 1;
        else                     //小于100分     == = 》 即为 5 分
            level[4] += 1;
    }

    // 打印成绩分布
    for (i = 0; i < 5; i++)
    {
        printf("%2d", level[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}
```

## 第二题

### 题目：阶乘和

*   题目：

    >   Caculate 1! + 2! + .. + n!

*   输入格式

    >An integer for n

*   输出格式

    >   An interger for the result

### 代码

```
#include <stdio.h>

int main()
{
	int i = 0;
	int j = 0;
	int n = 0;
	int sum = 0;
	int factorial = 1; // factorial   阶乘积，阶乘;  [fækˈtɔ:riəl] 
	printf("Please input a num:");
	scanf("%d", &n);
	
	// i 从 1 遍历到 n
	for (i = 1; i <= n; i++)
	{
		// 计算 i 的阶乘
		factorial = 1; // 初始化factorial的值为1
		for (j = 1; j <= i; j++)
		{
			factorial = factorial * j;
		}
		sum = sum + factorial;
	}

	printf("Result is %d\n", sum);

	return 0;
}
```

## 第三题

### 题目：排序

*   题目

    >   本题要求编写程序，读入5个字符串，按由小到大的顺序输出

*   输入格式

    >   输入为由空格分隔的5个非空字符串，每个字符串不包括空格、制表符、换行符等空白字符，长度小于80。

*   输出格式

    >   按照以下格式输出排序后的结果：
    >
    >   ```
    >   After sorted:
    >   每行一个字符
    >   ```

### 代码

```

#include <stdio.h>
#include <string.h>

int main()
{
	int i = 0;
	int j = 0;
	char str[5][80];
	char tmp[80] = "";
	printf("Please Input string:");

	// 接收5个字符串
	for (i = 0; i < 5; i++)
	{
		scanf("%s", str[i]);
	}
		
	// 冒泡排序，对字符串进行排序
	for (i = 5; i > 0; i--)
	{
		for (j = 0; j < i - 1; j++)
		{
			// 如果str[j] 大于 str[j + 1]
			if (strcmp(str[j], str[j + 1]) > 0)
			{
				strcpy(tmp, str[j]);
				strcpy(str[j], str[j + 1]);
				strcpy(str[j + 1], tmp);
			}
		}
	}

	// 循环打印排序后的结果
	printf("After sorted:\n");
	for (i = 0; i < 5; i++)
	{
		puts(str[i]);
	}

	return 0;
}
```

## 第四题

### 题目：矩阵转置

*   题目

    >   将一个3x3的矩阵转置(即行和列互换)

*   输入格式

    >在一行中输入9个小于100的整数，其间各以一个空格间隔

*   输出格式

    >输出3行3列的二维数组，每个数据输出占4列

### 代码

```
#include <stdio.h>

int main()
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	int array[3][3] = { 0 };


	printf("Please input integer:");

	// 从键盘按照行和列读取数据，
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			scanf("%d", &array[i][j]);
		}
	}
	
	// 对矩阵进行逆置
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j <= i; j++)
		{
			// 交换数据
			tmp = array[i][j];
			array[i][j] = array[j][i];
			array[j][i] = tmp;
		}
	}

	// 打印数据
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%-3d", array[i][j]);
		}
		printf("\n");
	}

	return 0;
}
```

## 第五题

### 题目:9x9乘法表

*   题目

    >   输出9\*9口诀,分行与列考虑，共9行9列，`i`控制行，`j`控制列。

*   输入格式:无

*   输出格式:无

### 代码

```
#include <stdio.h>

int main()
{
	int i = 0, j = 9;

	for(i = 1; i <= 9; i++)
	{
		for(j = 1; j <= i; j++)
		{
			printf("%-2d*%2d = %-2d ", j, i, i * j);
		}
		printf("\n");
	}
	return 0;	
}

```

