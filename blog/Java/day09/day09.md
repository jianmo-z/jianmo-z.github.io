# day09

## FIle类

> `java.io.File`类是文件和目录路径名的抽象表示，主要用于文件和目录的创建、查找和删除等操作。
>
> `file`：文件、`path`：路径、`directory`：目录。
>
### File类构造方法

- `public File(String pathname)`：通过给定的**路径名字符串**转化为抽象路径名来创建新的`File`实例；

  - `pathname`是以文件结尾、文件夹结尾、相对路径、绝对路径、路径可以存在也可以不存在。

- `public File(String parent, String child)`：从**父路径名字符串和子路径名字符串**创建新的`File`实例；

  - `String parent`：父路径；

  - `String child`：子路径。

    > 父路径和子路径，可以单独书写，使用起来非常灵活，父路径和子路径都可以变化。

- `public File(File parent, String child)`：从父抽象路径名和子路径名字符串创建新的`File`实例。

### File类作用

>
>* `File`类的方法：File类是一个与系统无关的类，任何的系统操作系统都可以使用这个类中的方法。
>  * **创建**文件/目录；
>  * **删除**文件/目录；
>  * **获取**文件/目录；
>  * **判断**文件/目录是否存在；
>  * 对**文件夹进行遍历**；
>  * 获取**文件的大小**。

### File类属性

>* File静态成员变量
>  * `static String pathSeparator`：与系统有关的路径分隔符，为了方便被表示为一个字符串；
>  * `static char pathSeparatorChar`：与系统有关的路径分隔符；
>  * `static String separator`：与系统有关的默认名称分隔符，为了方便，它被表示为一个字符串；
>  * `static char separatorChar`：与系统有关的默认名称分隔符。

## File常用方法

### 获取功能的方法

* `public String getAbsolutePath()`：返回此`File`的绝对路径名字符串；
* `public String getPath()`：将`File`转化为路径名字符串；
* `public String getName()`：返回由此`File`表示的文件或目录的名称；
* `public String length()`：返回由此`File`表示的文件的长度，文件夹是没有大小的，如果目录不存在`length`返回`0`。

```java
package com_01.jianmo.File;


import java.io.File;

public class FileGetTest {
	public static void main(String[] args) {
		File file = new File("..");
		// . (一个点)表示当前目录，
		// .. (两个点)表示上一级目录

		System.out.println("文件绝对路径：" + file.getAbsolutePath());
		System.out.println("文件构造路径：" + file.getPath());
		System.out.println("文件/目录名称：" + file.getName());
		System.out.println("文件长度：" + file.length() + "字节");
		System.out.println("打印抽象File类：" + file);  // file.toString => return this.getPath();
	}
}
```

### 判断功能的方法

* `public boolean exists()`：此`File`表示的文件或目录是否存在；
* `public boolean isDirectory()`：此`File`表示的是否为目录；
* `public boolean isFile()`：此`File`表示的是否为文件。

```java
package com_01.jianmo.File;

import java.io.File;

public class FileJudgeTest {
	public static void main(String[] args) {
		File file = new File("C:\\Users\\Pip\\Desktop");

		System.out.println("判断文件是否存在：" + file.exists());
		System.out.println("判断是否为目录：" + file.isDirectory());
		System.out.println("判断是否为文件：" + file.isFile());

	}
}
```

### 创建和删除功能的方法

* `public boolean createNewfile()`：当且仅当具有该名称的文件不存在时，创建一个新的空文件；
  * 此方法只能用来创建文件，不能创建文件夹；
  * 创建文件的路径必须存在，否则会抛出异常。
* `public boolean delete()`：删除由此`File`表示的文件或目录；
  * 文件删除成功，返回`true`；
  * 文件夹中有内容(文件或目录)，不会删除返回`false`。
* `public boolean mkdir()`：创建由此`File`表示的目录；
* `public boolean mkdirs()`：创建由此`File`表示的目录，包括任何必须但不存在的父目录。

