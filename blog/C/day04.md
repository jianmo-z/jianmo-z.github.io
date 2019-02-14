# day04

## 本章目标

* `msgsnd`函数
* `msgrcv`函数
* `getopt`函数，拓展

## msgsnd函数

> * 功能：把一条消息添加到消息队列中
>
> * 原型：
>
>   * `int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);`
>
> * 参数：
>
>   * `msgid`：由`msgget`函数返回的消息队列标识码
>
>   * `msgp`：是一个指针，指针指向准备发送的消息
>
>   * `msgsz`：是`msgp`指向的消息长度，这个长度不含保存消息类型`struct msgbuf`的那个`long ing`长整型。
>
>     > 消息结构体在两方面受到限制
>     >
>     > * 它必须小于系统规定的上限值；每个消息不能超过`8192`个字节
>     > * 它必须以一个`long int`长整形开始，接收者函数将利用这个长整数确定消息的类型。
>
>   * `msgflg`：控制着当前消息队列满或到达系统上限时将要发生的事情。
>
>     > `IPC_NOWAIT`表示队列满不等待立即返回，返回`EAGDIN`错误
>     >
>     > 如果添`0`表示消息队列满，一直等待
>
> * 返回值：成功返回`0`，失败返回`-1`。
>
> ```
> #include <sys/types.h>
> #include <sys/ipc.h>
> #include <sys/msg.h>
>
> int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
>
>
> struct msgbuf {
>   long mtype;       /* message type, must be > 0 */
>   char mtext[1];    /* message data，可以不指定一个字节大小 */
> };
> ```

## msgrcv函数

* 功能：是从一个消息队列接收消息

* 原型：
  * `ssize_t msgrcv(int msqid, void * msgp, size_t msgsz, long msgtyp, int msgflg);`

* 参数：
  * `msgid`：由msgget函数返回的消息队列标识码
  * `msgp`：是一个指针，指针指向准备接收u的消息
  * `msgsz`：是`msgp`指向的消息长度，这个消息长度不包含消息类型的那个`long int`长整形。
  * `msgtype`：它可以实现接收优先级的简单形式。如果为`0`则顺序接收，如果不为零，接收指定的消息类型，可以设置阻塞或者不阻塞
  * `msgflg`：控制着队列中没有响应类型的消息可供接收时将要发生的事

* 返回值：成功返回实际放到接收缓冲区里去的字符个数，失败返回`-1`

* `msgrcv`的`msgtype`、`msgflg`参数

  * `msgtype = 0`：返回队列的第一条消息；
  * `msgtype > 0`：返回队列第一条类型等于`msgtype`的消息；
  * `msgtype < 0`：返回队列，小于等于`msgtype`绝对值的消息集合且集合中最小的第一条消息；
  * `msgflg = IPC_NOWAIT`：队列没有可读消息不等待，返回`ENOMSG`错误；
  * `msgflg = MSG_NOERROR`：消息大小超过`msgsz`时被截断；
  * `msgtype > 0`且`msgflg = MSG_EXCEPT`，接收类型不等于`msgtype`的第一条消息。

  > 代码样例：

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
         char mtext[1];    /* message data */
  };
  int main(int argc, char *argv[])
  {
  	int flag = 0;
  	int type = 0;
  	int opt;
  	int msgid;
  	
  	while(1)
  	{
  		opt = getopt(argc, argv, "nt:");
                  if(opt == '?')//解析出来了一个错误，会自动输出这个错误
                          exit(EXIT_FAILURE);
                  else if(opt == -1)//所有的都解析完了
                          break;
                  switch(opt)
                  {
                  case 'n':
                          flag |= IPC_NOWAIT;
                          break;
                  case 't':
                          type = atoi(optarg);
                          break;
                  }
  	}
  	msgid  = msgget(0X123, 0666 | IPC_CREAT);
  	if(msgid < 0)
  		ERR_EXIT("msgget");
  	struct msgbuf * msg;
  	msg = (struct msgbuf *)malloc(sizeof(long) + MAX_BUF);
  	msg->mtype = type;
  	int ret = msgrcv(msgid, msg, MAX_BUF, type, flag);
  	if(ret < 0)
  	{
  		ERR_EXIT("msgsnd");
  	}
  	printf("type = %d, ret = %d, recv = %s\n", type, ret, msg->mtext);
  	return 0;
  }
  ```

## getopt函数

> 此函数用于实现，对可执行文件加参数，如`./opj -l -a`
>
> * `getopt`函数的使用
>
>   >  前两个参数即为，`main`的传进来的参数。
>   >
>   >  第三个参数，里面加要有的选项,如果选项有参数则在选项后面加：
>   >
>   >  ```
>   >  eg:  
>   >  	./getopt -n -t 100
>   >  ```
>   >
>   >  需要为`getopt`添加`-n`选项和`-t`选项，而`-t`如果需要指定参数则需要加`:`
>   >
>   >  则参数三为为`"nt:"`，而`-t`带的参数，储存在全局变量`optarg`中
>
> * `getopt`返回值
>
>   >  返回值为`-1`,表示所有的都解析完了,返回值为`'?'`表示解析错误，自动输出错误信息，但不会退出程序。
>
> ```
> #include <unistd.h>
>
> int getopt(int argc, char * const argv[], const char *optstring);
>
> extern char *optarg;
> extern int optind, opterr, optopt;
> ```
>

* 程序样例
  ```
  #include <stdio.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
  #include <unistd.h>

  #define ERR_EXIT(x) do{perror(x); exit(EXIT_FAILURE);}while(0)

  struct msgbuf {
         long mtype;       /* message type, must be > 0 */
         char mtext[1];    /* message data */
  };

  int main(int argc, char *argv[])
  {
          int opt;
          int n;
          while(1)
          {
                  opt = getopt(argc, argv, "nt:");
                  if(opt == '?')//解析出来了一个错误，会自动输出这个错误
                          exit(EXIT_FAILURE);
                  else if(opt == -1)//返回值为-1,表示所有的都解析完了
                          break;
                  switch(opt)
                  {
                  case 'n':
                          printf("n\n");
                          break;
                  case 't':
                          n = atoi(optarg);
                          printf("t num = %d\n", n);
                          break;
                  }
          }
          return 0;
  }
  ```

  > 运行样例：
  >
  > ```
  > [pip@localhost code]$ gcc getopt.c -o getopt
  > [pip@localhost code]$ ./getopt 
  > [pip@localhost code]$ ./getopt -n //Success
  > n
  > [pip@localhost code]$ ./getopt -t  //Error
  > ./getopt: option requires an argument -- 't'
  > [pip@localhost code]$ ./getopt -t 1100 //Success
  > t num = 1100
  > [pip@localhost code]$ ./getopt -n -t 1100 //Success
  > n
  > t num = 1100
  > [pip@localhost code]$ ./getopt -t 1100 -n //Success
  > t num = 1100
  > n
  > [pip@localhost code]$ ./getopt -t1100 -n //Success
  > t num = 1100
  > n
  > [pip@localhost code]$ ./getopt -nt1100 //Success
  > n
  > t num = 1100
  > [pip@localhost code]$ ./getopt -adsf //Error
  > ./getopt: invalid option -- 'a'
  > [pip@localhost code]$ ./getopt 123 //Success
  > ```
