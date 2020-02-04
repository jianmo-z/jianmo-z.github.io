# day06

## Java的`==`和`equals`区别

* `==`比较的是`hashCode`方法返回的值，即比较的是两个对象的哈希值；
* `equals`比较的是`equals`方法返回的值，即比较的两个对象的属性值，根据`equals`实现的区别区分。

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

### 不允许重复元素原因

> 

## Set的实现类

### 哈希值

> `java.lang.Object`对象的`int hashCode()`方法返回一个对象的哈希值。
>
> `public native int hashCode();`
>
> * `native`：代表该方法调用的是本地操作系统的方法。

### HashSet集合

> * 不允许重复的元素；
> * 没有索引，没有带索引的方法，也不能使用普通的`for`循环遍历；
> * 是一个无序的集合，存储元素和取出元素的顺序可能不一致；
> * 底层是一个哈希表结构，查询快；
> * 初始容量是16个，对相同的哈希值进行分组，然后使用链表/红黑树对相同哈希值的元素连接。
> * 在`jdk1.8`之后当链表的长度等于8个就会转化为红黑树，jdk代码`if (binCount >= 7) {this.treeifyBin(tab, hash);}`，包含新插入的元素即：`8 = 7 + 1`。

#### 哈希表底层实现	

* jdk1.8版本之前：
  * `哈希表=数组+链表`
* jdk1.8版本之后：
  * `哈希表=数组+链表`
  * `哈希表=数组+红黑树(提高查询速度)`

### LinkedHashSet集合

> * 继承自`HashSet`类，`extends HashSet`集合；
> * 底层：`哈希表（数组 + 链表/红黑树）` + `链表`，多一条链表用来记录元素的存储顺序，保证元素有序；
> * 元素有序但不能重复。

```java
package com_01.jianmo.ListAndSet;

import java.util.HashSet;
import java.util.LinkedHashSet;

public class LinkedHashSetTest {
	public static void main(String[] args) {
		HashSet<String> h1 = new HashSet<>();
		h1.add("www");
		h1.add("aaa");
		h1.add("aaa");
		h1.add("zzz");
		System.out.println(h1);  // [aaa, www, zzz]

		HashSet<String> h2 = new LinkedHashSet<>();
		h2.add("www");
		h2.add("aaa");
		h2.add("aaa");
		h2.add("zzz");
		System.out.println(h2);  // [www, aaa, zzz]
	}
}
```

## 可变参数

> 在`jdk1.5`之后，如果我们定义一个方法需要接受多个参数，并且多个参数类型一致，就可以使用可变参数，可变参数是`jdk1.5`之后的新特性。
>
> * `修饰符 返回值类型 方法名(参数类型... 形参名){   }`
>
> 本质是传进去了一个数组。

```java
package com_02.jianmo.VarArgs;

public class VarArgsTest {
	public static void main(String[] args) {
		System.out.println(sum01(1, 2, 3));
	}


	public static int sum01(int... nums) {
		int ret = 0;
		for (int i : nums) {
			ret += i;
		}
		return ret;
	}

	// 可变参数的终极写法，接受所有的数据类型
	public static void sum02(Object...obj) {
	}
}
```

### 注意事项

1. 一个方法的参数列表，只能有一个可变参数，与数据类型无关；
2. 如果方法的参数有多个，那么可变参数必须写在参数列表的末尾。

## Collections集合工具类

> 操作集合的工具类

* `public static <T> boolean addAll(Collection<? super T> c, T... elements)`，向集合中添加所有的元素；

* `public static void shuffle(List<?> list)`，打乱集合中的元素；

* `public static <T extends Comparable<? super T>> void sort(List<T> list)`，对集合的数据进行排序，默认是升序排序，对于自定义数据类型需要实现`Comparable`接口的`compareTo`方法。
* `Comparable`排序根据返回值
  * `= 0`：表示元素是相同；
  * `> 0`：表示当前元素大于传进来的元素，即`this-other`，升序；
    * `< 0`：表示当前元素小于传进来的元素，即`other-this`，降序。
* `public static <T> void sort(List<T> list, Comparator<? super T> c)`，对集合的数据进行排序，使用提供的排序接口`Comparator`。

> `Comparator`和`Comparable`的区别
>
> * `Comparable`：自己`this`和别人`other参数`进行比较；
> * `Comparator`：两个参数`o1`和`o2`进行比较。

```java
package com_03.jianmo.Collections;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class CollectionsTest {
	public static void main(String[] args) {
		ArrayList<Integer> lists = new ArrayList<>();

		// 往集合中添加多个元素
		Collections.addAll(lists, 1, 3, 5, 7, 9);
		System.out.println(lists);

		// 打乱集合中元素的顺序
		Collections.shuffle(lists);
		System.out.println(lists);

		// 元素排序:默认升序，字符串按照ASCII码进行排序
		Collections.sort(lists);  // 默认升序
		System.out.println(lists);

		// 逆序排序，传递一个匿名内部类
		Collections.sort(lists, new Comparator<Integer>() {
			@Override
			public int compare(Integer t1, Integer t2) {
				return t2 - t1;
			}
		});
		System.out.println(lists);

		// 逆序排序，lambda表达式
		Collections.shuffle(lists);
		Collections.sort(lists, (t1, t2) -> t1 - t2);
		System.out.println(lists);

	}
}
```

