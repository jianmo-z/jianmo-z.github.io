# day11

## 本章目标

* 套接字`I/O`超时设置方法
* 用`select`实现超时
  * `read_timeout`函数封装
  * `write_timeout`函数封装
  * `accept_timeout`函数封装
  * `connect_timeout`函数封装

## 套接字I/O超时设置方法

> 一共有三种方法

* `alarm`：闹钟定时
* 套接字选项：移植性比较差
  * `SO_SNDTIMEO`
  * `SO_RCVTIMEO`
* `select`：**优**

## 用select实现超时

> 自定义`read_timeout`、`write_timeout`、`accept_timeout`和`connect_timeout`函数对`select`函数进行了封装，所需要参数为`文件描述符`和`时间长度`

>    int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
>    
>    The timeout
>    	The time structures involved are defined in <sys/time.h> and look like
>    
>        struct timeval {
>        	long    tv_sec;         /* seconds */
>       		long    tv_usec;        /* microseconds */
>        };
>    
>    and
>    
>    	struct timespec {
>    		long    tv_sec;         /* seconds */
>    		long    tv_nsec;        /* nanoseconds */
>    	};
>    

##errno.h头文件

> 里面设置了很多的错误信息，可以通过错误信息来对函数的成功与否，以及错误原因进行详细的接收。
>
> 参考文档：
>
> ​	http://blog.163.com/wangxun_2233/blog/static/5511009120094795756775
>
> 这个博客写的很详细，不过这个没必须记，会查就行了

## getsockopt函数

> 参考文档：
>
> ​	https://blog.csdn.net/daiyudong2020/article/details/51893399
>
> `level`：设置为`SOL_SOCKET`和`IPPROTO_TCP`，详情参考上面的链接，一般设置为`SOL_SOCKET`。
>
> `optname`：参数`SO_ERROR`获取待处理错误并清除。
>
> 

```
NAME
       getsockopt, setsockopt - get and set options on sockets

SYNOPSIS
       #include <sys/types.h>          /* See NOTES */
       #include <sys/socket.h>

       int getsockopt(int sockfd, int level, int optname,
                      void *optval, socklen_t *optlen);
       int setsockopt(int sockfd, int level, int optname,
                      const void *optval, socklen_t optlen);

DESCRIPTION
	getsockopt()  and setsockopt() manipulate options for the socket referred to by the file descriptor sockfd.  Options may exist at multiple protocol levels; they are always present at the uppermost socket level.
	When manipulating socket options, the level at which the option resides and the name of the option  must  be  specified.   To  manipulate options at the sockets API level, level is specified as SOL_SOCKET.  To manipulate options at any other level the protocol number of the appropriate protocol controlling the option is supplied.  For example, to indicate that an option is to be interpreted by the TCP protocol, level should be set to the protocol number of TCP; see getprotoent(3).
	The arguments optval and optlen are used to access option values for setsockopt().  For getsockopt() they identify a buffer  in  which  the  value  for the requested option(s) are to be returned.  For getsockopt(), optlen is a valueresult argument, initially containing the size of the buffer pointed to by optval, and modified on return  to  indicate the actual size of the value returned.  If no option value is to be supplied or returned, optval may be NULL.
	Optname  and  any  specified options are passed uninterpreted to the appropriate protocol module for interpretation. The include file <sys/socket.h> contains definitions for socket level options, described below.   Options  at  other protocol levels vary in format and name; consult the appropriate entries in section 4 of the manual.
	Most  socket-level  options utilize an int argument for optval.  For setsockopt(), the argument should be nonzero to enable a boolean option, or zero if the option is to be disabled.
	For a description of the available socket options see socket(7) and the appropriate protocol man pages.

RETURN VALUE
	On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
```

## 一个函数fcntl

> 参考文档：
>
> https://blog.csdn.net/fengxinlinux/article/details/51980837
>
> `fcntl`函数，`man 3 fcntl`，`fcntl`可实现对指定文件描述符的各种操作
>
> 以下为该函数的`man手册`的说明，如果看不懂请到上面的连接中去学习该函数，我觉得上面的博客已经写的还不错吧，而且我的英语不太好，所以我就不卖弄自己垃圾的英语了... ...。

