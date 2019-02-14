# day08

> `System V`信号量

## 本章目标

* 信号量
* 信号量集结构
* 信号量集函数
* 信号量示意图

## 信号量

> * 信号量和`P`、`V`原语由Dijkstra(迪杰斯特拉)提出，前面已经简单介绍过了。
>
> * 信号量
>
>   * 互斥：`P`、`V`在同一个进程中
>   * 同步：`P`、`V`在不同进程中
>
> * 信号量值含义：
>
>   * `S > 0`：S表示可用资源的个数
>   * `S = 0`：表示无可用资源，无等待进程
>   * `S < 0`：|S|表示等待队列中进程个数
>
> * 信号量数据结构
>
>   ```
>   struct semaphore
>   {
>       int value;
>       pointer_PCB queue;
>   };
>   ```
>
> * `P`原语，原子操作无法中断
>
>   ```
>   P(s)//申请资源，原子操作无法中断
>   {
>       s.value = s.value--;
>       if(s.value < 0)
>       {
>           1、该进程状态置为等待状态
>           2、将该进程的PCB插入响应的等待队列s.queue末尾
>       }
>   }
>   ```
>
>   ​
>
> * `V`原语，原子操作无法中断
>
>   ```
>   V(s)//归还资源，原子操作无法中断
>   {
>        s.value = s.value++;
>       if(s.value <= 0)
>       {
>           1、唤醒响应等待队列s.queue中等待的一个进程
>           2、改变其状态为就绪态
>           3、将其插入就绪队列
>       }
>   }
>   ```

## 信号量集结构

> `man shmctl`

```
struct semid_ds
{
    struct ipc_perm sem_perm;  /* Ownership and permissions */
    time_t          sem_otime; /* Last semop time */最后一次执行semop函数的时间,即P/V操作的最后一次时间
    time_t          sem_ctime; /* Last change time */信号量集最后一次改变的时间
    unsigned long   sem_nsems; /* No. of semaphores in set */信号量集中信号量的个数。
};

struct ipc_perm
{
    key_t          __key; /* Key supplied to semget(2) */
    uid_t          uid;   /* Effective UID of owner */
    gid_t          gid;   /* Effective GID of owner */
    uid_t          cuid;  /* Effective UID of creator */
    gid_t          cgid;  /* Effective GID of creator */
    unsigned short mode;  /* Permissions */
    unsigned short __seq; /* Sequence number */
};
```

## 信号量集函数

> `man semget`、`man semctl`和`man semop`

> ```
> #include <sys/types.h>
> #include <sys/ipc.h>
> #include <sys/sem.h>
>
> int semget(key_t key, int nsems, int semflg);//创建打开一个信号量集
> int semctl(int semid, int semnum, int cmd, ...);//用来控制一个信号量集
> int semop(int semid, struct sembuf * sops, unsigned nsops);//即可以P操作又可以V操作
> ```

## semget函数

> `ipcs`查看信号量集
> * 功能：用来创建和访问一个消息队列
> * 原型：
>   * `int semget(key_t key, int nsems, int semflg);`
> * 参数：
>   * `key`：信号集的名字
>   * `nsems`信号集中信号量的个数
>   * `semflg`：由九个标志权限构成，它们的用法和创建文件时使用的`mode`模式标志是一样的。
> * 返回值：成功返回一个非负整数，即该信号集的标识码失败返回`-1`。

## semctl函数

> * 功能：用于控制信号量集，可以获取信号量状态、设置信号量集状态、删除信号量集... ...
>
> * 原型：
>
>   * `int semctl(int semid, int semnum, int cmd, ...);`
>
> * 参数：
>
>   * `semid`：由`semget`返回的信号量标识码
>
>   * `semnum`：信号集中信号量的序号
>
>   * `cmd`：将要采取的动作(有三个可取值)
>
>| 命令     | 说明                                                         |
>| -------- | ------------------------------------------------------------ |
>| SETVAL   | 设置信号量集中的信号量的计数值                               |
>| GETVAL   | 获取信号量中的信号量的计数值                                 |
>| IPC_STAT | 把`semid_ds`结构中的数据设置为信号集的当前关联值             |
>| IPC_SET  | 在进程有足够权限的前提下，把信号量的当前关联设置为`semid_ds`数据结构中给出的值。 |
>| IPC_RMID | 删除信号量                                                   |
>
>```
>union semun
>{
>  int              val;    /* Value for SETVAL */
>  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
>  unsigned short  *array;  /* Array for GETALL, SETALL */
>  struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
>};
>
>struct semid_ds
>{
>  struct ipc_perm sem_perm;  /* Ownership and permissions */
>  time_t          sem_otime; /* Last semop time */
>  time_t          sem_ctime; /* Last change time */
>  unsigned long   sem_nsems; /* No. of semaphores in set */
>};
>
>struct ipc_perm
>{
>  key_t          __key; /* Key supplied to semget(2) */
>  uid_t          uid;   /* Effective UID of owner */
>  gid_t          gid;   /* Effective GID of owner */
>  uid_t          cuid;  /* Effective UID of creator */
>  gid_t          cgid;  /* Effective GID of creator */
>  unsigned short mode;  /* Permissions */
>  unsigned short __seq; /* Sequence number */
>};
>
>```
>
>> 还有多个命令，更多详情请`man semctl`
>
>   * 最后一个参数根据命令不同而不同
>
> * 返回值：成功返回`0`，失败返回`-1`

## semop函数

> * 功能：用来创建和访问一个信号量集
>
> * 原型：
>
>   * `int semop(int semid, struct sembuf *sops, unsigned nsops);`
>
> * 参数：
>
>   * `semid`：是该信号量的标识码，也就是semget函数的返回值
>
>   * `sops`：是个指向一个结构数值的指针，对信号量集中的信号量操作，也可同时操作。
>
>     ```
>     struct sembuf
>     {
>         unsigned short sem_num;  /* semaphore number */表示要操作的信号量集中的那个信号量
>         short          sem_op;   /* semaphore operation */对信号量的操作是什么
>         short          sem_flg;  /* operation flags */当资源不够时，不阻塞为IPC_NOWAIT，返回-1，操作错误代码为：EAGAIN:11；SEM_UNDO当一个进程终止的时候，对信号量PV操作会被撤销。将这个进程的申请资源和释放资源操作撤销掉。
>     };
>     ```
>
>     > * `sem_num`是信号量的编号
>     >
>     > * `sem_op`是信号量一次`PV操作`时加减的数值，一般只会用到两个值，一个是`-1`也就是P操作，等待信号量变得可用，另一个时`+1`，也就是我们的V操作，发出信号量已经变的可用。
>     >
>     > * `sem_flag`的两个去取值是`IPC_NOWAIT`和`SEM_UNDO`。
>     >
>     >   > 这里只说一下`SEM_UNDO`标记
>     >   >
>     >   > 如果一个进程消亡时，它曾经对这个信号量进行PV操作都回被撤销，如：当进程运行时对信号量进行了`P操作`，那么这个进程消亡时，会取消这个`P操作`。V操作同理。
>
>   * `nsops`：信号量的个数
>
> * 返回值：成功返回`0`，失败返回`-1`

## ftok

> [参考连接](https://baike.baidu.com/item/ftok/2879057)

```
#include <sys/types.h>
#include <sys/ipc.h>

key_t ftok(const char *pathname, int proj_id);
```

* 参数一：必须是一个存在的路径
* 参数二：必须是一个整型，低序的八位必须非零。

