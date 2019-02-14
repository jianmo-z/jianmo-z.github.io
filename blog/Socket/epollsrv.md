# epollsrv.cpp

> `epollsrv.cpp`文件源代码，`epoll`只是服务器发生了变化而客户端不需要变化。

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
#include <poll.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <fcntl.h>


#define ERR_EXIT(err) {perror(err); exit(EXIT_FAILURE);}

typedef std::vector<struct epoll_event> EventList;

typedef struct package
{
	unsigned int len;
	char data[1024];
}package;

void handle(int sign)
{
	printf("sign = %d\n", sign);
	exit(EXIT_SUCCESS);
}



//size_t read(int fd, void *buf, size_t count);
//ssize_t 无符号整数
//size_t 有符号整数
ssize_t readn(int fd, void * buf, size_t count)
{
	size_t nleft = count;
	ssize_t nread = 0;
	char * bufp = static_cast<char *>(buf);
	while(nleft > 0)
	{
		if((nread = read(fd, bufp, nleft)) < 0)
		{
			if(errno == EINTR)//如果信号被中断，仍然要继续发送数据。
				continue;
			//return 0;
			return -1;
		}
		else if(nread == 0)
			return count - nleft;
		bufp += nread;
		nleft -= nread;
	}
	return count;
}

//ssize_t write(int fd, const void *buf, size_t count);
//ssize_t 无符号整数
//size_t 有符号整数
ssize_t writen(int fd, void * buf, size_t count)
{

	size_t nleft = count;
	ssize_t nwrite;
	char * bufp = static_cast<char *>(buf);
	while(nleft > 0)
	{
		if((nwrite = write(fd, bufp, nleft)) < 0)
		{
			if(errno == EINTR)//如果信号被中断，仍然要继续发送数据。
				continue;
			return -1;
		}
		else if(nwrite == 0)
			continue;
		bufp += nwrite;
		nleft -= nwrite;
	}
	return count;
}

ssize_t recv_peek(int sockfd, void * buf, size_t len)
{
	while(1)
	{	//recv读取数据但是不会把数据从缓冲区移除
		int ret = recv(sockfd, buf, len, MSG_PEEK);//有数据返回，无数据阻塞，对方套接口关闭，返回零，信号中断返回-1
		if(ret == -1 && errno == EINTR)//信号终止，继续进行操作
		{
			continue;
		}
		return ret;
	}
}
ssize_t readline(int sockfd, void * buf, size_t maxline)
{
	int ret;
	int nread;
	char * bufp = static_cast<char *>(buf);
	int nleft = maxline;
	while(1)
	{
		ret = recv_peek(sockfd, buf, nleft);
		if(ret < 0)
			return ret;
		else if(ret == 0)//表示对方关闭了套接口
			return ret;
		nread = ret;//接收到的字节数
		int i;
		for(i = 0; i < nread; i++)
		{
			if(bufp[i] == '\n')
			{
				ret = readn(sockfd, bufp, i+1);//取出数据并从缓冲区移除
				if(ret != i + 1)//接收数据失败，直接返回
				{
					printf("接收数据失败");
					exit(EXIT_FAILURE);
				}
				return ret;
			}
		}
		if(nread > nleft)//没有遇到'\n'把数据拿出来
		{
			printf("没有遇到回车换");
			exit(EXIT_FAILURE);
		}
		nleft -= nread;
		ret = readn(sockfd, bufp, nread);
		if(ret != nread)//接收数据失败，直接返回
		{
			printf("接收数据失败");
			exit(EXIT_FAILURE);
		}
		bufp += nread;//指针偏移，如果遇到'\n'指针已经偏移
	}
	return -1;
}

void activate_nonblock(int fd)
{
	int ret = 0;
	int flags = fcntl(fd, F_GETFL);//获取文件描述符的状态
	if(fd == -1)
	{
		ERR_EXIT("fcntl:1");
	}
	flags |= O_NONBLOCK;//不阻塞模式
	ret = fcntl(fd, F_SETFL, flags);//设置文件描述符的状态
	if(ret == -1)
	{
		ERR_EXIT("fcntl:2");	
	}
}
void deactivate_nonblock(int fd)
{
	int ret = 0;
	int flags = fcntl(fd, F_GETFL);
	if(flags == -1)
	{
		ERR_EXIT("fcntl:1");
	}
	flags &= ~O_NONBLOCK;//不阻塞，位操作,~按位取反
	ret = fcntl(fd, F_SETFL, flags);
	if(ret == -1)
	{
		ERR_EXIT("fcntl:1");
	}
}

