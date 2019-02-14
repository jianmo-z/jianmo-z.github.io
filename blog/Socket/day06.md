# day06

参考链接：

https://www.cnblogs.com/yuxingfirst/p/3165407.html

## 本章目标

* `TCP`回射客户/服务器

* `TCP`是个流协议

* 僵尸进程与`SIGCHLD`信号

## TCP是一个流协议

  * `TCP`是**基于字节流传输的**，只维护发送出去多少，确认收到了多少，没有维护消息与消息之间的边界，因而可能**导致粘包问题**，所以需要自己维护。
  * 粘包问题解决方法是**在应用层维护消息边界**。
      * 粘包问题
          * 定长包
          * 使用`\n`作为区分消息和消息的边界

## 僵尸进程的避免

> 僵尸进程：子进程死后，父进程未给子进程收尸，即父进程未回收子进程的资源
>
> 孤儿进程：父进程先于子进程死亡，子进程没有了父进程，成为了孤儿进程，而`linux`操作系统有一个孤儿院，进程`ID为1的进程`，会成为孤儿进程的父进程，使孤儿进程的资源可以让父进程回收

```
[pip@localhost code]$ ps -ef | grep echosrv
pip       4213  4145  0 17:40 pts/1    00:00:00 vim echosrv.c
pip       5237  4240  0 18:11 pts/2    00:00:00 ./echosrv
pip       5240  5237  0 18:11 pts/2    00:00:00 [echosrv] <defunct>
pip       5245  4289  0 18:11 pts/3    00:00:00 grep --color=auto echosrv
```

> 第三行即为僵尸进程。

* `SIGCHLD`信号

````
singal(SIGCHLD, SIG_IGN)；//忽略SIGCHLD信号
signal(SIGCHLD, handle_signld);//捕捉SIGCHLD信号，并对其进行处理，handle_signld是一个函数指针，用来处理SIGCHLD信号，返回值为零，参数为int型
````

* `wait()`函数

```
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
```

> `pid_t wait(int *status);`获取子进程的状态，传入`NULL`即为不关心子进程状态。

* 第一种处理结果

  ```
  pip       4213  4145  0 17:40 pts/1    00:00:01 vim echosrv.c
  pip       5378  4240  0 18:13 pts/2    00:00:00 ./echosrv
  pip       5386  4289  0 18:13 pts/3    00:00:00 grep --color=auto echosrv
  ```

* 第二种处理结果

  ```
  pip       4213  4145  0 17:40 pts/1    00:00:01 vim echosrv.c
  pip       5446  4240  0 18:15 pts/2    00:00:00 ./echosrv
  pip       5454  4289  0 18:15 pts/3    00:00:00 grep --color=auto echosrv
  ```

  > 由上两种处理结果发现僵尸进程都不存在了，则使用``SIGCHLD`可以避免僵尸进程的出现。

  > 如果有多个子进程那么就会出现问题，`wait`只会处理第一个返回的子进程，然后返回，如果需要处理多个子进程需要使用`waitpid`等待指定的只进程返回。

  [点击查看相关博客](http://39.106.165.33/#!./blog/C/3.C语言的多进程.md)

## 多个子进程的僵尸进程处理

> 如果有多个子进程的话，上述两种方式都可能会产生僵尸进程，相信如果是第一种情况对于多个子进程处理是肯定有僵尸进程的，因为`wait`只等待一个子进程就退出了，**而虽然`waitpid`可以等待多个子进程，但是如果子进程同时发送`SIGCHLD`信号，那么父进程可能不能接收到子进程的`SIGCHLD`信号，导致不能对子进程的资源进行回收。使子进程成为了僵尸进程。**

* 更加好的回收的子进程资源的方式出现了

  ```
  void signal_handle(int sign)
  {
  	//wait(NULL);//只接受一个子进程的的SIGCHLD然后直接返回
  	//waitpid(-1, NULL, WNOHANG);//可能会有僵尸进程的存在，因为进程发送了SIGCHLD信号但是没有接收到，无法处理导致了僵尸进程的存在
  	while(waitpid(-1, NULL, WNOHANG) > 0);//如果没有子进程退出循环,彻底避免僵尸进程
  }
  ```

  >**RETURN VALUE//返回值**
  >       **wait():** on success, returns the process ID of the terminated child; on error, -1 is returned.
  >       **waitpid():**  on  success, returns the process ID of the child whose state has changed; if WNOHANG was specified and one or more child(ren) specified by pid exist, but have not yet changed state, then 0 is returned.  On error, -1 is returned.

  ​