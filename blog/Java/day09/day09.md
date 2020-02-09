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