void signal_handle(int sign)
{
	//wait(NULL);
	//waitpid(-1, NULL, WNOHANG);//可能会有僵尸进程的存在，因为进程发送了SIGCHLD信号但是没有接收到，无法处理导致了僵尸进程的存在
	while(waitpid(-1, NULL, WNOHANG) > 0);//如果没有子进程退出循环,避免僵尸进程
}

void signpipe(int sign)
{
	printf("SIGPIPE = %d\n", sign);
}

int main()
{
	//int conn = -1;
	int listenfd;
	struct sockaddr_in servaddr;//一个服务器的地址
	signal(SIGPIPE, signpipe);//信号	
	//signal(SIGCHLD, SIG_IGN);//忽略信号	
	signal(SIGCHLD, signal_handle);//忽略信号	
	listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(listenfd < 0)
	{
		perror("创建scoket失败\n");
		exit(EXIT_FAILURE);//退出程序
	}

	memset(&servaddr, 0, sizeof(servaddr));//初始化地址
	servaddr.sin_family = AF_INET;//地址族
	servaddr.sin_port = htons(6000);//端口号，网络字节序转化为主机字节序

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


	std::vector<int> clients;
	int epollfd;
	epollfd = epoll_create1(EPOLL_CLOEXEC);//创建一个实例
	
	struct epoll_event event;
	event.data.fd = listenfd;
	event.events = EPOLLIN | EPOLLET;//EPOLLIN监听，EPOLLET边沿方式触发
	
	epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event);//添加一个套接字到epoll
	
	EventList events(16);
	struct sockaddr_in perraddr;
	socklen_t perrlen;
	int conn;
	int count = 0;
	int i;
	int nready;

	while(1)
	{
		//检测那个套接字产生的事件。 //&*：迭代器解绑定的感觉... ...
		nready = epoll_wait(epollfd, &(*events.begin()), static_cast<int>(events.size()), -1);
		if(nready == -1)
		{
			if(errno == EINTR)
				continue;
			ERR_EXIT("epoll_wait");
		}
		if(nready == 0)
			continue;
		if((ssize_t)nready == events.size())
			if(events.size() > 4096)
				events.resize(events.size() + 2048);
			else
				events.resize(events.size() * 2);
		for(i = 0; i < nready; i++)
		{
			if(events[i].data.fd == listenfd)
			{
				perrlen = sizeof(perraddr);
				conn = accept(listenfd, (struct sockaddr *)&peeraddr, &perrlen);
				if(conn == -1)
					ERR_EXIT("accept");
				printf("peer:ip = %s, port = %d\n", inet_ntoa(perraddr.sin_addr), ntohs(perraddr.sin_port));
				printf("count = %d\n", ++count);
				clients.push_back(conn);
				activate_nonblock(conn);//设置为非阻塞模式
				
				//添加新的套接字到event中
				event.data.fd = conn;
				event.events = EPOLLIN | EPOLLET;
				epoll_ctl(epollfd, EPOLL_CTL_ADD, conn, &event);
			}
			else if(events[i].events & EPOLLIN)
			{
				conn = events[i].data.fd;
				if(conn < 0)
					continue;
				char recvbuf[1024] = {0};
				int ret = readline(conn, recvbuf, 1024);

				if(ret == -1)
					ERR_EXIT("readline")
				else if(ret == 0)
				{
					count --;
					printf("client closed\n");
					close(conn);
					event = events[i];
					epoll_ctl(epollfd, EPOLL_CTL_DEL, conn, &event);
					clients.erase(std::remove(clients.begin(), clients.end(), conn), clients.end());//删除已经断开的客户端的套接字
				}
				fputs(recvbuf, stdout);
				writen(conn, recvbuf, strlen(recvbuf));
			}
		}
	}
	return 0;
}
```
