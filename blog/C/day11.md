# day11

##本章目标

* 用信号量解决生产者消费者问题
* 实现`shmfifo`
> <font size=4>如果需要运行程序请下载源文件</font><a href="./Download/day11.tar.gz"><font color="red"> 点击下载源文件</font></a>

## 生产者与消费者问题

> [生产者消费者问题](https://www.jianshu.com/p/b16296e9ac85)

## assert函数

>断言，表示某件事情或者条件一定满足否则一定会错误。即：`scalar expression`一定为真，否则程序中断退出。

```
#include <assert.h>
void assert(scalar expression);
```
## shmfifo

```
struct shmhead
{
    unsigned int blksize;	//块大小
    unsigned int blocks;	//总块数
    unsigned int rd_index;	//读索引
    unsigned int wr_index;	//写索引
};

struct shmfifo
{
    shmhead_t * p_shm;		//共享内存头部指针
    char * p_payload;		//有效负载的起始地址，存放数据的起始地址
    
    int shmid;				//共享内存ID
    int sem_mutex;			//用来互斥用的信号量
    int sem_full;			//用来控制共享内存是否满的信号量
    int sem_empt;			//用来控制共享内存是否空的信号量
};
```

##生产者消费者问题解决

## shmfifo.h

```
#ifndef _SHM_FIFO_H_
#define _SHM_FIFO_H_


#include <sys/ipc.h>

typedef struct shmfifo shmfifo_t;
typedef struct shmhead shmhead_t;

struct shmhead
{
    unsigned int blksize;	//块大小
    unsigned int blocks;	//总块数
    unsigned int rd_index;	//读索引
    unsigned int wr_index;	//写索引
};

struct shmfifo
{
    shmhead_t * p_shm;		//共享内存头部指针
    char * p_payload;		//有效负载的起始地址，存放数据的起始地址
    
    int shmid;				//共享内存ID
    int sem_mutex;			//用来互斥用的信号量
    int sem_full;			//用来控制共享内存是否满的信号量
    int sem_empt;			//用来控制共享内存是否空的信号量
};


shmfifo_t * shmfifo_init(int key, int blksize, int blocks);
void shmfifo_put(shmfifo_t * fifo, const void * buf);
void shmfifo_get(shmfifo_t * fifo, void * buf);
void shmfifo_destory(shmfifo_t *fifo);

#endif // _SHM_FIFO_H_
```

## shmfifo.c

```
#include "shmfifo.h"
#include <assert.h>
#include "sem.h"

#define ERR_EXIT(x) do{ perror(x); exit(EXIT_FAILURE);}while(0)


shmfifo_t * shmfifo_init(int key, int blksize, int blocks)
{
	shmfifo_t * fifo = (shmfifo_t *)malloc(sizeof(shmfifo_t));

	assert(fifo != NULL);//断言
	
	memset(fifo, 0, sizeof(shmfifo_t));
	
	int shmid = shmget(key, 0, 0);
	int size = sizeof(shmhead_t) + blksize * blocks;
	if(shmid == -1)
	{
		fifo->shmid = shmget(key, size, 0666 | IPC_CREAT);
		if(fifo->shmid == -1)
			ERR_EXIT("shmget create");

		fifo->p_shm = (shmhead_t *)shmat(fifo->shmid, NULL, 0);
		if(fifo->p_shm == (shmhead_t *)(-1))
		{
			ERR_EXIT("shmat:connect");
		}
		fifo->p_payload = (char *)(fifo->p_shm + 1);//有效负载的位置

		fifo->sem_mutex = sem_create(key);
		fifo->sem_full = sem_create(key + 1);
		fifo->sem_empt = sem_create(key + 2);

		fifo->p_shm->blocks = blocks;
		fifo->p_shm->blksize = blksize;
		fifo->p_shm->rd_index = 0;
		fifo->p_shm->wr_index = 0;

		sem_setval(fifo->sem_mutex, 1);//mutex互斥的意思，用来互斥的信号量
		sem_setval(fifo->sem_full, blocks);
		sem_setval(fifo->sem_empt, 0);
	}
	else
	{
		fifo->shmid = shmid;
		fifo->p_shm = (shmhead_t *)shmat(fifo->shmid, NULL, 0);
		if(fifo->p_shm == (shmhead_t *)(-1))
		{
			ERR_EXIT("shmat:connect");
		}
		fifo->p_payload = (char *)(fifo->p_shm + 1);//有效负载的位置

		fifo->sem_mutex = sem_open(key);
		fifo->sem_full = sem_open(key + 1);
		fifo->sem_empt = sem_open(key + 2);
	}
	return fifo;
}

void shmfifo_put(shmfifo_t * fifo, const void * buf)
{
	//buf的长度为blksize大小，默认统一
	sem_p(fifo->sem_full);
	sem_p(fifo->sem_mutex);
	
	//生产产品，在p_payload的位置生产产品
	char * tmp = fifo->p_payload + fifo->p_shm->blksize * fifo->p_shm->wr_index;	
	memcpy(tmp, buf, fifo->p_shm->blksize);
	fifo->p_shm->wr_index = (fifo->p_shm->wr_index + 1) % fifo->p_shm->blocks;
	//v操作
	sem_v(fifo->sem_mutex);
	sem_v(fifo->sem_empt);
}

void shmfifo_get(shmfifo_t * fifo, void * buf)
{

	//buf的长度为blksize大小，默认统一
	sem_p(fifo->sem_empt);
	sem_p(fifo->sem_mutex);
	
	//获取产品，在p_payload的位置获取产品
	char * tmp = fifo->p_payload + fifo->p_shm->blksize * fifo->p_shm->rd_index;	
	memcpy(buf, tmp, fifo->p_shm->blksize);
	fifo->p_shm->rd_index = (fifo->p_shm->rd_index + 1) % fifo->p_shm->blocks;

	//v操作
	sem_v(fifo->sem_mutex);
	sem_v(fifo->sem_full);
}

void shmfifo_destory(shmfifo_t *fifo)
{
	sem_del(fifo->sem_full);
	sem_del(fifo->sem_mutex);
	sem_del(fifo->sem_empt);
	shmdt(fifo->p_shm);
	shmctl(fifo->shmid, IPC_RMID, 0);	
	free(fifo);
}
```

## shmfifo_send.c

```
#include "shmfifo.h"
#include "sem.h"

typedef struct stu
{
	char name[32];
	int age;
}stu;

int main()
{
	key_t key = ftok(".", '1');
	shmfifo_t * fifo = shmfifo_init(key, sizeof(stu), 6);//容量为6个单位
	int i = 0;
	stu s;
	strcpy(s.name, "a");
	s.age = 12;
	for(i = 0; i < 10;  i++)
	{
		shmfifo_put(fifo, (char *)&s);
		printf("put OK name = %c, age = %d\n", s.name[0], s.age);
		++(s.name[0]);
		++s.age;
	}
	return 0;
}
```

## shmfifo_recv.c

```
#include "shmfifo.h"
#include "sem.h"

typedef struct stu
{
	char name[32];
	int age;
}stu;

int main()
{
	key_t key = ftok(".", '1');
	shmfifo_t * fifo = shmfifo_init(key, sizeof(stu), 6);
	int i = 0;
	stu s;
	for(i = 0; i < 10;  i++)
	{
		memset(&s, 0, sizeof(stu));
		shmfifo_get(fifo, (void *)&s);
		printf("name is %c; age is %d\n", s.name[0], s.age);
	}
	return 0;
}
```

## shmfifo_free.c

```
#include "shmfifo.h"

typedef struct stu
{
        char name[32];
        int age;
}stu;

int main()
{
        key_t key = ftok(".", '1');
        shmfifo_t * fifo = shmfifo_init(key, sizeof(stu), 10);
	shmfifo_destory(fifo);
}
```


