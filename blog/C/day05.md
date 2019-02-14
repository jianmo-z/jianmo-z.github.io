# day05

## 本章目标

* 用消息队列实现回射客户/服务器

##可能的死锁Bug

> 可能会发生死锁情况，当服务器准备发送数据时，客户端发送大量数据，然后导致队列满了，那么服务器发送不出去数据导致死锁，通过多个队列，使队列的功能分离开来，读的只读数据，写只写数据。客户端给服务器发送数据，共用一个。当服务器给客户端发送数据时，通过私有的队列来发送数据。可以解决死锁。

## echosrv.c

```
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERR_EXIT(x) do{perror(x); exit(EXIT_FAILURE);}while(0)
#define MSGMAX 8192

struct msgbuf {
       long mtype;       /* message type, must be > 0 */
       char mtext[MSGMAX];    /* message data */
};


void echo_srv(msgid)
{
	int pid;
	struct msgbuf msg;
	memset(&msg, 0, sizeof(msg));
	while(1)
	{
		int ret = msgrcv(msgid, &msg, MSGMAX, 1, 0);
		if(ret < 0)
		{
			ERR_EXIT("msgsnd");
		}
		pid = *((int *)msg.mtext);//按照pid回射回去数据
		msg.mtype = pid;
		printf("pid = %d msg = %s\n", pid, msg.mtext + sizeof(int));
		msgsnd(msgid, &msg, ret, 0);
	}
}
int main(int argc, char *argv[])
{
	int msgid;
	msgid  = msgget(0X123, 0666 | IPC_CREAT);//创建一个众所周知的消息队列
	if(msgid < 0)
		ERR_EXIT("msgget");

	echo_srv(msgid);
	return 0;
}

```

## echocli.c

```
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define ERR_EXIT(x) do{perror(x); exit(EXIT_FAILURE);}while(0)
#define MAX_BUF 8192

struct msgbuf {
       long mtype;       /* message type, must be > 0 */
       char mtext[MAX_BUF];    /* message data */
};


void echo_cli(int msgid, int flag)
{
	int type = 0;
	struct msgbuf msg;
	type = getpid();
	*((int *)msg.mtext) = type;
	
	while(fgets(msg.mtext + sizeof(int), 8192 - sizeof(int), stdin) != NULL)
	{
		msg.mtype = 1;
		int ret = msgsnd(msgid, &msg, strlen(msg.mtext + sizeof(int)) + sizeof(int), flag);
		if(ret < 0)
		{
			ERR_EXIT("msgsnd");
		}
		memset(msg.mtext, 0, MAX_BUF);
		ret = msgrcv(msgid, &msg, MAX_BUF, type, 0);
		if(ret < 0)
		{
			ERR_EXIT("msgrcv");
		}
		printf("recv:%s\n", msg.mtext + sizeof(int));
	}
}

int main(int argc, char *argv[])
{
	int flag = 0;
	int opt;
	int msgid;

	while(1)
	{
		opt = getopt(argc, argv, "n");
                if(opt == '?')//解析出来了一个错误，会自动输出这个错误
                        exit(EXIT_FAILURE);
                else if(opt == -1)//所有的都解析完了
                        break;
                switch(opt)
                {
                case 'n':
                        flag |= IPC_NOWAIT;
                        break;
                }
	}

	msgid  = msgget(0X123, 0666);
	if(msgid < 0)
		ERR_EXIT("msgget");

	echo_cli(msgid, flag);
	return 0;
}

```
