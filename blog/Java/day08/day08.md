# day08

## 异常

> 异常：指的是程序在执行工程中，出现的非正常的情况，最终会导致`JVM`的非正常停止。在`java`等面向对象的编程语言中，异常本身是一个类，产生异常就是创建异常对象并抛出一个异常对象，`java`处理异常的方式是中断处理。

## 异常体系

* `Throwable`类
  * `Error`子类：错误必须修改源代码，程序才能继续执行。不能处理，只能尽量避免，无法处理错误只能避免；
  * `Exception`子类：编译器异常，进行编译(写代码)java程序出现的问题。由于使用不当导致，可以避免。
    * `Runtimeexception`子类：运行期异常，java程序运行过程中出现的问题。处理异常后，程序可以继续执行。

> 异常的分类

![异常的分类](./Picture/01_异常的分类.png)

## 异常的产生与处理

### 异常产生

```java
throw new 异常类名(参数);
```

> 使用`throw`关键字在指定的方法中抛出指定的异常。
>
> * `throw`关键字必须写在方法的内部；
> * `throw`关键字后面`new`的对象必须是`Exception`或者`Exception`的子类对象；
> * `throw`关键字抛出指定的异常对象，我们就必须处理这个异常对象；
>   * `throw`关键字后面创建的是`RuntimeException`或者是`RuntimeException`的子类对象，我们如果不处理则会交给`JVM`处理（打印异常对象并中断程序）；
>   * `throw`关键字后面创建的是编译异常（写代码的时候报错），我们就必须处理这个异常，要么继续抛出`throw`，要么捕获异常`try..catch`。
>
> 写代码时首先需要对方法传递过来的参数进行合法性校验，如果参数不合法，那么我们就必须使用抛出异常的方式告知调用者，传递的参数有问题。可以使用`Object.requireNonNull()`
>
> ```java
> package com_01.jianmo.Exception;
> 
> import java.util.Objects;
> 
> public class ExceptionTest {
> 	public static void main(String[] args) {
> 		ExceptionTest.notNull(null);
> 	}
> 	public static void notNull(Object obj) {
> 		// 判断obj非空
> //		Objects.requireNonNull(obj);  // java.lang.NullPointerException
> 
> 		// 判断obj非空：重载加异常描述
> 		Objects.requireNonNull(obj, "obj为空");  // java.lang.NullPointerException: obj为空
> 	}
> 
> }
> ```

### 异常处理

#### throws声明处理

> 把异常交给别人处理，当方法内部抛出异常对象的时候，那么我们就必须处理这个异常对象。可以使用`throws`关键字处理异常对象，会把异常对象声明抛出给方法的调用者处理（自己不处理，给别人处理），最终交给`JVM`处理，`JVM`会采用中断处理。

```java
修饰符 返回值类型 方法名(产出列表) throws AAAException, BBBException, ... {
    if(AAA) {
          throw new AAAException("产生原因");  
    } else if(BBB) {
          throw new BBBException("产生原因");
    } else {
	    // ...
    }
}
```

#### throws注意事项

1. throws关键字必须写在方法声明出；
2. throws关键字后边声明的异常必须是`Exception`或者`Exception`的子类；
3. 方法内部如果抛出了多个异常对象，那么throws后面必须也声明多个异常，如果抛出的多个异常对象有父子类关系，那么直接声明父类异常即可；
4. 调用了一个声明抛出异常的方法，那么就必须处理声明的异常，要么继续使用throws声明抛出，交给方法的调用者处理，最终交给JVM中断处理，要么`try ... catch`自己处理异常。

#### try…catch捕获处理

> `try…catch`对异常有针对性的语句进行捕获，可以对出现的异常进行指定方式的处理。

#### try…catch注意事项

1. `try`中可能会抛出多个异常对象，那么就可以使用多个`catch`来处理这些异常对象；
2. 如果`try`中产生了异常，那么就会执行`catch`中的异常处理逻辑，执行完毕`catch`中的处理逻辑，继续执行`try...catch`，如果try中没有产生异常，那么就不会执行`catch`中异常的处理逻辑。

