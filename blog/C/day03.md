# day03

> `System V`消息队列

## 本章目标

* 消息队列
* `IPC`对象数据结构
* 消息队列结构
* 消息队列在内核中的表示
* 消息队列函数

## 消息队列

> `管道`传送数据是字节流的，无边界，数据先进先出。`消息队列`是传送的数据块，有边界，数据是可以指定顺序(优先级)。

* 消息队列提供了一个从一个进程向另一个进程发送一块数据的方法
* 每个数据块都被认为是有一个类型，接收者进程接收的数据块可以有不同的类型值
* 消息队列也有管道一样的不足，就是每个消息的最大长度是有上限的(MSGMAX)，每个消息队列的总的字节数也是有上限的(MSGMNB)，系统上消息队列的总数也有一个上限(MSGMNI)。

> 通过 `cat /proc/kernel/msgmax`，查看最大长度
>
> 通过 `cat /proc/kernel/msgmnb`，查看最大字节数
>
> 通过 `cat /proc/kernel/msgmni`，查看最大总数

## IPC对象数据结构

* 内核为每个IPC对象维护一个数据结构

  > 在`/usr/include/sys`目录下有一个`ipc.h`头文件，里面有关于下面的结构体的定义。

  ```
  struct ipc_perm
  {
    	key_t __key;  /*Key supplied to xxxget(2)*/
    	uid_t uid;	/*Effective UID of owner*/
    	gid_t gid;	/*Effective GID of owner*/
    	uid_t cuid;	/*Effective UID of creator*/
    	gid_t cgid;	/*Effective GID of creator*/
    	unsigned short mode;	/*Permissions*/
    	unsigned short __seq;	/*Sequence number*/

  };
  ```

  ​

## 消息队列结构

> 参看文档：
>
> ​	https://blog.csdn.net/ypist/article/details/6739560

```
struct msqid_ds
{
    struct msqid_ds {
    struct ipc_perm msg_perm;
    struct msg *msg_first;      /* first message on queue,unused  */
    struct msg *msg_last;       /* last message in queue,unused */
    __kernel_time_t msg_stime;  /* last msgsnd time */
    __kernel_time_t msg_rtime;  /* last msgrcv time */
    __kernel_time_t msg_ctime;  /* last change time */
    unsigned long  msg_lcbytes; /* Reuse junk fields for 32 bit */
    unsigned long  msg_lqbytes; /* ditto */
    unsigned short msg_cbytes;  /* current number of bytes on queue */
    unsigned short msg_qnum;    /* number of messages in queue */
    unsigned short msg_qbytes;  /* max number of bytes on queue */
    __kernel_ipc_pid_t msg_lspid;   /* pid of last msgsnd */
    __kernel_ipc_pid_t msg_lrpid;   /* last receive pid */
};
```

## 消息队列函数

```
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int msgget(key_t key, int msgflg);//创建/打开一个消息队列
int msgctl(int msqid, int cmd, struct msqid_ds *buf);//控制一个消息队列，改变权限，删除消息队列
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);//往消息队列中发送消息
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);//从消息队列中接收一条消息
```

## msgget函数

> * 功能：用来创建和访问一个消息队列
> * 原型：
>   * `int msgget(key_t key, int msgflg);`
> * 参数：
>   * `key`：某个消息队列的名字
>   * `msgflg`：由九个权限标志组成，他们的用法和创建文件时使用的`mode`模式标志是一样的。
> * 返回值：成功返回一个非负整数，即该消息队列的标识码；失败返回`-1`；

