# Makefile

## 参考链接

https://seisman.github.io/how-to-write-makefile/introduction.html

请先阅读：[从源代码到可执行文件](http://epi-cpp.top/#!./blog/C/6Linux%E7%94%9F%E6%88%90%E5%8F%AF%E6%89%A7%E8%A1%8C%E6%96%87%E4%BB%B6.md)

## 规则

```
target ... : prerequisities ...
	command
	...
	...
```

*   `target`:可以是一个`object file`(目标文件),也可以是一个执行文件,还可以是一个`label`(标签).
*   `prerequisites`:生成该`target`所依赖的文件或`target`
*   `command`:该`target`要执行的命令(任意的shell命令)

### 示例

```
edit : main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
    cc -o edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o

main.o : main.c defs.h
    cc -c main.c
kbd.o : kbd.c defs.h command.h
    cc -c kbd.c
command.o : command.c defs.h command.h
    cc -c command.c
display.o : display.c defs.h buffer.h
    cc -c display.c
insert.o : insert.c defs.h buffer.h
    cc -c insert.c
search.o : search.c defs.h buffer.h
    cc -c search.c
files.o : files.c defs.h buffer.h command.h
    cc -c files.c
utils.o : utils.c defs.h
    cc -c utils.c
clean :
    rm edit main.o kbd.o command.o display.o \
        insert.o search.o files.o utils.o
```

>   `\`表示换行符的意思
>
>   ​	目标文件`target`包含:执行文件edit和中间目标文件(`*.o`),依赖文件`(prerequisites)`,为冒号后面的`.c`和`.h`文件.每一个`.o`文件都有一组依赖文件,而`.o`文件又是`edit(最终的可执行程序)`的依赖文件
>
>   ​	确定好依赖关系后,后续的那一行定义了如何生成目标文件的操作命令,一定要以一个`Tab`键作为开头.make并不管命令是怎么工作的,它只管执行所定义的命令,`make`会比较`targets`文件和`prerequisites`文件的修改日期,如果`prerequisites`文件的日期要比`targets`文件的日期要新,或者	`targets`不存在的话,那么`make`就会执行后续定义的命令.
>
>   ​	`clean`不是一个文件,它是一个动作名字,`make clean`执行该动作.

## make 如何工作

1.  执行`make`命令
2.  在该目录下找到`Makefile`/`makefile`文件,上面的例子中会找到`edit`文件,并作为最终的目标文件
3.  如果`edit`文件不存在,或者`edit`所依赖的后面的`.o`文件的修改时间要比`edit`这个文件新,那么,它就会执行后面所定义的命令来生成`edit`这个文件
4.  如果`edit`所依赖的`.o`文件也不存在,那么`make`就会在当前文件中找目标`.o`文件的依赖性,如果找到则再根据那一个规则生成`.` 文件
5.  如果C文件和H文件是存在的,`make`就会生成`.`文件,然后再用`.o`,然后再用`.o`文件生成`make`的目标程序.

## makefile变量

*   变量的定义：`objects = main.o kdb.o`
*   变量的引用：`$(objects)`

## make自动推导

>   由`*.o`文件推导`*.c`文件

```
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

main.o : defs.h
kbd.o : defs.h command.h
command.o : defs.h command.h
display.o : defs.h buffer.h
insert.o : defs.h buffer.h
search.o : defs.h buffer.h
files.o : defs.h buffer.h command.h
utils.o : defs.h

.PHONY : clean
clean :
    rm edit $(objects)
```

*   `.PHONY`：表示后面的`clean`是一个伪目标文件
*   只要`make`看到一个`.o`文件，它就会自动的把`.c`文件加到依赖关系中，如果`make`找到一个`someone.o`文件，那么`someone.c`就会是`someone.o`目标文件的依赖文件，并且`cc -c someone.c`也会被推导出来．

>   　由`.o`文件推导`.h`文件

## 自动推导makefile

```
objects = main.o kbd.o command.o display.o \
    insert.o search.o files.o utils.o

edit : $(objects)
    cc -o edit $(objects)

$(objects) : defs.h
kbd.o command.o files.o : command.h
display.o insert.o search.o files.o : buffer.h

.PHONY : clean
clean :
    rm edit $(objects)
```

## 清空目标文件

```
.PHONY:clean
clean:
	-rm edit $(objects)
```

>   加`-`的意思是，如果某些文件出现问题不要管，继续做后面的事．且`clean`放在文件的最后．

## makefile

*   显式规则

    >   说明了如何生成一个或多个目标文件，这是`makefile`文件书写者明显指出要生成的文件，文件的依赖和生成的命令．

*   隐晦规则

    >   自动推到功能

*   变量定义

    >   定义一系列的变量，一般用作宏替换

*   文件指定

    >   在一个`makefile`引用另一个`makefile`，另一个定义一个多行的命令
    >
    >   引用其他的`makefile`，`include <filename>`，`filename`当前操作系统`shell`的文件模式(可以包含路径和通配符)，例`include foo.make a.mk b.mk`

*   注释

    >   使用`#`注释，可以使用反斜杠进行转义`\#`

## 文件搜索

>   `VPATH = src:../headers`，make在当前目录找不到的情况下，去到指定的目录`(src和../headers)`中找寻文件，用`:`隔开的两个路径中去找

### 指定文件到指定目录

>   ```
>   vpath %.c foo
>   vpath %   blish
>   vpath %.c bar   
>   ```
>
>   查找`.c`文件先去`ｆoo`目录，然后去`blish`，最后去`bar`目录

## 伪目标

>   `.PHONY: clean`，只要有这个声明就可以避免和文件重名的情况，

## 静态模式

### 规则

```
<targets ...> : <target-pattern> : <prereq-patterns ...>
    <commands>
    ...
```

>   *   `targets`：定义了一系列的目标文件，可以有通配符，是目标的一个集合
>   *   `target-pattern`：是指明了`targets`的模式，也就是目标集模式
>   *   `target-patterns`：是目标的依赖模式，它对`target-pattern`形成的模式再i进行一次模式再进行一次依赖目标的定义．

### 例子：

```
objects = foo.o bar.o

all: $(objects)

$(objects): %.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@
```

>   上面的例子表明我们的目标从`$object`，`%.o`表明要所有以`.o`结尾的目标，即为`foo.o bar.o`，也就是变量`$object`集合的模式，而依赖模式`%.c`则取模式`%.o`的`%`，也就是`for bar`，并为其加下`.c`的后缀，于是，我们的依赖目标就是`foo.c bar.c`．而命令中的`$<`和`$@`则是自动化变量，`$<`表示所有的依赖目标集(`foo.c bar.c`)，`$@`i表示目标集．
>
>   *   `$<`：表示所有的依赖目标集
>   *   `$@`：表示目标集合

## 显示命令

>   通常`make`会把其要执行的命令行在命令i执行前输出到屏幕上，当我们用`@`字符在命令行前，那么这个命令就不会被`make`显示出来

## 结语

>   我写的远没有原文多，所以想学习更多请点击[参考链接](https://seisman.github.io/how-to-write-makefile/overview.html)

