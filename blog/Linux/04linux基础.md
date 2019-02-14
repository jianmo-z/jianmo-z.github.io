# Linux基础

## 进程动态监控

>   `top`：动态查看进程
>
>   *   按`1`显示CPU每个核的负载
>   *   按`s`修改刷新频率
>   *   按`c`依照CPU负载排序
>   *   按`m`依照内存大小排序
>   *   按`h`获取帮助
>   *   按`u`查看指定用户的进程，需要输入用户名
>   *   按`k`对指定用户进程发起信号
>   *   按`q`退出
>
> | PID  | USER | PR    | NI   | VIRT      |
> | ---- | ---- | ----- | ---- | --------- |
> | 进程id | 进程用户 | 人物优先级 | 优先级值 | 进程使用的虚拟内存 |
>
> | RES              | SHR  | %CPU   | %MEM  | TIME       | COMMAND |
> | ---------------- | ---- | ------ | ----- | ---------- | ------- |
> | 进程使用的未被换出的物理内存大小 | 共享内存 | CPU使用率 | 内存使用率 | 使用CPU的时间总计 | 命令名     |
>
## 控制服务`systemctl`

>`C/S`：server、client
>
>*   `pstree`：查看进程树
>*   `systemd`系统初始化进程
>*   进程控制命令`systemctl`
>    *   `ssh`，`client` ===> `sshd`，`server`
>    *   `status`：查看服务状态
>    *   `start`：开启服务
>    *   `restart`：重启服务
>    *   `stop`：停止服务
>    *   `reload`：重新加载服务配置
>    *   `disable`：设置服务，开机不自启动  
>    *   `enable`：设置服务，开机自启动
>    *   `mask`：设置无法启动，注销服务
>*   查看端口
>    *   `netstat -antulpe | grep :22`，查看22端口的程序

## linux查看本机ip

*   `ip addr show`，推荐使用，可以查到所有的ip地址
*   `ifconfig`，只能查看到一个ip地址

## 修改hostname

>`hostnamctl set-hostname yourhostname`，将`yourhostname`改成你要设置的名字即可。

## ssh服务

>   `ssh username@ip`，文本方式链接
>
>   *   `username`：登陆的用户名
>   *   `ip`：目标主机ip
>   *   `-X`：在链接成功后可以打开图形，比如摄像头`cheese`... ...
>
>   >   `sshd`，表示服务，在服务器端使用
>   >
>   >   `ssh`，客户端使用，连接远程服务。
>
>   *   `sshd = secure shell`
>
>   `第一次链接会在家目录下生成`~/.ssh/known_hosts`认证文件
>
>   *   key认证
>
>       *   第一步：`ssh-keygen`，在`~/.ssh/`生成公钥和密钥，三次回车，不设置就回车。
>
>       *   第二步：进入`~/.ssh/`，有两个文件`id_rsa(私钥)`和`id_rsa.pub(公钥)`
>
>       *   第三步：使用公钥加密主机`ssh-copy-id -i id_rsa.pub root@ip`
>
>       *   第四步：把`id_rsa`发送给目标主机，且需要放在`~/.ssh`目录下。
>
>           ```
>           ssh-keygen
>           cd ~/.ssh/
>           ssh-copy-id -i id_rsa.pub root@172.25.254.108 
>           scp ./id_rsa root@172.25.254.108:/root/.ssh/
>           ```
>           >   `ssh`远程连接目标主机就不需要再输入密码，完成所有操作了。。。
>
>   *   访问控制
>
>       配置文件：`/etc/ssh/sshd_config`
>
>       *   字段：`PasswordAuthentication yes`，是否允许用户通过密码登陆
>       *   字段：`PermitRootLogin yes`，是否允许`root`登陆
>       *   字段：`Allowusers username1 username2`，允许登陆的白名单，多个用户用空格分隔开
>       *   字段：`Denyusers username1 username2`，不允许登陆的黑名单，多个用户用空格分隔开
>
>   *   配置文件生效需要重启`sshd`服务
>
>   *   查看配置文件的写法：`man 5 sshd_config`
>
>   *   登陆信息：`vim /etc/motd`，在用户登陆的时候提示信息，文件内容就是登陆后的显示信息。
>
>   *   用户审计：
>
>       *   `w -i`：查看正在登陆系统用户，显示ip
>       *   `w -f`：查看使用来源，显示主机名
>       *   `last`：查看谁登录过你的`shell`
>       *   `lastb`：试图登录但是没有成功
>

## scp服务

>   `scp sendfile username@ip:absolute_path`，上传文件
>
>   `scp username@ip:absolute_path_file dir `，下载文件
>
>   *   `-r`：下载/上传目录时会用到，递归下载/上传文件
>   *   `-p`：保存文件的信息(时间戳...)下载/上传到目的主机
>   *   `absolute_path`：**绝对路径**

## 忘记root密码？？？

>   *   第一步：重启电脑，进入系统选择界面按`e`。
>   *   第二步：找到倒数第二行把`ro`当前行的后面的内容删掉。并把`ro`改为`rw  rb.break`，再按`Ctrl + x`，启动系统。
>   *   第三步：进入系统后，`chroot /sysroot/`进入系统分区，并使用`passwd root`修改`root`用户密码。
>   *   第四步：在根目录下创建`touch /.autorelabel`，如果不创建系统启动会出问题。
>   *   第五步：使用两次`exit`来重启电脑，使用修改后的密码登录。

## rsync 远程同步

>速度快，默认会忽略文件属性，链接文件，设备文件
>
>参数：
>
>*   `-r`：同步目录
>*   `-p`：同步权限
>*   `-o`：同步文件所有人
>*   `-g`：同步文件所有组
>*   `-t`：同步文件时间戳
>*   `-l`：同步链接文件
>*   `-D`：同步设备文件

## 查看文件大小

>   `du -sh dir`
>
>   参数：
>
>   *   `-s`：显示总的文件大小
>   *   `-h`：人类容易辨别的字节大小单位

## 打包文件 tar

>`-x`：解包
>
>`-c`：创建一个压缩包
>
>`-v`：显示过程详情信息
>
>`-f`：指定打包后的名字
>
>`-t`：查看归档文件内容
>
>`-r`：添加文件到归档，第一个为归档，后面的是要添加的文件
>
>`--get`：解挡指定文件，`tar f etc.tar --get file`
>
>`--delete`：删除归档指定的文件，`tar f etc.tar --delete file`
>
>`-C`：指定解档目录
>
>`-z`：使用`gzip`压缩
>
>`-J`：使用`xz`压缩
>
>`-j`：使用`gzip2`压缩

## 压缩

>   *   `zip`压缩，压缩效率高，推荐使用
>       *   `zip -r filename.tar.zip etc.tar`
>       *   `unzip  filname.tar.zip`
>   *   `gzip`压缩，压缩效率高，推荐使用+1
>       *   `gzip filname.tar`
>       *   `gunzip filname.tar.gz`
>   *   `bzip2`压缩，压缩效率低
>       *   `bzip2 filname.tar`
>       *   `bunzip2 filname.tar.bz2`
>   *   `xz`压缩，压缩效率最高，很慢
>       *   `xz filname.tar`
>       *   `unxz filname.tar.xz`
