# Java

## 继承

> 面向对象的三大特征：封装、`继承`、多态。继承是`域、界、门、纲、目、科、属、种`。不是儿子继承父亲。

```java
public class Teacher extends Employee {
    // Teacher继承Employee
}
```

### 继承中的成员变量

* 子类会继承父类的成员变量和方法；
* 子类的方法名和父类方法名一样时：
  * 参数一样则为重写，那个对象调用谁的代码(**多态**)；
  * 参数不一样则为重定义。
* 子类变量名和父类的变量名一样时：
  * 使用`.`访问时，左边是谁优先用谁，没有上找；
  * 使用成员方法时，成员方法访问的是谁就是谁。

### 三种变量

```java
package com_01.jianmo.Extends;

// 父类中有一个变量为：public int num = 10;
public class Teacher extends Employee {
	int num = 20;
	public void method() {
		int num = 30;
		System.out.println(num);  // 10
		System.out.println(this.num);  // 20
		System.out.println(super.num);  // 30
	}
}
```

### 重写

* 重写(Override)：在继承关系中，方法的名称一样，参数列表也一样。
* 重载(Overload)：方法的名称一样，参数列表不一样。

> 重写：创建的是子类对象，则优先用子类方法。

注意事项：

* 必须保证父子类之间方法的名称相同，参数列表也相同。且`@Override`写在方法前面，用来检测是否有效哦的正确覆盖重写，这个注解只是用来安全检测，不写也可以；
* 子类方法的返回值必须小于等于父类方法的返回值范围，`Object`类是所有类的公共最高父类。
* 子类方法的权限必须大于等于父类方法的权限修饰符：`public` > `protected` > `(default)` > `private`，不写修饰符表示`default`。

#### 父类

```java
package com_02.jianmo.Override;

public class Phone {
	public void dial() {
		System.out.println("显示电话号");
	}
}
```

#### 子类

```java
package com_02.jianmo.Override;

public class NewPhone extends Phone{
	@Override
	public void dial() {
		super.dial();
		System.out.println("显示姓名");
		System.out.println("显示头像");
	}
}

```

#### 测试类

```java
package com_02.jianmo.Override;

public class OverrideTest {
	public static void main(String[] args) {
		Phone phone = new Phone();
		phone.dial();
		System.out.println("===============");
		NewPhone newPhone = new NewPhone();
		newPhone.dial();
	}
}
```

### 继承中的构造

* 先有父类后有子类，父子类调用顺序：先父类后子类。
* 当父类中没有默认无参构造函数时，在子类构造中通过`super.Father(param)`进行显示的调用，或者父类中写一个默认无参数构造。
* `super`的父类构造调用，必须是子类构造方法的第一个语句。且只能调用一次。不先构造父类就不会分配内存，这时子类构造中如果访问了父类变量那么会不安全。

>  总结：子类必须调用父类构造函数，不写则默认使用`super()`；写了则用自己写的指定的`super`调用，还必须是第一个语句。

### super

> 用来访问父类的内容

1. 在子类的成员方法中，访问父类的成员变量；
2. 在子类的成员方法中，访问父类的成员方法；
3. 在子类的构造方法中，访问父类的构造方法。

### this

> 用来访问本类的内容

1. 在本类的成员方法中，访问本类的成员变量；
2. 在本类的成员方法中，访问本类的另一个成员方法；
3. 在本类的构造方法中，访问本类的另一个构造方法，`this(param)`也必须是构造方法的第一个语句。

> `super`和`this`两种构造调用不能在子类构造中同时使用。

## Java三种继承

1. 单继承，子类 --> 父类；
2. 多级集成，子类 --> 父类 --> 父类(爷爷类)；
3. 品字继承，即一个父类被两个兄弟类继承。

![Java继承](./Picture/Java继承.jpg)

## 抽象方法&抽象类

* 抽象方法：在方法名前加`abstract`关键字修饰，然后去掉大括号，分号结尾和`C++`一样；
* 抽象类：抽象方法所在的类，必须是抽象类才行。在`class`前加`abstract`关键字修饰。

### 抽象方法和抽象类使用

1. 抽象类无法实例化；
2. 抽象类可以有构造方法，用来初始化父类的成员变量；
3. 抽象类中不一定包含抽象方法，但是有抽象方法那么该类就必须是一个抽象类；
4. 子类继承的抽象类必须实现父类的所有抽象方法。

#### 抽象类：Animal

```java
package com_03.jianmo.Abstract;

public abstract class Animal {
	public abstract void eat();  // 抽象方法
	public int num = 10;  // 普通成员变量
	public void normalMethod() {  // 普通成员方法
		System.out.println("普通的方法,num="+this.num);
	}
}
```

#### 子类：Dog

```java
package com_03.jianmo.Abstract;

public class Dog extends Animal{
	@Override
	public void eat() {
		System.out.println("狗吃骨头");
	}
}
```

#### 子类：Cat

```java
package com_03.jianmo.Abstract;

public class Cat extends Animal{
	@Override
	public void eat() {
		System.out.println("猫吃鱼");
	}
}
```

