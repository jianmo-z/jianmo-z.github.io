# day01

[TOC]

## IDEA常用快捷键

| 快捷键               | 功能                                           |
| -------------------- | ---------------------------------------------- |
| `Alt+Enter`          | 导入包，自动修正代码                           |
| `Ctrl+Y`             | 删除光标所在行                                 |
| `Ctrl+D`             | 复制光标所在行的内容，插入光标位置下面         |
| `Ctrl+Alt+L`         | 格式化代码                                     |
| `Ctrl+/`             | 单行注释，再按取消注释                         |
| `Ctrl+Shift+/`       | 选中代码注释，多行注释，再按取消注释           |
| `Alt+Insert`         | 自动生成代码，`toString`，`get*`，`set*`等方法 |
| `Alt+Shift+上下箭头` | 移动当前代码行                                 |
| `Shift+F6`           | 重命名当前行到后面的所有变量名                 |

## 面向过程和面向对象

* 面向过程：当需要实现一个功能的时候，每一个具体的步骤都要亲力亲为，详细处理每一个细节。
* 面向对象：当需要实现一个功能的时候，不关心具体的步骤，而是找一个已经具有该功能的人，来帮我做事。

## Java的标准类

1. 所有的成员变量都要使用`private`关键字修饰；
2. 为每一个成员变量编写一对`Getter`/`Setter`方法；
3. 编写一个无参数的构造方法；
4. 编写一个全参数的构造方法。

```java
package com.jianmo;

public class People {
    private String name;
    private Integer age;

    public People() {
    }

    public People(String name, Integer age) {
        this.name = name;
        this.age = age;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public Integer getAge() {
        return age;
    }
}
```

## java引用类型和基本类型

> 只要不是基本类型对于java而言都是引用类型，基本类型如：`int`、`long`、`float`、`double`、`char`等。

## 常用API

> `API(Application Programming Interface)`，应用程序编程接口。

* `Scanner`：接收键盘输入
* `Random`：产生随机数
* `ArrayList`：集合存储数据
* `String`：字符串类
* `Arrays`：数组工具类
* `Math`：数学函数类

## Scanner

> 接收键盘数据到程序中。

```java
package com_02.jianmo.API;

import java.util.Scanner;

public class ScannerTest {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Please input num:");
        int num = sc.nextInt();
        System.out.printf("num=%d\n", num);

        System.out.print("Please input str:");
        String str = sc.next();
        System.out.printf("str=%s\n", str);
    }
}
```

## 匿名对象

* 有名对象：`类名称 变量名 = new 类名称()`
* 匿名对象：`new 类名称()`

```java
package com_03.jianmo.Anonymous;

public class Anonymous {
	public static void main(String[] args) {
		Person person = new Person();
		person.name = "张三";
		person.age  = 19;
		System.out.print("有名对象：" + person);
		System.out.print("\n匿名对象：" + new Person("王五", 20));
	}
}

class Person{
	String name;
	Integer age;

	public Person() {
	}

	public Person(String name, Integer age) {
		this.name = name;
		this.age = age;
	}

	@Override
	public String toString() {
		return "Person{" +
				"name='" + name + '\'' +
				", age=" + age +
				'}';
	}
}
```

## Random

> 获取一个随机数

```java
package com_04.jianmo.Random;

import java.util.Random;

public class RandomTest {
	public static void main(String[] args) {
		Random random = new Random();
		int i = random.nextInt();  // abs取绝对值
		System.out.println("随机数为：" + i);

		i = random.nextInt(100); // 取值范围为[0, 100)
		System.out.println("随机数为(bound)：" + i);

	}
}
```

## ArrayList

> `ArrayList<E>`，`E`代表泛型，即C++的模板。但**泛型只能是引用类型**，不能是基本类型。基本类型使用包装类。

```java
package com_05.jianmo.Array;

import java.util.ArrayList;

public class ArrayListTest {
	public static void main(String[] args) {
		ArrayList<Person> array = new ArrayList<>();

		// 1.打印集合
		System.out.println(array);

		// 2.向集合中添加元素，返回值代表添加是否成功
		boolean ret = array.add(new Person("张三", 18));
		if (ret) {
			System.out.println("add success");
		} else {
			System.out.println("add failed");
		}
		array.add(new Person("王五", 23));
		array.add(new Person("李四", 32));
		array.add(new Person("王麻子", 20));

		// 3.获取元素
		Person tmp = array.get(1);
		System.out.println(tmp);

		// 4.删除元素
		array.remove(tmp);  // Object
		System.out.println(array);
		// tmp = array.remove(0); // index
		// System.out.println(array);

		// 5.获取大小
		int size = array.size();
		System.out.println("元素的个数为:"+size);

		// 6.遍历集合
		System.out.println("===========================");
		for (int i = 0; i < array.size(); ++i) {
			System.out.println(array.get(i));
		}
	}
}
```