```java
package com_01.jianmo.File;

import java.io.File;
import java.io.IOException;

public class FileCreateDeleteTest {
	public static void main(String[] args) {
		File file = new File("C:\\Users\\Pip\\Desktop\\test");

		try {
			System.out.println("创建新文件：" + file.createNewFile());
			System.out.println("删除文件：" + file.delete());
			System.out.println("创建由此File表示的目录：" + file.mkdir());
			System.out.println("创建由此File表示的目录递归创建：" + file.mkdirs());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

### File类遍历目录功能

* `public String[] list()`：返回一个`String`数组，表示该`File`目录中所有子文件或目录；
* `public File[] listFiles()`：返回一个`FIle`数组，表示该目录中所有的子文件或目录。

> 如果`list`和`listFiles`方法的目录不存在或者不是目录，那么就会抛出空指针异常。

```java
package com_01.jianmo.File;

import java.io.File;

public class FileListTest {
	public static void main(String[] args) {
		File file = new File("C:\\Users\\Pip\\Desktop");

		System.out.println("文件：");
		for(String it : file.list()) {
			System.out.println(it);  // 打印文件名或者目录名
		}
		System.out.println("文件：");
		for (File it:file.listFiles()) {
			System.out.println(it);  // 打印绝对路径
		}
	}
}
```

### 文件过滤器

> 在File类中有两个和`listFiles`重载的方法，方法的参数传递的就是过滤器。
>
> * `public String[] list(FilenameFilter filter)`
> * `public File[] listFiles(FileFilter filter)`
> * `public File[] listFiles(FilenameFilter filter)`
>
> 文件过滤器：下面两个文件过滤器接口都是没有实现类的，需要自己写实现类，重写`accept`方法，在方法中自己定义过滤的规则。
>
> * `java.io.FileFilter`接口：用于抽象路径名(File对象)的过滤器，用来过滤文件(File对象)。
>   * `boolean accept(File pathname)`，方法测试指定抽象路径是否包含在某个路径名列表中。
>     * `File pathname`：使用ListFiles方法遍历目录，得到的每一个文件对象
> * `java.io.FilenameFilter `接口：实现此接口的类实例可用于过滤器文件名，用于过滤文件名称。
>   * `boolean accept(File dir, String name)`
>     * `File dir`：构造方法中传递的被遍历的目录；
>     * `String name`：使用`ListFiles`方法遍历目录，获取的每一个`文件/目录`的名称。

#### FileFilterImpl

```java
package com_02.jianmo.FileFilter;

import java.io.File;
import java.io.FileFilter;

public class FileFilterImpl implements FileFilter {
	@Override
	public boolean accept(File file) {
		if (file.toString().endsWith("lnk"))
			return true;
		else return false;
	}
}
```

#### FileFilterTest

```java
package com_02.jianmo.FileFilter;

import java.io.File;

public class FileFilterTest {
	public static void main(String[] args) {
		File file = new File("C:\\Users\\Pip\\Desktop");
		PrintAllFile(file);
	}

	public static void PrintAllFile(File file) {
		File[] files = file.listFiles(new FileFilterImpl());
		for(File it : files) {
			if(it.isDirectory()) {
				PrintAllFile(it);
			} else {
				System.out.println(it);
			}
		}
	}
}
```

#### FileNameFilterImpl

```java
package com_03.jianmo.FileNameFilter;

import java.io.File;
import java.io.FilenameFilter;

public class FileNameFilterImpl implements FilenameFilter {
	@Override
	public boolean accept(File file, String s) {
		if (s.endsWith("lnk"))
			return true;
		else
			return false;
	}
}
```

#### FileNameFilterTest

```java
package com_03.jianmo.FileNameFilter;

import java.io.File;