```java
try {
    // 可能抛出异常的代码块
} catch(IndexOutOfBoundsException e) {
    // 捕获对应类型的异常
} catch(RuntimeException e) {
    // 捕获对应类型的异常
} catch(异常类型 e) {
    // 使用父类捕获所有的异常
}
```

## Throwable类

* `public String getMessage()`：简短信息，获取异常的描述信息，提示给用户的时候，就提示错误原因；
* `public String toString()`：详细信息，获取异常的类型和异常描述信息（一般不用）；
* `public void printStackTrace()`：最全面信息，打印异常的跟踪栈信息并输出到控制台。

## 多个异常处理

1. 多个异常分别处理；
2. 多个异常一次捕获，多次处理；
   * 一个`try`多个`catch`，`catch`里面定义的异常变量存在子父类关系，那么子类必须写在父类前面，否则会报错，因为子类的异常先被父类捕获。
3. 多个异常一次捕获，一次处理。

```java
package com_01.jianmo.Exception;

import java.util.List;

public class MultiExceptionTest {
	public static void main(String[] args) {
		MultiExceptionTest.test_01();  // 1.多个异常分别处理；
		MultiExceptionTest.test_02();  // 2.多个异常一次捕获，多次处理；
		MultiExceptionTest.test_03();  // 3.多个异常一次捕获，一次处理。
	}

	public static void test_01() {
		// 1.多个异常分别处理；
		try {
			int[] a = {1, 2, 3};
			System.out.println(a[3]);
		} catch (ArrayIndexOutOfBoundsException e) {
			System.out.println("ArrayIndexOutOfBoundsException:" + e.getMessage());
		}

		try {
			List<Integer> l = List.of(1, 2, 3);
			l.get(3);
		} catch (IndexOutOfBoundsException e) {
			System.out.println("IndexOutOfBoundsException:" + e.getMessage());
		}

	}

	public static void test_02() {
		// 2.多个异常一次捕获，多次处理；
		try {
			int[] a = {1, 2, 3};
			System.out.println(a[3]);

			List<Integer> l = List.of(1, 2, 3);
			l.get(3);
		} catch (ArrayIndexOutOfBoundsException e) {
			System.out.println("IndexOutOfBoundsException:" + e.getMessage());
		} catch (IndexOutOfBoundsException e) {
			System.out.println("ArrayIndexOutOfBoundsException:" + e.getMessage());
		}
	}

	public static void test_03() {
		// 3.多个异常一次捕获，一次处理。
		try {
			int[] a = {1, 2, 3};
			System.out.println(a[3]);

			List<Integer> l = List.of(1, 2, 3);
			l.get(3);
		} catch (IndexOutOfBoundsException e) {  // 或者写Exception
			System.out.println(e.toString());
		}
	}
}
```

## finally代码块

> 有一些特定的代码无论异常是否产生，都需要执行，另外因为`try`异常引起程序跳转，导致有些语句执行不到。finally一般用来释放`try`中的资源。`try...catch..finally`

### finally注意事项

1. `finally`不能单独使用，必须和`try`一起使用；
2. `finally`一般用于资源释放(资源回收)，无论程序是否出现异常，最后都需要释放资源；
3. 如果`finally`中有`return`语句，那么程序永远返回`finally`中的结果，因为`finally`是永远会执行的代码。

```java
package com_01.jianmo.Exception;

import java.util.Objects;

public class ExceptionTest {
	public static void main(String[] args) {
		try {
			ExceptionTest.notNull(null);
		} catch (NullPointerException e) {
			System.out.println("NullPointerException:" + e.getMessage());
		} finally {
            // 无论是否有异常都会执行该处代码
			System.out.println("释放资源");
		}
	}
	public static void notNull(Object obj) {
		// 判断obj非空：重载加异常描述
		Objects.requireNonNull(obj, "obj为空");
	}

}
```

