# day12

## 函数式接口

> 函数式接口在`Java`中是指：有且仅有一个抽象方法的接口。函数式接口，即适用于函数式编程场景的接口，而`Java`中的函数式编程体现就是`Lambda`，所以函数式接口就是可以适用于`Lambda`使用的接口，只有确保接口中有且仅有一个抽象方法，`Java`中的`Lambda`才能顺利地进行推导。

### 格式

> 只要确保接口中**有且仅有一个抽象方法**即可。

```java
修饰符 interface 接口名称 {
    public abstract 返回值类型 方法名称(可选参数信息);
    // 其他非抽象方法内容
}
```

### 函数式接口注解

> `@FunctionalInterface`注解，用于一个接口的定义上

## 函数式编程

> 有些场景的代码执行后，结果不一定会被使用，从而造成性能浪费。而`Lambda`表达式是延迟执行的，这正好可以作为解决方法，提升性能。

### Lambda的延迟执行

> 使用`Lambda`优化`LoggerTest`日志案例：
>
>  *   `lambda`的特点：延迟加载；
>  *   `lambda`使用前提：必须存在函数式接口。

#### Test02LambdaLogger类

```java
package com_02.jianmo.LambdaDelayExec;

/*
 * 使用Lambda优化LoggerTest日志案例：
 *   lambda的特点：延迟加载；
 *   lambda使用前提：必须存在函数式接口。
 *
 *  Lambda表达式作为参数传递，仅仅是把参数传递到showLog方法中，
 * 只有满足条件后才会执行方法然后拼接字符串。
 *
 * */

public class Test02LambdaLogger {

	public static void showLog(int level, MessageBuilder msg) {
		if (1 == level) {
			System.out.println(msg.builderMessage());
		}
	}

	public static void main(String[] args) {
		// 定义三个日志信息
		String msg1 = "hello";
		String msg2 = "world";
		String msg3 = "java";


		showLog(1, () -> msg1 + msg2 + msg3);  // lambda的特点：延迟加载
	}
}
```

#### MessageBuilder接口

```java
package com_02.jianmo.LambdaDelayExec;

@FunctionalInterface
public interface MessageBuilder {
	public abstract String builderMessage();
}
```

### Lambda作为参数和返回值

> `Lambda`作为参数前面已经讲解过，不再赘述。方法的返回值类型是一个函数式接口，所以我们可以返回一个`Lambda`表达式。

```
package com_03.jianmo.LambdaAsReturn;

import java.util.Arrays;
import java.util.Comparator;

public class MyCompareTest {
	public static Comparator<String> comp() {
			return (a, b) -> (a.length() - b.length());
	}

	public static void main(String[] args) {
		String [] array = {"aaaa", "bbbb", "cc", "eeeeeeee"};
		Arrays.sort(array, MyCompareTest.comp());
		System.out.println(Arrays.toString(array));
	}
}
```

## 常用函数式接口

> JDK提供大量常用的函数式接口以丰富Lambda的典型使用场景，它们主要在`java.util.function`包中被提供。`Lambda`表达式需要**对外提供**一个符合泛型类型的对象数据。

### Supplier接口

> `java.util.function.Supplier<T>`接口仅包含一个无参的方法：`T get()`，用来获取一个泛型参数指定类型的对象数据。`Supplier<T>`接口被称为**生产型接口**，指定接口的泛型是什么类型，那么接口中的`get`方法就会生产什么类型。

```java
package com_04.jianmo.Supplier;

import java.util.Arrays;
import java.util.function.Supplier;

public class SupplierTest {
	public static void main(String[] args) {
		// 生产一个字符串
		String str = getString(() -> "aaa");
		System.out.println(str);


		// 获取数组的最大值
		int [] array = {11, 3, 5, 7, 4, 6};
		Integer numValue = getMax(() -> {
			int max = array[0];
			for (int i: array) {
				if (i > max)
					max = i;
			}
			return max;
		});
		System.out.println("Max num:" + numValue);
	}

	public static String getString(Supplier<String> s) {
		return s.get();
	}

	public static Integer getMax(Supplier<Integer> s) {
		return s.get();
	}

}
```

### Consumer接口

> `java.util.function.Consumer<T>`接口正好与`Supplier`接口相反，它不是生产一个数据，而是消费一个数据，其数据类型由泛型决定，`Consumer`接口是一个消费型接口，泛型执行什么类型，就可以使用`accept`消费什么类型的数据。

* 抽象方法`accept`：接口中包含抽象方法`void accept(T t)`，意为消费一个指定泛型的数据；

```java
package com_05.jianmo.Consumer;

import java.util.function.Consumer;

public class ConsumerAcceptTest {
	public static void main(String[] args) {
		String name = "张三";
		myAccept(name, (String s) -> {
			// 对传递进来的变量进行消费：打印和反转
			System.out.println(s);
			System.out.println(new StringBuilder(s).reverse().toString());
		});
	}

	public static void myAccept(String s, Consumer<String> c) {
		c.accept(s);
	}
}
```

* 默认方法`antThen`：如果一个方法的参数和返回值全都是`Consumer`类型，那么就可以实现效果：消费数据的时候，首先做一个操作，然后再做另一个操作，实现组合。二者方法就是`Consumer`接口中的`default`方法`andThen`。

