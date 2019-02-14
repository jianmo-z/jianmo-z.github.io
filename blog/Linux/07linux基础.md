# Linux基础

## netstat命令

>   常用组合`netstat -antlpe`
>
>   *   `-a`：显示所有信息
>   *   `-n`：显示数字地址
>   *   `-t`：只显示`TCP`协议
>   *   `-l`：只显示监听状态的端口
>   *   `-p`：显示进程`ID`
>   *   `-e`：显示额外信息

## 挂载/取消挂载

>*   `mount -t type dev dir`
>    *   `-t`：指定挂载的设备类型，和`type`类型，可以不指定
>    *   `dev`：要挂载的设备
>    *   `dir`：挂载的目录点，一般为`/mnt`，最好是一个空目录
>
>*   `umount -t type dir`
>
>    *   `-t`：同上，非必选
>    *   `dir`：已经挂载的点
>
>*   挂载`ntfs`格式的硬盘
>
>    [点击跳转](http://39.106.165.33/#!./blog/etc/%E7%A1%AC%E7%9B%98%E6%8C%82%E8%BD%BD%E5%87%BA%E7%8E%B0ntfs%E9%97%AE%E9%A2%98.md)查看教程

## yum本地仓库配置

>   *   使用`mount`将系统镜像挂载到`/mnt/ISO`，如果`/mnt/ISO`目录不存在则新建`/mnt/ISO`目录
>   *   配置`yum`仓库文件
>
>        ```
>        [rhel7.3]
>
>        name=rhel 7.3
>        baseurl=file:///mnt/ISO
>        gpgcheck=0
>        ```
>
>        *   第一行：`[rhel7.3]`：不能有空格，否则会报错
>        *   第二行：`name`：仓库名
>        *   第三行：`baseurl`：路径名
>        *   第四行：`gpgcheck`：是否校验

## yum远程仓库

>   *   第一步：安装`httpd`服务，然后使用`systemctl start httpd`启动服务，使用`systemctl enable httpd`注册到开机自启中。
>
>   *   第二步：服务器默认加载路径`/var/www/html/`，可以在该目录下写自己的测试页面。
>
>   *   第三步：增加防火墙策略，否则别的主机无法访问，要么暂时关掉。。。。。。
>
>   *   第四步：在`/var/www/html/`新建一个目录`yum`，将镜像挂载到`/var/www/html/yum/`目录下。
>
>   *   第五步：修改`baseurl=http://IP/DIR`，`IP`就是远程仓库的`IP`记得加路径，配置文件和本地仓库一样，只是`baseurl`的不同。
>
>       例：`baseurl`不同的主机和不同的路径
>
>   ```
>   [rhel7.3]
>
>   name=rhel7.3
>   baseurl=http://172.25.254.208/yum/yum_iso/
>   gpgcheck=0
>   ```
>
>   *   使用`yum clean all `和`yum makecache`测试是否配置好了

## 开机自动挂载

>   *   方法一：按照格式修改`/etc/fstab`即可，可参考[点击链接](http://39.106.165.33/#!./blog/etc/./%E4%B8%80%E7%B3%BB%E5%88%97%E9%97%AE%E9%A2%98.md)
>   *   方法二：`/etc/rc.d/rc.local`，将挂载文件的命令写进去就可以了，需要绝对路径。然后给该文件加执行权限`chmod +x /etc/rc.d/rc.local`

## yum命令

>   *   `install softwarename`：安装`softwarename`命令
>   *   `reinstall softwarename`：重新安装软件`softwarename`
>   *   `repolist`：列出设定`yum`源信息
>   *   `remove softwarename`：卸载软件`softwarename`
>   *   `list package_name`：查看软件源中是否有软件`package_name`
>   *   `list all`：查看所有的软件包
>   *   `list installd softwarename`：查看安装的软件名
>   *   `list available`：列出可用的软件安装
>   *   `clean all`：清空`yum`的缓存
>   *   `search keyword`：根据软件信息搜索软件名
>   *   `yum whatprovides filename`：在`yum`源中查找`filename`文件的软件包
>   *   `yum update software`：更新指定的软件`software`，不接最后一个参数表示更新所有
>   *   `history list all`：查看安装历史
>   *   `history undo ID`：撤销安装软件包，ID号通过`history list all`查询
>   *   `--downloadonly`：从yum下载安装包

## rpm 

>   `rpm -ivh`，常用
>
>   *   `-i`：安装
>   *   `-v`：显示安装过程信息
>   *   `-h`：进行加密方式为hash
>   *   `-e`：卸载
>   *   `-qa`：查询系统中安装的所有软件名称，使用管道查询软件
>   *   `-pq name.rpm`：查询软件包安装后的名字
>   *   `-ql name`：查看软件安装生成的文件，不要加`.rpm`后缀
>   *   `-qlp name.rpm`：查看软件安装后生成的文件
>   *   `--force`：强制安装，不能忽略依赖性
>   *   `--nodeps`：忽略软件的依赖性
>   *   `-qi `：查看软件的信息，由软件的开发商写
>   *   `--scripts`：检测软件在安装或者卸载过程中执行的动作

## 第三方源的搭建

学会`man createrepo`，`-v`显示过程

>   把所有的rpm软件包放到一个文件夹中，执行`createrepo -v /Software/`，生成第三方的仓库，该目录下会生成一个`repodata`的文件，修改`yum.repo`将生成的第三方的仓库路径添加到配置文件中

