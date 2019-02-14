# day16

## 本章目标

* `UNIX`域协议特点
* `UNIX`域地址结构
* `UNIX`域字节流回射客户/服务
* `UNIX`域套接字编程注意点

## UNIX域协议特点

* `UNIX`域套接字与`TCP`套接字相比较，在同一台主机的传输速度前者是后者的两倍。
* `UNIX`域套接字可以在同一台主机上各进程之间传递描述符。
* `UNIX`域套接字与传统套接字的区别是用路径名来表示协议族的描述。

## UNIX域地址结构

> `man unix`

```
#define UNIX_PATH_MAX 108
struct sockaddr_un
{
    sa_family_t sun_family; //为AF_UNIX
    char sun_path[UNIX_PATH_MAX]; //pathname
}
```

##UNIX域字节流回射客户/服务

> `echosrv.c`

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

#define ERR_EXIT(x) do{perror(x); exit(EXIT_FAILURE);}while(0)

void echo_srv(int conn)
{
	int ret = 0;
	char recvbuf[1024] = {0};
	while(1)
	{
		memset(recvbuf, 0, sizeof(recvbuf));
		ret = read(conn, recvbuf, sizeof(recvbuf));
		if(ret < 0)
		{
			if(errno = EINTR)
				continue;
			 ERR_EXIT("read");
		}
		else if(ret == 0)
		{
			printf("对方关闭连接");
			break;
		}
		fputs(recvbuf, stdout);
		ret = write(conn, recvbuf, strlen(recvbuf));
	}
	close(conn);
}


int main()
{
	int conn;
	int listenfd;
	unlink("test_socket");//删除一个文件的目录项并减少它的链接数，若成功则返回0，否则返回-1，错误原因存于error。如果想通过调用这个函数来成功删除文件，你就必须拥有这个文件的所属目录的写和执行权
	if((listenfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");
	struct sockaddr_un servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, "test_socket");
	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)	
		ERR_EXIT("bind");
	if(listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");
	
	pid_t pid;
	while(1)
	{
		conn = accept(listenfd, NULL, NULL);	
		if(conn == -1)
		{
			//用户态资源并没有准备好，返回EINTR错误。以便用户态可以做出自己的决定。
			if(errno = EINTR)
				continue;
			ERR_EXIT("accept");
		}
		pid = fork();
		if(pid < 0)
			ERR_EXIT("fork");
		else if(pid == 0)//子进程处理新的连接
		{
			close(listenfd);//子进程不需要处理监听
			echo_srv(conn);
			exit(EXIT_SUCCESS);
		}
		close(conn);//父进程不需要处理连接
	}
	return 0;
}
```

> `echocli.c`

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

#define ERR_EXIT(x) do{perror(x); exit(EXIT_FAILURE);}while(0)

void echo_cli(int sock)
{
	int ret = 0;
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
	{
		ret = write(sock, sendbuf, sizeof(sendbuf));
		ret = read(sock, recvbuf, sizeof(recvbuf));
		fputs(recvbuf, stdout);
		memset(sendbuf, 0, sizeof(sendbuf));
		memset(recvbuf, 0, sizeof(recvbuf));
	}
	close(sock);
}
int main()
{
	int sock;
	if((sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");
	struct sockaddr_un servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, "test_socket");
	if(connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("connect");
	
	echo_cli(sock);
	return 0;
}
```

##UNIX套接字编程注意点

* `bind`成功将会创建一个文件，权限为`0777&umask`
* `sun_path`最好用一个绝对路径，一般定到`tmp`目录下。
* `UNIX`域协议支持流式接口`SOCK_STREAM`与报式套接口`SOCK_DGRAM`
* `UNIX`域流式套接字`connect`发现监听队列满时，会立即返回一个`ECONNERFUSED`，这和`TCP`不同，如果监听套接字队列满，会忽略到来的`SYN`，导致对方重发`SYN`。