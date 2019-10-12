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

## 重写

* 重写(Override)：在继承关系中，方法的名称一样，参数列表也一样。
* 重载(Overload)：方法的名称一样，参数列表不一样。

> 重写：创建的是子类对象，则优先用子类方法。

注意事项：

* 必须保证父子类之间方法的名称相同，参数列表也相同。且`@Override`写在方法前面，用来检测是否有效哦的正确覆盖重写，这个注解只是用来安全检测，不写也可以；
* 子类方法的返回值必须小于等于父类方法的返回值范围，`Object`类是所有类的公共最高父类。
* 子类方法的权限必须大于等于父类方法的权限修饰符：`public` > `protected` > `(default)` > `private`，不写修饰符表示`default`。

### 父类

```java
package com_02.jianmo.Override;

public class Phone {
	public void dial() {
		System.out.println("显示电话号");
	}
}
```

### 子类

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

### 测试类

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

## 继承中的构造

* 先有父类后有子类，父子类调用顺序：先父类后子类。
* 当父类中没有默认无参构造函数时，在子类构造中通过`super.Father(param)`进行显示的调用，或者父类中写一个默认无参数构造。
* `super`的父类构造调用，必须是子类构造方法的第一个语句。且只能调用一次。不先构造父类就不会分配内存，这时子类构造中如果访问了父类变量那么会不安全。

>  总结：子类必须调用父类构造函数，不写则默认使用`super()`；写了则用自己写的指定的`super`调用，还必须是第一个语句。

## super

> 用来访问父类的内容

1. 在子类的成员方法中，访问父类的成员变量；
2. 在子类的成员方法中，访问父类的成员方法；
3. 在子类的构造方法中，访问父类的构造方法。

## this

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

### 概念

* 抽象方法：在方法名前加`abstract`关键字修饰，然后去掉大括号，分号结尾和`C++`一样；
* 抽象类：抽象方法所在的类，必须是抽象类才行。在`class`前加`abstract`关键字修饰。

### 抽象方法和抽象类使用

1. 抽象类无法实例化；
2. 抽象类可以有构造方法，用来初始化父类的成员变量；
3. 抽象类中不一定包含抽象方法，但是有抽象方法那么该类就必须是一个抽象类；
4. 子类继承的抽象类必须实现父类的所有抽象方法。