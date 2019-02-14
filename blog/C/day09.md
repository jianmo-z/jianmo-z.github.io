# day09

## 本章目标

* 用信号量实现进程互斥示例


## print.c

> 此程序主要为了应用PV操作，子进程父进程任意睡眠N秒，来控制进程同步，程序结果`o`和`x`成对出现，但不仅仅指两个两个交替出现

```
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define ERR_EXIT(x) do{ perror(x); exit(EXIT_FAILURE);}while(0)

typedef struct stu
{
	char name[32];
	int age;
}stu;

union semun
{
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};


//创建信号量集
int sem_create(key_t key)
{
	//int semget(key_t key, int nsems, int semflg);
	//IPC_EXCL选项，如果创建过了，则不会再次创建，返回失败
	int semid = semget(key, 1, IPC_CREAT | 0666 | IPC_EXCL);
	if(semid == -1)
	{
		ERR_EXIT("semget create");
	}
	return semid;
}

//打开信号量集
int sem_open(key_t key)
{
	int semid = semget(key, 0, 0);
	if(semid == -1)
	{
		ERR_EXIT("semget open");
	}
	return semid;

}
//设置一个信号量集
int sem_setval(int semid, int val)
{
	union semun su;
	su.val = val;
	int ret = semctl(semid, 0, SETVAL, su);
	if(ret == -1)
	{
		ERR_EXIT("semctl:setval");
	}
	return ret;
}

//获取一个信号量集状态
int sem_getval(int semid)
{
	int ret = semctl(semid, 0, GETVAL);
	if(ret == -1)
	{
		ERR_EXIT("semctl:getval");
	}
	return ret;
}

//删除一个信号量集
int sem_del(int semid)
{
	int ret = semctl(semid, 0, IPC_RMID, 0);
	if(ret == -1)
	{
		ERR_EXIT("semctl:ipc-rmid");
	}
	return 0;
}

//P操作
int sem_p(int semid)
{

	struct sembuf buf = {0, -1, SEM_UNDO};
	int ret = semop(semid, &buf, 1);//第二个参数，可以是一个数组，表示对多个信号量操作。
	if(ret == -1)
	{
		//printf("errno = %d\n", errno);
		ERR_EXIT("semop:p");
	}
	return ret;
}

//V操作
int sem_v(int semid)
{
	struct sembuf buf = {0, 1, 0};
	int ret = semop(semid, &buf, 1);//第二个参数，可以是一个数组，表示对多个信号量操作。
	if(ret == -1)
	{
		ERR_EXIT("semop:v");
	}
	return ret;
}

int semid;

void print(char op_char)
{
	int pause_time;
	srand(getpid());
	int i = 0;
	for(i = 0; i < 10; i++)
	{
		sem_p(semid);
		printf("%c", op_char);
		fflush(stdout);
		pause_time = rand() % 3;
		sleep(pause_time);
		printf("%c", op_char);
		fflush(stdout);
		sem_v(semid);
		pause_time = rand() % 2;
		sleep(pause_time);
	}
}

//semid是全局变量，此程序目的为了实现，o和x成对出现，但不只是两个两个交叉出现
int main(int argc, char *argv[])
{
	semid = sem_create(IPC_PRIVATE);
	sem_setval(semid, 0);
	pid_t pid;
	pid = fork();
	if(pid == -1)
	{
		ERR_EXIT("fork");
	}
	else if(pid > 0)//父进程
	{
		sem_setval(semid, 1);
		print('o');
		wait(NULL);
		sem_del(semid);
	}
	else//子进程
	{
		print('x');
	}

	return 0;
}
```

