day01

## 本章目标

* 什么是`socket`?
* IPv4套接口地址结构
* 网络字节序
* 地址转换函数
* 套接字类型

## 什么是socket?

> `socket`可以看成是用户进程与内核网络协议栈的编程接口；
>
> `socket`不仅可以用于本机的进程间通信，还可以用于网络上不同主机的进程通信。
>
> 套接口通信是全双工通信。
>
> `socket`可以异构通信，通信双方的软件、硬件可以不同。

## IPv4套接口地址结构

>IPv4套接口地址结构通常也称为"网际套接字地址结构"，它以"sockaddr_in"命名，定义在头文件<netinet/in.h>中****
>
>**`man 7 ip`查看`sockaddr_in`结构体，`sockaddr_in`仅仅应用于`IPv4`地址结构**
>
> ```
> struct sockaddr_in
>
> {
>
>​		uint8_t sin_len;
>
>​		sa_family_t sin_family;
>
>​		in_port_t sin_port;
>
>​		struct in_addr sin_addr;
>
>​		char sin_zero[8];
>
>}
>```
>
>`sin_len`：整个`sockaddr_in`结构体的长度,在4.3BSD-Reno版本之前的第一个成员是`sin_family`；
>
>`sin_family`：指定该地址家族，在这里必须设为`AF_INET`；
>
>`sin_port`：端口；
>
>`sin_addr`：IPv4的地址；
>
>`sin_zero`：暂不使用，一般将其设置为0。

## 通用地址结构

>通用地址结构用来指定套接字关联的地址，`sockaddr`可以应用于所有的协议的套接口
>
>```
>struct sockaddr
>
>{
>
>​	uint8_t sin_len;
>
>​	sa_family_t sin_family;
>
>​	char sa_data[14];
>
>}
>```
>
>`sin_len`：整个`sockaddr`结构体的长度；
>
>`sin_family`：指定该地址家族；
>
>`sa_data`：由`sin_family`决定它的形式。

## 网络字节序

> https://www.cnblogs.com/gremount/p/8830707.html

* 字节序

  * 大端字节序(Big Endian)

    >最高有效位(MSB: Most Significant Bit)存储于最低内存地址处，最低有效位(LSB: Lowest Significant Bit)存储于最高内存地址处。

  * 小端字节序(Little Endian)

    >最高有效位(MSB:Most Significant Bit)存储于最高内存地址处，最低有效位(LSB: Lowest Significant Bit)存储于最低内存地址处。

    **假设有字节序`0x12345678`**
| 内存地址       | 低地址 | -->  | -->  | 高地址 |
| -------------- | ------ | ---- | ---- | ------ |
| 大端字节序(0x) | 12     | 34   | 56   | 78     |
| 小端字节序(0x) | 78     | 56   | 34   | 12     |

* 主机字节序

  >不同的主机有不同的字节序，如`x86`为小端字节序，`Motorola 6800`为大端字节序，`ARM`字节序是可配置的。

* 网络字节序

  >网络字节序规定为**大端字节序**。

### 为什么有字节序

> 计算机电路先处理低位字节，效率比较高，因为计算都是从低位开始的。所以，计算机的内部处理都是小端字节序。但是，人类还是习惯读写大端字节序。所以，除了计算机的内部处理，其他的场合几乎都是大端字节序，比如网络传输和文件储存。

##  字节序转换函数

> man 3 byteorder   查询字节序转换函数

```
#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong);//host to network long 四个字节

uint16_t htons(uint16_t hostshort);//host to network short 两个字节

uint32_t ntohl(uint32_t netlong);

uint16_t ntohs(uint16_t netshort);

注：在上述的函数中，h 代表 host; n 代表 network; s 代表 short; l 代表 long
```

## 地址转换函数

>`man 3 inet` 查询地址转换函数

```
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>

int inet_aton(const char *cp, struct in_addr *inp);

in_addr_t inet_network(const char *cp);//点分十进制的地址转化为32位无符号长整形

char *inet_ntoa(struct in_addr in);//32位无符号长整形转化位点分十进制

typedef uint32_t in_addr_t;
struct in_addr
{
	in_addr_t s_addr;
};
```

## 套接字类型

* 流式套接字(SOCK_STREAM) ---> `TCP/IP协议`	

  >提供面向**连接的、可靠的数据传输服务，数据无差错，无重复的发送，且按发送顺序接收。**

* 数据报式套接字(SOCK_DGRAM)

  >提供**无连接服务，不提供无错保证，数据可能丢失或重复，并且接收顺序混乱。**

* 原始套接字(SOCK_RAW)

  >跨越传输层，直接对`IP`层进行数据封装的套接字，通过原始套接字，将应用层的数据封装成`IP`	层能够认识的套接字。

  
