# day14

## 本章目标

* `UDP`特点
* `UDP`客户/服务基本模型
* `UDP`回射客户/服务器
* `UDP`注意点

## UDP特点

* 无连接
* 基于消息的数据传输服务，理解为数据包之间有边界。
* 不可靠
* 一般情况下UDP更加高效

## UDP注意点

* `UDP`报文可能会丢失、重复
* `UDP`报文可能会乱序
* `UDP`缺乏流量控制
* `UDP`协议数据报文截断
* `recvfrom`返回为0，不代表连接关闭，因为`UDP是无连接的`
* `ICMP`异步错误
* `UDP connect`
* `UDP`外出接口的确定

## echosrv.c

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

#define ERR_EXIT(x) do{perror(x); exit(EXIT_FAILURE);}while(0)

void echo_srv(int sock)
{
	int ret = 0;
	char recvbuf[1024] = {0};
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	while(1)
	{
		memset(recvbuf, 0, sizeof(recvbuf));
		ret = recvfrom(sock, recvbuf, 1024, 0, (struct sockaddr *)&peeraddr, &peerlen);
		if(ret < 0)
		{
			if(errno == EINTR)
				continue;
			ERR_EXIT("recvfrom");
			
		}
		else if(ret > 0)
		{
			fputs(recvbuf, stdout);
			sendto(sock, recvbuf, strlen(recvbuf), 0, (struct sockaddr *)&peeraddr, peerlen);
		}
	}
	close(sock);
}


int main()
{
	int sock = 0;
	sock = socket(PF_INET, SOCK_DGRAM, 0);//参数一表示为IPV4地址家族，第二个参数IPV4对应的UDP套接口，第三个参数0表示内核自动选择协议根据前两个可以确定通信协议为UDP的
	if(sock < 0)
	{
		ERR_EXIT("socket");
	}
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = 6000;
	//servaddr.sin_addr = htonl("127.0.0.1");//和下面的一样作用，绑定指定的地址，和绑定任意一个地址。
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");
	//不需要监听，直接连接的。
	echo_srv(sock);
	return 0;
}
```

## echocli.c

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

#define ERR_EXIT(x) do{perror(x); exit(EXIT_FAILURE);}while(0)

void echo_cli(int sock)
{
	struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = 6000;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//绑定服务器地址
	if(connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)//连接后只能给指定的IP发送数据，则sendto可以不需要指定IP和端口了,UDP的connect是进行了一个弱绑定，不会进行三次握手和四次挥手
		ERR_EXIT("connect");
	int ret = 0;
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	while(1)
	{
		memset(sendbuf, 0, sizeof(sendbuf));
		memset(recvbuf, 0, sizeof(recvbuf));
		if(fgets(sendbuf, sizeof(sendbuf), stdin) == NULL)
			ERR_EXIT("fgets");
		//sendto(sock, sendbuf, strlen(sendbuf), 0, NULL, 0);
		send(sock, sendbuf, strlen(sendbuf), 0);
		ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
		if(ret < 0)
		{
			if(errno == EINTR)
				continue;
			ERR_EXIT("recvbrom");
		}
		fputs(recvbuf, stdout);
	}
	
}

int main()
{
	int sock = 0;
	sock = socket(PF_INET, SOCK_DGRAM, 0);//参数一表示为IPV4地址家族，第二个参数IPV4对应的UDP套接口，第三个参数0表示内核自动选择协议根据前两个可以确定通信协议为UDP的
	if(sock < 0)
	{
		ERR_EXIT("socket");
	}
	echo_cli(sock);
	return 0;
}
```

