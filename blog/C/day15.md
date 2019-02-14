# day15

> `POSIX`线程

## 本章目标

* `POSIX`线程库相关函数
* 用线程实现回射客户/服务器

## POSIX线程库

> * 与线程有关的函数构成一个完整的系列绝大多数函数的名字都是以`pthread_`开头的
> * 要使用这些函数库，，要通过引入头文件`<pthread.h>`
> * 链接这些线程函数库时要使用编译器命令的`-lpthread`选项

## pthread_create函数

> * 功能：创建一个新的线程
>
> * 原型：
>
>   ```
>   #include <pthread.h>
>
>   int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
>
>   Compile and link with -pthread.
>   ```
>
> * 参数：
>
>   * `thread`：返回线程`ID`
>   * `attr`：设置线程的属性，`attr`为`NULL`表示使用默认属性
>   * `start_routine`：是个函数地址，线程启动后要执行的函数
>   * `arg`：传给线程启动函数的参数
>
> * 返回值：成功返回`0`，失败返回错误码保存在`errno`中。
>
> * 错误检查
>
>   * 传统的一些函数时，成功返回`0`，失败返回`-1`，并且对全局变量`errno`赋值以指示错误。
>   * `pthreads`函数出错时不会设置全局变量`errno`(而大部分其他的`POSIX`函数都会这样做，设置全局的errno)，而是将错误代码通过返回值返回；
>   * `pthreads`同样也提供了线程内的`errno`变量，每一个线程都有自己的`errno`，以支持其他使用`errno`的代码。用于`pthreads`函数的错误，建议通过返回值来判定，因为读取返回值要比读取线程内的`errno`变量的开销更小。

## pthread_exit函数

> * 功能：线程终止，在线程中调用该函数。
>
> * 原型：
>
>   ```
>   #include <pthread.h>
>
>   void pthread_exit(void *retval);
>
>   Compile and link with -pthread.
>   ```
>
> * 参数：
>
>   * `retval`：`retval`不要指向一个局部变量
>
> * 返回值：无返回值跟进程一样，线程结束的时候无法返回到它的调用者

## pthread_join函数

> * 功能：线程同步
>
> * 原型：
>
>   ```
>   #include <pthread.h>
>
>   int pthread_join(pthread_t thread, void **retval);
>
>   Compile and link with -pthread.
>   ```
>
> * 参数：
>
>   * `thread`：等待的线程`ID`
>   * `retval`：线程返回的参数，是`pthread_exit`的第二个参数的返回值。
>
> * 返回值：成功返回`0`，失败返回错误码保存在`errno`

##pthread_detach函数

> * 功能：新线程脱离主线程，避免僵线程出现。
>
>   ```
>   SYNOPSIS
>       #include <pthread.h>
>
>       int pthread_detach(pthread_t thread);
>
>       Compile and link with -pthread.
>
>   DESCRIPTION
>   	The pthread_detach() function marks the thread identified by thread as detached.  When a detached thread terminates, its resources are  automatically  released  back  to  the system without the need for another thread to join with the terminated thread. Attempting to detach an already detached thread results in unspecified behavior.
>          
>   RETURN VALUE
>   	On  success, pthread_detach() returns 0; on error, it returns an error number.
>   ```

## pthread_self函数

> * 功能：返回线程ID
>
> * 原型：
>
>   ```
>   #include <pthread.h>
>
>   pthread_t pthread_self(void);
>
>   Compile and link with -pthread.
>   ```
>
> * 返回值：成功返回线程ID，emmm这个函数很皮，说明手册中是这样说的
>
>   ```
>    This function always succeeds, returning the calling thread's ID.
>   ```

## pthread_cancel函数

> * 功能：取消一个执行中的线程，即杀死线程
>
> * 原型：
>
>   ```
>   #include <pthread.h>
>
>   int pthread_cancel(pthread_t thread);
>
>   Compile and link with -pthread.
>   ```
>
> * 参数
>
>   * `thread`：线程`ID`
>
> * 返回值：成功返回`0`，失败返回错误码。

## strerror函数

>将`errnor`的宏定义返回
>
>```
>#include <string.h>
>
>char *strerror(int errnum);
>
>int strerror_r(int errnum, char *buf, size_t buflen); /* XSI-compliant */
>
>char *strerror_r(int errnum, char *buf, size_t buflen); /* GNU-specific */
>```

## 线程、进程对比

|            | 进程                                                         | 线程                                                         |
| ---------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| ID号类型   | `pid_t`                                                      | `thread_t`                                                   |
| 创建       | `fork`                                                       | `pthread_create`                                             |
| 同步       | `waitpid`                                                    | `pthread_join`                                               |
| 退出：自杀 | `exit`、在`main`函数中调用`return`                           | `pthread_exit`、在线程的入口函数中调用`return`               |
| 僵***      | 僵尸进程：子进程先于父进程死亡，父进程尚未回收子进程资源时，这个时候的子进程就是僵尸进程了。`waitpid`回收子进程资源避免僵尸进程出现。 | 僵线程：新创建的线程结束，主线程没有调用`pthread_join`，新创建的线程就是处于僵线程的状态 |
| 退出：他杀 | `kill`杀死别的进程                                           | `pthread_cancel`杀死别的线程                                 |
|            |                                                              |                                                              |