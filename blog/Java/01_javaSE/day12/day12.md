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

## Stream流

> 此流与`IO`流无关，主要用来操作集合和数组。流式思想类似于工厂的`生产流水线`。`Stream`流调用指定的方法，可以从一个流模型转换到另一个流模型，`filter`、`map`、`skip`对函数模型进行操作，集合元素并没有真正被处理，当终结方法调用执行时才被操作执行。得益于`Lambda`的延迟执行特性。
>
> `Stream`流式一个来自数据源的元素队列：
>
> * 元素是特定类型的对象，形成一个队列，`Java`中的`Stream`并不会存储元素，而是按需计算；
> * 数据流的来源可以是集合也可以是数组等。
>
> `Stream`与`Collection`操作不同，`Stream`操作还要两个基础的特性：
>
> * `Pipelining`：中间操作都会返回流对象本身。这样多个操作可以串联成一个管道，如同流式风格(`fluent style`)。这样可以对操作进行优化，比如延迟执行`laziness`和短路`short-circuiting`。
> * **内部迭代**：以前对集合遍历都是通过`Iterator`或者增强`for`的方式，显式的在集合外部进行迭代，这种叫做外部迭代。`Stream`提供了**内部迭代的方式**，流可以直接调用遍历方法。
>
> `Stream`流属于管道流，只能被消费(使用)一次，第一个`Stream`流调用完毕，数据就会流到下一个`Stream`中，前一个`Stream`流就不能再调用方法了。

```java
package com_08.jianmo.Stream;

import java.util.ArrayList;
import java.util.List;

public class StreamTest {
	public static void main(String[] args) {
		List<String> list = new ArrayList<>();

		list.add("张三");
		list.add("王五");
		list.add("李四");
		list.add("王麻子");
		list.add("张无忌");
		list.add("张三丰");
		list.add("张将啊");


		list.stream()
				.filter((name) -> name.startsWith("张"))  // 1.使用Predicate接口，获取姓张的
				.filter((name) -> name.length() > 2)  // 2.使用Predicate接口，获取名字长度大于2的
				// .forEach((name) -> System.out.println(name));  // 3.1使用Consumer接口，进行遍历
				.forEach(System.out::println);  // 3.2使用Consumer接口，进行遍历，同上

	}
}
```

### 获取流

> `java.util.stream.Stream<T>`是`java 8`新加入的最常见的流接口。

* 所有的`Collection`集合都可以通过`stream`默认方式获取流；
* `Stream`接口的静态方法`of`可以获取数组对应的流。

```java
package com_08.jianmo.Stream;

import java.util.*;
import java.util.stream.Stream;

public class Collection2StreamTest {
	public static void main(String[] args) {
		// 把集合转化为Stream流
		List<String> list = new ArrayList<>();
		Stream<String> streamList = list.stream();


		Set<String> set = new HashSet<>();
		Stream<String> streamSet = set.stream();


		Map<String, Integer> map = new HashMap<>();
		Stream<String> streamMapKey = map.keySet().stream();
		Stream<Integer> streamMapValue = map.values().stream();
		Stream<Map.Entry<String, Integer>> streamMapEntry = map.entrySet().stream();

		// 把数组转化为Stream流
		Stream<Integer> streamArray1 = Stream.of(1, 2, 3, 4, 5);

		Integer[] array = {1, 2, 3, 4, 5};
		Stream<Integer> streamArray2 = Stream.of(array);
	}
}
```

### 常用方法

> 流模式的操作很丰富，常用`API`被分为两种：
>
> * **延迟方法**：返回值类型仍然是`Stream`接口自身类型的方法，因此支持链式调用。(除终结方法外，其余方法均为延迟方法)；
> * **终结方法**：返回值类型不再是`Stream`接口自身类型的方法，因此不再支持类似`StringBuilder`那样的链式调用，本节终结方法包括`count`和`forEach`方法。

* `forEach`遍历方法：该方法接收一个`Consumer`接口函数，会将每一个流元素交给该函数进行处理；
* `filter`过滤方法：通过`filter`方法将一个流转换成另一个子集流；
* `map`映射方法：如果需要将流中的元素映射到另一个流中，可以使用`map`方法；
* `count`统计方法：统计流中的元素个数；
* `limit`取用前`n`个方法：对流进行截取，只要前`n`个元素，当`n`大于流的大小，返回一个空流；
* `concat`组合方法：合并两个流，使之成为一个流，且这是`Stream`的静态方法，合并的两个流需要数据类型一样。

