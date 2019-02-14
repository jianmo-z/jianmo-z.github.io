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
#include <fcntl.h>

int main(int argc, char ** argv)
{
	int sock;
	struct sockaddr_in servaddr;//一个服务器的地址

	if(argc != 3)
	{
		printf("usage:./a.out <ip> <port>\n");
		exit(EXIT_FAILURE);
	}
	
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0)
	{
		perror("创建scoket失败");
		exit(EXIT_FAILURE);//退出程序
	}
	printf("socket success ...\n");

	memset(&servaddr, 0, sizeof(servaddr));//初始化地址
	servaddr.sin_family = AF_INET;//地址族

	if(servaddr.sin_addr.s_addr = inet_addr(argv[1]) == -1)//指定服务端的地址
	{
		printf("inet_addr error(bad ip)");
		exit(EXIT_FAILURE);
	}
	printf("ip:%s success ...\n", argv[1]);
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
	
	int conn = -1;
	if((conn = connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0))
	{
		perror("connect error");
		exit(EXIT_FAILURE);
	}
	printf("connect success ...\n");


	char recvbuf[1024] = {0};
	
	// 获取文件名字并新建文件
	bzero(recvbuf, sizeof(recvbuf));
	read(sock, recvbuf, sizeof(recvbuf));

	int file_fd = open(recvbuf, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if(file_fd < 0)
	{
		perror("create file error");
		exit(EXIT_FAILURE);
	}
	printf("create file success\n");


	// 接收文件内容
	while(1)
	{
		bzero(recvbuf, sizeof(recvbuf));
		int ret = read(sock, recvbuf, sizeof(recvbuf));
		if(ret == 0)
		{
			printf("server close\n");
			break;
		}
		else if(ret < 0)
		{
			perror("recv file error");
			exit(EXIT_FAILURE);
		}
		write(file_fd, recvbuf, ret);
		printf("%s", recvbuf);
		memset(recvbuf, 0, sizeof(recvbuf));
	}

	close(file_fd);
	close(sock);
	return 0;
}		