public class FileNameFilterTest {
	public static void main(String[] args) {
		File file = new File("C:\\Users\\Pip\\Desktop");
		PrintAllFile(file);
	}
	public static void PrintAllFile(File file) {
		File[] files = file.listFiles(new FileNameFilterImpl());
		for(File it : files) {
			if(it.isDirectory()) {
				PrintAllFile(it);
			} else {
				System.out.println(it);
			}
		}
	}
}
```



## IO流

> `java`中的`I/O`操作主要是指`java.io`包下的内容，进行输入、输出操作。**输入**也叫**读取数据**，**输出**也叫**写出数据**。

### IO的分类

> 根据数据的流向分为：**输入流**和**输出流**。
>
> * 输入流：把数据从**其他设备**上**读**取到**内存**中的流；
> * 输出流：把数据从**内存**中**写**出到**其他设备**上的流。
>
> 根据数据的类型分为：**字节流**和**字符流**。

## 字节流

> 一切皆为字节，一切文本数据(文本、图片、视频等)在存储时，都是以二进制数字的形式保存，都一个一个的字节，那么传输时也是如此。所以，字节流可以传输任意文件数据。在操作流的时候，我们时刻需要明白，无论使用什么样的流对象，底层传输的始终为二进制数据。

### 字节输出流OutputStream

> `java.io.OutputStream`**抽象类**是表示字节输出流的所有类的超类，将指定的字节信息写出到目的地，它定义了自己输出流的基本共性功能方法。
>
> * `public void close()`：关闭此输出流并释放与此流相关联的任何系统资源；
> * `public void flush()`：刷新此输出流并强制任何缓冲的输出字节被写出；
> * `public void write(byte [] b)`：将`b.length`字节从指定的字节数组写入此输出流；
> * `public void write(byte [] b, int off, int len)`：从指定的字节数组写入`len`字节，从偏移量`off`开始输出到此输出流；
> * `public abstract void write(int b)`：将指定的字节输出流。
>
> 当完成流的操作时，必须调用此`close`方法，释放系统资源。

### OutputStream实现类

> `OutputStream`的实现类`ByteArrayOutputStream`、`FileOutputStream`、`FilterOutputStream`、`ObjectOutputStream`、`PipedOutputStream`。

### 字节输入流InputStream

> `java.io.InputStream`抽象类是表示自己输入流的所有类的超类，可以读取字节信息到内存中，它定义了自己输入流的基本共性功能方法。
>
> * `public void close()`：关闭输入流并释放与此流相关联的任何系统资源；
> * `public abstract int read)()`：从输入流读取数据的下一个字节；
> * `public int read(byte[] b)`：从输入流中读取一些字节数，并将它们存储到字节数组`b`中。
>
> 当完成流的操作时，必须调用此`close`方法，释放系统资源。

### InputStream实现类

> `InputStream`的实现类`BufferedInputStream`、`ByteArrayInputStream`、`DataInputStream`、`FilterInputStream`、`PushbackInputStream`。

## FileOutputStream类

> `FileOutputStream`是`OutputStream`的文件流操作的实现类

### 构造方法

> **构造函数作用**：
>
> 1. 创建一个`FileOutputStream`对象；
> 2. 会根据构造方法中传递的`文件/文件路径`，创建一个空的文件；
> 3. 会把`FileOutputStream`对象指向创建好的文件。

* `public FileOutputStream(String name)`：创建一个新的文件，创建一个具有指定名称的文件中写入数据的输出文件流；
* `public FileOutputStream(File file)`：创建一个新的文件，创建一个指定`File`对象表示的文件中写入数据的文件输出流；
* `public FileOutputStream(String name, boolean append)`：同上，不会创建新文件，只是给原文件中追加写数据；
* `public FileOutputStream(File file, boolean append)`：同上，不会创建新文件，只是给原文件中追加写数据；
* `public FileOutputStream(FileDescriptor fdObj)`

### 成员方法

> `java`写数据原理：
>
> ​	1、`java`程序  →  2、`JVM`(`java`虚拟机) → 3、`OS`(操作系统) → 4、`OS`调用写数据的方法 → 5、把数据写入到文件中
>
> * `public void close()`：关闭此输出流并释放与此流相关的任何系统资源；
> * `public void flush()`：刷新此输出流并强制任何换种的输出字节被写出；
> * `public void write(byte[] b)`：创建爱你将`b.length`字节从指定的字节数组写入此输出流；
> * `public void write(byte[] b, int off, int len)`：从指定的字节数组写入`len`字节，从偏移量`off`开始输出到此输出流；
> * `public void write(int b)`：将指定的字节输出流，`b`为`ASCII`码值。
>
> `write(byte[] b)`一次写多个字节数据的时候：
>
> * 如果写的第一个字节是正数`(0-127)`，那么显示的时候会查询`ASCII`表；
> * 如果写的第一个字节是负数，那么第一个字节和第二个字节，两个字节组成一个中文显示，查询系统默认编码`(GBK)`。

```java
package com_04.jianmo.OutputStream;

import java.io.FileOutputStream;
import java.io.IOException;