```
ROLOG
       This  manual  page  is part of the POSIX Programmer's Manual.  The Linux implementation of this interface may differ
       (consult the corresponding Linux manual page for details of Linux behavior), or the interface may not be implemented
       on Linux.

NAME
       fcntl - file control

SYNOPSIS
       #include <unistd.h>
       #include <fcntl.h>

       int fcntl(int fildes, int cmd, ...);

DESCRIPTION
       The  fcntl()  function  shall  perform  the  operations described below on open files. The fildes argument is a file
       descriptor.

       The available values for cmd are defined in <fcntl.h> and are as follows:

F_DUPFD//复制文件描述符
	Return a new file descriptor which shall be the lowest numbered available (that is, not  already  open)  file descriptor  greater  than  or equal to the third argument, arg, taken as an integer of type int. The new file descriptor shall refer to the same open file description as the original file descriptor, and shall share any locks.  The  FD_CLOEXEC  flag  associated with the new file descriptor shall be cleared to keep the file open across calls to one of the exec functions.

F_GETFD//获取文件描述符
	Get the file descriptor flags defined in <fcntl.h> that are associated with the file descriptor fildes.  File descriptor  flags  are associated with a single file descriptor and do not affect other file descriptors that refer to the same file.

F_SETFD//设置文件描述符
	Set the file descriptor flags defined in <fcntl.h>, that are associated with fildes, to the  third  argument, arg,  taken as type int. If the FD_CLOEXEC flag in the third argument is 0, the file shall remain open across the exec functions; otherwise, the file shall be closed upon successful execution of one of  the  exec  func‐ tions.

F_GETFL//获取文件状态标志
	Get  the  file  status flags and file access modes, defined in <fcntl.h>, for the file description associated with fildes. The file access modes can be extracted from the return value using the mask O_ACCMODE, which  is defined in <fcntl.h>. File status flags and file access modes are associated with the file description and do not affect other file descriptors that refer to the same file with different open file descriptions.

F_SETFL//设置文件状态标志
	Set the file status flags, defined in <fcntl.h>, for the file description associated  with  fildes  from  the corresponding  bits in the third argument, arg, taken as type int. Bits corresponding to the file access mode and the file creation flags, as defined in <fcntl.h>, that are set in arg shall be ignored. If  any  bits  in arg other than those mentioned here are changed by the application, the result is unspecified.

F_GETOWN//获取当前接收SIGIO和SIGURG信号的进程嗯IO和进程组ID
	If  fildes  refers  to a socket, get the process or process group ID specified to receive SIGURG signals when out-of-band data is available. Positive values indicate a process ID; negative values, other than  -1,  indi‐cate a process group ID. If fildes does not refer to a socket, the results are unspecified.

F_SETOWN//设置当前接收SIGIO和SIGURG信号的进程嗯IO和进程组ID
        If  fildes  refers  to a socket, set the process or process group ID specified to receive SIGURG signals when out-of-band data is available, using the value of the third argument, arg, taken as type int. Positive values indicate  a process ID; negative values, other than -1, indicate a process group ID. If fildes does not refer to a socket, the results are unspecified.

       The following values for cmd are available for advisory record locking. Record locking shall be supported for  regular files, and may be supported for other files.
      
F_GETLK//获取文件锁
	Get  the  first  lock  which  blocks  the  lock description pointed to by the third argument, arg, taken as a pointer to type struct flock, defined in <fcntl.h>. The information retrieved shall overwrite the information passed  to  fcntl()  in the structure flock. If no lock is found that would prevent this lock from being created, then the structure shall be left unchanged except for the lock type which shall be set to F_UNLCK.

F_SETLK//设置文件锁
	Set or clear a file segment lock according to the lock description pointed to by  the  third  argument,  arg, taken  as  a pointer to type struct flock, defined in <fcntl.h>. F_SETLK can establish shared (or read) locks (F_RDLCK) or exclusive (or write) locks (F_WRLCK), as well as  to  remove  either  type  of  lock  (F_UNLCK). F_RDLCK, F_WRLCK, and F_UNLCK are defined in <fcntl.h>.  If a shared or exclusive lock cannot be set, fcntl() shall return immediately with a return value of -1.

F_SETLKW//与F_SETLK设置文件锁类似，不过等待返回
	This command shall be equivalent to F_SETLK except that if a shared or exclusive lock  is  blocked  by  other locks, the thread shall wait until the request can be satisfied. If a signal that is to be caught is received while fcntl() is waiting for a region, fcntl() shall be interrupted. Upon return  from  the  signal  handler, fcntl() shall return -1 with errno set to [EINTR], and the lock operation shall not be done.
```


## read_timeout函数封装

```
int read_timeout(int fd, unsinged int wait_seconds)
{
        int ret = 0;
        if(wait_seconds > 0)
        {
                fd_set rset;
                FD_ZERO(&rset);
                FD_SET(fd, &rset);//把fd添加到集合当中
                struct timeval time;
                time.tv_sec = wait_seconds;
                time_tv_usec = 0;
                do
                {       //超时检测，时间到了，却未发生可读事件，返回0
                        ret = select(fd + 1, &rset, NULL, NULL, &timeout);
                }while(ret < 0 && errno == EINTR);//中断后重启
                //如果ret < 0 则说明select函数是被中断的
                //errno是记录程序的最后一次错误代码
                //EINTR:当阻塞于某个慢系统调用的一个进程捕获某个信号且相应信号处理函数返回时，该系统调用可能返回一个EINTR错误。（查看网络编程的day09）
                if(ret == 0)
                {
                        ret = -1;
                        errno = ETIMEOUT;
                }
                else if(ret == 1)
                {
                        ret = 1;
                }
        }
        return ret;
}
```

## 剩下三个函数的封装

> 剩下的三个函数的封装在下载文件中，`write_timeout`和`read_timeout`类似，其他两个有所不同

<a href="./Download/day11.tar.gz"><font color="red" size=4> 点击下载源文件</font></a>

