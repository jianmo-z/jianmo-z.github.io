# day10

## 本章目标

* 用信号量解决哲学家就餐问题

## 哲学家就餐问题

> 在[day02](http://39.106.165.33/#!./blog/C/day02.md)中哦

- 五个哲学家围在一个圆桌就餐，每个人都必须拿起两把叉子才能就餐，总共有五把叉子两个哲学家之间有一个叉子。

- 哲学家就餐问题解法：

  > [解法连接](https://baike.baidu.com/item/%E5%93%B2%E5%AD%A6%E5%AE%B6%E5%B0%B1%E9%A4%90%E9%97%AE%E9%A2%98/10929794?fr=aladdin)

  - 服务生解法：找一个管理者管理叉子， 指导哲学家拿起叉子。
  - 最多四个哲学家拿起叉子：必然有一个哲学家可以就餐。[抽屉原则](https://baike.baidu.com/item/%E6%8A%BD%E5%B1%89%E5%8E%9F%E5%88%99/4034602?fr=aladdin)
  - 仅当一个哲学家两边叉子可用时才允许他拿起叉子
  - 给所有哲学家编号，奇数号的哲学家必须首先拿起左边的叉子，偶数号的哲学家则反之。

## 避免死锁

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
    #define DELAY (rand() % 5 + 1)

    union semun
    {
        int              val;    /* Value for SETVAL */
        struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
        unsigned short  *array;  /* Array for GETALL, SETALL */
        struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
    };

    int semid;

    void wait_for_2fork(int no)
    {
        int left = no;
        int right = (no + 1) % 5;
        struct sembuf sop[2] = {
            {left, -1, SEM_UNDO},
            {right, -1, SEM_UNDO} };
        semop(semid, sop, 2);//参数三为要操作的个数，即为sop的数组长度
    }

    void free_2fork(int no)
    {
        int left = no;
        int right = (no + 1) % 5;
        struct sembuf sop[2] = {
            {left, 1, 0},
            {right, 1, 0} };
        semop(semid, sop, 2);//参数三为要操作的个数，即为sop的数组长度
    }

    void philosopher(int no)//哲学家：philosoper
    {	
        srand(getpid());
        while(1)
        {
            printf("%d is thinking \n", no);
            sleep(DELAY);
            printf("%d is hunry\n", no);
            wait_for_2fork(no);
            printf("%d is eating\n", no);
            sleep(DELAY);
            free_2fork(no);
        }
    }

    int main(int argc, char *argv[])
    {
        int key = ftok(".", 'a');
        semid = semget(key, 5, IPC_CREAT | 0666);
        if(semid == -1)
            ERR_EXIT("semget");
        union semun un;
        un.val = 1;
        int i = 0;
        for(i = 0; i < 5; i++)
        {
            semctl(semid, i, SETVAL, un);
        }
        int no = 0;
        pid_t pid;
        for(i = 1; i < 5; i++)
        {
            pid = fork();
            if(pid == -1)
                ERR_EXIT("fork");
            if(pid == 0)
            {
                no = i;
                break;
            }
        }
        philosopher(no);//哲学家：philosoper
        return 0;
    }
```

## 使哲学家就餐产生死锁

>`wait_for_2fork`和`free_2fork`进行了修改，让哲学家每次只申请一个刀叉。

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
    #define DELAY (rand() % 5 + 1)

    union semun
    {
        int              val;    /* Value for SETVAL */
        struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
        unsigned short  *array;  /* Array for GETALL, SETALL */
        struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
    };

    int semid;

    void wait_for_2fork(int no)
    {
        int left = no;
        int right = (no + 1) % 5;
        struct sembuf sop[2] = {
            {left, -1, SEM_UNDO},
            {right, -1, SEM_UNDO} };
        semop(semid, sop, 1);//一个一个申请刀叉就可能出现死锁
        printf("%d get a fork\n", no);
        sleep(DELAY);//加快死锁发生条件
        semop(semid, sop + 1, 1);
        printf("%d get another fork\n", no);
    }

    void free_2fork(int no)
    {
        int left = no;
        int right = (no + 1) % 5;
        struct sembuf sop[2] = {
            {left, 1, 0},
            {right, 1, 0} };
        semop(semid, sop, 1);//一个一个释放刀叉就可能出现死锁
        printf("%d get a fork\n", no);
        sleep(DELAY);//加快死锁发生条件
        semop(semid, sop + 1, 1);
        printf("%d get another fork\n", no);
    }

    void philosopher(int no)//哲学家：philosoper
    {	
        srand(getpid());
        while(1)
        {
            printf("%d is thinking \n", no);
            sleep(DELAY);
            printf("%d is hunry\n", no);
            wait_for_2fork(no);
            printf("%d is eating\n", no);
            sleep(DELAY);
            free_2fork(no);
        }
    }

    int main(int argc, char *argv[])
    {
        int key = ftok(".", 'a');
        semid = semget(key, 5, IPC_CREAT | 0666);
        if(semid == -1)
            ERR_EXIT("semget");
        union semun un;
        un.val = 1;
        int i = 0;
        for(i = 0; i < 5; i++)
        {
            semctl(semid, i, SETVAL, un);
        }
        int no = 0;
        pid_t pid;
        for(i = 1; i < 5; i++)
        {
            pid = fork();
            if(pid == -1)
                ERR_EXIT("fork");
            if(pid == 0)
            {
                no = i;
                break;
            }
        }
        philosopher(no);//哲学家：philosoper
        return 0;
    }
```

