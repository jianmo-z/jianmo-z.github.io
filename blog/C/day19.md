# day19

> 一个简单线程池实现

## 本章目标

* 线程池实现

## 线程池实现

> * 线程池中拥有若干个线程
> * 计算密集型任务：占用CPU的任务，很少被外界的任务打断，这时当`线程数 = CPU个数`最佳。
> * `I/O`密集型任务：当执行任务的时候可能会被`I/O`中断，线程会挂起`线程数 > CPU个数`，但不会大很多。
>
> 线程池需求：
>
> * 用于执行大量相对短暂的任务，小于并发的任务量。
>
>
> * 当任务增加的时候能够动态的增加线程池中的数量直到达到一个阀值
> * 当任务执行完毕的时候，能够动态的销毁线程池中的线程
> * 该线程池的实现本质上也会是生产者与消费者模型的应用生产者线程向任务队列中添加任务，一旦队列有任务到来，如果有等待线程就唤醒来执行任务，如果没有等待线程并且线程数没有达到阀值，就创建新线程来执行任务。

## 线程池数据结构

```
//任务结构体，将任务放入队列由线程池中的线程来执行
typedef struct task
{
    void *(*run)(void * arg); //任务回调函数
    void * arg; //回调函数参数
    struct task * next;
}task_t;

//线程池结构体
typedef struct threadpool
{
    condition_t ready;	//任务准备就绪或者线程池销毁通知
    task_t *first;		//任务队列头指针
    task_t *last;		//任务队列尾指针
    int counter;		//线程池中当前线程数
    int idle;			//线程池中当前正在等待任务的线程数
    int max_threads;	//线程池中最大允许的线程数
    int quit;			//销毁线程池的时候置为1
};

//初始化线程池
void threadpool_init(threadpool_t *pool, int threads);
//往线程池中添加任务
void threadpool_add_task(threadpool_t *pool, void *(*run)(void *arg), void *arg);
//销毁线程池
void threadpool_destroy(threadpool_t *pool);
```

## 插播clock_gettime函数

> 获取时间的函数。

> ```
> #include <time.h>
>
> int clock_getres(clockid_t clk_id, struct timespec *res);
> int clock_gettime(clockid_t clk_id, struct timespec *tp);
> int clock_settime(clockid_t clk_id, const struct timespec *tp);
>
> Link with -lrt (only for glibc versions before 2.17).
>
> CLOCK_REALTIME
> CLOCK_REALTIME_COARSE
> CLOCK_MONOTONIC
> CLOCK_MONOTONIC_COARSE
> CLOCK_MONOTONIC_RAW
> CLOCK_BOOTTIME
> CLOCK_PROCESS_CPUTIME_ID
> CLOCK_THREAD_CPUTIME_ID
> ```

## condition.h文件

```
#ifndef _CONDITION_H_
#define _CONDITION_H_

#include <pthread.h>

typedef struct condition
{
	pthread_mutex_t pmutex;
	pthread_cond_t pcond;
}condition_t;

int condition_init(condition_t *cond);
int condition_lock(condition_t *cond);a
int condition_unlock(condition_t *cond);
int condition_wait(condition_t *cond);
int condition_timewait(condition_t *cond, const struct timespec * abstime);
int condition_signal(condition_t *cond);
int condition_broadcast(condition_t *cond);
int condition_destroy(condition_t *cond);

#endif //_CONDITION_H_
```

## threadpool.h文件

```
#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

//任务结构体，将任务放入队列由线程池中的线程来执行
typedef struct task
{
    void *(*run)(void * arg); //任务回调函数
    void * arg; //回调函数参数
    struct task * next;
}task_t;

//线程池结构体
typedef struct threadpool
{
    condition_t ready;	//任务准备就绪或者线程池销毁通知
    task_t *first;	//任务队列头指针
    task_t *last;	//任务队列尾指针
    int counter;	//线程池中当前线程数
    int idle;		//线程池中当前正在等待任务的线程数
    int max_threads;	//线程池中最大允许的线程数
    int quit;		//销毁线程池的时候置为1
}threadpool_t;

//初始化线程池
void threadpool_init(threadpool_t *pool, int threads);
//往线程池中添加任务
void threadpool_add_task(threadpool_t *pool, void *(*run)(void *arg), void *arg);
//销毁线程池
void threadpool_destroy(threadpool_t *pool);


#endif //_THREAD_POOL_H_
```

## condition.c文件

```
#include "condition.h"

int condition_init(condition_t *cond)
{
	int status;//成功返回0失败设置errno,所以对两个进行初始化
	if((status = pthread_mutex_init(&cond->pmutex, NULL)))
		return status;
	if((status = pthread_cond_init(&cond->pcond, NULL)))
		return status;
	return 0;
}
int condition_lock(condition_t *cond)
{
	return pthread_mutex_lock(&cond->pmutex);
}
int condition_unlock(condition_t *cond)
{
	return pthread_mutex_unlock(&cond->pmutex);
}
int condition_wait(condition_t *cond)
{
	return pthread_cond_wait(&cond->pcond, &cond->pmutex);
}
int condition_timewait(condition_t *cond, const struct timespec * abstime)
{
	return pthread_cond_timedwait(&cond->pcond, &cond->pmutex, abstime);
}
int condition_signal(condition_t *cond)
{
	return pthread_cond_signal(&cond->pcond);
}
int condition_broadcast(condition_t *cond)
{
	return pthread_cond_broadcast(&cond->pcond);
}
int condition_destroy(condition_t *cond)
{
	int status;//成功返回0失败设置errno,所以对两个进行初始化
	if((status = pthread_mutex_destroy(&cond->pmutex)))
		return status;
	if((status = pthread_cond_destroy(&cond->pcond)))
		return status;
	return 0;
}
```

