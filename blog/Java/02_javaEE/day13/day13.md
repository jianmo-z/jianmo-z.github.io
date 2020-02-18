# day13

## Junit单元测试

> `Junit`就是属于白盒测试。

### 测试分类

* **黑盒测试**：不需要写代码，给输入值，看程序是否能够输出期望的值；
* **白盒测试**：需要写代码的，关注程序具体的执行流程。

### Junit使用

1. 定义一个测试类；
   * 类名：建议测试类的类名为`测试的类名Test`，例如：`CalculatorTest`；
   * 包名：`xxx.yyy.zzz.test`包。
2. 定义测试方法：测试方法可以独立运行；
   * 方法名：`test测试的方法名`，例如：`testAdd()`；
   * 返回值：`void`类型，因为测试方法需要独立运行，所以返回值建议为`void`类型；
   * 参数列表：因为测试方法需要独立运行，所以建议空参。
3. 给方法加`@Test`注解；
4. 导入`Junit`依赖，测试方法可以运行；

### Junit结果判定

> 测试程序一般不输出结果，使用断言进行判断。
>
> * 红色：失败；
> * 绿色：成功；
> * 一般会使用断言操作来处理结果`public static void assertEquals(long expected, long actual);`还有其他的方法进行断言判断。
>   * 第一个参数`expected`：期望的结果；
>   * 第二个参数`actual`：实际的结果。

### Junit注解

* `@Before`：初始化方法，用于资源的申请，所有**测试方法**在执行**之前**都会执行该方法。自动在执行每个测试方法之前调用执行；
* `@After`：用于资源的释放，所有**测试方法**在执行**之后**都会执行该方法。自动执行，即使前面的程序出错也会执行。

## Junit运行问题解决

> 参考链接：https://blog.csdn.net/Feihongxiansen/article/details/83245832

![Junit运行问题解决](./Picture/01_Junit设置.png)

## 反射

> 反射是框架设计的**灵魂**，框架就是一个半成品软件。可以在框架的基础之上进行软件开发，简化编码。
>
> **反射**：将类的各个组成部分封装为其他对象，这就是反射机制。

### 反射优点

1. 可以在程序运行过程中，操作这些对象；
2. 可以解耦，提高程序的可扩展性。

### 获取Class对象的方式

1. `Class.forName("全类名")`：将字节码文件加载进内存，全类名需要包括包路径，返回`Class`对象；
   * 多用于配置文件，将类名定义在配置文件中，读取文件，加载类；
2. `类名.class`：通过类名的属性`class`获取；
   * 多用于参数的传递；
3. `对象.getClass()`：通过对象获取。
   * 多用于对象的获取字节码的方式。

> 同一个字节码文件(`*.class`)在一次程序运行过程中，只会被加载一次。无论通过哪一种方式获取的`Class`对象都是同一个。

```java
package com_01.jianmo.reflect;
/*
* 1. Class.forName("全类名")
* 2. 类名.class
* 3. 对象.getClass()
* */

import com_01.jianmo.domain.Person;

public class ReflectDemo01 {
	public static void main(String[] args) throws ClassNotFoundException {

		// 1.Class.forName("全类名")
		Class cls01 = Class.forName("com_01.jianmo.domain.Person");
		System.out.println(cls01);

		// 2. 类名.class
		Class cls02 = Person.class;
		System.out.println(cls02);

		// 3. 对象.getClass()
		Person p = new Person();
		Class cls03 = p.getClass();
		System.out.println(cls03);

		// 使用==比较三个对象是否是相等的？？？
		// 同一个字节码文件(*.class)在一次程序运行过程中，只会被加载一次。
		// 无论通过哪一种方式获取的Class对象都是同一个。
		System.out.println(cls01 == cls02);  // true
		System.out.println(cls02 == cls03);  // true
		System.out.println(cls02 == cls01);  // true

	}
}
```

### Class对象功能们

> `Class`对象大部分是`get`方法。
>
> * 获取功能：
>   1. 获取成员变量们，包含父类的东西；
>   2. 获取构造方法们，包含父类的东西；
>   3. 获取成员方法们，包含父类的东西；
>   4. 获取类名。

### Class对象获取成员变量们

