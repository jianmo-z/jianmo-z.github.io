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

> `OutputStream`的实现类`ByteArrayOutputStream`、`FileOutputStream`、`FilterOutputStream`、`ObjectOutputStream`、`PipedOutputStream`

## FileOutputStream类

> `FileOutputStream`是`OutputStream`的文件流操作的实现类

### 构造方法



> **构造函数作用**：
>
> 1. 创建一个`FileOutputStream`对象；
> 2. 会根据构造方法中传递的`文件/文件路径`，创建一个空的文件；
> 3. 会把`FileOutputStream`对象指向创建好的文件。

* `public FileOutputStream(String name)`：创建一个具有指定名称的文件中写入数据的输出文件流；
* `public FileOutputStream(File file)`：创建一个指定`File`对象表示的文件中写入数据的文件输出流；
* `public FileOutputStream(String name, boolean append)`
* `public FileOutputStream(File file, boolean append)`
* `public FileOutputStream(FileDescriptor fdObj)`

### 写数据

> `java`写数据原理：
>
> ​	1、`java`程序  →  2、`JVM`(`java`虚拟机) → 3、`OS`(操作系统) → 4、`OS`调用写数据的方法 → 5、把数据写入到文件中
>
> * `public void close()`：关闭此输出流并释放与此流相关的任何系统资源；
> * `public void flush()`：刷新此输出流并强制任何换种的输出字节被写出；
> * `public void write(byte[] b)`：将`b.length`字节从指定的字节数组写入此输出流；
> * `public void write(byte[] b, int off, int len)`：从指定的字节数组写入`len`字节，从偏移量`off`开始输出到此输出流；
> * `public void write(int b)`：将指定的字节输出流，`b`为`ASCII`码值。

