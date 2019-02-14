欢迎加入QQ：498903810 一起交流、讨论知识，里面有大佬，也有小白，天下码农一家亲，大家一起讨论进步。

# 循环链表和约瑟夫环问题求解

<font color=red size=5>注：测试程序代码和约瑟夫环问题求解不能同时运行，但是运行时需要包含头文件和函数实现</font>

## circule_link_list.h头文件
```
文件:circule_link_list.h
代码:
#ifndef _CIRCULE_LINK_LIST_H
#define _CIRCULE_LINK_LIST_H

typedef void CirculeLinkList;
typedef void CirculeLinkListNode;

typedef struct TagCirculeLinkListNode
{
	struct TagCirculeLinkListNode * next;
}TagCirculeLinkListNode;

//创建一个循环链表
CirculeLinkList * LinkLIst_Creat();

//销毁一个循环链表
void LinkList_Destory(CirculeLinkList * list);

//清理一个循环链表
void LinkList_Clear(CirculeLinkList * list);

//求链表长度
int LinkList_Length(CirculeLinkList * list);

//插入节点
int LinkList_Insert(CirculeLinkList * list, CirculeLinkListNode * node, int pos);

//获取链表节点信息
CirculeLinkListNode * LinkList_Get(CirculeLinkList * list, int pos);

//删除节点
CirculeLinkListNode * LinkList_Delete(CirculeLinkList * list, int pos);
//add--->新增游标概念

//删除游标指向的节点
CirculeLinkListNode * CirculeLinkList_Delete(CirculeLinkList * list, CirculeLinkListNode * node);

//重置游标
CirculeLinkListNode * CirculeLinkList_Reset(CirculeLinkList * list);

//获取游标位置
CirculeLinkListNode * CirculeLinkList_Current(CirculeLinkList * list);

//游标下移
CirculeLinkListNode * CirculeLinkList_Next(CirculeLinkList * list);

#endif
```
## circule_link_list.c函数实现
```
文件:circule_link_list.c
代码:
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "circule_link_list.h"

typedef struct TagCircleLink
{
	TagCirculeLinkListNode head;
	TagCirculeLinkListNode * vernier;//vernier游标
	int length;
}TagCircleLink;

//创建一个循环链表
CirculeLinkList * LinkLIst_Creat()
{
	TagCircleLink * begin;
	begin = (TagCircleLink *)malloc(sizeof(TagCircleLink));
	if (NULL == begin)
	{
		printf("(TagCircleLink *)malloc(sizeof(TagCircleLink)) error");
		return NULL;
	}
	begin->vernier = NULL;
	begin->length = 0;
	begin->head.next = NULL;
	return (void *)begin;
}
//销毁一个循环链表
void LinkList_Destory(CirculeLinkList * list)
{
	if (NULL != list)
	{
		free(list);
	}
}
//清理一个循环链表
void LinkList_Clear(CirculeLinkList * list)
{
	TagCircleLink * begin;
	begin = (TagCircleLink *)list;
	begin->head.next = NULL;
	begin->length = 0;
	begin->vernier = NULL;
}
//求链表长度
int LinkList_Length(CirculeLinkList * list)
{
	TagCircleLink * begin;
	begin = (TagCircleLink *)list;
	return begin->length;
}
//插入节点
int LinkList_Insert(CirculeLinkList * list, CirculeLinkListNode * node, int pos)
{
	if (NULL == list || NULL == node || pos < 0)
	{
		return -1;
	}
	TagCircleLink * begin = NULL;
	TagCirculeLinkListNode * insert = NULL, * tmp = NULL;

	begin = (TagCircleLink *)list;
	insert = (TagCirculeLinkListNode *)node;
	if (NULL == begin->head.next)//第一个插入的元素特殊处理
	{
		begin->head.next = insert;
		insert->next = insert;
		begin->vernier = insert;//游标指向0号结点
		begin->length++;
		return 0;
	}

	//如果插入的是零号位置特殊处理，插入零号位置相当于插入在最后一个位置，然后把头结点后移一位,
	if (pos > begin->length)
	{
		pos = begin->length;
	}
	if (0 == pos)
	{
		LinkList_Insert(list, node, begin->length);
		begin->head.next = insert;
		begin->vernier = insert;
		return 0;
	}

	tmp = begin->head.next;
	for (int i = 0; i < pos - 1; i++)
	{
		tmp = tmp->next;
	}
	insert->next = tmp->next;
	tmp->next = insert;
	begin->length++;
	return 0;
}
//获取链表节点信息
CirculeLinkListNode * LinkList_Get(CirculeLinkList * list, int pos)
{
	if (NULL == list  || pos < 0)
	{
		return NULL;
	}
	TagCircleLink * begin = NULL;
	TagCirculeLinkListNode * tmp = NULL;
	begin = (TagCircleLink *)list;
	tmp = begin->head.next;
	for (int i = 0; i < pos; i++)
	{
		tmp = tmp->next;
	}
	return (void *)tmp;
}
//删除节点
CirculeLinkListNode * LinkList_Delete(CirculeLinkList * list, int pos)
{
	if (NULL == list || pos < 0)
	{
		return NULL;
	}
	TagCircleLink * begin = NULL;
	TagCirculeLinkListNode * tmp = NULL, * ret = NULL;
	begin = (TagCircleLink *)list;
	tmp = begin->head.next;
	if (pos >= begin->length)
	{
		return NULL;
	}
	if (begin->vernier == (TagCirculeLinkListNode *)LinkList_Get(list, pos))//如果删除的结点是游标指向的位置，游标下移
	{
		begin->vernier = begin->vernier->next;
	}
	if (begin->length == 1 && pos == 0)//如果删除的最后一个结点
	{
		CirculeLinkListNode * ret = begin->head.next;
		begin->length--;
		begin->vernier = NULL;
		begin->head.next = NULL;
		return ret;
	}
	if (0 == pos)//如果是删除的头号结点特殊处理
	{
		begin->head.next = begin->head.next->next;//头结点移到一号位置
		CirculeLinkListNode * sign = LinkList_Delete(list, begin->length - 1);//删除最后一个元素
		if (NULL != sign)
		{
			return sign;
		}
		else
			return NULL;
	}


	for (int i = 0; i < pos - 1; i++)//删除普通结点
	{
		tmp = tmp->next;
	}
	ret = tmp->next;
	tmp->next = tmp->next->next;
	begin->length--;
	return (void *)ret;
}

//add--->新增游标概念
//删除游标指向的节点
CirculeLinkListNode * CirculeLinkList_Delete(CirculeLinkList * list, CirculeLinkListNode * node)
{
	//node是要删除的位置
	if (NULL == list || NULL == node)
	{
		return NULL;
	}
	int i = 0;
	TagCirculeLinkListNode * del = (TagCirculeLinkListNode *)node, * tmp = NULL;
	TagCircleLink * begin = (TagCircleLink *)list;
	tmp = begin->head.next;
	for (i = 0; i <= begin->length; i++)//找到要删除的结点的位置
	{
		if (i == begin->length)
		{
			return NULL;
		}
		if (del == tmp)
		{
			break;
		}
		tmp = tmp->next;
	}
	tmp = (TagCirculeLinkListNode *)LinkList_Delete(list, i);//移动结点
	if (tmp != NULL)
	{
		return tmp;
	}
	else
		return NULL;

}
//重置游标
CirculeLinkListNode * CirculeLinkList_Reset(CirculeLinkList * list)
{
	if (NULL == list)
	{
		return NULL;
	}
	TagCircleLink * begin = NULL;
	begin = (TagCircleLink *)list;

	begin->vernier = begin->head.next;
	return (CirculeLinkListNode *)begin->vernier;
}
//获取游标位置
CirculeLinkListNode * CirculeLinkList_Current(CirculeLinkList * list)
{
	if (NULL == list)
	{
		return NULL;
	}
	TagCircleLink * begin = (TagCircleLink *)list;
	return (CirculeLinkListNode *)begin->vernier;
	
}
//游标下移
CirculeLinkListNode * CirculeLinkList_Next(CirculeLinkList * list)
{
	if (NULL == list)
	{
		return NULL;
	}
	TagCircleLink * begin = (TagCircleLink *)list;
	(TagCirculeLinkListNode *)begin->vernier;
	begin->vernier = begin->vernier->next;
	return (CirculeLinkListNode *)begin->vernier;
}
```
##Joseph_question.c约瑟夫环问题求解
```
文件:Joseph_question.c
代码:
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "circule_link_list.h"

typedef struct Teacher
{
	TagCirculeLinkListNode * next;
	int age;
	char name[64];
}Teacher;

int main()
{
	Teacher t1;
	Teacher t2;
	Teacher t3;
	Teacher t4;
	Teacher t5;
	Teacher t6;
	Teacher t7;
	Teacher t8;
	Teacher t9;
	t1.age = 21;
	t2.age = 22;
	t3.age = 23;
	t4.age = 24;
	t5.age = 25;
	t6.age = 26;
	t7.age = 27;
	t8.age = 28;
	t9.age = 29;

	CirculeLinkList * list;
	Teacher * tmp;
	CirculeLinkList * ret = NULL;
	//创建链表
	list = LinkLIst_Creat();

	//插入元素
	LinkList_Insert(list, (CirculeLinkListNode *)&t1, 0);
	LinkList_Insert(list, (CirculeLinkListNode *)&t2, 0);
	LinkList_Insert(list, (CirculeLinkListNode *)&t3, 0);
	LinkList_Insert(list, (CirculeLinkListNode *)&t4, 0);
	LinkList_Insert(list, (CirculeLinkListNode *)&t5, 0);
	LinkList_Insert(list, (CirculeLinkListNode *)&t6, 0);
	LinkList_Insert(list, (CirculeLinkListNode *)&t7, 0);
	LinkList_Insert(list, (CirculeLinkListNode *)&t8, 0);
	LinkList_Insert(list, (CirculeLinkListNode *)&t9, 0);

	//遍历元素
	for (int i = 0; i < LinkList_Length(list); i++)
	{
		Teacher *tmp = NULL;
		ret = LinkList_Get(list, i);
		tmp = (Teacher *)ret;
		printf("age = %d\n", tmp->age);
	}

	printf("约瑟夫问题求解\n");
	for (int i = 0; i < LinkList_Length(list);)
	{
		for (int j = 0; j < 2; j++)
		{
			CirculeLinkList_Next(list);
		}
		ret = CirculeLinkList_Delete(list, CirculeLinkList_Current(list));
		if (ret != NULL)
		{
			tmp = (Teacher *)ret;
			printf("age = %d\n", tmp->age);
		}
		else
		{
			printf("error\n");
		}
	}
	system("pause");
	return 0;
}
```
## 测试程序代码
```
程序测试代码
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "circule_link_list.h"

typedef struct Teacher
{
	TagCirculeLinkListNode * next;
	int age;
	char name[64];
}Teacher;

int main()
{
	Teacher t1;
	Teacher t2;
	Teacher t3;
	Teacher t4;
	Teacher t5;
	t1.age = 21;
	t2.age = 22;
	t3.age = 23;
	t4.age = 24;
	t5.age = 25;
	CirculeLinkList * list;
	CirculeLinkList * ret = NULL;
	//创建链表
	list = LinkLIst_Creat();

	//插入元素
	LinkList_Insert(list, (CirculeLinkListNode *)&t1, 0);
	LinkList_Insert(list, (CirculeLinkListNode *)&t2, 1);
	LinkList_Insert(list, (CirculeLinkListNode *)&t3, 0);

	//CirculeLinkListNode * LinkList_Get(CirculeLinkList * list, int pos);
	//遍历元素
	for (int i = 0; i < LinkList_Length(list); i++)
	{
		Teacher *tmp = NULL;
		ret = LinkList_Get(list, i);
		tmp = (Teacher *)ret;
		printf("age = %d\n", tmp->age);
	}
	 
	////删除元素 --- > 测试通过
	//for (int i = 0; i < LinkList_Length(list);)
	//{
	//	ret = LinkList_Delete(list, 0);
	//	if (ret == NULL)
	//	{
	//		printf("删除失败!!!\n");
	//		break;
	//	}
	//	else
	//	{
	//		Teacher *tmp = NULL;
	//		tmp = (Teacher *)ret;
	//		printf("被删除的年龄是 age = %d\n", tmp->age);
	//	}
	//}

	//测试通过
	//ret = CirculeLinkList_Delete(list, (CirculeLinkListNode *)& t1);
	//if (ret == NULL)
	//{
	//	printf("失败!!!\n");
	//}
	//else
	//{
	//	Teacher *tmp = NULL;
	//	tmp = (Teacher *)ret;
	//	printf("年龄是 age = %d\n", tmp->age);
	//}
	////遍历元素
	//for (int i = 0; i < LinkList_Length(list); i++)
	//{
	//	Teacher *tmp = NULL;
	//	ret = LinkList_Get(list, i);
	//	tmp = (Teacher *)ret;
	//	printf("age = %d\n", tmp->age);
	//}

	//测试通过
	//ret = CirculeLinkList_Reset(list);
	//Teacher *tmp = NULL;
	//tmp = (Teacher *)ret;
	//printf("年龄是 age = %d\n", tmp->age);

	ret = CirculeLinkList_Next(list);
	Teacher *tmp = NULL;
	tmp = (Teacher *)ret;
	printf("年龄是 age = %d\n", tmp->age);

	/*
	//创建一个循环链表
	CirculeLinkList * LinkLIst_Creat();
	//销毁一个循环链表
	void LinkList_Destory(CirculeLinkList * list);
	//清理一个循环链表
	void LinkList_Clear(CirculeLinkList * list);
	//求链表长度
	int LinkList_Length(CirculeLinkList * list);
	//插入节点
	int LinkList_Insert(CirculeLinkList * list, CirculeLinkListNode * node, int pos);
	//获取链表节点信息
	CirculeLinkListNode * LinkList_Get(CirculeLinkList * list, int pos);
	//删除节点
	CirculeLinkListNode * LinkList_Delete(CirculeLinkList * list, int pos);
	//add--->新增游标概念
	//删除游标指向的节点
	CirculeLinkListNode * CirculeLinkList_Delete(CirculeLinkList * list, CirculeLinkListNode * node);
	//重置游标
	CirculeLinkListNode * CirculeLinkList_Reset(CirculeLinkList * list);
	//获取游标位置
	CirculeLinkListNode * CirculeLinkList_Current(CirculeLinkList * list);
	//游标下移
	CirculeLinkListNode * CirculeLinkList_Next(CirculeLinkList * list);
	*/
	system("pause");
	return 0;
}
```
