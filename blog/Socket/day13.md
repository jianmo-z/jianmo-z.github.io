# day13

## 本章目标

* `epoll`使用
* `epoll`与`select`、`poll`区别
* `epoll LR/ET`模式

## 复习select和poll

* `select`

  * 一个进程能打开的最大文件描述符个数是有限的
  * FD_SETSIZE的限制

* `poll`

  * 一个进程能打开的最大文件描述符个数是有限的，系统能打开的最大文件描述符个数是有限的，与系统内存有关`cat /proc/sys/fs/file-max`，查看系统能打开的最大的文件描述符的个数。

    > `ulimit -n num`

* 共同点：

  > 内核需要遍历所有的文件描述符，直到找到发生事件的文件描述符。--->提高效率点，`epoll`对此进行了优化

## epoll相关函数

- `int epoll_create(int size);`//创建一个`epoll`实例,使用哈希表存储的,size是内部创建的哈希表大小
- `int epoll_create1(int flags);`//同上,使用的是红黑数,所以不再需要指定大小了.--->优先选择使用.
- `int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);`//把一个套接字添加到实例中,进行管理
- `int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);`//等待事件

> `man 2 epoll_create`

```
SYNOPSIS
    #include <sys/epoll.h>

    int epoll_create(int size);
    int epoll_create1(int flags);

DESCRIPTION
	epoll_create()  creates  an  epoll(7)  instance.   Since  Linux 2.6.8, the size argument is ignored, but must be greater than zero; see NOTES below.
	epoll_create() returns a file descriptor referring to the new epoll  instance.   This  file descriptor  is  used  for  all the subsequent calls to the epoll interface.  When no longer required, the file  descriptor  returned  by  epoll_create()  should  be  closed  by  using close(2).   When  all file descriptors referring to an epoll instance have been closed, the kernel destroys the instance and releases the associated resources for reuse.

epoll_create1()
	If flags is 0, then, other than the fact  that  the  obsolete  size  argument  is  dropped, epoll_create1()  is  the  same  as  epoll_create().  The following value can be included in flags to obtain different behavior:

EPOLL_CLOEXEC
	Set the close-on-exec (FD_CLOEXEC)  flag  on  the  new  file  descriptor.   See  the description of the O_CLOEXEC flag in open(2) for reasons why this may be useful.

RETURN VALUE
	On  success,  these  system  calls  return  a nonnegative file descriptor.  On error, -1 is returned, and errno is set to indicate the error.
```

>`man 2 epoll_ctl`

```
SYNOPSIS
       #include <sys/epoll.h>

       int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

DESCRIPTION
       This system call performs control operations on the epoll(7) instance referred to by the file descriptor epfd.  It requests that the operation op be performed for the target file descriptor, fd.

Valid values for the op argument are :

EPOLL_CTL_ADD
	Register the target file descriptor fd on the epoll instance referred to by the  file  descriptor epfd and associate the event event with the internal file linked to fd.

EPOLL_CTL_MOD
	Change the event event associated with the target file descriptor fd.

EPOLL_CTL_DEL
	Remove  (deregister)  the  target file descriptor fd from the epoll instance referred to by epfd. The event is ignored and can be NULL (but see BUGS below). The event argument describes the object linked to the file descriptor fd.   The  struct  epoll_event  is defined as :
	
    typedef union epoll_data {
        void        *ptr;
        int          fd;
        uint32_t     u32;
        uint64_t     u64;
    } epoll_data_t;

    struct epoll_event {
        uint32_t     events;      /* Epoll events */
        epoll_data_t data;        /* User data variable */
    };

//epoll_event成员events的参数
The events member is a bit set composed using the following available event types:

EPOLLIN
	The associated file is available for read(2) operations.

EPOLLOUT
	The associated file is available for write(2) operations.

EPOLLRDHUP (since Linux 2.6.17)
	Stream  socket  peer  closed  connection, or shut down writing half of connection.  (This flag is especially useful for writing simple code to detect peer shutdown when using Edge Triggered monitoring.)

EPOLLPRI
	There is urgent data available for read(2) operations.

EPOLLERR
	Error  condition  happened on the associated file descriptor.  epoll_wait(2) will always wait for this event; it is not necessary to set it in events.

EPOLLHUP
	Hang up happened on the associated file descriptor.  epoll_wait(2)  will  always  wait  for  this event; it is not necessary to set it in events.

EPOLLET
	Sets  the  Edge  Triggered behavior for the associated file descriptor.  The default behavior for epoll is Level Triggered.  See epoll(7) for more detailed information about Edge and Level  Triggered event distribution architectures.

EPOLLONESHOT (since Linux 2.6.2)
	Sets the one-shot behavior for the associated file descriptor.  This means that after an event is pulled out with epoll_wait(2) the associated file descriptor is internally disabled and no  other events  will  be  reported  by  the  epoll  interface.   The  user  must  call  epoll_ctl()  with EPOLL_CTL_MOD to rearm the file descriptor with a new event mask.
```