## 异常注意事项

* 运行时异常被抛出可以不处理，即不捕获也不声明抛出；
* 如果`finally`中有`return`语句，那么程序永远返回`finally`中的结果，因为`finally`是永远会执行的代码；
* 父类异常时什么样，子类异常就是什么样。如果父类抛出了多个异常，子类重写父类方法时，抛出和父类相同的异常或者是父类异常的子类或者不抛出异常；
* 父类异常时什么样，子类异常就是什么样。父类方法没有抛出异常，子类重写父类该方法时也不可抛出异常，此时子类产生该异常，之能捕获处理，不能声明抛出；
* `try..catch`后面追加`finally`代码块，其中的代码一定会被执行，通常用于资源回收。

## 自定义异常类

> * 继承自`Exception`或`RuntimeException`类；
> * 需要包含两个构造方法：空参数构造方法和带异常信息的构造方法。

```java
package com_01.jianmo.Exception;

public class RegisterException extends Exception {
	public RegisterException() {
		super();
	}

	public RegisterException(String message) {
		super(message);  // 方法内部调用父类的异常信息构造方法，让父类来处理这个信息
	}
}
```

### 注意

1. 自定义异常类一般是以`Exception`结尾，说明该类是一个异常类；
2. 自定义异常类，必须继承自`Exception`或`RuntimeException`
   * 继承自`Exception`：那么自定义的异常类就是一个编译期异常，如果方法内部抛出了编译期异常，就必须处理这个异常，要么`throws`或者`try..catch`；
   * 继承自`RuntimeException`：那么自定义的异常类就是一个运行期异常，无序处理，交给虚拟机中断处理。

## 多线程

> `Java`程序属于抢占式调度，那个线程的优先级高，那个线程优先执行；同一个优先级，随机选择一个执行。

## 创建新线程

### 方式一

>  第一种方式：将类声明为`Thread`的子类，该子类应重写`Thread`类的`run`方法。接下来可以分配并启动该子类的实例，调用`start()`方法；
>
> 1. 创建一个Thread类的子类；
> 2. 在Thread类的子类中重写Thread类中run方法，设置线程任务；
> 3. 创建Thread类的子类对象；
> 4. 调用Thread类中的方法start方法，开启新的线程，执行run方法。
>
> 创建线程内存介绍，

#### Thread类

* **构造方法：**
  * `public Thread()`：分配一个新的线程对象；
  * `public Thread(String name)`：分配一个指定名字的新的线程对象；
  * `public Thread(Runnable target)`：分配一个带有指定目标新的线程对象；
  * `public Thread(Runable target, String name)`：分配带有指定目标新的线程对象并指定名字。
* **常用方法：**
  * `public void setName(String name)`：设置当前线程名称；
  * `public String getName()`：获取当前线程名称；
  * `public void start()`：开始执行该线程，`Java`虚拟机调用此线程的`run`方法；
  * `public void run()`：此线程要执行的任务在此处定义代码；
  * `public static void sleep(long mullis)`：使当前正在执行的线程以指定的毫秒数暂停（暂时停止执行）；
  * `publid static Tread currentThread()`：返回对当前正在执行的线程对象的引用。

### 方式二

>第二种方式：声明实现`Runable`接口的类，然后该类实现`run`方法。然后可以分配该类的实例，在创建`Thread`时作为一个参数来传递并启动。`Runnable`接口应该由那些打算通过某一线程执行其实例的类来实现。类必须定义一个称为`run`的无参数方法。
>
>1. 创建一个`Runnable`接口的实现类；
>2. 在实现类中重写`Runnable`接口的`run`方法，设置线程任务；
>3. 创建一个`Runnable`接口的实现类对象；
>4. 创建`Thread`类对象，构造方法中传递`Runnable`接口的实现类对象；
>5. 调用`Thread`类中的`static`方法，开启新的线程执行`run`方法。

#### Runnable接口

> 实现Runnable接口创建多线程程序的优点