```java
package com_08.jianmo.Stream;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

public class StreamMethodTest {
	public static void main(String[] args) {
		List<String> list = new ArrayList<>();

		list.add("张三");
		list.add("王五");
		list.add("李四");
		list.add("王麻子");
		list.add("张无忌");
		list.add("张三丰");
		list.add("张将啊");

		// foreach：遍历打印(消费)人名信息，该方法是一个终结方法
		// list.stream().forEach((name) -> System.out.println(name));

		// filter：过滤姓张的人名，该方法是一个延迟方法
		// list.stream().
		// 		filter((name) -> name.startsWith("张")).
		// 		forEach((name) -> System.out.println(name));

		// map：映射，把姓张的改为姓王的，该方法是一个延迟方法
		// list.stream().map(name -> name.replace('张', '王')).
		// 		forEach((name) -> System.out.println(name));

		// size：统计一共有多少人，该方法是一个终结方法
		// long size = list.stream().count();
		// System.out.println("size:" + size);

		// limit：取前n个元素，该方法是一个延迟方法
		// list.stream().limit(4).forEach((name) -> System.out.println(name));

		// skip：跳过n个元素，该方法是一个延迟方法
		// list.stream().skip(4).forEach((name) -> System.out.println(name));

		// limit + skip，只要（3,5]个元素
		// list.stream().skip(3).limit(2).forEach((name) -> System.out.println(name));

		// concat：合并两个流，该方法是一个延迟方法
		List<String> list2 = new ArrayList<>();

		list2.add("Tom");
		list2.add("Jerry");
		list2.add("Black");
		Stream.concat(list.stream(), list2.stream()).forEach((name) -> System.out.println(name));
	}
}
```

## 方法引用

> `对象名::方法名`，对象和方法必须都已经存在了。`::`方法引用的运算符，而它所在的表达式被称为**方法引用**，如果`Lambda`要表达的函数方案已经存在于某个方法的实现中，那么则可以通过双冒号来引用该方法作为`Lambda`的替代者。`Lambda`中传递的参数一定是方法引用中可以接收的类型，否则会抛出异常。

### 通过对象引用成员方法

> 对象名和成员方法必须都已经存在，才可以使用对象名来引用成员方法。`Lambda`中传递的参数一定是方法引用中可以接收的类型，否则会抛出异常。

```java
package com_09.jianmo.MethodReference;
/*
* 通过对象名引用成员方法：对象名和成员方法已经存在，才可以使用对象名来引用成员方法。
* */
public class MethodReferenceObjectTest {
	public static void main(String[] args) {
		printString( (s) -> {
			MethodReferenceObject obj = new MethodReferenceObject();
			obj.printUpperStr(s);
		});

		// 使用方法引用优化，使用对象名进行引用
		MethodReferenceObject obj = new MethodReferenceObject();
		printString(obj::printUpperStr);
	}

	public static void printString(Printable p) {
		p.print("hello");
	}
}
```

#### Printable

```java
package com_09.jianmo.MethodReference;

@FunctionalInterface
public interface Printable {
	void print(String str);
}
```

### 通过类名称引用静态方法

> `java.lang.Math`类中已经存在了静态方法`abs`，所以我们需要通过`Lambda`来调用该方法，即可以通过函数式接口，又可以通过类名称引用该静态方法。通过类名引用静态成员方法，类已经存在，静态成员方法也已经存在。

```java
package com_10.jianmo.StaticMethodReference;
/*
* 通过类名引用静态成员方法，类已经存在，静态成员方法也已经存在。
* */
public class StaticMethodReferenceTest {
	public static void main(String[] args) {
		long ret = 0;
		ret = myAbs(-10, (n) -> n > 0 ? n : -n);
		System.out.println(ret);

		ret = myAbs(-20, Math::abs);
		System.out.println(ret);
	}
	public static long myAbs(long num, Calculable c) {
		return c.calcAbs(num);
	}
}
```

#### Calculable

