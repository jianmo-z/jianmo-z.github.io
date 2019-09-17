# shell编程

[TOC]

## 初识

* `set`：查看当前shell中所有的变量

## 变量

> 字母、数字和下划线组成，不能以数字开头
>
> **等号两侧 不能有空格**
>
> 变量名一般习惯为大写
>
> 双引号和单引号有区别，双引号仅将空格脱意，单引号将所有特殊字符脱意。

* 定义变量：`变量=值`
* 撤销变量：`unset 变量`
* 声明静态变量：`readonly 变量=值`

## 命令的返回值赋值给变量

1. ```bash
   RET=`ls -al` # 使用反引号，运行反引号里面的命令，结果返回给ret，等号两边不要加空格
   ```

2. ```bash
   RET=$(ls -al) # 等价于上面的方式
   ```

## 设置环境变量

1. `export 变量名=变量值`，设置环境变量
2. `source 配置文件`，让修改后的配置信息立即生效
3. `echo $变量名`，查询环境变量的值

## 位置参数变量

1. `$n`：`n`表示数字，`$0`表示命令本身，`$1-$9`代表第一个到第九个参数，十个以上的参数，需要用大括号括起来，例：`${10}`；
2. `$*`：代表命令行中所有的参数，`$*`把所有的参数看做一个整体；
3. `$@`：代表命令行中所有的参数，`$@`把每个参数区分对待；
4. `$#`：代表命令行中所有参数的个数。
5. `$$`：当前进程号
6. `$!`：后台运行的最后一个进程的进程号
7. `$?`：最后一次执行的命令的返回状态，如果为`0`表示成功执行，否则为失败。

### $\*和$@的区别

* 代码：

  ```bash
  #!/bin/bash
  
  # 注意区分$*和$@
  for i in  "$*"
      do
          echo "says:{$i}"
  done
  
  echo "==================="
  
  for i in  "$@"
      do
          echo "says:{$i}"
  done
  ```

* 运行结果：

  ```bash
  says:{asdf asdf aa}
  ===================
  says:{asdf}
  says:{asdf}
  says:{aa}
  ```

## 运算符

1. `$((运算式))`或者`$[运算式]`，乘法：`*`

2. `expr m + n`，注意：`expr`运算符间要有空格，乘法：`\*`

3. `expr m - n`，注意：`expr`运算符间要有空格，乘法：`\*`

4. `*， /， %`

   ```bash
    r=`expr 4 \* 2` && echo $r  # 很难用，建议不用
    a=$[10 - 1] && echo $a
    echo $((4 - 1))
   ```

## 条件判断

> `[ condition ]`，注意condition前后需要有空格
>
> 只要`[]`里面有内容就会返回true，否则`[]`而会返回false。

### 两个整数之间比较判断

1. `=`：字符串比较
2. `-lt`：小于，`less than`
3. `-le`：小于等于，`less than or -equal`
4. `-eq`：等于，`equal`
5. `-gt`：大于，`greater than`
6. `-ge`：大于等于，`greater than or equal`
7. `-ne`：不等于，`not equal`

### 文件权限判断

1. `-r`：有读权限
2. `-w`：有写权限
3. `-x`：有执行权限

### 文件类型判断

1. `-r`：文件存在并且是一个常规的文件
2. `-e`：文件存在
3. `-d`：文件存在并且是一个目录

## 流程控制

### if判断

1. ```bash
   if [ 条件判断式 ];then
   	程序
   fi
   ```

2. ```bash
   if [ 条件判断式 ]
     then
   	程序
   fi
   ```

   PS：`[ 条件判断式 ]`，**中括号和条件判断式之间必须有空格**

   ```bash
   #!/bin/bash
   
   if [ $1 -eq "123" ];then
       echo "is 123"
   elif [ $1 -eq "456" ];then
       echo "is 456"
   fi
   ```

### case语句

1. ```bash
   case $变量名 in
   	"值1")
   		# 如果变量值等于1，则执行程序1
   		;; # ;;作为一个语句的结束
   	"值2")
   		# 如果变量的值等于值2，则执行程序2
   		;; # ;;作为一个语句的结束
   	... 
   	*)
   		# 如果变量值都不是以上的值，则执行此程序
   		;; # ;;作为一个语句的结束
   esac # 逆序写case表示结束，同if-fi
   ```

