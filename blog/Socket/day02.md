# day02

## 本章目标

* `TCP`客户/服务器模型 ---> `C/S`模型
* 回射客户/服务器，`echosrv.c ` `echocli.c`文件
* socket、bind、listen、accept、connect函数

## socket函数

> **man 2 socket 查看帮助**

* 包含头文件`<sys/socket.h>`

* 功能：创建一个套接字用于通信

* 原型：

  * `int socket(int domain, int type, int protocol);`

* 参数：

  * `domain` ：指通信协议族`(protocol family)`
  * `type` ：指定`socket`类型。
    * 流式套接字`SOCK_STREAM`；
    * 数据报套接字`SOCK_DGRAM`；
    * 原始套接字`SOCK_RAW`；
  * `protocol`：协议类型

* 返回值：

  >成功返回非负整数，它和文件描述符类似，我们把它称为套接字，简称套接字；
  >
  >失败返回`-1`。


## bind函数

* 包含头文件`<sys/socket.h>`

* 功能：绑定一个本地地址到套接字

* 原型

  * `ing bind(int sockfd, const struct sockaddr * addr, socklen_t addrlen);`

* 参数

  * `sockfd`：`sockfd`函数返回的套接字
  * `addr`：要绑定的地址
  * `addrlen`：地址长度

* 返回值：

  > 成功返回`0`	，失败返回`-1`。


## listen函数

> `man 2 listen`	`SOMAXCONN`	查看此宏，是第二个参数，表示队列的最大值

* 包含头文件`<sys/socket.h>`
* 功能：将套接字用于监听进入的连接
* 原型
  * `int listen(in sockfd, int backlog);`
* 参数
  * `sockfd`：`socket`函数返回的套接字
  * `backlog`：规定内核为此套接字排队的最大连接个数
  * 返回值：成功返回`0`，失败返回`-1`。


>主动套接字：主动发起连接，会调用`connect()`函数。
>
>被动套接字：用来接收连接的，会调用`accept()`函数。

* 一般来说，`listen`函数应该在调用`socket`和`bind`函数之后，调用函数`accept`之前调用
* 对于给定的监听套接口，内核要维护两个队列
  * 1.已由客户发出并到达服务器，服务器正在等待完成相应的TCP三路握手过程
  * 2.已完成连接的队列

## accept函数

* 包含头文件`<sys/socket.h>`
* 功能：从已完成连接队列返回第一个连接，如果已完成连接队列为空，则阻塞。
* 原型：
  * `int accept(int socket, struct sockaddr * addr, socklen_t * addrlen);`
* 参数
  * `sockfd`：服务器套接字
  * `addr`：将返回对等方的套接字地址
  * `addrlen`：返回对等方的套接字地址长度。**是一个输入输出的参数，所以一定要初始化。**
* 返回值：成功返回i非负整数，失败返回`-1`.

## connect函数

* 包含头文件`<sys/socket.h>`
* 功能：建立一个连接至`addr`所指定的套接字
* 原型
  * `int connect(int sockfd, const struct sockaddr * addr, socklen_t addrlen);`
* 参数
  * `sockfd`：未连接套接字
  * `addr`：要连接的套接字地址
  * `adrlen`：第二个参数`addr`长度
  * 返回值：成功返回`0`，失败返回`-1`。

