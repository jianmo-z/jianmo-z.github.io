#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include "getFileList.h"
#include <vector>
#include <string>
#include <iostream>
#include <fcntl.h>

using std::string;

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		printf("Usage:./a.out <ip> <port> <dir>\n");
		exit(EXIT_FAILURE);
	}
    int sock = 0;
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
		exit(EXIT_FAILURE);
    }
	printf("socket success ...\n");
    
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    
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
		perror("port out of range\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		servaddr.sin_port = htons(port);
	}
	printf("port:%d success ...\n", port);

    if(bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("bind error");
		exit(EXIT_FAILURE);
	}
	
    //不需要监听，直接连接的。
	int ret = 0;
	char recvbuf[1024] = {0};
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);


	// 接收和发送HELLO ===> 目的:确认客户主机是否可达
	memset(recvbuf, 0, sizeof(recvbuf));
	ret = recvfrom(sock, recvbuf, 1024, 0, (struct sockaddr *)&peeraddr, &peerlen);
	if(ret < 0 && errno != EINTR)
	{
		perror("recvfrom");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("\nreceive:%s\n", recvbuf);
		sendto(sock, recvbuf, strlen(recvbuf), 0, (struct sockaddr *)&peeraddr, peerlen);
		printf("says:%s\n\n", recvbuf);
	}


	// 获取文件夹下所有文件名
	printf("start get file list from \"%s\"\n", argv[3]);
	string dir = argv[3];
	vector<string> file_list = get_file_list(dir);
	if(file_list.size() <= 0)
	{
		perror("getFileList error");
		exit(EXIT_FAILURE);
	}
	printf("dir:%s success ...\n", argv[3]); // 打开目录

	string sendstr;

	// 发送文件个数
	sendstr = std::to_string(htonl(file_list.size()));
	ret = sendto(sock, sendstr.c_str(), sendstr.length(), 0, (struct sockaddr *)&peeraddr, peerlen);
	if(ret <= 0)
	{
		perror("send file num error");
		exit(EXIT_FAILURE);
	}
	printf("file list num is %d\n", file_list.size());

	// 发送文件名列表
	for(int i = 0; i < file_list.size(); i++)
	{
		sendto(sock, file_list[i].c_str(), file_list[i].length(), 0, (struct sockaddr *)&peeraddr, peerlen);
		fprintf(stdout, "filename : %s\n", file_list[i].c_str());
	}
	printf("send file list success ...\n");

	// 填充路径
	string filename = argv[3];

	// 获取请求的文件序列
	int num = 0;
	
	bzero(recvbuf, sizeof(recvbuf));
	ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
	if(ret < 0 && errno != EINTR)
	{
		perror("receive request file num error");
		exit(EXIT_FAILURE);
	}
	sscanf(recvbuf, "%d", &num);
	num = ntohl(num);
	printf("request file num is %d\nfilename is %s\n", num, file_list[num].c_str());
	
	// 获取文件大小并发送
	filename = filename + string(file_list[num]);
	struct stat statbuf;
	if(-1 == stat(filename.c_str(), &statbuf))
	{
		perror("get file size error");
		exit(EXIT_FAILURE);
	}
	sendstr = std::to_string(htonl(statbuf.st_size));
	ret = sendto(sock, sendstr.c_str(), sendstr.length(), 0, (struct sockaddr *)&peeraddr, peerlen);
	if(ret < 0)
	{
		perror("send file num error");
		exit(EXIT_FAILURE);
	}
	printf("file size is %d\n", statbuf.st_size);

	

	// 打开文件
	int file_fd = open(filename.c_str(), O_RDONLY);
	if(file_fd < 0)
	{
		perror("open send file error");
		exit(EXIT_FAILURE);
	}
	printf("open file %s success\n", filename.c_str());


	int send_size = 0;
	// 发送文件
	printf("\033[?25l]");
	while(1)
	{
		bzero(recvbuf, sizeof(recvbuf));
		ret = read(file_fd, recvbuf, sizeof(recvbuf));	
		if(0 == ret)
			break;
		else if(ret < 0)
		{
			perror("read file error");
			exit(EXIT_FAILURE);
		}
		sendto(sock, recvbuf, ret, 0, (struct sockaddr *)&peeraddr, peerlen);
		send_size += ret;	

		// 显示发送的进度条
		printf("\rsend  %d/%d [", send_size, statbuf.st_size);
		for(int i = 0; i < 40; i++)
		{
			if(send_size * 1.0 / statbuf.st_size * 40 >  i)
				printf("#");
			else
				printf(" ");
		}
		printf("] %.2f%%", send_size * 1.0 / statbuf.st_size * 100);
	    recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
	}
	printf("\nsend success\n");
	//printf("\33[?25h]");


	close(sock);

    return 0;
}