| 基本类型  | 包装类(引用类型) |
| --------- | ---------------- |
| `byte`    | `Byte`           |
| `short`   | `Short`          |
| `int`     | `Integer`        |
| `long`    | `Long`           |
| `float`   | `Float`          |
| `double`  | `Double`         |
| `char`    | `Character`      |
| `boolean` | `Boolean`        |

> 从JDK1.5+后，支持自动装箱、自动拆箱。

* 自动装箱：基本类型 --> 引用类型
* 自动拆箱：包装类型 --> 基本类型

## String

> `Java`程序中的所有字符串字面值(如：“abc”)都作为此类的实例实现。

* 字符串是常量，它们的值创建之后不能更改。但字符串缓冲区支持可变的字符串；
* 因为`String`不可变，所以可以共享；
* `String`内部使用的是`byte[]`存储的，` private final byte[] value;`。

### 字符串的创建

1. 构造创建：`public String()`
2. 构造创建：`public String(char[] value)`
3. 构造创建：`public String(byte[] bytes)`
4. 直接创建：`String s4 = "hello world";`

```java
package com_06.jianmo.Str;

public class StringTest {
	public static void main(String[] args) {
		// 创建方式一：
		String s1 = new String();
		s1 = "hello world";

		// 创建方式二：
		char [] CharArray = {'h', 'e', 'l', 'l', 'o'};
		String s2 = new String(CharArray);

		// 创建方式三：
		byte[] ByteArray = {97, 98, 99};
		String s3 = new String(ByteArray);

		// 创建方式四：
		String s4 = "hello world";
	}
}
```

### 字符串池

> 字符串常量池

```java
package com_06.jianmo.Str;

import org.w3c.dom.ls.LSOutput;

public class StringPool {
	public static void main(String[] args) {
		String s1 = "abc";
		String s2 = "abc";
		String s3 = new String(new char[]{'a', 'b', 'c'});

		System.out.println(s1 == s2);
		System.out.println(s1 == s3);
		System.out.println(s2 == s3);
		System.out.println("=============");
		System.out.println(s1.equals(s2));
		System.out.println(s1.equals(s3));
		System.out.println(s2.equals(s3));
	}
}

```

> 结果

```java
true
false
false
=============
true
true
true
```

> 原因分析，对于基本类型而言，`==`是进行数值的比较；对于引用类型而言，`==`是进行地址值的比较。引用类型需要重写`equals`，String已经重写过了。

### String方法

> `Java`的任何对象都可以用`Object`对象进行接收，`Object`是所有类的基类。注意：`Java`的`String.split`方法里面是一个正则，特殊字符需要转义`* ^ : | . \`，用`\\`转义。

```java
package com_06.jianmo.Str;

public class StringMethods {
	public static void main(String[] args) {
		String s1 = "hello world";
		char[] array = {'h', 'e', 'l', 'l', 'o'};
		String s2 = new String(array);

		// 1.字符串比较
		System.out.println(s1.equals(s2));

		// 2.字符串比较，忽略大小写
		String s3 = "HELLO";
		System.out.println(s1.equalsIgnoreCase(s3));

		// 3.获取字符串长度
		System.out.println("字符串长度为"+s1.length());

		// 4.拼接字符串
		System.out.println("s1 + s2="+s1.concat(s2));

		// 5.获取某个位置上的字符
		System.out.println(s1.charAt(1));

		// 6.查询某个字符串第一次出现的位置，没有返回-1
		System.out.println("'l'第一次出现的位置："+s1.indexOf('l'));
		System.out.println("'lo'第一次出现的位置："+s1.indexOf("lo"));

		// 7.字符串截取
		System.out.println("[2,] = "+s1.substring(2));
		System.out.println("[2,4) = "+s1.substring(2, 4));  // 左闭右开:[begin, end)

		// 8.String与转换相关的常用方法
		char [] cs = s1.toCharArray();
		byte [] bs = s1.getBytes();
		System.out.println(cs[0]);
		System.out.println(((char) bs[0]));  // 获得的是ASCII，需要进行类型转换为char

		// 9.字符串替换
		String target = "l";
		String replacement = "w";
		System.out.println(s1.replace(target, replacement));  // 返回替换后的字符串，不改变s1
		System.out.println(s1.replace("l", "w"));  // 返回替换后的字符串，不改变s1
		System.out.println(s1);  // s1不会发生变化

		// 10.字符串分割
		String [] ret = "a|b|c|d|e".split("\\|");  // 参数是正则，特殊字符需要转义，*,^,:,|,.,\ 用\\转义。
		for (String r : ret) {
			System.out.println(r);
		}
	}
}
```

## Static关键字

> 如果一个类的成员变量使用了`static`关键字修饰，那么这个变量不再属于对象自己，而是属于所在类。可以通过对象调用，但是推荐使用类名直接进行调用。

* `static`修饰变量：变量属于类，可通过类名直接调用，不需要实例化对象。
* `static`修饰方法：方法属于类，可通过类名直接调用，不需要实例化对象。

> 静态方法无法直接访问非静态变量或调用方法，非静态可以访问静态。但是不能通过`this`指针。

### 类静态成员

#### 测试代码

```java
package com_07.jianmo.Static;

