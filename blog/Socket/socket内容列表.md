# socket详细列表信息

## day01
>[Socket_day01](day01.md)<a href="./Download/day01.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述：
>  * 什么是`socket`?
>  * IPv4套接口地址结构
>  * 网络字节序
>  * 地址转换函数
>  * 套接字类型


## day02
>[Socket_day02](day02.md)<a href="./Download/day02.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  - `TCP`客户/服务器模型 ---> `C/S`模型
>  - 回射客户/服务器，`echosrv.c` `echocli.c`文件
>  - `socket`、`bind`、`listen`、`accept`、`connect`函数

## day03

>[Socket_day03](day03.md)<a href="./Download/day03.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  - `REUSEADDR`，地址重复利用
>  - 处理多客户端连接(`process-per-conection`)
>  - 点对点聊天程序实现

## day04
>[Socket_day04](day04.md)<a href="./Download/day04.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  - 流协议与粘包：**`TCP`是字节流协议会导致粘包问题的出现**
>  - 粘包产生的原因
>  - 粘包处理方案
>  - `readn`、`writen`
>  - 回射客户/服务器

## day05
>[Socket_day05](day05.md)<a href="./Download/day05.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  - `read`、`write`与`recv`、`send`
>  - `readline`实现
>  - 用`readline`实现回射客户端/服务器
>  - `getsockname`、`getpeername`
>  - `gethostname`、`gethostbyname`、`gethostbyadr`

## day06
>[Socket_day06](day06.md)<a href="./Download/day06.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  - `TCP`回射客户/服务器
>  - `TCP`是个流协议
>  - 僵尸进程与`SIGCHLD`信号

## day07
>[Socket_day07](day07.md)<a href="./Download/day07.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>
>  * `ACK`、`SYN`和`FIN`
>
>    * `TCP` 11种状态
>
>    * `SIGPIPE`信号

## day08
>[Socket_day08](day08.md)<a href="./Download/day08.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  * 五种`I/O`模型
>  * 1、阻塞`I/O`模型
>  * 2、非阻塞`I/O`模型
>  * 3、`I/O`复用
>  * 4、信号驱动`I/O`
>  * 5、异步`I/O`
>  * `select`模型 --->重点

## day09
>[Socket_day09](day09.md)<a href="./Download/day09.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  * `select`
>  * 读、写、异常事件发生条件
>  * 并发服务器

## day10
>[Socket_day10](day10.md)<a href="./Download/day10.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>
>  *     本章目标
>  *     `close`和`shutdown`
>  *     `shutdown`


## day11
>[Socket_day11](day11.md)<a href="./Download/day11.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  *     套接字`I/O`超时设置方法
>  *     用`select`实现超时
>  *     `errno.h`头文件
>  *     `getsockopt`函数
>  *     一个函数`fcntl`
>  *     `read_timeout`函数封装
>  *     剩下三个函数的封装

## day12

>[Socket_day12](day12.md)<a href="./Download/day12.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  * `select`限制
>  * 这里是一条插播的关于`vim`内容
>  * `getrlimit`和`setrlimit`
>  * `getrlimit`和`setrlimit`函数使用代码
>  * 测试一个进程可以打开的最大文件文件描述符
>  * `poll`函数
>  * `struct pollfd`的`events`附录

## day13

>[Socket_day13](day13.md)<a href="./Download/day13.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  * 复习`select`和`poll`
>  * `epoll`相关函数
>  * `epoll`实现并发服务器--->优
>  * `epoll`、`select`和`poll`的区别
>  * `epoll LT/ET`模式
>  * `EPOLLLT`模式
>  * `EPOLLET`模式

## day14

>[Socket_day14](day14.md)<a href="./Download/day14.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  * `UDP`特点
>  * `UDP`注意点
>  * `echosrv.c`
>  * `echocli.c`

## day15

> 这里本应该有一个用UDP实现的聊天室，但是emmm 没写，但是后期会补上的，敬请期待。

## day16

>[Socket_day16](day16.md)<a href="./Download/day16.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  * `UNIX`域协议特点
>  * `UNIX`域地址结构
>  * `UNIX`域字节流回射客户/服务
>  * `UNIX`套接字编程注意点

## day17

>[Socket_day17](day17.md)<a href="./Download/day17.tar.gz"><font color="red"> 点击下载源文件</font></a>
>
>* 内容简述
>  * `socketpair`
>  * `sendmsg`和`recvmsg`
>  * 插播一个`vim`
>  * `sendmsg`和`recvmsg`应用代码
>  * 测试代码

