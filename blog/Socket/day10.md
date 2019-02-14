# day10

## 本章目标

* `close`和`shutdown`的区别
* 进一步改进回射客户端程序

## close和shutdown

* `close`终止了数据传送的两个方向

* `shutdown`可以有选择的终止某个方向的数据传送或者终止数据传送的两个方向

* `shutdown how=1`就可以保证对等方接收到一个`EOF`字符，而不管其他进程是否已经打开了套接字，即不关心引用计数。而`close`不能保证一定给对等方发送`EOF`，而是直到套接字引用计数减为`0`时才发送，也就是说直到所有的进程都关闭了套接字。才是真的关闭了套接字。

  >`FIN`：是用来扫描保留的端口，发送一个FIN包（或者是任何没有`ACK`或`SYN`标记的包）到目标的一个开放的端口，然后等待回应。许多系统会返回一个复位标记。

> 当客户端(或者服务器)发送消息后，另一端没有读取消息，消息还在管道中，但是客户端(或者服务器)使用`close`关闭了套接字，那么另一端就不能把未读取的数据读取出来。所以需要`shutdown`，终止某个方向的数据传送。

关于`shutdown`和`close`参考文档：https://blog.csdn.net/lgp88/article/details/7176509

## shutdown

> `man 2 shutdown`查看帮助，这个是一个函数，和`linux`命令一样但是... ...，这俩不一样
>
> **假设客户端使用了`close(fd)`，那么客户端的其他进程如果也使用了这个套接字(即：引用计数 > 1)，则只是引用计数减一操作，其他的进程仍然可以通过这个套接字与服务器进行通信。**
>
> **假设客户端如果使用了`shutdown(fd, SHUT_RD)`，则直接关闭读端(不管引用计数为多少)，其他进程则不能通过读端再进行数据的读取了，同理可得`SHUT_WR`：关闭写端，`SHUT_RDWR`：读端和写端都关闭。**

```
#include <sys/socket.h>

int shutdown(int sockfd, int how);

DESCRIPTION
	The  shutdown() call causes all or part of a full-duplex connection on the socket associated with sockfd to be shut down. If how is SHUT_RD, further receptions will be disallowed.  If how is SHUT_WR, further transmissions will  be  disallowed. If how is SHUT_RDWR, further receptions and transmissions will be disallowed.

RETURN VALUE
	On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

ERRORS
	EBADF  
		sockfd is not a valid descriptor.
	EINVAL 
		An invalid value was specified in how (but see BUGS).
	ENOTCONN
		The specified socket is not connected.
	ENOTSOCK
		sockfd is a file, not a socket.
```

* 参数一：`shutdown`的套接字描述符
* 参数二：关闭的状态：`TCP/IP`是全双工的
  * `SHUT_RD`：关闭读端，宏定义为`0`
  * `SHUT_WR`：关闭写端，宏定义为`1`
  * `SHUT_RDWR`：读端和写端都关闭，宏定义为`2`

## 注意啦

> 本篇博客请重点查看下代码，因为这篇博客不好整理，所以... ...
>
> `echocli.c`的`185-186行`、`205行`、`215-217行`
>
> `echosrv.c`的`279-282行`、`286行`
>
> 有注释所以应该可以比较好理解