```java
package com_05.jianmo.Consumer;

import java.util.function.Consumer;

public class ConsumerAndThenTest {
	public static void main(String[] args) {
		String name = "zhang SAN";
		myAndThen(name,
				(String s) -> {  /*第一个消费*/
					System.out.println("消费1：" + s.toLowerCase());
				},
				(String s) -> { /*第二个消费*/
					System.out.println("消费2：" + s.toUpperCase());
				});
	}

	public static void myAndThen(String s, Consumer<String> c1, Consumer<String> c2) {
		// c1和c2分别对s进行消费

		// 方式一
		// c1.accept(s);
		// c2.accept(s);

		// 方式二：谁在前面谁先消费，c1先消费，c2后消费
		c1.andThen(c2).accept(s);
	}
}
```

#### Consumer练习案例

```java
package com_05.jianmo.Consumer;

import java.util.function.Consumer;

public class ConsumerAndThenPractice {
	public static void main(String[] args) {
		String[] infos = {"张三,17", "李四,18", "王五,21", "李六,20"};
		catStr(infos,
				(String s) -> {  /*消费字符串打印姓名*/
					System.out.print("姓名：" + s.split(",")[0] + ", ");
				},
				(String s) -> {  /*消费字符串打印年龄*/
					System.out.println("年龄：" + s.split(",")[1]);
				});
	}

	public static void catStr(String[] array, Consumer<String> c1, Consumer<String> c2) {
		for (String it : array) {
			c1.andThen(c2).accept(it);
		}
	}
}
```

### Predicate接口

> 有时候需要对某种类型的数据进行判断，从而得到一个boolean值结果，这时可以使用`java.util.function.Predicate<T>`接口。

* 抽象方法`test`：`boolean test(T t)`，用于条件判断的场景；

```java
package com_06.jianmo.Predicate;

import java.util.function.Predicate;

public class PredicateTestTest {
	public static void main(String[] args) {
		String name = "张三";
		boolean ret = checkStr(name, (String str) -> str.length() > 5 || str.startsWith("张"));
		System.out.println("ret:" + ret);
	}

	public static boolean checkStr(String str, Predicate<String> p) {
		return p.test(str);
	}
}
```

* 默认方法`and`：将两个`Predicate`条件使用**与**逻辑连接起来实现`&&`效果，可以使用默认方法`and`，该方法满足**短路与**。

```java
package com_06.jianmo.Predicate;

import java.util.function.Predicate;

public class PredicateAndTest {
	public static void main(String[] args) {
		String name = "张三";
		boolean ret = checkStrAnd(name, (String s) -> s.startsWith("张"), (String s) -> s.length() > 5);
		System.out.println("ret:" + ret);
	}

	public static boolean checkStrAnd(String str, Predicate<String> p1, Predicate<String> p2) {
		return p1.and(p2).test(str);
	}
}
```

* 默认方法`or`：将两个`Predicate`条件使用**或**逻辑连接起来实现`||`效果，可以使用默认方法`or`，该方法满足**短路或**。

```java
package com_06.jianmo.Predicate;

import java.util.function.Predicate;

public class PredicateOrTest {
	public static void main(String[] args) {
		String name = "张三";
		boolean ret = checkStrOr(name, (String s) -> s.startsWith("张"), (String s) -> s.length() > 5);
		System.out.println("ret:" + ret);
	}

	public static boolean checkStrOr(String str, Predicate<String> p1, Predicate<String> p2) {
		return p1.or(p2).test(str);
	}
}
```

* 默认方法`negate`：对结果`boolean`值进行`!`取反操作，一定要在`test`前调用`negate`方法。

```java
package com_06.jianmo.Predicate;

import java.util.function.Predicate;

public class PredicateNegateTest {
	public static void main(String[] args) {
		String name = "张三";
		boolean ret = checkStrNegate(name, (String s) -> s.startsWith("张"));
		System.out.println("ret:" + ret);
	}
	public static boolean checkStrNegate(String str, Predicate<String> p1) {
		return p1.negate().test(str);
	}
}
```

### Function接口

> `java.util.function.Function<T, R>`接口用来根据一个类型的数据得到另一个类型的数据，前者称为前置条件，后者称为后置条件

* 抽象方法`apply`：`R apply(T t)`根据类型T的参数获取类型R的结果；例如：将`String`类型转换为`Integer`类型。

```java
package com_07.jianmo.Function;

import java.util.function.Function;

public class FunctionApplyTest {
	public static void main(String[] args) {
		String data = "1234";
		int num = applyTest(data, (String str) -> Integer.parseInt(str) % 100);
		System.out.println("num:" + num);

	}

	public static Integer applyTest(String str, Function<String, Integer> f) {
		return f.apply(str);
	}
}
```

* 默认方法`andThen`：用来组合操作，先做什么，在做什么，那个先调用先做那个和`Consumer`的`andThen`一样。

```java
package com_07.jianmo.Function;

import java.util.function.Function;

/*
* Math.ceil(num)：去掉小数，进一法；12.1 => 13, 12.9 => 13
* Math.floor(num)：去掉小数，不进位；12.1 => 12, 12.9 => 12
* Math.round(num)：四舍五入。12.5 => 13, 12.4 => 12
* */

public class FunctionAndThenTest {
	public static void main(String[] args) {
		String data = "12.345";
		int num = andThenTest(data, (String s) -> Double.parseDouble(s) * 100, (Double d) -> (int)Math.floor(d));
		System.out.println("num:" + num);

	}

	public static Integer andThenTest(String str, Function<String, Double> f1, Function<Double, Integer> f2) {
		return f1.andThen(f2).apply(str);
	}
}
```

