# day17

## 本章目标

* `socketpair`：全双工的流管道
* `sendmsg`和`recvmsg`
* `UNIX`域套接字传递描述符字

## socketpair

* 功能：创建一个全双工的流管道，只能用于亲缘进程通信。
* 原型
  * `int socketpair(int domain, int type, int protocol, intsv[2]);`
* 参数
  * `domain`：协议家族
  * `type`：套接字类型
  * `protocol`：协议类型
  * `sv`：返回套接字对，两个套接字可读可写。
* 返回值：成功返回`0`，失败返回`-1`。

## sendmsg和recvmsg

> `sendmsg`：`ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);`
> `recvmsg`：` ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);`
>
> 主要为了用`UNIX`域协议传递套接字，`sockfd`只能套接字，不能是文件描述符。
>
> `struct iovec *msg_iov;        /* scatter/gather array */与readv和writev有关，真正所发送的数据。`
>
> **由于存在字节对齐，所以可能会有填充字节。**

```
struct msghdr {
    void         *msg_name;       /* optional address */
    socklen_t     msg_namelen;    /* size of address */
    struct iovec *msg_iov;        /* scatter/gather array */与readv和writev有关，真正所发送的数据。struct iovec
    size_t        msg_iovlen;     /* # elements in msg_iov */发送的iovec()的个数
    void         *msg_control;    /* ancillary data, see below */辅助控制信息，为struct cmsghdr
    size_t        msg_controllen; /* ancillary data buffer len */
    int           msg_flags;      /* flags on received message */
};
```
> `struct msghdr`的成员变量结构体。
```
// struct iovec *msg_iov;  
struct iovec {                    /* Scatter/gather array items */
    void  *iov_base;              /* Starting address */
    size_t iov_len;               /* Number of bytes to transfer */
};
//void	*msg_control;
struct cmsghdr {
    size_t cmsg_len;    /* Data byte count, including header (type is socklen_t in POSIX) */
    int    cmsg_level;  /* Originating protocol */
    int    cmsg_type;   /* Protocol-specific type */
    /* followed by 
    unsigned char cmsg_data[]; 
    */
};
```

> `readv`和`writev`与`struct iovec`有关。

```
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
```

> `man CMSG_FIRSTHDR`
>
> 参考文档：
>
> ​	https://blog.csdn.net/sparkliang/article/details/5486069
>
> 非亲缘进程之间传递套接字。

```
#include <sys/socket.h>

struct cmsghdr *CMSG_FIRSTHDR(struct msghdr *msgh);
struct cmsghdr *CMSG_NXTHDR(struct msghdr *msgh, struct cmsghdr *cmsg);
size_t CMSG_ALIGN(size_t length);
size_t CMSG_SPACE(size_t length);
size_t CMSG_LEN(size_t length);
unsigned char *CMSG_DATA(struct cmsghdr *cmsg);

struct cmsghdr {
    size_t cmsg_len;    /* Data byte count, including header
    (type is socklen_t in POSIX) */
    int    cmsg_level;  /* Originating protocol */
    int    cmsg_type;   /* Protocol-specific type */
    /* followed by
    unsigned char cmsg_data[]; */
};

```

## 插播一个vim

> 在`vim`的插入模式下按`insert`键，可以进入`replace`模式
>
>  
>
> 参考文档：https://blog.csdn.net/overstack/article/details/9174693
>
> 多行复制：
>
> ```
> 例如要将第5到10行黏贴到第15行后面可以这么写：5,10 copy 15 这个方法适合有大量的行数情况。
> move：5,10 move 15是移动，类似剪切+复制
> delete为删除：5,10 delete删除5到10行
> ```

## sendmsg和recvmsg应用代码

>`sendmsg`和`recvmsg`是在父子进程间传递文件描述符的，不能只通过传递文件描述符的数值来传递给别的进程，因为你虽然传递了‘文件描述符’，但是这个只是数值上和文件描述符相等，并不代表真的传递过去了一个文件描述符，**举个简单的例子**：大学都需要考英语四级证书，如果说有人考过了四级，你没有去参加考试，你去把那个人的四级证书复制了一份改成你的名字了，那么不代表你也通过了大学英语四级考试，你只是有一个英语四级证书，而在存储英语四级证书通过人的数据库里面没有你的信息存在。所以你并没有通过四级考试，同理，进程间传递文件描述符，也不能只是简简单单的传递一个`fd`(这里指那个fd数字)，在你看来`fd`代表了这个文件，其实不然，在这个`fd`的背后有着系统对这个`fd`的一些系列服务的内容，比如你打开了一个文件那么系统就为了维护了这个文件的相关信息，而数字`fd`系统不过是提供了一个友好的接口来让你方便操作你的那个文件。
>
>且不能通过`TCP`、`UCP`传递文件描述符。非亲缘进程的文件描述符的传递只能通过`UNIX`域协议来传递。
>
>父子进程可以通过`socketpair`来传递，下面的代码是父子进程通过`socketpair`来传递文件描述符的。