1. 避免了单线程的局限性；
   * 一个类只能继承一个类，类继承了Thread类就不能继承其他的类，实现类Runnable接口，还可以继承其他的类，实现其他接口。
2. 增强了程序的扩展性，降低了程序的耦合性(解耦)；
   * 实现`Runnable`接口的方式，把设置线程任务和开启新线程进行了分离(解耦)
     * 在实现类中，重写了`run`方法：用来设置线程任务；
     * 当创建`Thread`类对象，调用`start`方法：用来开启新线程。

## 匿名内部类创建线程

> 使用线程内的匿名内部类方式，可以方便的实现每个线程执行不同的线程任务操作，使用匿名内部类的方式实现`Runnable`接口，重写`Runnable`接口中的run方法。
>
> * 匿名：没有名字；
> * 内部类：写在其他类内部的类；
> * 匿名内部类作用：简化代码
>   * 把子类继承父类，重写父类的方法，创建子类对象合一步完成。
>   * 把实现类实现类接口，重写接口中的方法，创建实现类对象合成一步完成。
> * 匿名内部类的最终产物：`子类/实现类`对象，而这个类没有名字。

```java
package com_02.jianmo.Thread;

public class ThreadTask03Test {
	public static void main(String[] args) {
		new Thread() {
			@Override
			public void run() {
				System.out.println(Thread.currentThread().getName());
			}
		}.start();

		Runnable r = new Runnable() {
			@Override
			public void run() {
				System.out.println(Thread.currentThread().getName());
			}
		};
		new Thread(r).start();


		new Thread(new Runnable() {
			@Override
			public void run() {
				System.out.println(Thread.currentThread().getName());
			}
		}).start();
	}
}
```

## 线程安全

> 单线程不会出现单线程问题，多线程访问共享资源才会出现。

### 线程安全问题解决思路

> 我们可以让一个线程在访问共享数据的时候，无论是否失去cpu的执行权限，让其他的线程都只能等待，等待当前线程访问完共享资源，保证多线程的共享资源在某一个时候只能有一个线程访问。

### 三种同步操作

1. 同步代码块；
2. 同步方法；
3. 锁机制。

### 第一种：同步代码块

1. 通过**代码块**中的锁对象，可以使用任意的对；
2. 但是必须保证多个线程使用的锁对象是同一个；
3. 锁对象作用：把代码块锁住，只让一个线程在同步代码块中执行。

```java
synchronized(锁对象) {
    // 可能会出现线程安全问题的代码
}
```

> 总结：同步中的线程，没有执行完毕不会释放锁，同步外的线程没有锁进不去同步代码块。

### 第二种：同步方法

1. 把访问共享资源的代码抽取出来，放到一个方法中；
2. 在**方法**上添加`synchronized`修饰符。

```java
public synchronized void method() {
    // 可能会产生线程安全问题的代码
}
```

### 第三汇总：Lock锁

> `java.util.concurrent.locks.Lock`机制提供了比`synchronized代码块`和`synchronized方法`更广泛的锁定操作，`同步代码块/同步方法`具有的功能Lock都有，除此之外更加强大，更体现面向对象。
>
> `Lock锁`也称为同步锁：
>
> * `public void lock()`：加同步锁；
> * `public void unlock()`：释放同步锁。
>
> 使用步骤：
>
> 1. 在成员位置创建一个`ReentrantLock`对象；
> 2. 在可能会出现安全问题的代码前调用`Lock()`接口中的方法`lock`获取锁；
> 3. 在可能会出现安全问题的代码后调用`Lock()`接口中的方法`unlock`获取锁；

## 线程状态

