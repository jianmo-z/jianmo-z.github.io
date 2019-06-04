# HDFS入门

[TOC]

## 什么是HDFS?

### 概念

> HDFS，它是一个文件系统，用来存储文件，通过目录树来定位文件；其次，它是分布式的，有很多服务器联合起来实现其功能，集群中的服务器有各自的角色。每个块默认最大为128M
>
> HDFS的设计**适合一次写入，多次读出**的场景，且**不支持文件的修改**。**适合用来做数据分析**，且不适合用来做网盘应用。

### 组成

1. HDFS集群包括，NameNode和DataNode以及SecondaryNameNode。
2. NameNode负责管理整个文件系统的[元数据](<https://baike.baidu.com/item/%E5%85%83%E6%95%B0%E6%8D%AE>)，以及每一个路径(文件)所对应的数据块信息。
3. DataNode负责管理用户的文件数据块，每一个数据块都可以在多个DataNode上存储多个副本信息。
4. SecondaryNameNode用来监控HDFS状态的辅助后台程序，每隔一段时间获取HDFS元数据的快照

### HDFS文件块大小

> 块的大小可以通过配置参数( dfs.blocksize)来规定，默认的块大小实际为64MB，但是很多情况下HDFS使用128MB的块设置。HDFS的块比磁盘的块大，其目的是为了最小化寻址开销。

## HDFS操作命令

1. `hadoop fs`/`hadoop fs -help`：查看简略/详细帮助

2. `hadoop fs command`/`Usage: hadoop fs [generic options]`：用法

3. 常用命令(23个)：

   1. `-help`：输出命令参数
   2. `-ls`：显示目录信息
   3. `-mkdir`：在hdfs上创建目录
   4. `-moveFromLocal`：从本地剪切粘贴到hdfs
   5. `-moveToLocal`：从hdfs剪切粘贴到本地
   6. `--appendToFile`：追加一个文件到已经存在的文件末尾
   7. `-cat`：查看文件内容
   8. `-tail`：显示一个文件的末尾
   9. `-text`：以字符形式打印一个文件的内容
   10. `-chgrp、-chmod、-chown`：linux文件系统中的用法一样，修改文件所属权限
   11. `-copyFromLocal`：从本地文件系统中拷贝到hdfs路径去
   12. `-copyToLocal`：从hdfs拷贝到本地
   13. `-cp`：从hdfs的一个路径拷贝到hdfs的另一个路径
   14. `-mv`：在hdfs目录中移动文件
   15. `-get`：等同于copyToLocal，就是从hdfs下载文件到本地
   16. `-getmerge`：合并下载多个文件
   17. `-put`：等同于copyFromLocal
   18. `-rm`：删除文件或文件夹
   19. `-rmdir`：删除空目录
   20. `-df`：统计文件系统的可用空间信息
   21. `-du`：统计文件夹的大小信息
   22. `-count`：统计一个指定目录下的文件节点数量
   23. `-setrep`：设置hdfs中文件的副本数量

4. 完整命令使用帮助：

   ```bash
   Usage: hadoop fs [generic options]
   	[-appendToFile <localsrc> ... <dst>]
   	[-cat [-ignoreCrc] <src> ...]
   	[-checksum <src> ...]
   	[-chgrp [-R] GROUP PATH...]
   	[-chmod [-R] <MODE[,MODE]... | OCTALMODE> PATH...]
   	[-chown [-R] [OWNER][:[GROUP]] PATH...]
   	[-copyFromLocal [-f] [-p] [-l] <localsrc> ... <dst>]
   	[-copyToLocal [-p] [-ignoreCrc] [-crc] <src> ... <localdst>]
   	[-count [-q] [-h] <path> ...]
   	[-cp [-f] [-p | -p[topax]] <src> ... <dst>]
   	[-createSnapshot <snapshotDir> [<snapshotName>]]
   	[-deleteSnapshot <snapshotDir> <snapshotName>]
   	[-df [-h] [<path> ...]]
   	[-du [-s] [-h] <path> ...]
   	[-expunge]
   	[-find <path> ... <expression> ...]
   	[-get [-p] [-ignoreCrc] [-crc] <src> ... <localdst>]
   	[-getfacl [-R] <path>]
   	[-getfattr [-R] {-n name | -d} [-e en] <path>]
   	[-getmerge [-nl] <src> <localdst>]
   	[-help [cmd ...]]
   	[-ls [-d] [-h] [-R] [<path> ...]]
   	[-mkdir [-p] <path> ...]
   	[-moveFromLocal <localsrc> ... <dst>]
   	[-moveToLocal <src> <localdst>]
   	[-mv <src> ... <dst>]
   	[-put [-f] [-p] [-l] <localsrc> ... <dst>]
   	[-renameSnapshot <snapshotDir> <oldName> <newName>]
   	[-rm [-f] [-r|-R] [-skipTrash] <src> ...]
   	[-rmdir [--ignore-fail-on-non-empty] <dir> ...]
   	[-setfacl [-R] [{-b|-k} {-m|-x <acl_spec>} <path>]|[--set <acl_spec> <path>]]
   	[-setfattr {-n name [-v value] | -x name} <path>]
   	[-setrep [-R] [-w] <rep> <path> ...]
   	[-stat [format] <path> ...]
   	[-tail [-f] <file>]
   	[-test -[defsz] <path>]
   	[-text [-ignoreCrc] <src> ...]
   	[-touchz <path> ...]
   	[-truncate [-w] <length> <path> ...]
   	[-usage [cmd ...]]
   
   Generic options supported are
   -conf <configuration file>     specify an application configuration file
   -D <property=value>            use value for given property
   -fs <local|namenode:port>      specify a namenode
   -jt <local|resourcemanager:port>    specify a ResourceManager
   -files <comma separated list of files>    specify comma separated files to be copied to the map reduce cluster
   -libjars <comma separated list of jars>    specify comma separated jar files to include in the classpath.
   -archives <comma separated list of archives>    specify comma separated archives to be unarchived on the compute machines.
   
   The general command line syntax is
   bin/hadoop command [genericOptions] [commandOptions]
   ```

## 客户端操作HDFS

### 通过API操作HDFS

```java
public static void main(String[] args) throws Exception {
    // 1.1 获取配置信息
    Configuration configuration = new Configuration();
    configuration.set("fs.defaultFS", "hdfs://centos202:8020");

    // 1.2 方式一：连接文件服务器
    // FileSystem fileSystem = FileSystem.get(configuration);

    // 1.2 方式二：连接文件服务器
    FileSystem fileSystem = FileSystem.get(new URI("hdfs://centos202:8020"), configuration, "pip");


    // 2 文件操作
    fileSystem.copyFromLocalFile(new Path("/etc/passwd"), new Path("/usr/pip/test/"));  // 拷贝文件
    // fileSystem.deleteOnExit(new Path("/usr/pip/test/passwd")); // 删除文件
    // 进行操作

    // 3 关闭资源
    fileSystem.close();
}
```

### FileSystem操作API

1. 获取文件系统：
   1. 方式一：`FileSystem fileSystem = FileSystem.get(configuration);`
   2. 方式二(优)：`FileSystem fileSystem = FileSystem.get(new URI("hdfs://centos202:8020"), configuration, "pip");`
2. 上传文件：
   1. API：`void copyFromLocalFile(boolean delSrc, Path src, Path dst)`
   2. 例：`fileSystem.copyFromLocalFile(true, new Path("/etc/passwd"), new Path("/usr/pip/test"));`
3. 下载文件：
   1. API：`void copyToLocalFile(Path src, Path dst)`
   2. 例：`fileSystem.copyToLocalFile(new Path("/usr/pip/test/passwd"), new Path("/tmp/"));`
4. 创建目录：
   1. API：`boolean mkdirs(Path f)`
   2. 例：`fileSystem.mkdirs(new Path("/usr/pip/test"));`
5. 文件夹删除：
   1. API：`boolean delete(Path var1, boolean var2)`
   2. 例：`fileSystem.delete(new Path("/usr/pip/test/passwd"), true);`
6. 文件名改名：
   1. API：`boolean rename(Path var1, Path var2)`
   2. 例：`fileSystem.rename(new Path("/usr/pip/test"), new Path("/usr/pip/test1"));`
7. 文件详情查看：
   1. API：`RemoteIterator<LocatedFileStatus> listFiles(final Path f, final boolean recursive)`
   2. 例：`fileSystem.listFiles(new Path("/usr/pip"), true);`
8. 文件夹查看：
   1. API：`FileStatus[] listStatus(Path var1)`
   2. 例：`fileSystem.listStatus(new Path("/usr/pip"));`

### IO流操作HDFS

