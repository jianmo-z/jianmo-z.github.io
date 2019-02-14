# day12

<font size=4>`POSIX`消息队列</font>

## 本章目标

* `POSIX`消息队列相关函数
* `POSIX`消息队列示例

## System V IPC 和 POSIX IPC

> * `System V IPC`
>   * 消息队列
>   * 共享内存
>   * 信号量
> * `POSIX IPC`
>   * 消息队列
>   * 共享内存
>   * 信号量
>   * 互斥锁
>   * 条件变量
>   * 读写锁
>   * 自旋锁
>   * 文件锁

## mq_open函数

> * 功能：用来创建和访问一个消息队列，编译时需要连接`-lrt`
>
> * 原型：
>   * `mqd_t  mq_open(const char * name, int oflag);`
>   * `mqd_t mq_open(const char * name, int oflag, mode_t mode, struct mq_attr * sttr);`
>
> * 参数：
>   * `name`：某个消息队列的名字，命名有规则，使用须注意
>     * 必须以`/`打头，并且后续不能有其他的`/`，例如：`/somename`
>     * 长度不能超过`NAME_MAX`，不同的环境值不同。
>   * `oflag`：与`open`函数蕾西，可以是`O_RDONLY`、`O_WRONLY`和`O_RDWR`，还可以按位或上`O_CREAT`、`O_EXCL`和`O_NONBLOCK`等。
>   * `mode`：如果`oflag`指定了`O_CREAT`，需要设置`mode`。
>
> * 返回值：成功返回消息队列描述符，失败返回`-1`
>
> * 查看消息队列
>
>   * 如果`/dev/mqueue`则需要挂载。删除`/dev/mqueue下的文件`，就删除了这个消息队列。即使没有挂载这个消息队列仍然存在只是自己不可见而已。
>
>   * ```
>     # mkdir /dev/mqueue
>     # mount -t mqueue none /dev/mqueue
>     ```

## mq_close函数

> * 功能：关闭消息队列
> * 原型：
>   * `mqd_t mq_close(mqd_t mqdes);`
> * 参数：
>   * `mqdes`：消息队列描述符
> * 返回值：成功返回`0`，失败返回`-1`。

##mq_unlink函数

> * 功能：删除消息队列，引用计数减一，直到引用计数为0时才会真正删除。
> * 原型：
>   * `mqd_t mq_unlink(const char * name);`
> * 参数：
>   * `name`：消息队列的名字
> * 返回值：成功返回`0`，失败返回`-1`。

## mq_getattr/mq_setattr函数

> * 功能：获取/设置消息队列属性
>
> * 原型：
>
>   * `mq_getattr`：获取属性
>   * `mq_setattr`：设置属性
>
>   ```
>   int mq_getattr(mqd_t mqdes, struct mq_attr *attr);
>   int mq_setattr(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr);
>   Link with -lrt.
>
>   struct mq_attr {
>       long mq_flags;       /* Flags: 0 or O_NONBLOCK */阻塞和非阻塞模式
>       long mq_maxmsg;      /* Max. # of messages on queue */消息队列中容纳的最大消息个数
>       long mq_msgsize;     /* Max. message size (bytes) */每条消息的最大长度
>       long mq_curmsgs;     /* # of messages currently in queue */队列中当前消息的个数
>   };
>   ```
>
> * 返回值：成功返回`0`，失败返回`-1`。

## mq_send函数

> * 功能：发送消息到消息队列中
>
> * 原型：
>
>   ```
>   #include <mqueue.h>
>
>   int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio);
>
>   #include <time.h>
>   #include <mqueue.h>
>
>   int mq_timedsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio, const struct timespec *abs_timeout);
>
>   Link with -lrt.
>   ```
>
> * 参数：
>
>   * `mqdes`：消息队列描述符
>   * `msg_ptr`：指向消息的指针
>   * `msg_len`：消息长度
>   * `msg_prio`：消息优先级，大于等于`0`的一个数。
>
> * 返回值：成功返回`0`，失败返回`-1`

## mq_recivse函数

> * 功能：从消息队列中接收一个消息，优先接收为优先级最高的。
>
> * 原型：
>
>   ```
>   #include <mqueue.h>
>
>   ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio);
>
>   #include <time.h>
>   #include <mqueue.h>
>
>   ssize_t mq_timedreceive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio, const struct timespec *abs_timeout);
>
>   Link with -lrt.
>   ```
>
> * 参数：
>
>   * `mqdes`：消息队列描述符
>   * `msg_ptr`：返回接收到的消息
>   * `msg_len`：消息长度，一定要等于消息队列中最大的消息队列的长度，通过`mq_getattr`获取最大长度。
>   * `msg_prio`：返回接收道德消息优先级
>
> * 返回值：成功返回接收到的消息字节数，失败返回`-1`
>
> * 注意：**返回指定消息队列中最高优先级的最早消息。**

## mq_notify函数

> * 功能：建立或者删除消息到达通知事件
>
> * 原型：
>
>   ```
>   #include <mqueue.h>
>
>   int mq_notify(mqd_t mqdes, const struct sigevent *sevp);
>
>   Link with -lrt.
>   ```
>
> * 参数：
>
>   * `mqdes`：消息队列描述符
>
>   * `sevp`：
>
>     * 非空表示当前消息到达且消息队列先前为空，那么将得到通知
>
>     * NULL表示撤销已注册的通知
>
>     * `man sigevent`获取结构体信息
>
>       ```
>       union sigval {          /* Data passed with notification */
>           int     sival_int;         /* Integer value */
>           void   *sival_ptr;         /* Pointer value */
>       };
>
>       struct sigevent {
>           int          sigev_notify; /* Notification method */通知的方式，信号或者线程
>           int          sigev_signo;  /* Notification signal */
>           union sigval sigev_value;  /* Data passed with notification */
>           void       (*sigev_notify_function) (union sigval); /* Function used for thread notification (SIGEV_THREAD) */
>           void        *sigev_notify_attributes; /* Attributes for notification thread (SIGEV_THREAD) */
>           pid_t        sigev_notify_thread_id; /* ID of thread to signal (SIGEV_THREAD_ID) */
>       };
>       ```
>
>       * `sigev_notity`成员量取值
>         * `SIGEV_NONE`：不能通知
>         * `SIGEV_SIGNAL`：信号方式通知，需要指定`sigev_signo`和`sigev_value`参数。
>         * `SIGEV_THREAD`：线程方式通知，需要指定`(*sigev_notify_function) (union sigval)`、`*sigev_notify_attributes`和`sigev_notify_thread_id`参数。
>
> * 返回值：成功返回`0`，失败返回`-1`。
>
> * 通知方式：
>
>   * 产生一个信号
>   * 创建一个线程执行一个指定的函数。
>
> * `mq_notify`注意点
>
>   * 任何时刻只能有一个进程可以被注册为接收某个给定队列的通知
>   * 当有一个信号到达某个先前为空的队列，而且已有一个进程被注册为接收该队列的通知时，只是没有任何线程阻塞在该队列的`mq_receive`调用的前提下，通知才会发出
>   * 当通知被发送给它的注册进程时，其注册被撤销，进程必须在次调用`mq_notify`以重新注册(如果需要的话)重新注册要放在从消息队列读出消息之前而不是之后。