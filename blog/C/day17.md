# day17

> `POSIX`信号量与互斥锁

## 本章目标

* `POSIX`信号量相关函数
* `POSIX`互斥锁相关函数
* 生产者消费者问题
* 自旋锁与读写锁介绍

## POSIX信号量相关函数

> * `sem_open`：//初始化打开或者一个存在的有名信号量
>
> * `sem_close`：//关闭一个信号量
>
> * `sem_unlink`：//将一个信号量的引用计数减一，减为零时删除。
>
>   ```
>   #include <fcntl.h>           /* For O_* constants */
>   #include <sys/stat.h>        /* For mode constants */
>   #include <semaphore.h>
>
>   sem_t *sem_open(const char *name, int oflag);
>   sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
>   int sem_close(sem_t *sem);
>   int sem_unlink(const char *name);
>
>   Link with -pthread.
>   ```
>
>   ​
>
>
> * `sem_init`：//初始化一个匿名的信号量，无名信号量能不能用于进程、线程间通信，主要取决于第二个参数，如果非零，且第一个参数的信号量在共享内存上则可以用于进程、线程间通信。
>
> * `sem_destroy`：//无名信号量的销毁
>
>   ```
>   #include <semaphore.h>
>
>   int sem_init(sem_t *sem, int pshared, unsigned int value);
>   int sem_destroy(sem_t *sem);
>
>   Link with -pthread.
>   ```
>
>   ​
>
> * `sem_wait`：信号量的`V操作`，即可用于有名也可用于无名信号量。
>
> * `sem_post`：信号量的`P操作`，即可用于有名也可用于无名信号量。
>
>   ```
>   #include <semaphore.h>
>
>   int sem_wait(sem_t *sem);
>   int sem_trywait(sem_t *sem);
>   int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
>
>   int sem_post(sem_t *sem);
>
>   Link with -pthread.
>   ```

## POSIX互斥锁

> * `pthread_mutex_init`：初始化一个互斥锁，此互斥锁是无名的，但是可以用于不同的进程、线程间。
>
> * `pthread_mutex_lock`：锁定操作
>
> * `pthread_mutex_unlock`：解锁操作
>
> * `pthread_mutex_destroy`：销毁一个互斥锁
>

> ```
> #include <pthread.h>
> 
> int pthread_mutex_destroy(pthread_mutex_t *mutex);
> int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
> pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
> 
> #include <pthread.h>
> 
> int pthread_mutex_lock(pthread_mutex_t *mutex);
> int pthread_mutex_trylock(pthread_mutex_t *mutex);
> int pthread_mutex_unlock(pthread_mutex_t *mutex);
> 
> ```

## 通过信号量和互斥锁对生产者消费者求解

> [生产者消费者问题](http://39.106.165.33/#!./blog/C/day11.md)

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

#define CONSUMERS_COUNT 4
#define PRODUCERS_COUNT 5
#define BUFFSIZE 10

int g_buffer[BUFFSIZE];
int product_id = 0;

unsigned short in = 0;
unsigned short out = 0;
unsigned short produce_id = 0;
unsigned short consume_id = 0;

sem_t g_sem_full;
sem_t g_sem_empt;
pthread_mutex_t g_mutex;

pthread_t g_thread[CONSUMERS_COUNT + PRODUCERS_COUNT];

void * consume(void * arg)
{	       
	int i = 0;
	while(1)
	{
		printf("thread:%d is waiting for consume\n", (int)arg);
		sem_wait(&g_sem_empt);
		pthread_mutex_lock(&g_mutex);

		for(i = 0; i < BUFFSIZE; i++)
		{
			printf("ThreadID_consume: %d>%3d:", (int)arg, i);
			if(g_buffer[i] == -1)
				printf("%s", "null");
			else
				printf("%3d", g_buffer[i]);
			if(i == out)
				printf("\tconsume");
			printf("\n");
		}

		printf("begin conmuse %d\n", product_id);
		g_buffer[out] = -1;
		out = (out + 1) % BUFFSIZE;
		printf("end conmuse\n");
		sleep(1);

		pthread_mutex_unlock(&g_mutex);
		sem_post(&g_sem_full);
	}
}

void * produce(void * arg)
{
	int i = 0;
	while(1)
	{
		printf("thread:%d is waiting for produce\n", (int)arg);
		sem_wait(&g_sem_full);
		pthread_mutex_lock(&g_mutex);
		
		for(i = 0; i < BUFFSIZE; i++)
		{
			printf("ThreadID_produce: %d>%3d:", (int)arg, i);
			if(g_buffer[i] == -1)
				printf("%s", "null");
			else
				printf("%3d", g_buffer[i]);
			if(i == in)
				printf("\tproduce");
			printf("\n");
		}
		
		printf("begin produce %d\n", product_id);
		g_buffer[in] = product_id;
		in = (in + 1) % BUFFSIZE;
		product_id++;
		printf("end produce\n");
		sleep(1);

		pthread_mutex_unlock(&g_mutex);
		sem_post(&g_sem_empt);
	}
	return NULL;
}
int main()
{
	int i = 0;
	int ret = 0;
	for(i = 0; i < BUFFSIZE; i++)
		g_buffer[i] = -1;

	sem_init(&g_sem_full, 0, BUFFSIZE);//表示当前的仓库空位
	sem_init(&g_sem_empt, 0, 0);//表示可消费的产品数
	pthread_mutex_init(&g_mutex, NULL);//第二个参数表示属性，NULL使用默认属性

	for(i = 0; i < CONSUMERS_COUNT; i++)
	{
		ret = pthread_create(&g_thread[i], NULL, consume, (void *)i);//不能&i会有静态问题
		if(ret != 0)
			ERR_EXIT("pthread_create");
	}

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
	return 0;
}
```

## 自旋锁

> * 自旋锁类似于互斥锁，它的性能比互斥锁更高
> * 自旋锁与互斥锁很重要的一个区别在于，线程在申请自旋锁的时候，线程不会被挂起，它处于忙等待的状态，如果没有申请到锁，则一直向CPU申请。所以不适用等待事件比较长的应用。
> * `pthread_spin_init`
> * `pthread_spin_destory`
> * `pthread_spin_lock`
> * `pthread_spin_unlock`
>
> ```
> #include <pthread.h>
>
> int pthread_spin_destroy(pthread_spinlock_t *lock);
> int pthread_spin_init(pthread_spinlock_t *lock, int pshared);
> int pthread_spin_lock(pthread_spinlock_t *lock);
> int pthread_spin_trylock(pthread_spinlock_t *lock);
> ```

## 读写锁

> * 只要被有线程持有给写的读写锁用于写，那么任意数目的线程可以持有读写锁用于读；
> * 仅当没有线程持有某个给定的读写锁用于读或者用于写时，才分配读写锁用于写；
> * 读写锁用于读称为共享锁，读写锁用于写称为排它锁。一个线程锁定了共享锁，允许其他的线程继续添加共享锁；只要有线程添加了排它锁，其他的线程则不允许再加排它锁。
>
>
>
> 相关函数：
>
> * `pthread_rwlock_init`
> * `pthread_rwlock_destroy`
> * `pthread_rwlock_rdlock`
> * `int pthread_rwlock_wrlock`
> * `int pthread_rwlock_unlock`
>
> ```
> #include <pthread.h>
>
> int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
> int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
>
> int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
> int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
>
> int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
> int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
>
> int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
> ```
>