> `send_recv_msg.h`

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define ERR_EXIT(x) do{perror(x); exit(EXIT_FAILURE);}while(0)


void send_fd(int sock_fd, int send_fd)
{
	int ret;
	struct msghdr msg;
	struct cmsghdr *p_cmsg;//struct msghdr的第五个成员变量msg_control的辅助控制信息,p_cmsg需要指向一块缓冲区
	struct iovec vec;
	char cmsgbuf[CMSG_SPACE(sizeof(send_fd))];//使用send_fd通过CMSG_SPACE算出来辅助空间的大小，CMEG_SPACE是一个宏.
	int * p_fds;
	char sendchar = 0;

	msg.msg_control = cmsgbuf;//将msg_control指向cmsgbuf辅助数据
	msg.msg_controllen = sizeof(cmsgbuf);//长度为sizeof(cmsgbuf)

	p_cmsg = CMSG_FIRSTHDR(&msg);//通过宏CMSG_FIRSTHDR获取msg里面的第一个消息,通过CMSGNXTHDR获取第二个消息，特此说明：是CMSGNXTHDR不是CMSGNEXTHDR这个宏的NEXT没有E。
	p_cmsg->cmsg_level = SOL_SOCKET;//和下面一句共同表示传递的是文件描述字
	p_cmsg->cmsg_type = SCM_RIGHTS;
	p_cmsg->cmsg_len = CMSG_LEN(sizeof(send_fd));//通过宏得到长度
	p_fds = (int *)CMSG_DATA(p_cmsg);//得到数据的首地址
	*p_fds = send_fd;//真正的存放数据的步骤。
	
	//填充struct msghdr结构体变量msg
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &vec;
	msg.msg_iovlen = 1;//发送一个字符所以为1
	msg.msg_flags = 0;

	//填充struct iovec结构体变量vec
	vec.iov_base = &sendchar;//因为只发送一个字符
	vec.iov_len = sizeof(sendchar);//大小为一个字节

	//数据终于在这里填充完毕了，可以发送数据了
	ret = sendmsg(sock_fd, &msg, 0);
	if(ret != 1)
	{
		ERR_EXIT("sendmsg");
	}
}

int  recv_fd(int sock_fd)
{
	int ret;
	struct msghdr msg;
	char recvchar;
	struct iovec vec;
	int recv_fd;
	char cmsgbuf[CMSG_SPACE(sizeof(send_fd))];//使用send_fd通过CMSG_SPACE算出来辅助空间的大小，CMEG_SPACE是一个宏.
	struct cmsghdr *p_cmsg;//struct msghdr的第五个成员变量msg_control的辅助控制信息,p_cmsg需要指向一块缓冲区
	int * p_fds;

	//填充struct iovec结构体变量vec
	vec.iov_base = &recvchar;//因为只发送一个字符
	vec.iov_len = sizeof(recvchar);//大小为一个字节

	//填充struct msghdr结构体变量msg
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &vec;
	msg.msg_iovlen = 1;//发送一个字符所以为1
	msg.msg_flags = 0;
	msg.msg_control = cmsgbuf;//将msg_control指向cmsgbuf辅助数据
	msg.msg_controllen = sizeof(cmsgbuf);//长度为sizeof(cmsgbuf)
	msg.msg_flags = 0;

	p_fds = (int *)(CMSG_DATA(CMSG_FIRSTHDR(&msg)));//得到数据的首地址
	*p_fds = -1;//真正的存放数据的步骤。

	//数据终于在这里填充完毕了，可以接收数据了
	ret = recvmsg(sock_fd, &msg, 0);
	if(ret != 1)
	{
		ERR_EXIT("recvmsg");
	}
	p_cmsg = CMSG_FIRSTHDR(&msg);
	if(p_cmsg == NULL)
	{
		-ERR_EXIT("CMSG_FIRSTHDR");
	}
	
	p_fds = (int *)CMSG_DATA(p_cmsg);
	recv_fd = *p_fds;
	if(recv_fd == -1)
	{
		ERR_EXIT("CMSG_DATA");
	}
	return recv_fd;
}
```

## 测试代码

> `send_recv_msg.c`

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/un.h>
#include "sendmsg.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define ERR_EXIT(x) do{perror(x); exit(EXIT_FAILURE);}while(0)

void send_fd(int sock_fd, int send_fd);
int  recv_fd(int sock_fd);

int main()
{
	int sockfds[2];
	if(socketpair(PF_UNIX, SOCK_STREAM, 0, sockfds) < 0)
		ERR_EXIT("sockfdsetpair");
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		ERR_EXIT("fork");
	}
	else if(pid == 0)
	{
		//close(sockfds[1]);
		int fd;
		fd = open("text.txt", O_RDONLY);
		if(fd == -1)
		{
			ERR_EXIT("open");	
		}
		send_fd(sockfds[0], fd);
	}
	else
	{
		char buf[1024];
		//close(sockfds[0]);
		int fd = recv_fd(sockfds[1]);
		read(fd, buf, sizeof(buf));
		printf("buf = %s\n", buf);
	}
	return 0;
}
```

