# day07

> `System V`共享内存

##本章目标

* 共享内存数据结构
* 共享内存函数
* 共享内存示例

## 共享内存数据结构

```
struct shmid_ds {
    struct ipc_perm shm_perm;    /* Ownership and permissions */
    size_t          shm_segsz;   /* Size of segment (bytes) */共享内存段的大小
    time_t          shm_atime;   /* Last attach time */最后一次映射共享内存的时间
    time_t          shm_dtime;   /* Last detach time */最后一次解除映射的时间
    time_t          shm_ctime;   /* Last change time */最后一次共享内存状态改变的时间爱你
    pid_t           shm_cpid;    /* PID of creator */共享内存创建者的进程PID
    pid_t           shm_lpid;    /* PID of last shmat(2)/shmdt(2) */最后一次连接/脱离共享内存的PID
    shmatt_t        shm_nattch;  /* No. of current attaches */当前共享内存被连接的次数
    ...
};

struct ipc_perm {
    key_t          __key;    /* Key supplied to shmget(2) */
    uid_t          uid;      /* Effective UID of owner */
    gid_t          gid;      /* Effective GID of owner */
    uid_t          cuid;     /* Effective UID of creator */
    gid_t          cgid;     /* Effective GID of creator */
    unsigned short mode;     /* Permissions + SHM_DEST and
    SHM_LOCKED flags */
    unsigned short __seq;    /* Sequence number */
};
```

## 共享内存函数

> ```
> #include <sys/ipc.h>
> #include <sys/shm.h>
>
> int shmget(key_t key, size_t size, int shmflg);//创建或者访问一个共享内存端
> void * shmat(int shmid, const void * shmaddr, int shmflg);//将一个共享内存端映射到进程的某个空间
> int shmdt(const void * shmaddr);//将共享内存段从进程中脱离
> int shmctl(int shmid, int cmd, struct shmid_ds *buf);//共享内存端的控制函数
> ```

## shmget函数

> * 功能：用来创建/打开共享内存，与`System V`消息队列的`msgget`类似。
> * 原型：
>   * `int shmget(key_t key, size_t size, int shmflg);`
> * 参数：
>   * `key`：这个共享内存段名字
>   * `size`：共享内存大小
>   * `shmflg`：由九个权限标志构成，它们的用法和创建文件时使用的`mode`模式标志一样的
> * 返回值：成功返回一个非负整数，即该共享内存段的标识码；失败返回`-1`。

##shmat函数

> * 功能：将共享内存段连接到进程地址空间
>
> * 原型：
>
>   * `void * shmat(int shmid, const void * shmaddr, int shmflg);`
>
> * 参数：
>
>   * `shmid`：共享内存标识
>
>   * `shmaddr`：指定连接的地址
>
>   * `shmflg`：它的两个可能取值是`SHM_RND`和`SHM_RDONLY`，为0时可读可写。
>
>| SHM_RND    | 当shmaddr不为NULL，且设置了该标记，则连接的地址会自动向下调整为SHMLBA的整数倍，公式`shmaddr - (shmaddr % SHMLBA)`，`%`取余。 |
>| ---------- | ------------------------------------------------------------ |
>| SHM_RDONLY | 表示连接操作用来只读共享内存的                               |
>> 其实还有其他的可能取值，详情请参考`man shmat`
>
> * 返回值：成功返回一个指针，指向共享内存第一个字节，失败返回`-1`
>
> * 函数说明：
>
>   * `shamaddr`为`NULL`，内核自动选择一个地址，一般使用为`NULL`
>   * `shmaddr`不为`NULL`且`shmflg`无`SHM_RND`标记，则以`shmaddr`为连接地址
>   * 当`shmaddr`不为`NULL`，且设置了该标记，则连接的地址会自动向下调整为`SHMLBA`的整数倍，公式`shmaddr - (shmaddr % SHMLBA)`，`%`取余。
>   * `shmflg = SHM_RDONLY`，表示连接操作用来只读共享内存的

## shmdt函数

> * 功能：将共享内存段与当前进程脱离
> * 原型：
>   * `int shmdt(const void * shmaddr);`
> * 参数：
>   * `shmaddr`：由`shmat`返回的指针
> * 返回值：
>   * 成功返回`0`，失败返回`-1`
> * 注意：将共享内存段与当前进程脱离不等于删除共享内存段。

##shmctl函数

> * 功能：用来控制一个共享内存，`ipcrm -m shmid`也可以删除共享内存
>
> * 原型：
>
>   * `int shmctl(int shmid, int cmd, struct shmid_ds *buf);`
>
> * 参数：
>
>   * `shmid`：由`shmget`返回的共享内存标识码
>
>   * `cmd`：将要采取的动作(有三个可取值)
>
>| cmd(命令) | 说明                                                         |
>| --------- | ------------------------------------------------------------ |
>| IPC_STAT  | 把shmid_ds结构中的数据设置为共享内存的当前关联值             |
>| IPC_SET   | 在进程有足够权限的前提下，把共享内存的当前关联设置为`shmid_ds`数据结构中给出的值 |
>| IPC_RMID  | 删除共享内存段                                               |
>
>   * `buf`：指向一个保存着共享内存的模式状态和访问权限的数据结构。
>
> * 返回值：成功返回`0`，失败返回`-1`。
