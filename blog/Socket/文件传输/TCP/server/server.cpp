#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include "read_recv.h"

int main(int argc, char ** argv)
{
	if(argc != 4)
	{
		printf("Usage:./a.out <ip> <port> <filename>\n");
		return -1;
		exit(EXIT_FAILURE);
	}

	int file_fd;
	int listenfd;
	struct sockaddr_in servaddr; // 服务器地址结构体

	bzero(&servaddr, sizeof(servaddr)); //初始化地址
	servaddr.sin_family = AF_INET; //地址族

	// 填充ip
	if(-1 == (servaddr.sin_addr.s_addr = inet_addr(argv[1])))
	{
		perror("inet_addr error(bad ip)");
		exit(EXIT_FAILURE);
	}
	printf("ip:%s success ...\n", argv[1]);

	// 填充port
	int port = atoi(argv[2]);
	if(-1 == port && 0 != strcmp(argv[2], "-1")) 
	{
		perror("atoi error(bad port)");
		exit(EXIT_FAILURE);
	}
	else if(port < 0 || port > 65535)
	{
		printf("port out of range\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		servaddr.sin_port = htons(port);
	}
	printf("port:%d success ...\n", port);

	// 文件是否存在
	file_fd = open(argv[3], O_RDONLY);
	if(file_fd < 0)
	{
		perror("file not exit or not readable");
		exit(EXIT_FAILURE);
	}

	// 创建套接字
	listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(listenfd < 0)
	{
		perror("socket error");
		exit(EXIT_FAILURE);
	}
	printf("socket success ...\n");
	
	// 端口重复利用
	int on = 1;
	on = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if(on < 0)
	{
		perror("reuse addr error");
		exit(EXIT_FAILURE);
	}
	printf("reuse addr success ...\n");


	// 绑定
	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("bind error");
		exit(EXIT_FAILURE);
	}
	printf("bind success ...\n");

	// 监听
	if(listen(listenfd, 1) < 0)
	{
		perror("listen error");
		exit(EXIT_FAILURE);
	}
	printf("listen success ...\n");
	printf("waiting for connect ...\n");
	
	// 接受连接
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	int conn = accept(listenfd, (struct sockaddr *)&peeraddr, (socklen_t *)&peerlen);
	if(conn < 0)
	{
		perror("accept error");
		exit(EXIT_FAILURE);
	}
	printf("accept success ...\n");


	char sendbuf[1024] = "";
	// 发送文件名
	int n = 0;

	n = writen(conn, argv[3], strlen(argv[3]));	
	if(n < 0)
	{
		perror("write error");
		exit(EXIT_FAILURE);
	}

	printf("\nsend filename:%s\n", argv[3]);
	// printf("content:\n");

	// 发送文件内容
	memset(sendbuf, 0, sizeof(sendbuf));

	while((n = read(file_fd, sendbuf, sizeof(sendbuf) - 1)) > 0)
	{
		//printf("%s", sendbuf);
		writen(conn, sendbuf, strlen(sendbuf));
		memset(sendbuf, 0, sizeof(sendbuf));
	}

	// 等待客户端先关闭连接  
	printf("\nsend content success\n");
	close(file_fd);
	close(listenfd);
	close(conn);

    return 0;
}











