# day04

## Object类

* `public String toString()`，返回字符串，常用打印；
* `public boolean equals(java.lang.Object obj)`，对象比较；

## Date类

> `java.util.Date`类，表示特定的瞬间，精确到毫秒。

* `public Date()`，构造方法并初始化对象，精确到毫秒；
* `public Date(long date)`，从`1970.1.1 00:00:00`以来指定的毫秒数，中国为东八区`1970.1.1 08:00:00`；

## DateFormat和SimpleDateFormat类

> `DateFormat`日期/时间格式化子类的抽象类；`SimpleDateFormat`是该类的实现类，

| 字母 |          代表           | 字母  |          代表           |
| :--: | :---------------------: | :---: | :---------------------: |
| `G`  |         Era标识         |  `y`  |           年            |
| `M`  |       年中的月份        |  `w`  |       年中的周数        |
| `W`  |      月份中的周数       |  `D`  |       年中的天数        |
| `d`  |      月份中的天数       |  `F`  |      月份中的星期       |
| `E`  |       星期中天数        |  `a`  |      `Am/Pm`的标识      |
| `H`  |  一天中的小时数(0~23)   |  `k`  |  一天中的小时数(1~24)   |
| `K`  | `Am/Pm`中的小时数(0~11) |  `h`  | `Am/Pm`中的小时数(1~12) |
| `m`  |     小时中的分钟数      |  `s`  |      分钟中的秒数       |
| `S`  |         毫秒数          | `z/Z` |          时区           |

> 常用：`y:年`、`M:月`、`d:日`、`H:时`、`m:分`、`s:秒`。模式中的字母不能改变，连接模式的符号可以改变：`yyyy年MM月dd日 HH时mm分ss秒`

### 日期的格式化与解析

```java
package com_03.jianmo.DateFormat;

import java.text.ParseException;
import java.text.ParsePosition;
import java.text.SimpleDateFormat;
import java.util.Date;

public class DateFormatTest {
	public static void main(String[] args) {
		// 日期 -> 文本
		SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy年MM月dd日 HH时mm分ss秒");
		String dateString = simpleDateFormat.format(new Date());
		System.out.println(dateString);

		// 文本 -> 日期：2019-10-20日 22:10:05
		SimpleDateFormat simpleDateFormat1 = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		try {
			// 需要解决抛出的异常，catch或者继续抛出
			Date date = simpleDateFormat1.parse("2019-10-20 22:10:05");
			System.out.println(date.toString());
		}
		catch (ParseException e) {
			System.out.println("解析错误");
		}
	}
}
```

## Calender类

> 日历类(抽象类)无法直接实例化，使用`getInstance`获取一个子类实例对象。提供了很多操作日历字段的方法。

* `int get(int field)`：返回给定日历字段的值；

```java
public static final int ERA = 0;
public static final int YEAR = 1;
public static final int MONTH = 2;
public static final int WEEK_OF_YEAR = 3;
public static final int WEEK_OF_MONTH = 4;
public static final int DATE = 5;
public static final int DAY_OF_MONTH = 5;
public static final int DAY_OF_YEAR = 6;
public static final int DAY_OF_WEEK = 7;
public static final int DAY_OF_WEEK_IN_MONTH = 8;
public static final int AM_PM = 9;
public static final int HOUR = 10;
public static final int HOUR_OF_DAY = 11;
public static final int MINUTE = 12;
public static final int SECOND = 13;
public static final int MILLISECOND = 14;
public static final int ZONE_OFFSET = 15;
public static final int DST_OFFSET = 16;
public static final int FIELD_COUNT = 17;
```

* `void set(int field, int value)`：给定的日历字段设置为指定值
* `void set(int year, int month, int date);`：重载形式
* `void set(int year, int month, int date, int hourOfDay, int minute, int second);`：重载形式
* `void add(int var1, int var2);`：指定字段`增加/减少`值
* `Date getTime();`：日历对象转化为日期对象

```java
package com_04.jianmo.Calendar;

import java.util.Calendar;
import java.util.Date;

public class CalendarTest {
	public static void main(String[] args) {
		Calendar calendar = Calendar.getInstance();
//		System.out.println(calendar);

		// get方法
		System.out.println(calendar.get(1) + " -> " + Calendar.YEAR);  // 年
		System.out.println(calendar.get(2) + "(0~11) -> " + Calendar.MONTH);  // 月(0~11)
		System.out.println(calendar.get(5) + " -> " + Calendar.DAY_OF_MONTH);  // 日
		System.out.println(calendar.get(11) + " -> " + Calendar.HOUR_OF_DAY);  // 时
		System.out.println(calendar.get(12) + " -> " + Calendar.MINUTE);  // 分
		System.out.println(calendar.get(13) + " -> " + Calendar.SECOND);  // 秒

		// set方法
		calendar.set(Calendar.YEAR, 12);
		System.out.println(calendar.get(Calendar.YEAR));  // 年
		calendar.set(Calendar.MONTH, 1);
		System.out.println(calendar.get(Calendar.MONTH));  // 月(0~11)

		// add 方法
		calendar.add(Calendar.YEAR, 2007);
		System.out.println(calendar.get(Calendar.YEAR));  // 年
		calendar.add(Calendar.MONTH, -15);  // 减到前年了，啊哈哈
		System.out.println(calendar.get(Calendar.MONTH));  // 月(0~11)

		// getTime
		Date date = calendar.getTime();
		System.out.println(date.toString());
	}
}
```