> * 获取成员变量们；
>   * `Field[] getFields()`：获取所有`public`修饰的成员变量；
>   * `Field[] getField(String name)`：获取指定的成员变量，只能获取`public`的变量；
>   * `Field[] getDeclaredFields()`：获取所有的成员变量，不考虑修饰符；
>   * `Field getDeclaredField(String name)`：获取指定的成员变量，不考虑修饰符。
>
> ```java
> package com_01.jianmo.reflect;
> 
> import com_01.jianmo.domain.Person;
> 
> import java.lang.reflect.Field;
> 
> public class ReflectDemo02 {
> 	/*
> 	 * 1. 获取成员变量们；
> 	 *    - Field[] getFields()：获取成员变量；
> 	 *    - Field[] getField(String name)：获取指定的成员变量；
> 	 *    - Field[] getDeclaredFields()：
> 	 *    - Field getDeclaredField(String name)：
> 	 * */
> 	public static void main(String[] args) throws NoSuchFieldException, IllegalAccessException {
> 		Class<Person> personClass = Person.class;
> 		Person p = new Person();
> 
> 		// 1.获取public成员变量
> 		final Field[] fields = personClass.getFields();
> 		for (Field it : fields) {
> 			System.out.println(it);
> 		}
> 
> 		// 2.获取指定的public成员变量
> 		final Field a = personClass.getField("a");
> 
> 			// 2.1获取成员变量a的值
> 			Object value = a.get(p);
> 			System.out.println(value);
> 
> 			// 2.2设置成员变量a的值
> 			a.set(p, new String("张三"));
> 			System.out.println(p);
> 			// Person{name='null', age=0, a='张三', b='null', c='null', d='null'}
> 
> 		// 3.获取所有的成员变量，不考虑修饰符
> 		final Field[] declaredFields = personClass.getDeclaredFields();
> 		for (Field it : declaredFields) {
> 			System.out.println(it);
> 		}
> 
> 		// 4.获取指定的成员变量，不需要考虑修饰符
> 		final Field d = personClass.getDeclaredField("d");
> 			//4.1获取私有变量b的值，需要忽略权限修饰符的安全检查
> 			 d.setAccessible(true);  // 忽略权限修饰符的安全检查，又称暴力反射
> 			// d.setAccessible(false);  // java.lang.IllegalAccessException:
> 			Object o = d.get(p);
> 			System.out.println(o);
> 
> 			// 4.2设置成员变量d的值
> 			d.set(p, "d");
> 			System.out.println(p);
> 
> 	}
> }
> ```

### Class对象获取构造方法们

> *	获取构造方法们；
>   *	`Constructor<?>[] getConstructors()`：获取成员变量；
>   *	`Constructor<T>[] getConstructor(Class<?>... parameterTypes)`：获取构造方法，通过传入的参数不同，区分不同的构造方法；
>   *	`Constructor<?>[] getDeclaredConstructors()`：获取成员变量；
>   *	`Constructor<T>[] getDeclaredConstructor(Class<?>... parameterTypes)`：获取指定的成员变量。
>
> ```java
> package com_01.jianmo.reflect;
> 
> import com_01.jianmo.domain.Person;
> 
> import java.lang.reflect.Constructor;
> import java.lang.reflect.Field;
> import java.lang.reflect.InvocationTargetException;
> 
> public class ReflectDemo03 {
> 	/*
> 	 * 2. 获取构造方法们；
> 	 *    - Constructor<?>[] getConstructors()：获取成员变量；
> 	 *    - Constructor<T>[] getConstructor(Class<?>... parameterTypes)：获取指定的成员变量；
> 	 *    - Constructor<?>[] getDeclaredConstructors()：获取成员变量；
> 	 *    - Constructor<T>[] getDeclaredConstructor(Class<?>... parameterTypes)：获取指定的成员变量；
> 	 * */
> 	public static void main(String[] args) throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException {
> 		Class<Person> personClass = Person.class;
> 
> 		// 1.获取所有的public构造方法
> 		Constructor<?>[] constructors = personClass.getConstructors();
> 		for (Constructor<?> it : constructors) {
> 			System.out.println(it);
> 		}
> 
> 		// 2.获取指定参数类型的构造方法
> 		Constructor<Person> constructor_01 = personClass.getConstructor(String.class, int.class);
> 		System.out.println(constructor_01);
> 
> 			// 2.1创建对象
> 			Person p1 = constructor_01.newInstance("张三", 18);
> 			System.out.println(p1);
> 
> 			// 使用空参构造，方式一
> 			Constructor<Person> constructor_02 = personClass.getConstructor();
> 			Person p2 = constructor_02.newInstance();
> 			System.out.println(p2);
> 
> 			// 使用空参构造，方式二
> 			Person p3 = personClass.newInstance();
> 			System.out.println(p3);
> 
> 
> 		// 3.获取所有的构造方法，不考虑权限修饰符
> 		Constructor<?>[] declaredConstructors = personClass.getDeclaredConstructors();
> 		for (Constructor<?> it : declaredConstructors) {
> 			System.out.println(it);
> 		}
> 
> 		// 4.获取指定参数类型的构造方法，不考虑权限修饰符
> 		Constructor<Person> declaredConstructor = personClass.getDeclaredConstructor(String.class);
> 		declaredConstructor.setAccessible(true);
> 		// declaredConstructor.setAccessible(false);  // java.lang.IllegalAccessException
> 		Person a = declaredConstructor.newInstance("a");
> 		System.out.println(a);
> 
> 	}
> }
> ```