public class OutputStreamTest {
	public static void main(String[] args)  {
		try {
			byte[] bytes = {65, 70, 66, 69, 80};
			FileOutputStream stream = new FileOutputStream("C:\\Users\\Pip\\Desktop\\a.txt");
			stream.write(97);  // ASCII的字母a
			stream.write(bytes);  // 写入byte数组
			stream.write(bytes, 1, 2);  // 写入数组中指定的一部分数据
			stream.write("你好".getBytes());  // String转Bytes数组
			stream.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

## FileInputStream类

### 构造方法

> 构造方法的作用：
>
> 1. 会创建一个`FileInputStream`对象；
> 2. 会把`FileInputStream`对象指定构造方法中要读取的文件。

* `FileInputStream(File file)`：通过打开一个到实际文件的连接来创建一个`FileInputStream`，该文件通过文件系统中的`File`对象`file`指定；
* `FileInputStream(FileDescriptor fdObj)`：通过使用文件描述符fdObj创建一个FileInputStream，该文件描述符表示到文件系统中某个实际文件的现有连接；
* `FileInputStream(String name)`：通过打开一个到实际文件的连接来创建一个`FileInputStream`，该文件通过文件系统中的路径名`name`指定。

### 成员方法

> `java`读取数据原理：
>
> ​	1、`java`程序  →  2、`JVM`  →  3、`OS`  →  4、`OS`读取数据的方法  →  5、 读取文件
>
> * `public int read()`：从文件中读取一个字节，如果读取到文件末尾返回`-1`；
> * `public int read(byte[] b)`：从输入流中读取一定数量的字节，并将其存储在缓冲区数组`b`中
>   * `byte[] b`：缓冲区用来存储数据；
>   * `int`：返回值表示读取到了多少个字节的数据，返回-1表示读取到了文件末尾。

```java
package com_05.jianmo.InputStream;

import java.io.FileInputStream;
import java.io.IOException;

public class InputStreamTest {
	public static void main(String[] args) {
		readByte();
		readByteArray();
	}

	// 读取一个字节
	public static void readByte() {
		try {
			FileInputStream stream = new FileInputStream("C:\\Users\\Pip\\Desktop\\a.txt");
			int b = stream.read();
			System.out.println("读取一个字节数据：" + (char) b);
			stream.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	// 读取一个byte数组
	public static void readByteArray() {
		try {
			FileInputStream stream = new FileInputStream("C:\\Users\\Pip\\Desktop\\a.txt");
			byte[] b = new byte[1024];
			int size = stream.read(b);
			System.out.println("读取:" + size + "字节的数据");
			System.out.println(new String(b, 0, size));  // 转化有效长度为字符
			stream.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

## 字符流

> 当使用字节流读取文本文件时，可能会有一个小问题。就是遇到中文字符时，可能不会显示完整的字符，那是因为一个中文字符可能占多个字节存储。所以`java`提供一些字符流类，以字符为单位读写数据，专门用于处理文本文件。

### 字符输入流Reader

> `java.io.Reader`抽象类是表示用于读取字符流的所有类的超类，可以读取字符信息到内存中，它定义了字符输入流的基本共性功能方法。
>
> * `public void close()`：关闭此流并释放与此流相关联的任何系统资源；
> * `public int read()`：从输入流中读取一个字符；
> * `public int read(char[] cbuf)`：从输入流中读取一些字符，并将它们存储到字符数组`cbuf`中；
> * `public int read(byte[] b, int off, int len)`：`off`是对于`byte[] b`的偏移量写`len`个字符。

### Reader实现类

> `Reader`的实现类`BufferedReader`、`CharArrayReader`、`FilterReader`、`InputStreamReader`、`PipedReader`、`StringReader`。

### 字符输出流Writer

> `java.io.Writer`抽象类是用于写出字符流的所有类的超类，将指定的字符信息写出到目的地。它定义了字节输出流的基本共性功能方法。
>
> * `void write(int c)`：写入单个字符；
> * `void write(char[] cbuf)`：写入字符数组；
> * `abstract void write(char[] cbuf, int off, int len)`：写入字符数的一部分，`off`偏移量数组的开始索引，`len`写的字符个数；
> * `void write(String str)`：写入字符串；
> * `void write(String str, int off, int len)`：写入字符串的某一部分，`off`字符串偏移量的开始索引，`len`写的字符长度；
> * `void flush()`：刷新该流的缓冲；
> * `void close()`：关闭此流，调用前先刷新该流。

### Writer实现类

> `Writer`的实现类`BufferdWriter`、`CharArrayWriter`、`FilterWriter`、`OutputStreamWriter`、`PipeWriter`、`StringWriter`。

## FileReader类

> `java.io.FileReader`类是读取字符文件的便捷类，是`InputStreamReader`的子类。构造时使用系统默认的字符编码和默认字符缓冲区。
>
> **字符编码**：字节与字符的对应规则，`WIndows`系统默认的中文编码的`GBK`编码，`IDEA`是`UTF-8`。

### 构造方法

> 构造方法的作用：
>
> 1. 创建一个`FileReader`对象；
> 2. 会把`FileReader`对象指向要读取的文件。

* `public FileReader(String fileName)`
* `public FileReader(File file)`
* `public FileReader(FileDescriptor fd)`
* `public FileReader(String fileName, Charset charset)`
* `public FileReader(File file, Charset charset)`

### 成员方法

> * `public int read()`：读取一个字符，返回对应的`int`需要进行类型转化为`char`才可以打印出来；
> * `public int read(char[] cbuf, int offset, int length)`：在`char[] cbuf`的`offset`偏移量处写`length`个字符。

## FileWriter类

> `java.io.FileWriter`类是写字符文件的便捷类，是`OutputStreamWriter`的子类。构造时使用系统默认的字符编码和默认字符缓冲区。

### 构造方法

> 构造方法的作用：
>
> 1. 创建一个`FileWriter`对象；
> 2. 会根据构造方法中传递的文件/文件的路径，创建文件；
> 3. 会把`FileWriter`对象指向创建好的文件。

* `FileWriter(File file)`：根据给定的`File`对象构造一个`FileWriter`对象；
* `FileWriter(File file, boolean append)`：根据给定的`File`对象构造一个`FileWriter`对象。
* `FileWriter(FileDescriptor fd)`：构造与某个文件描述符相关联的`FileWriter`对象；
* `FileWriter(String fileName)`：根据给定的文件名构造一个`FileWriter`对象；
* `FileWriter(String fileName, boolean append)`：根据给定的文件名以及指示是否附加写入数据的`boolean`值来构造`FileWriter`对象。

### 成员方法

> - `void write(int c)`：写入单个字符；
> - `void write(char[] cbuf)`：写入字符数组；
> - `abstract void write(char[] cbuf, int off, int len)`：写入字符数的一部分，`off`偏移量数组的开始索引，`len`写的字符个数；
> - `void write(String str)`：写入字符串；
> - `void write(String str, int off, int len)`：写入字符串的某一部分，`off`字符串偏移量的开始索引，`len`写的字符长度；
> - `void flush()`：刷新该流的缓冲；
> - `void close()`：关闭此流，调用前先刷新该流。

```java
package com_07.jianmo.FileWriteer;

import java.io.FileWriter;
import java.io.IOException;

public class FileWriterTest {
	public static void main(String[] args) {
		try {
			FileWriter writer = new FileWriter("C:\\Users\\Pip\\Desktop\\a.txt");
			writer.write((int)'你');  // 写入一个字符
			writer.write(new char [] {'好', '啊', 'a', 'a', 'a'});
			writer.write(new String("hello world"));

			writer.flush();
			writer.close();  // 关闭也会调用flush刷新缓冲区
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

### 关闭和刷新

> 因为内置缓冲区的原因，如果不关闭输出流，无法写字符到文件中。但是关闭的流对象，是无法继续写出数据丶
>
> * `flush`：刷新缓冲区，流对象可以继续使用；
> * `close`：先刷新缓冲区，然后通知系统释放资源，且流对象不可以再被使用了。

## 文件IO异常处理

> 处理文件异常，以及关闭文件时出现的异常。`JDK1.7`新特性：在try的后边增加一个`()`，在括号中可以定义流对象，可以定义多个。那么这个流对象的作用域就在`try`中有效。`try`中的代码执行完毕后会自动释放掉，不需要写`finally`释放流对象了。

### JDK1.7之前处理异常

```java
package com_08.jianmo.FileIOException;

import java.io.FileWriter;
import java.io.IOException;

public class FileIOException {
	public static void main(String[] args) {
		FileWriter writer = null;  // 提升变量的作用域
		try {
			writer = new FileWriter("C:\\Users\\Pip\\Desktop\\a.txt");
			writer.write(new String("hello world"));

			writer.flush();
			writer.close();  // 关闭也会调用flush刷新缓冲区
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (writer != null)  // 检查是否为空，避免异常
					writer.close();  // 保证资源被释放
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
```

### JDK1.7处理异常

> `JDK1.7`**新特性**：在try的后边增加一个`()`，在括号中可以定义流对象，可以定义多个。那么这个流对象的作用域就在`try`中有效。`try`中的代码执行完毕后会自动释放掉，不需要写`finally`释放流对象了。

```java
package com_08.jianmo.FileIOException;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileIOExceptionNew {
	public static void main(String[] args) {

		// 自动释放资源
		try (FileReader reader = new FileReader("C:\\Users\\Pip\\Desktop\\a.txt");
		     FileWriter writer = new FileWriter("C:\\Users\\Pip\\Desktop\\b.txt")) {

			// 写文件
			writer.write(new String("hello world"));
			writer.flush();

			// 读文件
			char[] buf = new char[1024];
			int size = reader.read(buf);
			System.out.println("size:" + size);
			System.out.println(buf);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

### JDK1.9处理异常

> `JDK1.9`**新特性**，在`try`的前边定义流对象，在`try`后边的`()`中可以引入流对象的名称(变量名)。在`try`代码块执行完毕后，流对象也可以被释放掉，也不用写`finally`。需要把`new`可能产生的`IOException`异常抛出。

```java
package com_08.jianmo.FileIOException;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileIOException9 {
	public static void main(String[] args) throws IOException {
		// JDK1.9处理文件异常

		FileReader reader = new FileReader("C:\\Users\\Pip\\Desktop\\a.txt");
		FileWriter writer = new FileWriter("C:\\Users\\Pip\\Desktop\\b.txt");
		// 自动释放资源
		try (reader; writer) {
			// 写文件
			writer.write(new String("hello world"));
			writer.flush();

			// 读文件
			char[] buf = new char[1024];
			int size = reader.read(buf);
			System.out.println("size:" + size);
			System.out.println(buf);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

## 属性集

> `java.util.Properties`继承于`Hashtable`，来表示一个持久的属性集。它使用键值结构存储数据，每个键及其对应值都是一个字符串。该类也被许多`Java`类使用，比如获取系统属性时，`System.getProperties`方法就是返回一个`Properties`对象。`Properties`可保存在流中或从流中加载。`Properties`集合是一个唯一和IO流相结合的集合。
>
> 1. 可以使用`Properties`集合中的方法`store`，把集合中的临时数据，持久化写到硬盘中存储；
> 2. 可以使用`Properties`存储中的方法`load`，把硬盘中保存的文件`键值对`，读取到集合中使用。
>
> 属性列表中每一个键及其对应值都是一个字符串：`Properties`集合是一个双列集合，`key`和`value`默认都是字符串。
>
> 1. 存储键值对的文件中，键与值默认的连接符号可以使用`=`等号和` `空格(其他符号)；
> 2. 存储键值对的文件中，可以使用`#`进行注释，被注释的键值对不会再被读取；
> 3. 存储键值对的文件中，键与值默认都是字符串，不用再加引号。
>
> 

### 成员方法

* `Object setProperty(String key, String value)`：调用`Hashtable`的方法`put`；
* `String getProperty(String key)`：用指定的键在此属性列表中搜索属性；
* `Set<String> stringPropertyNames()`：返回此属性列表中的键集，其中该键及其对应值是字符串，如果在主属性列表中为找到同名的键，则还包括默认属性列表中不同的键。此方法相当于`Map`集合中的`keySet`方法；
* `void store(OutputStream out, String comments)`：字节输出流，**不能写入中文**，`comments`注释，用来解释说明保存的文件是做什么的，注释不能使用中文，会产生乱码，注释是`Unicode`编码，一般使用`“”`空字符串；
* `void store(Writer writer, String comments)`：字符输出流，**可以写中文**，`comments`注释，用来解释说明保存的文件是做什么的，注释不能使用中文，会产生乱码，注释是`Unicode`编码，一般使用`“”`空字符串；
* `void load(InputStream inStream)`：从字节输入流中读取属性列表(`key`和`value`)，`InputStream`不能读取含有中文的键值对；
* `void load(Reader reader)`：按照简单的面向行的格式从输入字符流中读取属性列表(`key`和`value`)，`Reader`可以读取含有中文的键值对；