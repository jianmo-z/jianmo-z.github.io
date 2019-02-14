# Linux基础

## 磁盘管理

>   *   `df -h`：查看已经挂载的设备
>   *   `fdisk -l`：查看系统中所有的设备，包括未识别的
>   *   `cat /proc/partitions`：参看系统已经挂载的硬盘
>       *   `sda`：第一块硬盘，`adb`第二块分区，... ...
>       *   `sr0`：光驱
>   *   `blkid`：系统可以使用的设备

## 设备的挂载和卸载

*   设备名称
    *   `/dev/*d*`：例`/dev/hd0`、`/dev/hd1`、`/dev/sda`  、 `/dev/sdb`、`/dev/sda1`、`/dev/sdb1`。
    *   `/dev/sr0`：光驱
    *   `/dev/mapper/*`：虚拟设备(用软件模拟出来)
*   设备的挂载
    *   `mount`：查看挂载信息
    *   `mount 设备 挂载点`，使用`-t`指定挂载格式
    *   `mount -o ro 设备 挂载点`：只读挂载
    *   `umount 挂载点`：卸载挂载
    *   `mount -o remount,rw /mnt/`，对设备重新挂载，改变其挂载点的属性
*   解决设备正忙问题
    *   `lsof 设备`：查看谁正在使用设备
    *   `fuser -vm 设备`：查看谁在用设备
        *   `-k`：查看并踢出谁正在用设备
*   手动同步分区表
    *   `partprobe`：同步分区表

## 磁盘分区

*   `dd if=/dev/zero of=/dev/vda bs=446 count=1`：从`if`截取446个字节，拷贝到`of`所指向的位置，`bs`字节大小，`count`写入次数。
*   `fdisk 磁盘`
    *   `n`：创建新分区
        *   `p`：主分区
        *   `e`：拓展分区里面分的区叫逻辑分区
    *   `w`：写入分区
    *   `p`：打印分区表
*   第一步：`fdisk -l`
*   第二步：`fdisk /dev/vdb`
    *   `d`：删除
    *   `n`：新建分区
    *   `p`：显示分区信息
    *   `q`：退出
    *   `t`：修改分区id，使用`L`查看分区标签
        *   `swap`：格式化交换分区`mkswap /dev/vdb6`
    *   `w`：保存
*   第三步：建立主分区，主分区最多四个，所以第四个分区默认为拓展分区。
    *   `n`新建
    *   `p`主分区
    *   默认id
    *   分区起始默认
    *   分区大小自己指定

## 格式化分区

>   `mkfs.*`：使用`.`后面的参数，选择不同的格式进行格式化
>
>   `mount -a`：挂载`/etc/fstab`的文件重新执行

## SWAP分区管理

>   *   划分分区：`t`
>   *   设置标签：交换分区为82号标签
>   *   格式化：`mkswap /dev/vdb6`
>   *   挂载：`swapon -a /dev/vdb6`
>   *   卸载：`swapoff /dev/vdb6`
>   *   查看挂载分区：`swapon -s`
>   *   修改`/etc/fstab`进行开机自启动

## 用户参数配额

>   `mount -o usrquota /dev/sdb7 /public`挂载时激活参数
>
>   `edquota -u USER`：修改第一个`hard`的值，单位为`kb`
>
>   | Filesystem | blocks | soft      | hard           | inodes    | soft      | hard           |
>   | ---------- | ------ | --------- | -------------- | --------- | --------- | -------------- |
>   | 文件系统       | 块大小    | 软限制(超过警告) | 硬限制(客观限制，超过丢失) | inode节点个数 | 软限制(超过警告) | 硬限制(客观限制，超过丢失) |
>
>   `/etc/fstab`配置文件添加内容：`/dev/vdb2 /public/user xfs.userquota 0 0`
>

## 磁盘加密

>   `cryptsetup`加密文件，加密时需要在格式化的时候进行加密
>
>   *   加密：`cryptsetup lucksFormat /dev/vdb8`，输入大写`YES`和密码
>   *   打开：`cryptsetup open /dev/vdb8 name`，`name`名字可以自己取
>   *   格式化`mkfs.xfs /dev/mapper/name`
>   *   挂载`mount /dev/mapper/name /mnt`
>   *   关闭：`cryptsetup close name`，挂载原始设备也不能查看其中内容

