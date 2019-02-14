# 三种基本排序

>   冒泡排序,选择排序,插入排序

```
#include <stdio.h>


// 冒泡排序
void Bubble_sort(int * arr, int size);

// 选择排序
void Selection_sort(int * arr, int size);

// 插入排序
void Insertion_sort(int * arr, int size);

// 打印数组
void Print(int * arr, int size)
{
	int i = 0;
	for(i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main()
{
	int arr1[8] = {2, 1, 4, 7, 4, 8, 3, 6};
	int arr2[8] = {2, 1, 4, 7, 4, 8, 3, 6};
	int arr3[8] = {2, 1, 4, 7, 4, 8, 3, 6};
	
	// 冒泡排序
	Bubble_sort(arr1, 8);
	Print(arr1, 8);
	
	// 选择排序
	Selection_sort(arr2, 8);
	Print(arr2, 8);
	
	// 插入排序
	Insertion_sort(arr3, 8);
	Print(arr3, 8);
	
	return 0;
}
// 冒泡排序
void Bubble_sort(int * arr, int size)
{
	int i = 0, j = 0, tmp = 0;
	for(i = size - 1; i > 0; i--)
		for(j = 0; j < i; j++)
		{
			if(arr[j] > arr[j + 1])
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
	for(i = size - 1; i > 0; i--)
	{
		index_max = 0;
		for(j = 1; j <= i; j++)
		{
			if(arr[j] > arr[index_max])
				index_max = j;
		}
		if(index_max != i)
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
	for(i = 1; i < size; i++)
	{
		tmp = arr[i];
		for(j = i - 1; j >= 0; j--)
		{
			if(tmp < arr[j])
				arr[j + 1] = arr[j];	
			else
				break;
		}
		if(i != j)
			arr[j + 1] = tmp;
	}
}
```