| 线程状态                | 导致状态发生条件                                             |
| ----------------------- | ------------------------------------------------------------ |
| NEW(新建)               | 线程刚被创建，但是并未启动，还没有调用`start`方法。          |
| Runnable(可运行)        | 线程可以在`Java`虚拟机中运行的状态，可能正在运行自己代码，也可能没有，这取决于操作系统处理器。 |
| Blocked(锁阻塞)         | 当一个线程试图获取一个对象锁，而该对象锁被其他的线程持有，则该线程进入`Blocked`状态；当该线程持有锁时，该线程将变成`Runnable`状态。 |
| Waiting(无限等待)       | 一个线程在等待另一个线程执行一个(唤醒)动作时，该线程进入`Waiting`状态。进入这个状态后是不能自动唤醒的，必须等待两一个线程调用`notify`或者`notifyALL`方法才能够唤醒。 |
| Timed_Waiting(计时等待) | 同`waiting`状态，有几个方法有超时参数，调用他们将进入`Timed Waiting`状态。这一状态将一直保持到超时期满或者接收到唤醒通知，带有超时参数的正常方法有`Thread.sleep`、`Object.wait`。 |
| Teminated(死亡状态)     | 因为`run`方法正常退出而死亡，或者因为没有捕获的异常终止了`run`方法而死亡。 |

###  等待与唤醒机制

> 只有锁对象才能调用`wait()`和`notify()/notifyAll()`方法。线程之间的通信，有效的利用资源，防止资源竞争。
>
> * `void wait()`：在其他线程调用此对象`notify()/notifyAll()`方法前，导致当前线程等待。此时该线程不再活动，不参与线程调度，进入`wait set`中，因此不会浪费`CPU`资源；
> * `void notify()`：唤醒在此对象监视器上等待的单个线程，会继续执行`wait`方法之后的代；
> * `void notifyAll()`：同`notify`，但是是唤醒所有在此监视器上等待的线程。
>
> **注意：**
>
> 哪怕只通知了一个等待的线程，被通知的线程也不会立即恢复执行，因为它当初中断的地方是在同步块内，而此刻它已经不持有锁，所以它需要再次尝试去获取锁(很可能其他面临其他线程的竞争)，成功后才能在当初调用wait方法之后的地方恢复执行。
>
> * 如果能获取锁，线程就从`WAITING`状态转化为`RUNNABLE`状态；
> * 否则，从`wait set`出来，又进入`entry set`，线程就从`WAITING`状态又变成了`BLOCKED`状态。

### wait和notify注意

1. `wait`方法与`notify`方法必须要由同一个锁对象调用，因为，对应的锁对象可以通过`notify`唤醒使用同一个锁对象调用的`wait`方法后的线程；
2. wait方法与notify方法是属于Object类的方法的，因为，锁对象可以是任意对象，而任意对象的所属类都是继承了Object类的；
3. `wait`方法与`notify`方法必须要**在同步代码块或者同步函数中使用**，因为，**必须要通过锁对象调用者两个方法**。

```java
package com_07.jianmo.LockObject;

public class LockObjectTest {
	public static void main(String[] args) {
		Object obj = new Object();


		// 消费者1
		new Thread() {
			@Override
			public void run() {
				while (true) {
					synchronized (obj) {
						System.out.println("消费者1等待包子。。。");
						try {
							obj.wait();
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
						System.out.println("消费者1等到了一个包子，消费者吃了一个包子");
					}
				}

			}
		}.start();

		// 消费者2
		new Thread() {
			@Override
			public void run() {
				while (true) {
					synchronized (obj) {
						System.out.println("消费者2等待包子。。。");
						try {
							obj.wait();
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
						System.out.println("消费者2等到了一个包子，消费者吃了一个包子");
					}
				}

			}
		}.start();

		// 生产者
		new Thread() {
			@Override
			public void run() {
				while (true) {
					try {
						Thread.sleep(2 * 1000);  // 做包子需要五秒
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					synchronized (obj) {
						// 一次唤醒一个顾客：
						// System.out.println("生产者花费2秒做了一个包子");
						// obj.notify(); // 一次唤醒一个顾客

						// 一次唤醒所有的顾客
						System.out.println("生产者花费2秒做了两个包子");
						obj.notifyAll();
					}
				}
			}
		}.start();

	}
}
```

大事发生的发顺丰