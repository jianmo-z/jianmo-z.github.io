# day18

> `POSIX`条件变量

##本章目标

* 条件变量介绍
* 条件变量函数
* 条件变量使用规范
* 使用条件变量解决生产者消费者问题

## 条件变量介绍

> * 当一个线程互斥地访问某个变量时，它可能发现在其他线程改变状态之前，它什么也做不了。
> * 例如一个线程访问队列时，发现队列为空，它只能等待，直到其他线程将一个节点添加到队列中。这种情况就需要用到条件变量。

## 条件变量函数

> * `pthread_cond_init`：初始化一个条件变量
>
> * `pthread_cond_destroy`：销毁一个条件变量
>
> * `pthread_cond_wait`：在一个条件上等待
>
>   * `pthread_cond_wait`函数的内部干了什么？？？
>
>     * 第一件事：对`mutex`进行解锁；
>     * 第二件事：等待条件，直到有线程向它发起通知；
>     * 第三件事：重新对`mutex`进行加锁。
>
>   * 等待条件使用
>
>     > 如果被虚假的唤醒，则需要重型进入等待。则需要加`while`循环，比如惊群效应，如果有信号通知，资源只有一个，但是唤醒后发现资源已经被别的线程占有，则需要重新进入等待，即为虚假唤醒。因此，在这里不能用`if`来判断`等待条件`。
>     >
>     > ```
>     > while(等待条件)
>     > {
>     > 	pthread_cond_wait(&g_cond, &g_mutex);
>     > }
>     > ```
>
> * `pthread_cond_signal`：当条件满足时，向等待的线程通知
>
>   * 会向第一个等待的线程发起通知，如果没有一个线程处理等待条件的状态，这个通知将被忽略。
>
> * `pthread_cond_broadcast`：可能会导致惊群效应。
>
>   * 向等待的所有线程通知，广播通知会引起惊群。
>
> ```
> #include <pthread.h>
>
> int pthread_cond_destroy(pthread_cond_t *cond);
> int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
> pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
>
> int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
> int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
>
> int pthread_cond_broadcast(pthread_cond_t *cond);
> int pthread_cond_signal(pthread_cond_t *cond);
>
> 两种不同的通知方式：
> 	The pthread_cond_broadcast() function shall unblock all threads currently blocked on the specified condition variable cond.
>
> 	The pthread_cond_signal() function shall unblock at least one of  the  threads  that are  blocked on the specified condition variable cond (if any threads are blocked on cond).
> ```

## 调节变量使用规范

> * 等待条件代码
>
>   ```
>   pthread_mutex_lock(&mutex);
>   while(条件为假)
>   	pthread_cond_wait(cond, mutex);
>   修改条件
>   pthread_mutex_unlock(&mutex);
>   ```
>
> * 给条件发送信号代码
>
>   ```
>   pthread_mutex_lock(&mutex);
>   设置条件为真
>   pthread_cond_signal(cond);
>   pthread_mutex_unlock(&mutex);
>   ```

## 使用条件变量解决生产者消费者问题

>> 消费者一方
>
>```
>void * consume(void * buf)
>{
>        while(1)
>        {
>                pthread_mutex_lock(&g_mutex);//对临界区进行保护
>                while(检测条件)
>                {
>                        pthread_cond_wait(&g_cond, &g_mutex);//等待条件，直到满足
>                }
>                Do something you want to do;//进行操作
>                pthread_mutex_unlock(&g_mutex);//解锁
>        }
>        return NULL;
>}
>```
>> 生产者一方
>
>```
>void * produce(void * buf)
>{
>        while(1)
>        {
>                pthread_mutex_lock(&g_mutex);//对互斥锁进行加锁
>                
>			Do something you want to do;//进行操作
>			if(修改条件)
>                	pthread_cond_signal(&g_cond);//向等待条件的线程发送信号
>                pthread_mutex_unlock(&g_mutex);//解锁
>        }
>        return NULL;
>}
>```

##生产者消费者问题求解代码

```
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


#define ERR_EXIT(x) do{ perror(x); exit(EXIT_FAILURE);}while(0)

#define CONSUMERS_COUNT 2
#define PRODUCERS_COUNT 1

unsigned short in = 0;
unsigned short out = 0;
unsigned short produce_id = 0;
unsigned short consume_id = 0;

sem_t g_sem_full;
sem_t g_sem_empt;
pthread_mutex_t g_mutex;
pthread_cond_t g_cond;

pthread_t g_thread[CONSUMERS_COUNT + PRODUCERS_COUNT];

int nready = 0;

void * consume(void * buf)
{	       
	int arg = (int)buf;
	while(1)
	{
		pthread_mutex_lock(&g_mutex);
		while(nready == 0)
		{
			//条件变量需要和互斥锁配合使用，目的保护条件
			//解锁临界区，使其他线程可以对nready(临界变量)，以便可以其他线程进入临界区
			printf("%d > begin wait condtion(consume), nready = %d\n", (int)arg, nready);
			pthread_cond_wait(&g_cond, &g_mutex);
		}
		printf("%d > end wait condition(consume),nready = %d\n", (int)arg, nready);
		--nready;//进行消费产品操作
		pthread_mutex_unlock(&g_mutex);
	}
	return NULL;
}

void * produce(void * buf)
{
	int arg = (int)buf;
	while(1)
	{
		sleep(1);
		pthread_mutex_lock(&g_mutex);
		++nready;//进行生产产品操作
		printf("%d emit a signal nready = %d\n", (int)arg, nready);
		pthread_cond_signal(&g_cond);
		pthread_mutex_unlock(&g_mutex);

	}
	return NULL;
}
int main()
{
	int i = 0;
	int ret = 0;

	pthread_mutex_init(&g_mutex, NULL);//第二个参数表示属性，NULL使用默认属性
	pthread_cond_init(&g_cond, NULL);

	for(i = 0; i < CONSUMERS_COUNT; i++)
	{
		ret = pthread_create(&g_thread[i], NULL, consume, (void *)i);//不能&i会有静态问题
		if(ret != 0)
			ERR_EXIT("pthread_create");
	}

	sleep(1);

	for(i = 0; i < PRODUCERS_COUNT; i++)
	{
		ret = pthread_create(&g_thread[CONSUMERS_COUNT + i], NULL, produce, (void *)i);//不能&i会有静态问题
		if(ret != 0)
			ERR_EXIT("pthread_create");
	}
	for(i = 0; i < CONSUMERS_COUNT + PRODUCERS_COUNT; i++)
		pthread_join(g_thread[i], NULL);
	
	sem_destroy(&g_sem_full);
	sem_destroy(&g_sem_empt);
	pthread_mutex_destroy(&g_mutex);
	pthread_cond_destroy(&g_cond);
	return 0;
}
```



