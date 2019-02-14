# day03

## 本章目标

* `REUSEADDR`，地址重复利用
* 处理多客户端连接(`process-per-conection`)
* 点对点聊天程序实现


## REUSEADDR

* 服务器端尽可能使用`REUSEADDR`。
* 在绑定之前尽可能调用`setsockopt`来设置`REUSEADDR`套接字选项。
* 使用`REUSEADDR`选项可以使得不必等待`TIME——WAIT`状态消失就可以重启服务器。


## process-per-connection

* 一个连接一个进程来处理并发，多进程处理多客户端的连接。
* 每一个客户端都有一个独立的进程，所以通信不会出现串线。

## 点对点聊天程序实现

* 用多进程方式实现点对点聊天


>`getppid()`获取父进程的`pid`

## echosrv.c源文件

```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

void handle(int sign)
{
	printf("sign = %d\n", sign);
	exit(EXIT_SUCCESS);
}

int main()
{
	int listenfd;
	struct sockaddr_in servaddr;//一个服务器的地址
	//listenfd = socket(AF_INET, SOCK_STREAM, 0);
	////和下面的一样,第三个参数为0表示自动获取协议。
	
	listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(listenfd < 0)
	{
		perror("创建scoket失败\n");
		exit(EXIT_FAILURE);//退出程序
	}
		
	memset(&servaddr, 0, sizeof(servaddr));//初始化地址
	servaddr.sin_family = AF_INET;//地址族
	servaddr.sin_port = htons(5188);//端口号，网络字节序转化为主机字节序
	
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//表示绑定本机的任意地址(返回一个主机字节序)--->和下面的两个一样作用绑定IP地址
	//servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//(和上面的一样的意思)指定网络地址---> 真实的情况下表示本机的ip地址
	//inet_aton("127.0.0.1", &servaddr.sin_addr);//绑定IP地址

	int on = 1;
	on = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if(on < 0)
	{
		printf("端口重复利用失败\n");
		exit(EXIT_FAILURE);
	}	
	
	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("绑定本地地址到套接字失败\n");
		exit(EXIT_FAILURE);
	}
	
	if(listen(listenfd, SOMAXCONN) < 0)
	{
		perror("绑定本地地址到套接字失败\n");
		exit(EXIT_FAILURE);
	}	
	
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);//必须有初始值，否则accept会失败

	int conn = -1;
	if((conn = accept(listenfd, (struct sockaddr *)&peeraddr, &peerlen) )< 0)
	{
		perror("接收连接失败\n");
		exit(EXIT_FAILURE);
	}
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		perror("创建进程失败\n");
		exit(EXIT_FAILURE);
	}
	else if(pid ==  0)//子进程发送数据
	{

		signal(SIGUSR1, handle);
		char sendbuf[1024] = {0};
		while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
		{
			write(conn, sendbuf, strlen(sendbuf));
			memset(sendbuf, 0, sizeof(sendbuf));
		}
	}
	else//父进程接收数据
	{
		char recvbuf[1024] = {0};
		while(1)
		{
			fflush(stdin);
			memset(recvbuf, 0, sizeof(recvbuf));
			int ret = read(conn, recvbuf, sizeof(recvbuf));

			if(ret == -1)
			{
				printf("获取客户端的数据失败\n");
				break;
				//exit(EXIT_FAILURE);
			}
			else if(ret == 0)
			{
				printf("客户端关闭连接\n");
				break;
				//exit(EXIT_SUCCESS);
			}
			printf("服务器接收到的数据:");
			fputs(recvbuf, stdout);
			//write(conn, recvbuf, ret);
		}
		close(conn);
		printf("parent die\n");
		kill(pid, SIGUSR1);
		exit(EXIT_SUCCESS);
	}


	close(listenfd);
	close(conn);
	return 0;
}		
```



## echocli.c源文件

```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

void handle(int sign)
{
	printf("sign = %d\n", sign);
	exit(EXIT_SUCCESS);
}

int main()
{
	int sock;
	struct sockaddr_in servaddr;//一个服务器的地址
	//sock = socket(AF_INET, SOCK_STREAM, 0);
	////和下面的一样,第三个参数为0表示自动获取协议。
	
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0)
	{
		perror("创建scoket失败\n");
		exit(EXIT_FAILURE);//退出程序
	}
	memset(&servaddr, 0, sizeof(servaddr));//初始化地址
	servaddr.sin_family = AF_INET;//地址族
	servaddr.sin_port = htons(5188);//端口号，网络字节序转化为主机字节序
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//指定服务端的地址
	
	int conn = -1;
	if((conn = connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0))
	{
		printf("连接服务器失败\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		printf("创建进程失败\n");
		exit(EXIT_FAILURE);
	}
	else if(pid >  0)//父进程接收数据
	{
		char recvbuf[1024] = {0};
		while(1)
		{
			fflush(stdin);
			memset(recvbuf, 0, sizeof(recvbuf));
			int ret = read(sock, recvbuf, sizeof(recvbuf));
			if(ret == -1)
			{
				printf("客户端接收从服务器的数据失败\n");
				//:close(sock);
				break;
				//exit(EXIT_FAILURE);
			}
			else if(ret == 0)
			{
				printf("服务器断开了连接\n");
				//close(sock);
				break;
				//exit(EXIT_SUCCESS);
			}
			printf("客户端接收到的数据:");
			fputs(recvbuf, stdout);
		}
		close(sock);
		printf("parent die\n");
		kill(pid, SIGUSR1);//getppid(),获取父进程的pid
		exit(EXIT_SUCCESS);
	}
	else//子进程发送数据
	{
		char sendbuf[1024] = {0};
		signal(SIGUSR1, handle);
		while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
		{
			write(sock, sendbuf, strlen(sendbuf));
			memset(sendbuf, 0, sizeof(sendbuf));
		}
	}
	close(sock);
	return 0;
}
```

