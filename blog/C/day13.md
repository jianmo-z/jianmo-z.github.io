# day13

## 本章目标

* `POSIX`共享内存相关函数
* `POSIX`共享内存示例

## shm_open函数

> * 功能：用来创建或打开一个共享内存对象，`man 7 shm_overview`，文件在`/dev/shm/`下可以查看到共享内存。
>
> * 原型：
>
>   ```
>   #include <sys/mman.h>
>   #include <sys/stat.h>        /* For mode constants */
>   #include <fcntl.h>           /* For O_* constants */
>
>   int shm_open(const char *name, int oflag, mode_t mode);
>   int shm_unlink(const char *name);
>
>   Link with -lrt.
>   ```
>
> * 参数：
>
>   * `name`：共享内存对象的名字，**命名规则有要求**
>     * 必须以`/`打头，并且后续不能有其他的`/`，例如：`/somename`
>     * 长度不能超过`NAME_MAX`，不同的环境值不同。
>   * `oflag`：与`open`函数类似可以是`O_RDONLY`、`O_RDWR`，还可以按位或上`O_CREAT`、`O_EXCL`和`O_TRUNC(截断)`等。
>   * `mode`：此参数总需要设置，权限，如果`oflag`没有指定`O_CREAT`，可以指定`0`。
>
> * 返回值：成功返回非负整数文件描述符，失败返回`-1`。

## ftruncate函数

> * 功能：修改共享内存对象大小
> * 原型：
>   * `int ftruncate(int fd, off_t length);`
> * 参数：
>   * `fd`：文件描述符，共享内存的`fd`
>   * `length`：长度
> * 返回值：成功返回`0`，失败返回`-1`

## fstat函数

> * 功能：获取共享内存对象信息
>
> * 原型：
>
>   * `int fstat(int fd, struct stat *buf);`
>
>   ```
>   #include <sys/types.h>
>   #include <sys/stat.h>
>   #include <unistd.h>
>
>   int stat(const char *path, struct stat *buf);
>   int fstat(int fd, struct stat *buf);
>   int lstat(const char *path, struct stat *buf);
>
>   struct stat {
>       dev_t     st_dev;     /* ID of device containing file */
>       ino_t     st_ino;     /* inode number */
>       mode_t    st_mode;    /* protection */
>       nlink_t   st_nlink;   /* number of hard links */
>       uid_t     st_uid;     /* user ID of owner */
>       gid_t     st_gid;     /* group ID of owner */
>       dev_t     st_rdev;    /* device ID (if special file) */
>       off_t     st_size;    /* total size, in bytes */
>       blksize_t st_blksize; /* blocksize for file system I/O */
>       blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
>       time_t    st_atime;   /* time of last access */
>       time_t    st_mtime;   /* time of last modification */
>       time_t    st_ctime;   /* time of last status change */
>   };
>   ```
>
>   > 文件类型和权限相关
>
>   ```
>   The  following  POSIX  macros are defined to check the file type using
>   the st_mode field:
>
>   S_ISREG(m)  is it a regular file?
>   S_ISDIR(m)  directory?
>   S_ISCHR(m)  character device?
>   S_ISBLK(m)  block device?
>   S_ISFIFO(m) FIFO (named pipe)?
>   S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
>   S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)
>   ```
>
>   ```
>   The following flags are defined for the st_mode field:
>
>   S_IFMT     0170000   bit mask for the file type bit fields
>   S_IFSOCK   0140000   socket
>   S_IFLNK    0120000   symbolic link
>   S_IFREG    0100000   regular file
>   S_IFBLK    0060000   block device
>   S_IFDIR    0040000   directory
>   S_IFCHR    0020000   character device
>   S_IFIFO    0010000   FIFO
>   S_ISUID    0004000   set-user-ID bit
>   S_ISGID    0002000   set-group-ID bit (see below)
>   S_ISVTX    0001000   sticky bit (see below)
>   S_IRWXU    00700     mask for file owner permissions
>   S_IRUSR    00400     owner has read permission
>   S_IWUSR    00200     owner has write permission
>   S_IXUSR    00100     owner has execute permission
>   S_IRWXG    00070     mask for group permissions
>   S_IRGRP    00040     group has read permission
>   S_IWGRP    00020     group has write permission
>   S_IXGRP    00010     group has execute permission
>   S_IRWXO    00007     mask for permissions for others (not in group)
>   S_IROTH    00004     others have read permission
>   S_IWOTH    00002     others have write permission
>   S_IXOTH    00001     others have execute permission
>   ```

## shm_unlink函数

> * 功能：删除一个共享内存对象
>
> * 原型：
>
>   ```
>   #include <sys/mman.h>
>   #include <sys/stat.h>        /* For mode constants */
>   #include <fcntl.h>           /* For O_* constants */
>
>   int shm_open(const char *name, int oflag, mode_t mode);
>   int shm_unlink(const char *name);
>
>   Link with -lrt.
>   ```
>
> * 参数：
>
>   * `name`：共享内存对象的名字
>
> * 返回值：成功返回`0`，失败返回`-1`。

## 共享内存对象的映射 mmap函数

> 前面说过了，请查看`day06`的内容

> * 功能：将共享内存对象映射到进程地址空间，进行读写操作。
> * 原型：
>   * `void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);`
> * 参数：
>   * `addr`：要映射的起始地址，通常指定为`NULL`，即让内核自动选择
>   * `len`：映射到进程地址空间的字节数
>   * `prot`：映射区保护方式
>   * `flags`：标志
>   * `fd`：文件描述符
>   * `offset`：从文件头开始的偏移量
> * 返回值：成功返回映射到的内存区的起始地址，失败返回`-1`。
> * **注意：如果`prot`为`PROT_WRITE`且`flags`为`MAP_SHARED`，共享内存的打开方式必须为`O_RDWR`，否则会有`EACCES`错误。**