#### 测试类

```java
package com_03.jianmo.Abstract;

public class AbstractTest {
	public static void main(String[] args) {
		AbstractTest.method(new Dog());
		AbstractTest.method(new Cat());
	}
	static void method(Animal a) {  // 传入不同对象不同的行为
		a.eat();
		a.normalMethod();
	}
}
```

## 接口

> 接口：多个类公共的规范标准，接口是一种引用数据类型。最重要的内容就是其中的`抽象方法`。接口当中的修饰符必须是`public stract`所以可以不写。

* 接口(Java 7)可以包含的内容：
  1. 常量
  2. 抽象方法
* 接口(Java 8)可以额外包含的内容
  3. 默认方法
  4. 静态方法
* 接口(Java 9)可以额外包含的内容
  5. 私有方法

### 接口注意事项

* 接口当中的抽象方法，修饰符必须是两个固定的关键字：`public abstract`，可以省略不写；
* 接口无法直接使用，需要通过`实现类`来实现接口；
* 实现类通过`implements`来实现接口，实现类必须实现接口的所有方法；
* 接口中可以定义变量必须有初始值且不能被修改(常量变量)；
* 如果实现类没有实现所有的抽象方法，那么该类必须是抽象类。

### 接口：Animal

```java
package com_04.jianmo.Interface;

// 接口定义
public interface Animal {
	void eat();  // 默认加上public abstract
	public abstract void sleep();  // public abstract可以不加
	int num = 10;  // 变量必须有初始值，但是无法修改
	//	void normalMethod() {  // Error:(7, 29) java: 接口抽象方法不能带有主体
	//		System.out.println("普通成员方法：num="+num);
	//	}
}

```

### 子类：Dog

```java
package com_04.jianmo.Interface;

// 接口继承用implements
public class Dog implements Animal {
	@Override
	public void eat() {
		// num = 20;  // Error:(6, 17) java: 无法为最终变量num分配值
		System.out.println("狗吃" + num + "个骨头");
	}

	@Override
	public void sleep() {
		System.out.println("狗睡觉");
	}
}
```

### 子类：Cat

```java
package com_04.jianmo.Interface;

// 接口继承用implements
public class Cat implements Animal {
	@Override
	public void eat() {
		System.out.println("猫吃" + num + "条鱼");
	}

	@Override
	public void sleep() {
		System.out.println("猫睡觉");
	}
}
```

### 测试类

```java
package com_04.jianmo.Interface;

public class InterfaceTest {
	public static void main(String[] args) {
		Animal dog = new Dog();
		InterfaceTest.method(dog);
		System.out.println("==========");
		Animal cat = new Cat();
		InterfaceTest.method(cat);
	}
	public static void method(Animal a) {
		a.eat();
		a.sleep();
	}
}
```

## 接口默认方法

1. 接口的默认方法，可以通过接口实现类对象，直接调用；
2. 接口的默认方法，可以被接口实现类进行重写；
3. 接口默认方法用来解决接口的升级问题。

> `Java 8`以后可以在接口中定义默认方法，仅`public`可以省略
>
> ```java
> // Java 8以后才可以在接口中定义默认方法，可以有函数体
> public default void drink() {
>     // 方法体
> }
> ```

### 接口：Animal

```java
package com_05.jianmo.Default;

public interface Animal {
	public abstract void eat();

	// 虽然这个样接口设计不合理，但是说明问题就行了
	// 猫和狗类已经被放在项目中无法改变了，现在想升
	// 级接口给鹦鹉提供一个唱歌的方法，那么就可以使
	// 用default
	public default void sing() {
		System.out.println("sing");
	}

}
```

### 子类：Cat

```java
package com_05.jianmo.Default;

public class Cat implements Animal {
	@Override
	public void eat() {
		System.out.println("猫吃鱼");
	}
}
```

### 子类：Dog

```java
package com_05.jianmo.Default;

public class Dog implements Animal {
	@Override
	public void eat() {
		System.out.println("狗吃骨头");
	}
}
```

### 子类：Parrot

```java
package com_05.jianmo.Default;

public class Parrot implements Animal {
	@Override
	public void eat() {
		System.out.println("鹦鹉吃坚果");
	}

	@Override
	public void sing() {
		System.out.println("鹦鹉在唱歌");
	}
}
```

### 测试类

```java
package com_05.jianmo.Default;

public class DefaultTest {
	public static void main(String[] args) {
		Animal dog = new Dog();
		Animal cat = new Cat();
		DefaultTest.oldCode(dog, cat);

		// 升级接口后dog和cat也能调用sing不过是调用的默认的接口
		Animal parrot = new Parrot();
		DefaultTest.newCode(parrot);

        // 调用默认方法，如果实现类当中没有，会向上找接口
		// 也可以重写，但是前提是Dog和Cat类不能重写sing方法
		dog.sing();
		cat.sing();
	}
	static void oldCode(Animal dog, Animal cat) {
		// 无法更改的代码
		dog.eat();
		cat.eat();
	}
	static void newCode(Animal a) {
		// 新功能
		a.eat();
		a.sing();
	}
}
```

