# day10

## 缓冲流

> 缓冲流，也叫高效流，是对四个基本的`FileXXX`流的增强，所以也是四个流，按照数据类型分类：
>
> * 字节缓冲流：`BUfferedInputStream`、`BufferedOutputStream`；
> * 字符缓冲流：`BufferedReader`、`BufferedWriter`。
>
> 缓冲流的基本原则，是在创建流对象时，会创建一个内置的默认大小的缓冲区数组，通过缓冲区读写，减少`IO`次数，从而提高读写的效率。

## BufferedOutputStream字节缓冲流

### 构造方法

* `public BufferedOutputStream(OutputStream out)`：创建一个新的缓冲输出流，以将数组写入指定的底层输出流；
* `public BufferedOutputStream(OutputStream out, int size)`：创建一个新的缓冲输出流，以将具有指定缓冲区大小的数据写入指定的底层从输出流，`int size`指定缓冲区流内部缓冲区的大小，不指定使用默认大小。

### 成员方法

* `public void close()`：关闭此输出流并释放与此流相关联的任何系统资源；
* `public void flush()`：刷新此输出流并强制任何缓冲的输出字节被写出；
* `public void write(byte[] b)`：将`b.length`字节从指定的字节数组写入此输出流；
* `public void write(byte[] b, int off, int len)`：从指定的字节数组写入`len`字节，从偏移量`off`开始输出到此输出流；
* `public abstract void write(int b)`：将指定的字节输出流。

```java
package com_01.jianmo.BufferedOutputStream;

import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class BufferedOutputStreamTest {
	public static void main(String[] args) {
		try (FileOutputStream fos = new FileOutputStream("C:\\Users\\Pip\\Desktop\\a.txt");
		     // BufferedOutputStream bis = new BufferedOutputStream(fos)
		     BufferedOutputStream bis = new BufferedOutputStream(fos, 1024)
		) {
			bis.write(98);  // 数据写到了内存缓冲区中
			bis.flush();  // 把内存缓冲区中的数据写到文件中
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

## BufferedInputStream字节缓冲流

### 构造方法

* `BufferedInputStream(InputStream in)`：创建一个`BufferedInputStream`并保存其参数，即输入流`in`，以便将来使用；
* `BufferedInputStream(InputStream in, int size)`：创建一个具有指定缓冲区大小的`BufferedInputStream`并保存其参数，即输入流`in`，`int size`指定缓冲区流内部缓冲区的大小，不指定则使用默认大小。

### 成员方法

* `public int read()`：从输入流中读取数据的下一个字节；
* `public int read(byte[] b)`：从输入流中读取一定数量的字节，并将其存储在缓冲区数组`b`中；
* `public void close()`：关闭此输入流并释放与该流关联的所有系统资源。

```java
package com_02.jianmo.BufferedInputStream;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;