* 创建一个消息队列

    > `ipcs`：查看已经存在的共享内存`Shared Memory Segments`，信号量`Semaphore Arrays`和消息队列` Message Queues `
    >
    > `ipcrm -q msqid`：删除指定`msqid`的消息队列

    * ​`msgget`函数参数

        - `IPC_CREAT`

          > 此参数或操作`msgflg`，如果`key`不存在则需要添加`IPC_CREAT`，来新建一个消息队列，如果不添加`IPC_CREAT`且这个`key`不存在则会产生，`ENOENT`错误。更多信息请`man msgget`

        - `IPC_EXCL`

          > 此参数或操作`msgflg`，加了`IPC_CREAT | IPC_EXCL`如果消息队列已经存在了，则会报错错误为：`EEXIST`

        - `IPC_PRIVATE`

          > key的参数改为`IPC_PRIVATE`，`IPC_PRIVATE`的宏是`0`，每次都会创建一个私有的消息队列这个消息队列不能与其他的非亲缘进程共享。可以和亲缘进程(父子进程、兄弟进程)共享，但是父子兄弟进程需要“拷贝”了这个消息队列的`msgid`，否则不可以共享。
          >
          > 如果有`IPC_PRIVATE`则可以不指定`IPC_CREAT`也可以创建成功。


* 打开一个消息队列

  > 打开一个消息队列用的也是`msgget`函数。
  >
  > 例：`int msgfd = msgget(1234, 0);`如果说要打开一个消息队列，则不需要指定`msgid`参数，直接设置为`0`，当然也可以添加。如果打开一个已经存在的消息队列，打开的权限大于创建文件的权限则会打开失败。`0`表示创建的时候是什么权限，打开就用什么权限。

## 消息队列的删除

* 方法一

  > `ipcs -q msgid`
  >
  > ```
  > -Q, --queue-key msgkey//根据msgkey删除消息队列，不能删除为0的情况，key == 0 时只能用小写q删除
  > 	removes the message queue created with msgkey.
  >
  > -q, --queue-id msgid//根据msgid删除消息队列
  > 	removes the message queue identified by msgid.
  > ```
  > asdf

* 方法二

  > 通过`msgctl`函数删除消息队列

## msgctl函数

> * 功能：消息队列的控制函数
>
> * 原型：
>
>   * `int msgctl(int msqid, int cmd, struct msqid_ds * buf);`：第三个参数存储这个队列的特征，可置为`NULL`表示不关心队列的特征。
>
>     ```
>     struct msqid_ds {
>         struct ipc_perm msg_perm;     /* Ownership and permissions */
>         time_t          msg_stime;    /* Time of last msgsnd(2) */
>         time_t          msg_rtime;    /* Time of last msgrcv(2) */
>         time_t          msg_ctime;    /* Time of last change */
>         unsigned long   __msg_cbytes; /* Current number of bytes in queue (nonstandard) */
>         msgqnum_t       msg_qnum;     /* Current number of messages in queue */
>         msglen_t        msg_qbytes;   /* Maximum number of bytes allowed in queue */
>         pid_t           msg_lspid;    /* PID of last msgsnd(2) */
>         pid_t           msg_lrpid;    /* PID of last msgrcv(2) */
>     };
>
>     struct ipc_perm {
>         key_t          __key;       /* Key supplied to msgget(2) */
>         uid_t          uid;         /* Effective UID of owner */
>         gid_t          gid;         /* Effective GID of owner */
>         uid_t          cuid;        /* Effective UID of creator */
>         gid_t          cgid;        /* Effective GID of creator */
>         unsigned short mode;        /* Permissions */
>         unsigned short __seq;       /* Sequence number */
>     };
>     ```
>
> * 参数
>
>   * `msqid`：由`msgget`函数返回的消息队列标识码
>
>   * `cmd`：是将要采取的动作(有三个可取值)
>
|   命令   | 说明                                                         |
| :------: | :----------------------------------------------------------- |
| IPC_STAT | 把`msqid_ds`结构体中的数据设置为消息队列的当前关联值         |
| IPC_SET  | 在进程有足够权限的前提下，把消息队列的当前关联值设置为`msqid_ds`数据结构体中给出的值 |
| IPC_RMID | 删除消息队列                                                 |
>
> > 其实还有三个可取值，一共有六个可取值请`man msgctl`，为`IPC_INFO`、`MSG_INFO`和`MSG_STAT`
>
>
> * 返回值：成功返回`0`，失败返回`-1`