## threadpool.c文件

```
#include "condition.h"
#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

void * thread_routine(void * arg)
{
	int timeout = 0;
	struct timespec abstime; 
	threadpool_t * pool = (threadpool_t *)(arg);

	printf("Thread:%ld is starting \n", (long int)pthread_self());
	while(1)
	{
		//加锁
		condition_lock(&pool->ready);
		pool->idle++;//空闲线程数加一
		//等待任务队列是否有任务，或者线程池销毁通知
		while(pool->first == NULL && !pool->quit)
		{
			//condition_wait(&pool->ready);
			clock_gettime(CLOCK_REALTIME, &abstime);
			abstime.tv_sec += 2;
			int ret = condition_timewait(&pool->ready, &abstime);//使用等待超时自动销毁函数
			if(ret == ETIMEDOUT)//errno的宏,Socket编程day11有介绍
			{
				timeout = 1;
				break;
			}
		}
		pool->idle--;//空闲线程数减一
		if(pool->first != NULL)//执行任务
		{
			//取出队头任务
			task_t *t = pool->first;
			//队头发生改变
			pool->first = pool->first->next;

			//执行任务需要时间，所以要先解锁，以便添加新的任务，其他消费者线程能进入等待任务
			condition_unlock(&pool->ready);
			t->run(t->arg);
			free(t);
			condition_lock(&pool->ready);
		}
		if(pool->quit && pool->first == NULL)//销毁线程池,要求任务执行完了
		{
			//condition_destory(&pool->cond);
			pool->counter--;
			if(pool->counter == 0)
				condition_signal(&pool->ready);
			condition_unlock(&pool->ready);
			break;
		}
		if(timeout && pool->first == NULL)
		{
			pool->counter--;
			condition_unlock(&pool->ready);
			break;
		}	
		condition_unlock(&pool->ready);
	}
	printf("Thread:%ld is timeout\n", (long int)pthread_self());
	return NULL;	
}

//初始化线程池
void threadpool_init(threadpool_t *pool, int threads)
{
	//线程的初始化
	condition_init(&pool->ready);
	pool->first = NULL;
	pool->last = NULL;
	pool->counter = 0;
	pool->idle = 0;
	pool->max_threads = threads;
	pool->quit = 0;
}
//往线程池中添加任务
void threadpool_add_task(threadpool_t *pool, void *(*run)(void *arg), void *arg)
{
	//生成新任务
	task_t *newtask = (task_t *)malloc(sizeof(task_t));
	newtask->run = run;
	newtask->arg = arg;
	newtask->next = NULL;

	//添加新任务需要唤醒
	condition_lock(&pool->ready);

	//将任务添加到队列中
	if(pool->first == NULL)
		pool->first = newtask;
	else
		pool->last->next = newtask;
	pool->last = newtask;

	//有空等待线程，唤醒其中一个
	if(pool->idle > 0)
	{
		condition_signal(&pool->ready);
	}
	else if(pool->counter < pool->max_threads)
	{
		//没有等待线程，且当前线程数小于最大线程数(阀值)，创建一个新线程完成任务
		pthread_t tid;
		pthread_create(&tid, NULL, thread_routine, pool);
		pool->counter++;
	}	
	condition_unlock(&pool->ready);
}
//销毁线程池
void threadpool_destroy(threadpool_t *pool)
{
	if(pool->quit)
	{
		return;
	}
	condition_lock(&pool->ready);

	pool->quit = 1;
	if(pool->counter > 0)
	{
		//发送广播，如果处于正在执行任务的线程不会收到这个广播信号
		//让空闲线程退出
		if(pool->idle >0)
		{
			condition_broadcast(&pool->ready);
		}
		//等待正在执行任务的线程，保证全部退出
		while(pool->counter > 0)
		{
			condition_wait(&pool->ready);
			
		}
	}	

	condition_unlock(&pool->ready);
	condition_destroy(&pool->ready);
}
```

## main.c文件

```
#include "condition.h"
#include "threadpool.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void * mytask(void *arg)
{
	printf("thread:%ld is working task %d\n", (long int)pthread_self(), *((int *)arg));
	sleep(1);//假设在执行任务
	free(arg);//可以返回释放，这里简单直接释放掉
	return NULL;
}

int main()
{
	int i = 0;
	threadpool_t pool;
	threadpool_init(&pool, 3);
	
	for(i = 0; i < 10; i++)
	{
		int *arg = (int *)malloc(sizeof(int));
		*arg = i;
		threadpool_add_task(&pool, mytask, (void *)arg);
	}

	threadpool_destroy(&pool);
	return 0;
}
```

## makefile文件

```
.PHONY: clean all
CC=gcc
CFLAGS= -Wall -g
BIN=condition.o threadpool.o main.o
OBJ=main
all:$(BIN) $(OBJ)
$(BIN):%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(OBJ):$(BIN)
	gcc $(CFLAGS) $(BIN) -o $(OBJ) -lpthread
	rm -f *.o $(BIN)
clean:
	rm -f $(OBJ)
```