## System类

> `java.lang.System`类中提供了大量的静态方法，可以获取与系统相关的信息或系统级操作。

* `static long currentTimeMillis();`：获取当前系统的13位时间戳；
* `static void arraycopy(Object var0, int var1, Object var2, int var3, int var4);`：拷贝数组

```java
package com_05.jianmo.System;

import java.util.Arrays;

public class SystemTest {
	public static void main(String[] args) {
		System.out.println(System.currentTimeMillis());

		int [] src = new int[] {1, 3, 4, 2, 8, 4};
		int [] des = new int[] {5, 3, 1, 2, 3};
//		System.arraycopy(src, 0, des, 4, 4);  // 越界了
		System.arraycopy(src, 0, des, 0, 5);
		System.out.println(Arrays.toString(src));
		System.out.println(Arrays.toString(des));
	}
}
```

## StringBuilder类

> 字符串`String`是一个常量，他们的值在创建之后不能更改，字符串的底层是一个被`final`修饰的数组，不能改变，是一个常量，`private final byte[] value;`，那么就需要一个`StringBuilder`(字符串缓冲区)，缓冲可以提高效率。看成一个长度可以变化的字符串，`byte[] value;`不是`final`关键字修饰的。
>
> `StringBuilder`在内存中始终是一个数组，占用空间少，效率高，如果超出了`StringBuilder`的容量，会自动的扩容。

* `StringBuilder()`：构造一个不带任何字符的字符串生成器，其初始容量为16个字符；
* `StringBuilder(String str)`：构造一个字符串生成器，并初始化为指定的字符串内容；

### 常用方法

* `StringBuilder append(...)`：添加任意格式类型数据的字符形式，并返回当前对象自身，可以链式编程。
* `String toString()`：将当前`StringBuilder`对象转换为`String`对象。

### StringBuilder和String相互转化

* `String` ---> `StringBuilder`：使用`StringBuilder`的构造方法；
* `StringBuilder`  ---> `String`：使用`toString()`将当前`StringBuilder`对象转化为`String`对象。

## 包装类

> 基本数据类型，使用起来非常方便，但是没有对应的方法来操作这些基本类型的数据可以使用一个类，把基本的数据装起来，在类中定义一些方法这个类就叫做包装类。我们可以使用类中的方法来操作这些基本类型的数据。

| 基本类型 | 对应的包装类  | 基本类型 | 对应的包装类 |
| -------- | ------------- | -------- | ------------ |
| byte     | Byte          | short    | Short        |
| int      | **Integer**   | long     | Long         |
| float    | Float         | double   | Double       |
| char     | **Character** | boolean  | Boolean      |

### 装箱与拆箱

* 装箱：基本类型的数据，包装到包装类中；	
* 拆箱：在包装类中取出基本类型的数据。

```java
package com_07.jianmo.Package;

public class PackageTest {
	public static void main(String[] args) {
		// 装箱：基本类型的数据，包装到包装类中
		Integer a = new Integer(10);  // 方法有横线，说明方法过时了
		Integer b = new Integer("20");  // 字符串必须为整数，否则NumberFormatException
		System.out.println("a:" + a + " b:" + b);

		Integer c = Integer.valueOf(30);
		Integer d = Integer.valueOf("40");
		System.out.println("c:" + c + " d:" + d);


		// 拆箱：在包装类中取出基本类型的数据
		int e = a.intValue();
		int f = b.intValue();
		System.out.println("e:" + e + " f:" + f);
	}
}
```

### 自动装箱与自动拆箱

> 基本类型的数据和包装类之间可以自动的相互转换，`JDK1.5`之后出现的新特性。

* 自动装箱：直接把`int`类型的数据赋值包装类
* 自动拆箱：`i`是包装类，无法直接参与运算，可以自动转换为基本数据类型，再进行计算。

```java
package com_07.jianmo.Package;

import java.util.ArrayList;

public class AutoPackageTeest {
	public static void main(String[] args) {
		// 自动装箱：直接把int类型的数据赋值包装类；
		Integer i = 10;

		// 自动拆箱：i是包装类，无法直接参与运算，可以自动转换为基本数据类型，再计算。
		i = i + 10;

		ArrayList<Integer> list = new ArrayList();
		list.add(1);  // 涉及到自动装箱, list.add(new Integer(1));
		int j = list.get(0);  // 涉及到自动拆箱, list.get(0).intValue();
	}
}
```

### 基本类型与字符串类型之间的相互转换

* 基本类型 ---> 字符串：
  1. `基本类型的值 + “”`，最简单的方法。
  2. 包装类的静态方法`toString(parm)`，不是`Object`类的`toString()`重载，`static String toString(int i)`。
  3. `String`类的静态方法：`static String valueOf(parm)`
* 字符串 ---> 基本类型：
  1. 包装类的静态方法`parseXXX(parm)`，如：`static int parseInt(String s)`

```java
package com_07.jianmo.Package;

public class Basic2String {
	public static void main(String[] args) {

		// 基本类型 ---> 字符串
		String s1 = 10 + "" + 200;
		System.out.println(s1);

		String s2 = new Integer(10).toString() + 200;
		System.out.println(s2);

		String s3 = String.valueOf(10) + 200;
		System.out.println(s3);

		// 字符串 ---> 基本类型
		int a = Integer.parseInt("10") + 200;
		System.out.println(a);
	}
}
```

