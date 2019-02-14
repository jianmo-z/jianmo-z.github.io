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
#include <string>
#include <vector>

using std::string;
using std::vector;

int main(int argc, char ** argv)
{
	bool df_port = false;
	if(argc == 2)
	{
		printf("use default port:8000\n");
		df_port = true;
	}
	else if(argc != 3)
	{
		printf("Usage:./a.out <ip> <port>\n");
		return -1;
		exit(EXIT_FAILURE);
	}
	int sock;
	struct sockaddr_in servaddr; // 服务器地址结构体

	bzero(&servaddr, sizeof(servaddr)); //初始化地址
	servaddr.sin_family = AF_INET; //地址族

	// 创建套接字
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		perror("socket error");
		exit(EXIT_FAILURE);
	}
	printf("socket success ...\n");
	
	// 填充ip
	if(-1 == (servaddr.sin_addr.s_addr = inet_addr(argv[1])))
	{
		perror("inet_addr error(bad ip)");
		exit(EXIT_FAILURE);
	}
	printf("ip:%s success ...\n", argv[1]);

	
	// 填充port
	int port = 8000;
	if(df_port) // 使用默认的
	{
		servaddr.sin_port = htons(port);
	}
	else // 使用用户输入的端口
	{
		port = atoi(argv[2]);
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
	}
	printf("port:%d success ...\n", port);


	// 连接服务器
	int conn = connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(conn < 0)
	{
		perror("connect error");
		exit(EXIT_FAILURE);
	}
	printf("conn server success\n");
	
	int n = 0;
	char recvbuf[1024] = "HELLO";
	
	// 发送 hello给服务器
	int ret = sendto(sock, recvbuf, strlen(recvbuf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(ret < 0)
	{
		perror("send error");
		exit(EXIT_FAILURE);
	}
	printf("says:%s\n", recvbuf);
	
	// 接收 hello
	bzero(recvbuf, sizeof(recvbuf));
	ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
	if(ret < 0 && errno != EINTR)
	{
		perror("recvfrom error");
		exit(EXIT_FAILURE);
	}
	printf("server says:%s\n", recvbuf);

	// 获取文件个数
	int list_num = 0;

	bzero(recvbuf, sizeof(recvbuf));
	ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
	if(ret < 0 && errno != EINTR)
	{
		perror("recv file list num error");
		exit(EXIT_FAILURE);
	}
	sscanf(recvbuf, "%d", &list_num);
	list_num = ntohl(list_num);
	printf("file list num is %d\n", list_num);


	// 获取文件名列表
	printf("file list:\n");
	vector<string> list;
	for(int i = 0; i < list_num; i++)
	{
		bzero(recvbuf, sizeof(recvbuf));
		ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
		if(ret < 0 && errno != EINTR)
		{
			perror("recv file list error");
			exit(EXIT_FAILURE);
		}
		printf("%d : %s\n", i, recvbuf);
		list.push_back(string(recvbuf));
	}
		

	// 发送请求传输文件的序号
	while(1)
	{
		printf("\nPlease input file num:");
		scanf("%d", &list_num);
		if(list_num >= 0 && list_num < list.size())
			break;
		printf("out of range, please reenter!!!\n");
	}
	string re_num = std::to_string(htonl(list_num));
	ret = sendto(sock, re_num.c_str(), re_num.length(), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(ret < 0)
	{
		perror("send error");
		exit(EXIT_FAILURE);
	}
	printf("request for : %s\n", list[list_num].c_str());


	// 接收文件大小
	int file_size = 0;
	bzero(recvbuf, sizeof(recvbuf));
	ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
	if(ret < 0 && errno != EINTR)
	{
		perror("recv file size error");
		exit(EXIT_FAILURE);
	}
	sscanf(recvbuf, "%d", &file_size);
	file_size = ntohl(file_size);
	printf("file size is %d\n", file_size);


	// 新建文件
	int file_fd = open(list[list_num].c_str(), O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if(file_fd < 0)
	{
		perror("create file error");
		exit(EXIT_FAILURE);
	}
	printf("success create file:%s\n", list[list_num].c_str());


	int recv_size = 0;

	// 内容写入文件
	printf("\033[?25l]");
	while(1)
	{
		bzero(recvbuf, sizeof(recvbuf));
		n = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
		recv_size = recv_size + n;
		//
        // 显示接收的进度条
		printf("\rrecv  %d/%d [", recv_size, file_size);
		for(int i = 0; i < 40; i++)
		{
			if(recv_size * 1.0 / file_size* 40 >  i)
				printf("#");
			else
				printf(" ");
		}

		if(recv_size == file_size)
			break;
		else if(recv_size > file_size)
		{
			printf("recv error\n");
			exit(EXIT_FAILURE);
		}
		write(file_fd, recvbuf, n);

		
		printf("] %.2f%%", recv_size * 1.0 / file_size * 100);
	    sendto(sock, "ok", strlen("ok"), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	}
	sendto(sock, "ok", strlen("ok"), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("\nreceive success totally:%d\n", recv_size);
	printf("\33[?25h]");
	close(file_fd);

    return 0;
}











