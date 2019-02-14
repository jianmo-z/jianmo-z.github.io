# day05

## 本章目标

* `read`、`write`与`recv`、`send`
* `readline`实现
* 用`readline`实现回射客户端/服务器
* `getsockname`、`getpeername`
* `gethostname`、`gethostbyname`、`gethostbyadr`

## read、write与recv、send函数

> `man recv`
>
> `recv`函数只能用于套接口的`I/O·`	,`read`函数可以用于任何的`I/O`
>
> `recv`函数增加了可选参数`flgs`，flags取值为`MSG_OOB` ：接收紧急指针数据。`MSG_PEEK`：接收数据但是不把缓冲区的数据清除。

```
#include <sys/types.h>
#include <sys/socket.h>

ssize_t recv(int sockfd, void *buf, size_t len, int flags);
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
```

##flags标志：

````
MSG_OOB
    This flag requests receipt of out-of-band data that would not be
    received  in the normal data stream.  Some protocols place expe‐
    dited data at the head of the normal data queue, and  thus  this
    flag cannot be used with such protocols.

MSG_PEEK
    This  flag  causes the receive operation to return data from the
    beginning of the receive queue without removing that  data  from
    the queue.  Thus, a subsequent receive call will return the same
    data.
````

## readline实现

> `readline`：是为了解决粘包问题。

## getsockname、getpeername

> `getsockname`：获取套接口本地的地址
>
> `getpeername`：获取远程套接口的地址

````
#include <sys/socket.h>

int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

struct sockaddr {
	sa_family_t sa_family;
	char        sa_data[14];
}
````

```
#include <sys/socket.h>

int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

struct sockaddr {
	sa_family_t sa_family;
	char        sa_data[14];
}
```

## gethostname、gethostbyname和gethostbyaddr

> `gethostname`：获取主机名字
>
> `gethostbyname`：通过主机名获取所有的IP地址

```
#include <unistd.h>

int gethostname(char *name, size_t len);
```

```
#include <netdb.h>
extern int h_errno;

struct hostent *gethostbyname(const char *name);

#include <sys/socket.h>       /* for AF_INET */
struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type);

struct hostent {
    char  *h_name;            /* official name of host */
    char **h_aliases;         /* alias list */
    int    h_addrtype;        /* host address type */
    int    h_length;          /* length of address */
    char **h_addr_list;       /* list of addresses *///IP地址列表
}
 #define h_addr h_addr_list[0] /* for backward compatibility */
```

>注：`struct hostent`的成员`h_addr_list`虽然是`char **`但是是需要用`inet_ntoa`转化一下才能输出IP地址。