public class BufferedInputStreamTest {
	public static void main(String[] args) {
		try (FileInputStream fis = new FileInputStream("C:\\Users\\Pip\\Desktop\\a.txt");
		     // BufferedInputStream bis = new BufferedInputStream(fis)
		     BufferedInputStream bis = new BufferedInputStream(fis, 1024)
		) {
			int c = bis.read();
			System.out.println((char) c);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

## BufferedWriter字符缓冲流

### 构造方法

* `public BufferedWriter(Writer out)`：创建一个新的缓冲输出流，使用默认缓冲区大小；
* `public BufferedWriter(Writer out, int size)`：创建一个使用给定大小输出缓冲区的新缓冲字符输出流。

### 成员方法

* `public void write(int c)`：写入单个字符；
* `public void write(char[] cbuf)`：写入字符数组；
* `public abstract void write(char[] cbuf, int off, int len)`：写入字符数的一部分，`off`偏移量数组的开始索引，`len`写的字符个数；
* `public void write(String str)`：写入字符串；
* `public void write(String str, int off, int len)`：写入字符串的某一部分，`off`字符串偏移量的开始索引，`len`写的字符长度；
* `public void flush()`：刷新该流的缓冲；
* `public void close()`：关闭此流，调用前先刷新该流；
* `public void newLine()`：写入一个行分隔符，会根据不同的操作系统获取不同的行分隔符。

```java
package com_03.jianmo.BufferedWriter;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class BufferedWriterTest {
	public static void main(String[] args) {
		try (
				FileWriter writer = new FileWriter("C:\\Users\\Pip\\Desktop\\a.txt");
				// BufferedWriter bWriter = new BufferedWriter(writer)
				BufferedWriter bWriter = new BufferedWriter(writer, 1024)
		) {
			bWriter.write("你好，世界");
			bWriter.flush();
			bWriter.newLine();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

## BufferedReader字符缓冲流

### 构造方法

* `public BufferedReader(Reader in)`：创建一个新的缓冲输入流；
* `public BufferedReader(Reader in, int size)`：创建一个使用给定大小输入缓冲区的新缓冲字符输入流。

### 成员方法

* `public int read()`：读取一个字符，返回对应的`int`需要进行类型转化为`char`才可以打印出来；
* `public int read(char[] cbuf, int offset, int length)`：在`char[] cbuf`的`offset`偏移量处写`length`个字符。
* `public void close()`：关闭输入流对象，释放资源。
* `public String readLine()`：读取一行数据，不包含任何终止符(`\n`、`\r`、`\r\n`)如果已达到末尾，则返回`null`。

```java
package com_04.jianmo.BufferedReader;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class BufferedReaderTest {
	public static void main(String[] args) {
		try (
				FileReader reader = new FileReader("C:\\Users\\Pip\\Desktop\\a.txt");
				// BufferedReader bReader = new BufferedReader(reader);
				BufferedReader bReader = new BufferedReader(reader, 1024);
		) {
			String line = bReader.readLine();
			System.out.println(line);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

## 转换流

* 转换流`InputStreamReader`，读取字节然后解码为字符；
* 转换流`OutputStreamWriter`，读取字符然后编码为字节。

### 常见字符集

* `ASCII`字符集
  * `ASCII`编码
* `GBK`字符集
  * `GBK`编码
* `Unicode`字符集：包含所有的语言的字符，是业界的一种标准，也称为统一码，标准万国码。
  * `UTF8`编码
  * `UTF16`编码
  * `UTF32`编码

## OutputStreamWriter类

> 转换流`java.io.OutputStreamWriter`，是`Writer`的子类，是从**字符流到字节流的桥梁**。使用指定的字符集将字符编码为字节。它的字符集可以由名称指定，也可以接受平台的默认字符集。编码的过程。

### 构造方法

* `OutputStreamWriter(OutpuStream out)`：创建一个使用默认字符集的字符流；
* `OutputStreamWriter(OutputStream out, Charset cs)`：创建一个指定字符集的字符流；
* `OutputStreamWriter(OutputStream out, CharsetEncode enc)`：创建使用给定字符集编码的`OutputStreamWriter`；
* `OutputStreamWriter(OutputStream out, String charsetName)`：创建使用指定字符集的`OutputStreamWriter`，例：`utf-8/UTF-8`、`gbk/GBK`、`… …`，不指定使用`UTF-8`。

### 成员方法

- `void write(int c)`：写入单个字符；
- `void write(char[] cbuf)`：写入字符数组；
- `abstract void write(char[] cbuf, int off, int len)`：写入字符数的一部分，`off`偏移量数组的开始索引，`len`写的字符个数；
- `void write(String str)`：写入字符串；
- `void write(String str, int off, int len)`：写入字符串的某一部分，`off`字符串偏移量的开始索引，`len`写的字符长度；
- `void flush()`：刷新该流的缓冲；
- `void close()`：关闭此流，调用前先刷新该流；
- `String getEncoding()`：获取此流使用的字符编码的名称。

```java
package com_05.jianmo.OutputStreamWriter;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;

public class OutputStreamWriterTest {
	public static void main(String[] args) {

		try (
				FileOutputStream oStream = new FileOutputStream("C:\\Users\\Pip\\Desktop\\a.txt");
				// OutputStreamWriter osw = new OutputStreamWriter(oStream)
				OutputStreamWriter osw = new OutputStreamWriter(oStream, "utf-8")
		) {
			System.out.println("encoding：" + osw.getEncoding());
			osw.write("你好");
			osw.flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

## InputStreamReader类

> 转换流`java.io.InputStreamReader`，是`Reader`的子类，是从**字节流到字符流的桥梁**，它读取字节，并使用指定的字符集将其解码为字符。它的字符集可以由名称指定，也可以接受平台的默认字符集。解码的过程。

### 构造方法

* `InputStreamReader(InpuStream in)`：创建一个使用默认字符集的字符流；
* `InputStreamReader(InputStream in, String charsetName)`：创建一个指定字符集的字符流。

### 成员方法

- `public void close()`：关闭此流并释放与此流相关联的任何系统资源；
- `public int read()`：从输入流中读取一个字符；
- `public int read(char[] cbuf)`：从输入流中读取一些字符，并将它们存储到字符数组`cbuf`中；
- `public int read(byte[] b, int off, int len)`：`off`是对于`byte[] b`的偏移量写`len`个字符。

```java
package com_06.jianmo.InputStreamReader;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class InputStreamReaderTest {

	public static void main(String[] args) {
		try (
				FileInputStream iStream = new FileInputStream("C:\\Users\\Pip\\Desktop\\a.txt");
				// InputStreamReader isr = new InputStreamReader(iStream)
				InputStreamReader isr = new InputStreamReader(iStream, "utf-8")
		) {
			char [] cBuf = new char[1024];
			isr.read(cBuf);
			System.out.println(cBuf);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

## 序列化

> `Java`提供了一种**对象序列化**的机制：用一个字节序列可以表示一个对象，该字节序列包含该`对象的数据`、`对象的类型`和`对象中存储的属性`等信息。字节序列写出到文件后，相当于文件中**持久保持**了一个对象的信息。反之，该字节序列还可以从文本中读取回来，重构对象，对它进行反序列化，`对象的数据`、`对象的类型`和`对象中存储的数据`等信息，都可以用来在内存中创建对象。**一个文件只能保存一个对象的序列化**，想要在一个文件中保存多个对象就把多个对象添加到集合中，再对集合进行序列化。
>
> **序列化/反序列化注意事项**：
>
> * `static`关键字：静态优先于非静态加载到内存中`(静态优先于对象进入到内存中)`，**被`static`修饰的成员变量不能被序列化**，序列化的都是对象，`static`修饰的属于类成员变量；
>
> * 被`transient`修饰的成员变量，不能被序列化；
>
> * 当`JVM`反序列对象时，能找到`class`文件，但是`class`文件再序列化对象之后**发生了修改**，那么反序列化操作会失败，抛出一个`InvaildClassException`异常。
>
>   * 该类的序列版本号与从流中读取的类描述符的**版本号不匹配**；
>
>     > **解决方案**：无论是否对类的定义进行修改，都不重新生成新的序列号，可以手动给类添加一个序列号。格式在`Serializable`接口中规定：可序列化类可以通过声明`serialVersionUID`的字段(该字段必须是`static、final`的`long`类型字段)，显示声明自己的`serialVersionUID`序列号。
>
>   * 该类包含未知数据类型；
>
>   * 该类没有可访问的无参构造方法。
>
>   

## ObjectOutputStream类

> 对象序列化流，`java.io.ObjectOutputStream`类继承自`OutputStream`，将`java`对象的原始数据类型写出到文件，实现对象的持久存储。

### 构造方法

* `public ObjectOutputStream(OutputStream out)`：创建一个指定`OutputStream`的`ObjectOutputStream`。

### 成员方法

> 具有`OutputStream`类的共性方法。

* `void writeObject(Object obj)`：将指定的对象写入`ObjectOutputStream`。

### 序列化操作

> 一个对象想要序列化，必须满足以下两个条件：
>
> 1. 该类必须实现`java.io.Serializable`接口，`Serializable`是一个标记接口，不实现此接口的类将不会使任何序列化或反序列化抛出`NotSerializableException`异常；
> 2. 该类的所有属性必须是可序列化的，如果有一个属性不需要可序列化，则该属性必须注明是瞬态的，使用`transient`关键字修饰，如文件描述符，网络套接字等资源。

### 测试代码

```java
package com_07.jianmo.ObjectOutputStream;

import com_00.jianmo.CommonClass.Person;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

public class ObjectOutputStreamTest {
	public static void main(String[] args) {
		try(ObjectOutputStream objectOS = new ObjectOutputStream(new FileOutputStream("C:\\Users\\Pip\\Desktop\\a.txt"))) {
			Person p = new Person("张三", 18);
			// 序列化对象，写对象
			objectOS.writeObject(p);
			objectOS.flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

### Person类

```java
package com_00.jianmo.CommonClass;

import java.io.Serializable;

public class Person implements Serializable {
	public String name;
	public int age;

	public Person() {
	}

	public Person(String name, int age) {
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

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}
}
```

## ObjectInputStream类

> 对象反序列化流，`java.io.ObjectInputStream`类继承自`InputStream`类，把文件中保存的对昂，以流的方式读取出来。

### 构造方法

* `ObjectInputStream(InputStream in)`：创建从指定`InputStream`读取`ObjectInputStream`。

### 成员方法

> 具有`InputStream`类的共性方法。
>
> - `Object readObject()`：从`ObjectInpuStream`读取对象。

### 反序列化操作

> 对象的需要反序列化，必须满足以下两个条件：
>
> 1. 类必须实现`java.io.Serializable`接口，`Serializable`接口是标记性接口；
> 2. 必须存在类对应的`class`文件。

### 测试代码

```java
package com_08.jianmo.ObjectInpuStream;

import com_00.jianmo.CommonClass.Person;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

public class ObjectInputStreamTest {
	public static void main(String[] args) {
		try(final ObjectInputStream objectIS = new ObjectInputStream(new FileInputStream("C:\\Users\\Pip\\Desktop\\a.txt"))) {
			Object o = objectIS.readObject();
			if(o instanceof Person) {
				Person p = (Person)o;
				System.out.println(p);
			}
		} catch (IOException | ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
}
```

### Person类

```java
package com_00.jianmo.CommonClass;

import java.io.Serializable;

public class Person implements Serializable {
	public String name;
	public int age;

	public Person() {
	}

	public Person(String name, int age) {
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

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}
}
```

## 打印流

> 平时我们在控制台打印输出，是调用`print`方法的`println`方法完成的，这两个方法都来自于`java.io.PrintStream`类，该类能够方便的打印各种数据类型的值，是一种便捷的输出方式。

## PrintStream类

> `PrintStream`继承自`OutputStream`，是一个字节流类。

### 构造方法

* `public PrintStream(File file)`：创建具有指定文件不带自动刷新的新打印流；
* `public PrintStream(File file, String csn)`：创建具有指定文件名和字符集且不带自动行刷新的新打印流；
* `public PrintStream(OutputStream out)`：创建新的打印流；
* `public PrintStream(OutputStream out, boolean autoFlush)`：创建新的打印流，并且是否自动刷新缓冲区；
* `public PrintStream(OutputStream out, boolean autoFlush, String encoding)`：创建新的打印流，并且是否自动刷新缓冲区，设置编码字符集；
* `public PrintStream(String fileName)`：使用指定的文件名创建一个新的打印流；
* `public PrintStream(String filename, String csn)`：创建具有指定文件名称和字符集且不带自动行刷新的新打印流。

### 成员方法

> 具有继承自父类`OutputStream`的成员方法。
>
> * `void print(任意类型的值)`；
> * `void println(任意类型的值)`。
>
> **注意：**
>
> ​	如果使用继承自父类的write方法写数据，那么查看数据的时候会查询编码表`(97→a)`，如果使用自己特有的方法`print/println`方法写数据，写的数据原样输出`(97→97)`。

```java
package com_09.jianmo.PrintStream;

import java.io.File;
import java.io.IOException;
import java.io.PrintStream;

public class PrintStreamTest {
	public static void main(String[] args) {
		try(PrintStream pStream = new PrintStream(new File("C:\\Users\\Pip\\Desktop\\a.txt"))) {
			pStream.println("你好啊");
		}catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

### 改变标准打印流向

> `System.out`就是`PrintStream`类型的，只不过它的流向是系统规定的，打印在控制台。既然是流对象，那么就可以改变它的流向，**通过`System`类的`setOut`方法改变输出流向**。 
>
> 打印流的特定：
>
> 1. 只负责数据的输出，不负责数据的读取；
> 2. 与其他输出流不同，`PrintStream`永远不会跑出`IOException`；
> 3. 有特有的方法，`print`、`println`等方法。
>    * `void print(任意类型的值)`
>    * `void println(任意类型的值并换行)`

```java
package com_09.jianmo.PrintStream;

import java.io.File;
import java.io.IOException;
import java.io.PrintStream;

public class ChangeStdoutStreamTest {
	public static void main(String[] args) {
		try(PrintStream pStream = new PrintStream(new File("C:\\Users\\Pip\\Desktop\\a.txt"))) {
			System.setOut(pStream);  // 改变标准输出的流向
			System.out.println("你好啊，哈哈哈");
		} catch(IOException e) {
			e.printStackTrace();
		}
	}
}
```