```java
package com_10.jianmo.StaticMethodReference;

@FunctionalInterface
public interface Calculable {
	public abstract long calcAbs(long num);
}
```

### 通过super引用成员方法

> 如果存在继承关系，当`Lambda`中需要出现`super`调用时，也可以使用方法引用进行替代。

```java
package com_11.jianmo.SuperMethodReference;

public class Man extends Human{
	@Override
	public void sayHello() {
		System.out.println("子：hello");
	}

	public void method(Greetable g) {
		g.greet();
	}

	public void show() {
		// 1.通过创建父类对象调用父类方法
		// method(()->{
		// 	Human h = new Human();
		// 	h.sayHello();
		// });

		// 2.因为存在子父类关系，所以可以通过super关键字调用父类方法
		// method(() -> super.sayHello());

		// super父类存在，父类的方法也存在，可以通过引用父类的成员方法，
		method(super::sayHello);
	}

	public static void main(String[] args) {
		Man m = new Man();
		m.show();
	}
}
```

#### 父类

```java
package com_11.jianmo.SuperMethodReference;

// 定义父类
public class Human {
	public void sayHello() {
		System.out.println("父：你好");
	}
}
```

#### Greetable

```java
package com_11.jianmo.SuperMethodReference;

@FunctionalInterface
public interface Greetable {
	public abstract void greet();
}
```

### 通过this引用成员方法

> `this`代表当前对象，吐过需要引用的方法就是当前类中的方法，那么就可以通过`this::成员方法`的方式进行引用。

```java
package com_12.jianmo.ThisMethodReference;

public class ThisMethodReferenceTest {
	public static void main(String[] args) {
		ThisMethodReferenceTest t = new ThisMethodReferenceTest();
		t.test();
	}
	public void test() {
		// 对象内调用方法
		method("Lambda", (s) -> System.out.println(s + ":I'm rich"));

		// 使用this调用成员方法
		method("this.member", (s) -> this.isRich(s));

		// 使用this引用成员方法
		method("this.Ref", this::isRich);
	}

	private void method(String s, Richable r) {
		r.rich(s);
	}

	private void isRich(String w) {
		System.out.println(w +":I'm rich");
	}
}
```

#### Richable

```java
package com_12.jianmo.ThisMethodReference;

@FunctionalInterface
public interface Richable {
	public abstract void rich(String s);
}
```

### 类构造器引用

> 由于构造器的名称与类名完全一样，并不固定。所以构造器引用使用`类名称::new`的格式表示。

```java
package com_13.jianmo.ClassConstructorReference;

public class ClassConstructorReferenceTest {
	public static void main(String[] args) {
		// 传入一个Lambda表达式创建对象
		printPersonName("王五", (s) -> new Person(s));


		// 类构造器(构造方法)引用
		printPersonName("张三", Person::new);
	}
	public static void printPersonName(String name, PersonBuilder p) {
		System.out.println(p.BuilderPerson(name).getName());
	}
}
```

#### Person

```java
package com_13.jianmo.ClassConstructorReference;

public class Person {
	private String name;

	public Person() {
	}

	public Person(String name) {
		this.name = name;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
}
```

#### PersonBuilder

```java
package com_13.jianmo.ClassConstructorReference;

@FunctionalInterface
public interface PersonBuilder {
	// 根据姓名创建对象
	public abstract Person BuilderPerson(String name);
}
```

### 数组构造器引用

> 数组也是`Object`的子类对象，所以同样具有构造器，但是语法不同。`int[]::new`的方式数组构造器，可以改变不同的数组类型。

```java
package com_14.jianmo.ArrayConstructorReference;

public class ArrayConstructorReferenceTest {
	public static void main(String[] args) {
		int [] arr;
		arr = initArray(5, (len) -> new int[len]);
		System.out.println(arr + " len:" + arr.length);

		// 已知是int类型的数组
		arr = initArray(10, int[]::new);
		System.out.println(arr + " len:" + arr.length);
	}
	public static int[] initArray(int len, ArrayBuilder builder) {
		return builder.buildArray(len);
	}
}
```

#### ArrayBuilder

```java
package com_14.jianmo.ArrayConstructorReference;

@FunctionalInterface
public interface ArrayBuilder {
	public abstract int[] buildArray(int len);
} 
```

