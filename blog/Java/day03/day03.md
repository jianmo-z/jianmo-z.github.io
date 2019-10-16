# day03

## 多态

> 面向对象三大特征：封装性、继承性、多态性。`extends`和`implements`实现，是多态的前提。

* 对象拥有多种形态， 一般在类中表示为：表面形态和内部形态；
* `父类名称 对象名 = new 子类名();`或`接口名称 对象名 = new 实现类名称();`

> 编译看左边，运行看右边。

### 多态下的成员变量和方法

* 成员变量：
  * 直接通过对象名称访问成员变量，看等号左边是谁，优先用谁，没有则向上找；
  * 简介通过成员方法访问成员变量，看该方法属于谁，优先用谁，没有则向上找。
* 成员方法：
  * 看`new`的是谁，就优先用谁，没有就向上找。

### Java多态转型

* 向上转型：父类引用指向子类对象。
* 向下转型：用对象向下转型，还原。`对象名称 对象名 = (子类名称)父类对象;`
  * 向下转型可能会出现不安全的情况，当向下转型错误时，出现，`ClassCastException`类型的错误。

## 多态案例

### Compter

```java
package com_03.jianmo.Example;

public class Computer {
	public void powerOn() {
		System.out.println("开机");
	}

	public void powerOff() {
		System.out.println("关机");
	}
	public void useDevice(USB u) {  // 参数注入
		if (u instanceof Mouse) {  // 先判断再转型调用
			((Mouse) u).click();
		} else if (u instanceof Keyboard) {  // 先判断再转型
			((Keyboard) u).typing();
		}
		u.openDevice();
		u.closeDevice();
	}
}
```

### USB接口类

```java
package com_03.jianmo.Example;

public interface USB {
	public void openDevice();
	public void closeDevice();
}
```

### 实现类：Keyboard

```java
package com_03.jianmo.Example;

public class Keyboard implements USB {
	@Override
	public void openDevice() {
		System.out.println("安装键盘驱动");
	}

	@Override
	public void closeDevice() {
		System.out.println("卸载键盘驱动");
	}

	public void typing() {
		System.out.println("打字");
	}

}
```

### 实现类：Mouse

```java
package com_03.jianmo.Example;

public class Mouse implements USB {
	@Override
	public void openDevice() {
		System.out.println("安装鼠标驱动");
	}

	@Override
	public void closeDevice() {
		System.out.println("卸载鼠标驱动");
	}

	public void click() {
		System.out.println("点击");
	}
}
```

### 测试类：ComputerTest

```java
package com_03.jianmo.Example;


public class ComputerTest {
	public static void main(String[] args) {
		Computer computer = new Computer();
		computer.powerOn();

		Mouse mouse = new Mouse();
		computer.useDevice(mouse);

		Keyboard keyboard = new Keyboard();
		// 方法参数是USB类型，传递进去的是实现类
		computer.useDevice(keyboard);  // 不是多态，但是自动类型转化可以成功
		computer.useDevice(new Keyboard());  // 匿名对象

		computer.powerOff();
	}
}
```

## final关键字

> 对于类和方法来说，`abstract`和`final`关键字不能同时使用，因为`abstract`意味着继承或重写，但`final`表示不能继承或重写。明显冲突了。

### 四种用法

1. 用来修饰一个类，当前这个类不能有任何子类；
2. 用来修饰一个方法，该方法不能被覆盖重写；
3. 用来修饰一个局部变量，这个变量就不能再进行更改了，一次赋值，终**生**不变；
4. 用来修饰一个成员变量，这个变量也无法改变。成员变量有默认值，用了`final`就不会有默认值了，所以用了`final`修饰必须手动赋值。可以采用直接赋值或者在构造函数(所有重载形式中都需要赋值)中赋值，且只能一次。

> 对于一个基本类型而言，不可变指的是变量的数据不能改变。
>
> 对于一个引用类型而言，不可变指的是引用指针的指向不能改变。

## 权限修饰符

| 不同位置\\修饰符(权限大到小) | public | protected | (default) | private |
| :--------------------------: | :----: | :-------: | :-------: | :-----: |
|           同一个类           |  YES   |    YES    |    YES    |   YES   |
|           同一个包           |  YES   |    YES    |    YES    |   NO    |
|         不同包的子类         |  YES   |    YES    |    NO     |   NO    |
|         不同包非子类         |  YES   |    NO     |    NO     |   NO    |

