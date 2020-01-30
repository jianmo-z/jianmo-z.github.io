# day06

## 集合数据结构

> 常见集合的数据结构：栈、队列、数组、链表和红黑树。

## 栈

> 栈是**先进后出**，运算受限的线性表，其限制是仅允许在线性表一端进行插入和删除操作，不允许在另一端进行添加、查找、删除等操作。	

## 队列

> 队列是先进先出，运算受限的线性表，其限制是允许在线性表一端仅允许进行插入操作，在另一端仅允许进行删除操作。

## 数组

> 数组是查询快、增删慢。
>
> * 查询快：通过下标索引快，数组的地址是连续的，我们通过数组的首地址可以找到数据，通过数组的索引可以快速查找某一个元素。
> * 增删慢：数组的长度是固定的，我们想要**增加/删除**一个元素，必须创建一个新数组，把源数组的数据复制过来。

## 链表

> 链表是查询慢、增删快。
>
> * 查询慢：链表中的地址不是连续的，每次查询元素都必须从头开始查询。
> * 增删快：链表结构，增加或者删除一个元素对链表的整体结构没有影响，所以增删快。
>
> 链表中的每一个元素称为节点，一个节点包含一个数据域（存数据），两个指针域(存地址)

### 链表分类：

* 单向链表：链表中只有一条链。
* 双向链表：链表中有两条链。

## List接口

> `List`继承自`collection`、
>
> * `List`是一个有序的集合；
> * `List`有索引，可以通过索引访问元素；
> * `List`允许存储重复的元素。

### List接口中带索引的方法

* `public void add(int index, E element)`：将指定的元素添加到该集合中的指定位置上；
* `public E get(int index)`：返回集合汇总指定位置的元素；
* `public E remove(int index)`：移除列表中指定位置的元素，返回的是被移除的元素；
* `public E set(int index, E element)`：用指定元素替换集合中指定位置的元素，返回值是更新之前的元素。

> 操作索引的时候需要防止索引越界的情况发生

### 越界异常

* `IndexOutOfBoundsException`：索引越界异常；
* `ArrayIndexOutOfBoundsException`：数组索引越界异常；
* `StringIndexOutOfBoundsException`：字符串索引越界异常。

```java
package com_01.jianmo.ListAndSet;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/*
* public void add(int index, E element)：将指定的元素添加到该集合中的指定位置上；
* public E get(int index)：返回集合中指定位置的元素；
* public E remove(int index)：移除列表中指定位置的元素，返回的是被移除的元素；
* public E set(int index, E element)：用指定元素替换集合中指定位置的元素，返回值是更新之前的元素。
* */

public class ListTest {
	public static void main(String[] args) {
		// List 是一个抽象接口无法被实例化
		List<String> list = new ArrayList<>();

		// 使用add方法给集合中添加元素
		list.add("a");
		list.add("b");
		list.add("c");
		list.add("e");
		list.add("e");

		// 打印元素
		System.out.println(list);

		// 添加元素
		list.add(3, "d");
		System.out.println(list);

		// 移除元素
		System.out.println("被移除的元素；" + list.remove(4));;
		System.out.println(list);

		// 替换元素
		System.out.println("被替换的元素：" + list.set(0, "A"));
		System.out.println(list);

		// 获取元素
		System.out.println("获取指定元素：" + list.get(3));

		// 遍历
		// 1、普通for循环
		for (int i = 0; i < list.size(); ++i) {
			System.out.print(list.get(i));
		}
		System.out.println();


		// 2、使用迭代器遍历
		Iterator<String> it = list.iterator();
		while (it.hasNext()) {
			System.out.print(it.next());
		}
		System.out.println();

		// 3、增强for循环
		for(String i:list) {
			System.out.print(i);
		}
		System.out.println();

		// 处理数组越界异常
		// list.get(100);  // java.lang.IndexOutOfBoundsException
	}
}
```

## List的实现类

### ArrayList集合