public class StaticTest {
	public static void main(String[] args) {
		Student.setRoom("101教室");  // static属性的类通过类直接可以访问该类型的变量
		Student s1 = new Student("张三", 18);
		Student s2 = new Student("李四", 20);
		Student s3 = new Student("王麻子", 22);

		Student.room = "202教室";  // static属性的类变量
		System.out.println(s1);
		System.out.println(s2);
		System.out.println(s3);

	}
}
```

#### Student类

```java
package com_07.jianmo.Static;

public class Student {
	private String name;
	private Integer age;
	public static String room;

	public Student() {
	}

	public Student(String name, Integer age) {
		this.name = name;
		this.age = age;
	}

	public static String getRoom() {
		return room;
	}

	public static void setRoom(String room) {
		Student.room = room;
	}

	@Override
	public String toString() {
		return "Student{" +
				"name='" + name + '\'' +
				", room='" + Student.room + '\'' +
				", age=" + age +
				'}';
	}
}
```

### 静态代码块

> 当首次用到该类执行一次，典型用途来给静态成员变量赋值。

#### 测试代码

```java
package com_07.jianmo.Static;

public class PersonTest {
	public static void main(String[] args) {
		Person p1 = new Person();
		Person p2 = new Person();
	}
}

```

#### Person类

```java
package com_07.jianmo.Static;

public class Person {
	static {
        // 静态代码块，一般用来给静态变量赋值
		System.out.println("欢迎使用该类");
	}

	public Person() {
		System.out.println("调用一次构造");
	}
}
```

#### 运行结果

```java
欢迎使用该类
调用一次构造
调用一次构造
```

## Arrays

> 与数组相关的工具类，提供了大量的静态方法，用来实现数组常见的操作。

### 自定义类的排序

> 注意泛化传入，自定义类的类型。

* 方式一：继承`Comparator`接口，需要实现`compare`方法。
* 方式二：继承`Comparable`接口，需要实现`compareTo`接口。

### 测试类

```java
package com_08.jianmo.Arrays;

import java.util.Arrays;

public class ArraysTest {
	public static void main(String[] args) {
		Student[] array = {
				new Student("张三", 18),
				new Student("李四", 22),
				new Student("王麻子", 20),
		};

		// 1.数组转为字符串形式
		System.out.println(Arrays.toString(array));

		// 2.数组进行排序
		Arrays.sort(array);
		System.out.println(Arrays.toString(array));
	}
}
```

### Student类

```
package com_08.jianmo.Arrays;

public class Student implements Comparable<Student>{
	private String name;
	private Integer age;

	public Student() {

	}

	public Student(String name, Integer age) {
		this.name = name;
		this.age = age;
	}

	@Override
	public String toString() {
		return "Student{" +
				"name='" + name + '\'' +
				", age=" + age +
				'}';
	}

	@Override
	public int compareTo(Student t) {
		return this.age - t.age;
	}
}
```

## Math

> 该类提供了大量的静态方法，完成与数学运算相关的操作。

```java
package com_09.jianmo.Math;

public class MathTest {
	public static void main(String[] args) {
		double a = -34.56;

		// 1.获取绝对值
		System.out.println(Math.abs(a));

		// 2.向上取整，不是四舍五入
		System.out.println(Math.ceil(a));

		// 3.向下取整，不是四舍五入
		System.out.println(Math.floor(a));

		// 4.四舍五入取整
		System.out.println(Math.round(a));
	}
}
```