2. 代码示例

   ```bash
   #!/bin/bash
   
   case $1 in
       "1")
           echo "is 1"
           ;;
       "2")
           echo "is 2"
           ;;
       "3")
           echo "is 3"
           ;;
       *)
           echo "is default"
           ;;
   esac
   ```

### for循环

1. 第一种

   ```bash
   for 变量 in 值1 值2 值3 ...
   	do
   		程序
   done
   ```

   代码：

   ```bash
   #!/bin/bash

   for i in  hello world pip
       do
           echo "says:{$i}"
   done
   ```

   运行结果：(注意$\*和$@的区别)

   ```bash
   says:{hello}
   says:{world}
   says:{pip}
   
   ```

2. 第二种

   ```bash
   for((初始值; 循环条件; 变量变化))
   	do
   		程序
   done
   ```

   代码：(计算1~100和)

   ```bash
   #!/bin/bash
   
   sum=0
   for((i=0;i <= 100; i++))
       do
           sum=$[$sum+$i]
   done
   
   echo "sum = $sum"
   ```

   运行结果：

   ```bash
   sum = 5050
   ```

### while循环

1. ```bash
   while [条件判断式]
   	do
   		程序
   done
   ```

2. 代码：(计算1~100的和)

   ```bash
   #!/bin/bash
   
   sum=0
   i=1
   while [ $i -ne 101 ]  # 注意左右空格
       do
           sum=$[ $sum + $i ]
           i=$[ $i + 1 ]
   done
   
   echo "sum = $sum"
   ```

3. 运行结果：

   ```bash
   sum = 5050
   ```

## read指令

> read读取控制台输入
>
> * `-p`：指定读取值时的提示符
> * `-t`：指定读取值时等待的时间(秒)

代码：(模拟goland的select)

```bash
#!/bin/bash

read -p "Please input username:" name
echo "Your name is {$name}"

read -p "Please input phone number(3S-timeout):" -t 3 phone
if [ $phone ];then
    echo "Your phone number is {$phone}"
else
    echo -e "\nTimeout!!!"
fi
```

运行结果1：(未超时)

```bash
Please input username:pip
Your name is {pip}
Please input phone number(3S-timeout):123456789
Your phone number is {123456789}
```

运行结果2：(超时)

```
Please input username:pip
Your name is {pip}
Please input phone number(3S-timeout):
Timeout!!!
```

## 函数

### 系统函数

1. basename基本用法

   1. `basename [pathname] [suffix]`

   2. `basename [string] [suffix]`，`basename`命令会删除所有的前缀包括后一个`/`字符，然后将字符串显示出来

      代码：

      ```bash
      #!/bin/bash
      
      name=$(basename $PWD)
      echo "current directory name is {$name}"
      ```

      运行结果：

      ```bash
      current directory name is {code}
      # echo $PWD
      # /home/pip/Desktop/Git/ainihu.github.io/blog/BigData/day01/code
      ```

   3. `dirname [pathname]`

   4. `dirname [string]`

      代码：

      ```bash
      #!/bin/bash
      
      name=$(dirname $PWD)
      echo "current dirname is {$name}"
      ```

      运行结果

      ```bash
      current dirname is {/home/pip/Desktop/Git/ainihu.github.io/blog/BigData/day01}
      # echo $PWD
      # /home/pip/Desktop/Git/ainihu.github.io/blog/BigData/day01/code
      ```

### 自定义函数

1. ```bash
   [ function ] funname[()]
   {
       Action;
       [return int;]
   }
   ```

2. 注意事项

   1. 必须在调用函数之前，先声明函数，`shell`脚本是逐行执行，不是像其他的语言一样先编译
   2. 函数返回值，只能通过`$?`系统变量获取，可以显示加`return`返回；如果不加，将最后一条命令运行结果作为返回值，`return`后面的数值取值范围`[0-255]`

3. 代码：(计算两个数之和)

   ```bash
   #!/bin/bash
   
   function sum()
   {
       s=0
       s=$[ $1 + $2 ]
       echo "sum is {$s}"
   }
   
   read -p "please input first num:" n1;  # ;表示一个命令结束，可以在一行写多个独立语句
   read -p "please input first num:" n2;
   
   sum n1 n2 # 调用函数并传参
   ```

   运行结果：

   ```bash
   please input first num:12
   please input first num:34
   sum is {46}
   ```

   