>`man 2 epoll_wait`

```
SYNOPSIS
	#include <sys/epoll.h>

	int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
	int epoll_pwait(int epfd, struct epoll_event *events,int maxevents, int timeout, const sigset_t *sigmask);

DESCRIPTION
	The  epoll_wait()  system call waits for events on the epoll(7) instance referred to by the file descriptor epfd.  The memory area pointed to by events will contain  the  events  that will  be available for the caller.  Up to maxevents are returned by epoll_wait().  The maxevents argument must be greater than zero.

	The timeout argument specifies the minimum number of milliseconds  that  epoll_wait()  will block.   (This  interval  will  be  rounded  up to the system clock granularity, and kernel scheduling delays mean that the blocking interval may overrun by a small amount.)  Specifying  a  timeout of -1 causes epoll_wait() to block indefinitely, while specifying a timeout equal to zero cause epoll_wait() to return immediately, even if no events are available.

The struct epoll_event is defined as :

    typedef union epoll_data {
        void    *ptr;
        int      fd;
        uint32_t u32;
        uint64_t u64;
    } epoll_data_t;

    struct epoll_event {
        uint32_t     events;    /* Epoll events */
        epoll_data_t data;      /* User data variable */
    };

	The data of each returned structure will contain  the  same  data  the  user  set  with  an epoll_ctl(2)  (EPOLL_CTL_ADD,EPOLL_CTL_MOD)  while  the  events  member  will  contain  the returned event bit field.
```

## epoll实现并发服务器--->优

> `epoll`实现服务器会占用五个套接字，`标准输入`、`标准输出`、`标准错误`、`服务器监听套接字`和`epoll的句柄`。剩下的，所以当进程的``最大套接字的个数 - 5`，就是`epoll`可以连接的最大客户端个数了。`epoll`比`poll`效率要高。 
>
> <font size=5>[点击查看epollsrv代码](./epollsrv.md)</font>

## epoll、select和poll的区别

* 相比于`select`与`poll`、`epoll`最大的好处载于它不会随着监听套接字`fd`数目的增多而降低效率。

* 内核中的`select`与`poll`的实现是采用轮询来处理的，轮询的`fd`数目越多，自然消耗时间越长

* `epoll`的实现是基于回调的，如果`fd`有期望的事件发生就通过回调函数将其加入`epoll`就绪队列中，也就是说它只关心`活跃`的fd，与`fd`的数目无关。

* `内核/用户空间` 内存拷贝问题，如何让内核把`fd`消息通知给用户空间呢？

  > 在这个问题上`select/poll`采用了内存拷贝方法，而`epoll`采用了共享内存的方法。

* `epoll`不仅会告诉应用程序有`I/O`事件，还会告诉应用程序相关的信息，这些信息是应用程序填充的，因此根据这些信息应用程序就能直接定位到事件，而不必遍历整个`fd`集合了。

> 学后感！！！
>
> 个人感觉`epoll`的机制和`Qt的信号和槽`的处理机制很有共同点，这里说的是思想方面，不是底层代码的实现和一些细节性的问题，比如说Qt的信号和槽的设计思想，当有信号时，才会去调用槽(槽就是一回调函数的，入口指针)，节省了不停的轮巡遍历的操作，大大节省了CPU和内存的资源，因为你活跃起来了我再去处理你，否则的话，你就老老实实的待在哪里等信号。个人观点如有理解错误，请多多包含，同时希望可以指正。

##epoll LT/ET模式

* `EPOLLLT`：电平触发模式
* `EPOLLET`：边沿触发模式，效率高。

## EPOLLLT模式

> 电平/水平触发模式，完全靠`kernel epoll`驱动，应用程序只需要处理从`epoll_wait`返回的fds，这些`fds`我们认为它们处于就绪状态

## EPOLLET模式

> 边沿触发模式，是一把双刃剑，如果处理不当可能会导致效率不如，`LT模式`。如果需要高效率，则程序员则需要更高的要求，来维护`ET模式`
>
> ​	此模式下，系统仅通知应用程序那些`fds`变成了就绪状态，一旦`fd`变成就绪状态，`epoll`将不再关注这个`fd`的任何状态信息(从`epoll`队列中移除)，直到应用程序通过读写操作触发`EAGAIN`状态，`epoll`认为这个`fd`又变为空闲状态，那么`epoll`又重新关注这个`fd`的状态变话(添加到`epoll`队列中)
>
> ​	随着`epoll_wait`的返回，队列中的`fds`是在减少的，所以在大并发的系统中，`EPOLLET`模式更具有优势，但是对程序员的要求也变高了。（emmm， 这是什么鬼啊），程序员需要对程序维护，避免读取一部分数据后剩下数据无法读出导致阻塞。