## 接口静态方法

> 从`Java 8`开始，接口中允许定义静态方法。

```java
public static void eat() {
    // 方法体
}
```

1. 不能通过接口实现类的对象来调用接口中的静态方法；
2. 应该通过接口名称，直接调用接口中的静态方法。

### 接口：Animal

```java
package com_06.jianmo.Static;

public interface Animal {
	public static void eat() {
		System.out.println("eat");
	}
}
```

### 子类Dog

```java
package com_06.jianmo.Static;

public class Dog implements Animal {
}
```

### 测试类

```java
package com_06.jianmo.Static;

public class StaticTest {
	public static void main(String[] args) {
//		Animal dog = new Dog();
//		dog.eat(); // 错误：Error:(6, 24) java: 静态接口方法调用非法 应将接收方表达式替换为类型限定符 'com_06.jianmo.Static.Animal'
		Animal.eat();  // 通过接口调用静态方法
	}
}
```

## 接口私有方法

> 从`Java 9`开始，接口中允许定义私有方法。

1. 普通私有方法，解决多个默认方法之间重复代码问题；

   ```java
   private void P() {
       System.out.print("hello,");
       System.out.println("world");
   }
   ```

2. 静态私有方法，解决多个静态方法之间重复代码问题。

   ```java
   private static void S() {
       System.out.print("你好,");
       System.out.println("世界");
   }
   ```

   ### 接口：Animal

   ```java
   package com_07.jianmo.Private;
   
   public interface Animal {
   	// 普通私有方法，解决默认方法之间重复代码问题
   	public default void method1() {
   		P();
   	}
   
   	public default void method2() {
   		P();
   	}
   	private void P() {
   		System.out.print("hello,");
   		System.out.println("world");
   	}
   
   	// 静态私有方法，解决多个静态方法之间重复代码问题
   	public static void method3() {
   		Animal.S();
   	}
   
   	public static void method4() {
   		Animal.S();
   	}
   	private static void S() {
   		System.out.print("你好,");
   		System.out.println("世界");
   	}
   }
   ```

   ### 子类：Dog

   ```java
   package com_07.jianmo.Private;
   
   public class Dog implements Animal {
   }
   ```

   ### 测试类

   ```java
   package com_07.jianmo.Private;
   
   public class PrivateTest {
   	public static void main(String[] args) {
   		Animal dog = new Dog();
   		dog.method1();
   		dog.method2();
   //		dog.P();  // Error:(8, 20) java: P() 在 com_07.jianmo.Private.Animal 中是 private 访问控制
   		System.out.println("==============");
   		Animal.method3();
   		Animal.method4();
   //		Animal.S();  // Error:(11, 23) java: S() 在 com_07.jianmo.Private.Animal 中是 private 访问控制
   	}
   }
   ```

## 接口成员变量

> 接口当中可以定义`成员变量`，必须使用`public static final`三个关键字修饰，可以不写默认加。必须有初始值。该成员变量为常量则**变量名必须大写**；

1. 接口当中的常量，可以省略`public static final`，注意：不写也是这样；
2. 接口当中的常量，必须进行赋值，即初始化；
3. 接口当中的常量，建议使用全大写字母表示，并用下划线`_`分割单词。

```java
public interface Animal {
	public static final int A = 10;
	int VALUE_OF_B = 20;
}
```

### 接口：Animal

```java
package com_08.jianmo.Constant;

public interface Animal {
	public static final int A = 10;
	int VALUE_OF_B = 20;  // 同上，public static final默认可以不写
}
```

### 测试类：

```java
package com_08.jianmo.Constant;

public class ConstantTest {
	public static void main(String[] args) {
//		Animal.a = 11;  // Error:(5, 23) java: 无法为最终变量a分配值
		System.out.println(Animal.A);
		System.out.println(Animal.VALUE_OF_B);
	}
}
```

## 接口总结

### Java_9

1. 成员变量其实是常量，`public static final 数据类型 常量名 = 值`

   * 常量必须进行初始化，且再也不能被改变；
   * 常量名称完全大写，用下划线进行分割。

2. 接口中最重要的就是抽象方法，`[public] [abstract] 返回值类型 方法名(参数列表);`

   * 实现类必须重写接口所有的方法，如果是抽象类则可以不重写。

3. 接口中允许定义私有方法

   1. 普通私有方法：`private 返回值类型 方法名(参数列表) {方法体}`
   2. 静态私有方法：`private static 返回值类型 方法名(参数列表) {方法体}`

   > `private`的方法只有接口自己才能调用，不能被实现类或别人使用。

### Java_8

1. 接口中允许定义默认方法，`[public] default 返回值类型 方法名(参数列表) {方法体}`
   * 默认方法可以被重写
2. 接口中允许定义静态方法，`[public] static 返回值类型 方法名(参数列表) {方法体}`
   * 只能通过接口名调用静态方法