> `java.util.ArrayList`，该集合的底层数据结构是**数组结构**，元素增删慢、查找快。日常开发中使用最多的功能是查询数据、遍历数据，所以`ArrayList`是常用的集合。

### LinkedList集合

> `java.util.LinkedList`，该集合数据存储的结构是**双向链表结构**。
>
> * 元素增删快，查找慢；
> * 包含大量操作首尾元素的方法；
>
> 使用`LinkedList`特有的方法的时候，不能使用多态。

### 特有的方法

* `public void addFirst(E e)`：将指定元素插入此列表的开头；
* `public void addLast(E e)`：将指定元素插入此列表的末尾，和`add`一样；
* `public E getFirst()`：获取链表的头部元素；
* `public E getLast()`：获取链表的尾部元素；
* `public E removeFirst()`：移除并返回链表的头部元素；
* `public E removeLast()`：移除并返回链表的尾部元素；
* `public E pop()`：从此链表所表示的堆栈处弹出一个元素；
* `public void push(E e)`：将元素压入此链表所表示的堆栈中，底层调用`addFirst`方法；
* `public boolean isEmpty()`：判断链表是否为空，是则返回`true`。

```java
package com_01.jianmo.ListAndSet;

import java.util.LinkedList;

/*
 * public void addFirst(E e)：将指定元素插入此列表的开头；
 * public void addLast(E e)：将指定元素插入此列表的末尾；
 * public void push(E e)：将元素压入此链表所表示的堆栈中；

 * public E getFirst()：获取链表的头部元素；
 * public E getLast()：获取链表的尾部元素；

 * public E removeFirst()：移除并返回链表的头部元素；
 * public E removeLast()：移除并返回链表的尾部元素；
 * public E pop()：从此链表所表示的堆栈处弹出一个元素；

 * public boolean isEmpty()：判断链表是否为空，是则返回true。
 *
 * */

public class LinkedListTest {
	public static void main(String[] args) {
//		LinkedListTest.test01();
//		LinkedListTest.test02();
		LinkedListTest.test03();
	}

	// addFirst、addLast、push
	public static void test01() {
		LinkedList<String> list = new LinkedList<>();

		list.add("a");
		list.add("b");
		list.add("c");
		list.add("d");

		list.addFirst("z");
		list.push("y");  // List的头是栈顶，push内部调用的是addFirst方法

		list.add("e");
		list.addLast("f");

		System.out.println(list);
	}

	// getFirst、getLast
	public static void test02() {
		LinkedList<String> list = new LinkedList<>();

		list.add("a");
		list.add("b");
		list.add("c");
		list.add("d");

		// 当集合的元素为空时：getFirst、getLast方法会抛出异常NoSuchElementException
		System.out.println("getFirst：" + list.getFirst());
		System.out.println("getLast：" + list.getLast());

		list.clear();

		if(!list.isEmpty()) {
			System.out.println("集合不为空");
			System.out.println("getFirst：" + list.getFirst());
			System.out.println("getLast：" + list.getLast());
		} else {
			System.out.println("集合为空");
		}
	}

	// removeFirst、removeLast、pop
	public static void test03() {
		LinkedList<String> list = new LinkedList<>();

		list.add("a");
		list.add("b");
		list.add("c");
		list.add("d");

		System.out.println("Original：" + list);

		list.removeFirst();
		System.out.println("removeFirst：" + list);

		list.removeLast();
		System.out.println("removeLast：" + list);

		list.pop();  // 底层调用的是：removeFirst
		System.out.println("pop：" + list);
	}
}
```

## Set接口

> `Set`继承自`collection`、
>
> * `Set`没有索引；
> * `Set`不允许存储重复的元素。

## Set的实现类

### HashSet集合

> * 不允许重复的元素；
> * 没有索引，没有带索引的方法，也不能使用普通的`for`循环遍历；
> * 是一个无序的集合，存储元素和取出元素的顺序可能不一致；
> * 底层是一个哈希表结构，查询快。