### Class获取成员方法们

> * 获取成员方法们；
>   - `Method[] getMethods()`：
>   - `Method getMethod(String name, Class<?>... parameterTypes)`：
>   - `Method[] getDeclaredMethods()`：
>   - `Method getDeclaredMethod(String name, Class<?>... parameterTypes)`。
>
> ```java
> package com_01.jianmo.reflect;
> 
> import com_01.jianmo.domain.Person;
> 
> import java.lang.reflect.InvocationTargetException;
> import java.lang.reflect.Method;
> 
> public class ReflectDemo04 {
> 	/*
> 	 * 3. 获取成员方法们；
> 	 *    - Method[] getMethods()：
> 	 *    - Method getMethod(String name, Class<?>... parameterTypes)：
> 	 *    - Method[] getDeclaredMethods()：
> 	 *    - Method getDeclaredMethod(String name, Class<?>... parameterTypes)：
> 	 * */
> 	public static void main(String[] args) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {
> 		Class<Person> personClass = Person.class;
> 		Person p = new Person("张三", 18);
> 
> 		// 1.获取所有的public修饰的成员方法
> 		Method[] methods = personClass.getMethods();
> 		for (Method method : methods) {
> 			System.out.println(method);
> 		}
> 
> 		// 2.获取指定的public修饰的成员方法
> 		Method getName = personClass.getMethod("getName");
> 		System.out.println(getName.invoke(p));
> 
> 		// 3. 获取所有的成员方法，不考虑修饰符
> 		Method[] declaredMethods = personClass.getDeclaredMethods();
> 		for (Method it : declaredMethods) {
> 			System.out.println(it);
> 		}
> 
> 		// 4.获取指定的成员方法，不考虑修饰符
> 		Method getAge = personClass.getDeclaredMethod("setAge", int.class);
> 		getAge.setAccessible(true);  // 仍需要设置忽略访问权限检查
> 		getAge.invoke(p, 20);
> 		System.out.println(p);
> 	}
> }
> ```

### Class获取类名

> * 获取类名。
>   - `String getName()`：获取类名。
>
> ```java
> package com_01.jianmo.reflect;
> 
> import com_01.jianmo.domain.Person;
> 
> public class ReflectDemo05 {
> 	/*
> 	 * 4. 获取类名。
> 	 *    - String getName()：获取类名。
> 	 * */
> 	public static void main(String[] args) throws NoSuchFieldException, IllegalAccessException {
> 		Class<Person> personClass = Person.class;
> 		Person p = new Person();
> 
> 		String name = personClass.getName();
> 		System.out.println(name);
> 	}
> }
> ```

## Field类

> 用来操作类的**成员变量**。
>
> * 获取方法：
>   * `public Object get(Object obj)`：
> * 设置方法：
>   * `public void set(Object obj, Object value)`：
> * 忽略访问权限修饰符的安全检查：
>   * `public void setAccessible(boolean flag)`

