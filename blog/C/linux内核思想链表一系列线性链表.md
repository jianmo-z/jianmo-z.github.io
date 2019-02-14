欢迎加入QQ：498903810 一起交流、讨论知识，里面有大佬，也有小白，天下码农一家亲，大家一起讨论进步。

#Linux内核线性表

## linklist.h文件
```
文件：linklist.h
代码：
#ifndef _HEAD_H
#define _HEAD_H

typedef void LinkList;
typedef void LinkListNode;

typedef struct tag_LinkListNode
{
	struct tag_LinkListNode * next;
}TLinkListNode;

LinkList * LinkLIst_Creat();

void LinkList_Destory(LinkList * list);
void LinkList_Clear(LinkList * list);
int LinkList_Length(LinkList * list);
int LinkList_Insert(LinkList * list, LinkListNode * node, int pos);

LinkListNode * LinkList_Get(LinkList * list, int pos);
LinkListNode * LinkList_Delete(LinkList * list, int pos);

#endif
```
## linklist.c文件
```
文件：linklist.c
代码：
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "linklist.h"

typedef struct tag_LinkList//linux内核链表原型
{
	TLinkListNode  head;
	int length;
}TLinkList;

LinkList * LinkLIst_Creat()
{
	TLinkList *tmp = (TLinkList *)malloc(sizeof(TLinkList));
	if (NULL == tmp)
	{
		printf("LinkLIst_Creat: error");
		return NULL;
	}
	memset(tmp, 0, sizeof(TLinkList));
	tmp->head.next = NULL;
	tmp->length = 0;
	return (void *)tmp;
}

void LinkList_Destory(LinkList * list)
{
	if (NULL != list)
	{
		free(list);
		list = NULL;
	}
	return;
}

void LinkList_Clear(LinkList * list)
{
	if (NULL == list)
	{
		return;
	}
	TLinkList * tmp = (TLinkList *)list;
	tmp->length = 0;
	tmp->head.next = 0;
}

int LinkList_Length(LinkList * list)
{
	if (NULL == list)
	{
		return -1;
	}
	TLinkList * tmp = (TLinkList *)list;
	return tmp->length;
}

int LinkList_Insert(LinkList * list, LinkListNode * node, int pos)
{
	int i = 0;
	int ret = 0;
	if (NULL == list || NULL == node || pos < 0)
	{
		ret = -1;
		return ret;
	}
	TLinkList * tmp = (TLinkList *)list;
	TLinkListNode * current = &(tmp->head);
	TLinkListNode * pnode = node;

	if (pos >= tmp->length)//插入的位置大于链表的长度，插在链表的尾部。
	{
		while (current->next)
		{
			current = current->next;
		}
		current->next = node;
		pnode->next = NULL;
		tmp->length++;
		return 0;
	}
	for (i = 0; (i < pos - 1) && (current->next != NULL); i++)
	{
		current = current->next;
	}
	pnode->next = current->next;
	current->next = node;
	tmp->length++;
	return 0;
}


LinkListNode * LinkList_Get(LinkList * list, int pos)
{
	int i = 0;
	if (NULL == list || pos < 0)
	{
		return NULL;
	}

	TLinkList * tmp = (TLinkList *)list;
	TLinkListNode * current = &(tmp->head);

	if (pos > tmp->length)
	{
		return NULL;
	}

	for (i = 0; i < pos + 1; i++)
	{
		current = current->next;
	}

	return current;
}

LinkListNode * LinkList_Delete(LinkList * list, int pos)
{
	int i = 0;
	if (NULL == list || pos < 0)
	{
		return NULL;
	}

	TLinkList * tmp = (TLinkList *)list;
	TLinkListNode * current = &(tmp->head);
	TLinkListNode * ctmp = NULL;

	if (pos > tmp->length)
	{
		return NULL;
	}

	for (i = 0; i < pos; i++)
	{
		current = current->next;
	}

	if (current->next != NULL)
	{
		ctmp = current->next;
		current->next = current->next->next;
	}
	else
	{
		ctmp = current;
		current = NULL;
	}
	tmp->length--;
	return ctmp;
}

```
## linklist_test.c文件
```
文件：linklist_test.c
代码：
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "linklist.h"
typedef struct Teacher
{
	TLinkListNode node;
	int age;
	char name[64];
}Teacher;

int main()
{
	int len = 0, ret = 0;
	Teacher t1, t2, t3, t4, t5;
	LinkList * head = NULL;

	t1.age = 21;
	t2.age = 22;
	t3.age = 23;
	t4.age = 24;
	t5.age = 25;

	head = LinkLIst_Creat();
	if (NULL == head)
	{
		return 0;
	}

	len = LinkList_Length(head);

	ret = LinkList_Insert(head, (TLinkListNode *)&t1, 2);
	ret = LinkList_Insert(head, (TLinkListNode *)&t2, 0);
	ret = LinkList_Insert(head, (TLinkListNode *)&t3, 4);
	ret = LinkList_Insert(head, (TLinkListNode *)&t4, 0);
	ret = LinkList_Insert(head, (TLinkListNode *)&t5, 0);

	printf("遍历链表");
	for (int i = 0; i < LinkList_Length(head); i++)
	{
		Teacher * tmp = (Teacher *)(LinkList_Get(head, i));
		if (NULL == tmp)
		{
			return 0;
		}
		printf("length = %d age = %d\n", LinkList_Length(head), tmp->age);
	}

	printf("删除链表\n");
	//while (LinkList_Length(head))
	//{
	//	Teacher * tmp = LinkList_Delete(head, 0);
	//	if (NULL == tmp)
	//	{
	//		return 0;
	//	}
	//	printf("length = %d age = %d\n", LinkList_Length(head), tmp->age);
	//}

	LinkList_Delete(head, 2);
	printf("遍历链表");
	for (int i = 0; i < LinkList_Length(head); i++)
	{
		Teacher * tmp = (Teacher *)(LinkList_Get(head, i));
		if (NULL == tmp)
		{
			return 0;
		}
		printf("length = %d age = %d\n", LinkList_Length(head), tmp->age);
	}
	/*

	void LinkList_Destory(LinkList * list);
	void LinkList_Clear(LinkList * list);
	LinkListNode * LinkList_Delete(LinkList * list, int pos);
	*/
	system("pause");
	return 0;
}
```
