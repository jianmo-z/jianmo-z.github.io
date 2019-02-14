## Linux基础

## LVM逻辑卷

*   `pv`物理卷，被`lv`命令处理过的物理分区
*   `vg`物理卷组，被组装到一起的物理卷
*   `pe`物理扩展，`lvm`设备的最小单元，`lvm`是`pe`的最小单元
*   `lvm`逻辑卷，直接使用的设备，可以增大缩减并保持原有数据不变
*   创建LVM
    1.  `pvcreate /dev/vdb1`，创建一个分区，前提需要一个分区，使用`fdisk`分区，标签为`LVM`
    2.  ``vgcreate vg0 /dev/vdb1`，后面的参数是，vg的名字和要组合的硬盘内存
    3.  `lvcreate -L 20M -n lv0 vg0`
    4.  `mkfs.xfs /dev/vg0/lv0`，格式化分区
    5.  `mount /dev/vg/lv0 /mnt`，挂载

## 查看信息

*   `pvs`：查看`pv`列表信息
*   `lvs`：查看`lv`列表信息
*   `vgs`：查看`vg`列表信息

## LVM减小和扩容

### xfs格式

*   当vg剩余容量充足
    *   扩展：`lvextend -L 80M /dev/vg0/lv0`
    *   文件系统拉伸：`xfs_growfs /dev/vg0/lv0`
*   当vg不足时，需要拓展vg大小
    *   `pvcreate /dev/vdb2`
    *   `vgextend vg0 /dev/vdb2`
    *   `lvextend -L 200M /dev/vg0/lv0`
    *   `xfs_growfs /dev/vg0/lv0`

### ext格式

> 针对ext文件系统的设备拉伸和缩减，只能热拉伸不能热缩减
>
> ```
> umont /mnt
> mkfs.ext4 /dev/vg0/lv0
> mount /dev/vg0/lv0 /mnt
> ```

*   拉伸分区大小

    *   需要一块格式化为`ext4`的文件系统
    *   `lvextend -L 250M /dev/vg0/lv0`
    *   `resize2fx /dev/vg0/lv0`

*   缩减分区大小

    *   `umont /dev/vg0/lv0`
    *   `e2fsck -f /dev/vg0/lv0`
    *   `resize2fs /dev/vg0/lv0 100M`
    *   `lvreduce -L 100M /dev/vg0/lv0`
    *   `mount /dev/vg0/lv0 /mnt`

*   缩减`vg`

    *   `vgreduce vg0 /dev/vdb2`
    *   `vgextend vg0 /dev/vdb2`

*   数据迁移

    *   `pvmove /dev/vdb1 /dev/vdb2`

    *   `vgreduce vg0 /dev/vdb1`

    *   `pvremove /dev/vdb1`


### LVM快照

*   创建快照：`lvcreate -L 40M -n lv0-backup -s /dev/vg0/lv0`
*   重新挂载：`mount /dev/vg0/lv0-backup /mnt`
*   PS：如果截取数据大于10M，会损坏设备，自动卸载
*   恢复快照
    *   `lvremove /dev/vg0/lv0-backup`
    *   `lvcreate -L 40M -n lv0-backup -s /dev/vg0/lv0`，相当于`reset`
*   删除LVM
    *   `lvremove /dev/vg0/lv0-backup`
    *   `lvremove /dev/vg0/lv0`
    *   `vgremove vg0`
    *   `pvremove /dev/vdb1`

## ftp服务

*   服务程序
    *   安装`yum install -y vsftpd`
    *   `systemctl start vsftpd`
    *   `systemctl enable vsftpd`
    *   访问数据的端口：21
    *   数据传输端口：> 1024的随机端口
    *   默认发布目录
        *   匿名用户登录`lftp 172.25.254.100`，默认目录`/var/ftp`
        *   用户登录：`lftp 172.25.254.100 -u username`，默认在家目录下
    *   配置文件：`/etc/vsftpd/vsftpd.conf`
    *   查看配置文件：`rpm -qc vsftpd`


*   客户端`yum install lftp`

## ftp的安全部署

*   报错信息和命令
    *   `?`：查看命令
    *   500报错：权限过大
    *   530报错：认证失败
    *   550报错：服务本身不允许
    *   553报错：文件系统权限过小 
    *   上传文件命令`put`

## ftp匿名用户配置

*   匿名用户登录：`anonymous_enable=YES`
*   匿名用户上传文件：`anon_upload_enable=YES`，针对匿名用户
    *   修改权限：`chmod 775 /var/ftp/pub`
    *   修改属组：`chgrp ftp /var/ftp/pub`
*   匿名用户新建目录：`anon_mkdir_write_enable=YES`
*   匿名用户删除目录：`anon_other_write_enable=YES`
*   修改匿名用户的家目录：`anon_root=/westos`，重新指定匿名用户登录的家目录。
*   匿名用户下载文件：`anon_world_readable_only=NO`，针对匿名用户
*   匿名用户的`umask`：`anon_umask=066`
*   匿名用户上传文件的身份：
    *   `chown_uploads=YES`，打开上传身份设置
    *   `chown_username=student`，设置用户名
*   最大上传速率
    *   `anon_max_rate=102400` 单位：字节
*   最大连接个数
    *   `client_connects=5`

## ftp本地用户配置

*   本地用户：`local_enable=YES`
*   上传文件：`write_enable=YES`，针对本地用户
*   `local_root=/westos`：本地用户的默认家目录
*   `local_umask=xxx`，本地用户上传软件权限
*   `chroot_local_user=YES`，禁止本地用户登录后锁定到家目录，PS：需要去掉对家目录的写权限，`chmod u-x /home/kiosk`，否则会报错
*   切换路径黑/白名单设置
    *   `chroot_local_user=NO`，需要自己新建`/etc/vsftpd/chroot_list`
        *   设置为`NO`，`chroot_list_file=/etc/vsftpd/chroot_list`是黑名单
        *   设置为`YES`，`chroot_list_file=/etc/vsftpd/chroot_list`是白名单
    *   `chroot_list_enable=YES`
    *   `chroot_list_file=/etc/vsftpd/chroot_list`
*   `/etc/vsftpd/ftpusers`：永久黑名单
*   `/etc/vsftpd/user_list`：临时黑名单
    *   需要设置`userlist_enable=YES`下面的才会生效
    *   设置`/etc/vsftpd/vsftpd.conf`的`userlist_deny=NO`，`/etc/vsftpd/user_list`变成了白名单
    *   设置`/etc/vsftpd/vsftpd.conf`的`userlist_deny=YES`，`/etc/vsftpd/user_list`变成了黑名单

## ftp虚拟用户配置

>   *   用户列表创建，假设为`westos`，可以加多个
>
>       ```
>       username1
>       password1
>       username2
>       password2
>       ```
>
>   *   加密`db_load -T -t hash -f /etc/vsftpd/westos /etc/vsftpd/westos.db`
>
>   *   `pam`配置文件`/etc/pam.d/westos`，创建一个文件内容如下
>
>       ```
>       account required pam_userdb.so db=/etc/vsftpd/westos
>       auth required pam_userdb.so db=/etc/vsftpd/westos
>       ```
>
>       >   账户和验证信息，`db=/etc/vsftpd/westos`会自动默认加`db`后缀，所以不需要加
>
>   *   设置配置文件`vim /etc/vsftpd/vsftpd.conf`
>
>       *   `pam_service_name=westos`，pam的加密文件名
>       *   `guest_enable=YES`，允许访客模式登录
>
>   *   虚拟用户的独立家目录`/etc/vsftpd/vsftpd.conf`
>
>       *   家目录：`local_root=/ftphome/$USER`，设置每个用户的家目录`$USER`指代用户名是`shell`的一个全局变量，让配置文件可以识别这个shell变量`user_sub_token=$USER`
>
>   *   独立配置用户权限`/etc/vsftpd/vsftpd.conf`
>
>       *   配置文件添加内容`user_config_dir=/etc/vsftpd/userconf`，在该目录下创建该用户的配置文件，文件名为用户名，上传下载的配置，例如：`anon_upload_enable=YES`

## 防火墙

*   `firewall-cmd --list-all`，列出防火墙策略
*   `firewall-cmd --permanent --add-service=ftp`，永久添加`ftp`到防火墙策略，选项`--permanent`表示永久生效
*   `firewall-cmd --reload`，重新加载配置文件


## SELinux内核级别的加强防火墙

>配置文件：`/etc/selinux/config `
>
>临时修改：`setenforce 0`
>
>*    `0`：警告模式
>*   `1`：强制模式