```java
Person p = new Person();

// 1.获取成员变量a的值
Object value = a.get(p);
System.out.println(value);

// 2.设置成员变量a的值
a.set(p, new String("张三"));
System.out.println(p);

// 3.忽略权限修饰符的安全检查，又称暴力反射
d.setAccessible(true);  // d成员变量被private修饰
// d.setAccessible(false);  // java.lang.IllegalAccessException
```

## Constructor类

> 用来表示类的**构造方法**，以便创建对象。
>
> * 创建对象：
>   * `T newInstance(Object... initargs)`：获取一个实例对象；
> * 忽略访问权限修饰符的安全检查，使用`private`构造器：
>   * `public void setAccessible(boolean flag)`
>
> 如果创建一个空参对象可以使用`Class`的`newInstance`方法进行简化操作。

## Method类

> 用来表示类的**成员方法**。
>
> * 执行方法：
>   * `public Object invoke(Object obj, Object... args)`：执行该方法；
> * 获取方法名：
>   * `public String getName()`：获取该方法的方法名；

## 注解

> 注解概念：说明程序的，给计算机看的；注释概念：用文字描述程序，给程序员看的。注解是`JDK1.5`之后的新特性。
>
> 作用分类：
>
> 1. 编写文档：通过代码里标识的注解生成文档，生成doc文档；
> 2. **代码分析**：通过代码里标识的注解对代码进行分析，使用反射；
> 3. 编译检查：通过代码里标识的注解让编译器能够实现基本的编译键查，`Override`。

### 注解编写文档演示

```java
package com_01.jianmo.annotation;

/**
 * 注解javadoc演示
 *
 * @author Pip
 * @version 1.0
 * @since 1.5
 */
public class AnnotationDemo01 {
	/**
	 * 计算两个数之和
	 * @param a 整数
	 * @param b 整数
	 * @return 两个数之和
	 */
	public int add(int a, int b) {
		return a + b;
	}
}
```

### JDK中预定义注解

> * `@Override`：检测被该注解标记的方法是否是继承自父类(父接口)的；
> * `@Deprecated`：将该注解标注的内容已过时，有更好的替代方案；
> * `@SuppressWarnings`：压制警告，一般传递参数为`all`，例：`@SuppressWarnings("all")`。

### 自定义注解

> * 注解定义格式：
>
> ```java
> 元注解
> public @interface 注解名称 {
>     属性列表
> }
> ```
>
> * 注解的本质：注解本质就是一个接口，该接口默认继承`java.lang.annotation.Annotation`；
>
> ```java
> public interface MyAnnotation extends java.lang.annotation.Annotation {
>     
> }
> ```
>
> * 注解的属性：接口中的抽象方法(属性)；
>   * 要求
>     1. 属性允许的返回值类型：
>        * 基本数据类型(4类8种)；String；枚举；注解，已经以上类型的数组类型。
>     2. 定义了属性，在使用注解时需要给属性赋值；
>        * 如果定义属性时，使用`default`关键字给属性默认初始化值，则使用注解时，可以不进行属性的赋值；
>        * 如果**有且仅有一个属性需要赋值**，并且属性的名称是value，则value可以省略，直接定义值即可，例`SuppressWarnings`注解；
>        * 数组赋值是，只使用`{}`大括号进行包裹。如果数组中只有一个值，那么`{}`可以省略。
> * 元注解：用于描述注解的注解。
>   * `@Target`：描述注解能够作用的位置；
>     * `ElementType`取值：
>       * `TYPE`：可以作用于类上；
>       * `METHOD`：可以作用于方法上；
>       * `FIELD`：可以作用于成员变量上。
>   * `@Retention`：描述注解被保留的阶段；
>     * `@Rentention(RetentionPolicy.RUNTIME)`：当前被描述的注解，会保留到`class`字节码文件中，并被`JVM`读取到，一般使用`RUNTIME`。
>   * `@Documented`：描述注解是否被抽取到api文档中；
>   * `Inherited`：描述注解是否被子类继承。

### 在程序使用(解析)注解

> 在程序中使用(解析)，获取注解中定义的属性值。

1. 注解获取该类的字节码文件对象；
2. 获取该对象的注解`getAnnotation(Class)`；
3. **调用**注解对象中定义的抽象方法，获取返回值就是属性值。