# Linux基础

## kickstart自动安装系统脚本

*   第一步：`yum install -y system-config-kickstart httpd`安装服务
*   第二步：`system-config-kickstart`，配置安装文件
*   第三步：给`ks.cfg`添加安装的脚本，即安装系统基础安装包和配置yum等
*   第三步：使用`ksvalidator`对配置文件进行检测
*   第四步：共享配置文件，使用`httpd`服务共享文件

```
#!/bin/bash

virt-install \
--name $1 \
--ram 1024 \
--cpus 1 \
--disk /var/lib/libvirt/images/$1.qcow2,bus=virtio,size=10 \
--network bridge=br0,model=virtio \
--location http://172.25.254.8/yum/ \
--extra-args ks=http://172.25.254.8/ks.cfg &
```

ks.cfg的配置文件，需要添加安装包文件

```
#platform=x86, AMD64, 或 Intel EM64T
#version=DEVEL
# Install OS instead of upgrade
install
# Keyboard layouts
keyboard 'us'
# Root password
rootpw --iscrypted $1$Jpz4OVkL$kzqAMWU4j3iXUZMZOX.nA.
# Use network installation
url --url="http://172.25.254.8/yum/"
# System language
lang en_US
# Firewall configuration
firewall --disabled
# System authorization information
auth  --useshadow  --passalgo=sha512
# Use graphical install
graphical
firstboot --disable
# SELinux configuration
selinux --disabled

# Network information
network  --bootproto=dhcp --device=eth0
# Reboot after installation
reboot
# System timezone
timezone Africa/Abidjan
# System bootloader configuration
bootloader --location=mbr
# Clear the Master Boot Record
zerombr
# Partition clearing information
clearpart --all --initlabel
# Disk partitioning information
part swap --fstype="swap" --size=1024
part /boot --fstype="xfs" --size=400
part / --fstype="xfs" --grow --size=1

%packages
@base
lftp
%end

%post
cat >> /etc/yum/yum.repo.d/rhel.repo << EOF
[rhel]

nam=pip
baseurl=http://172.25.254.8/yum/
gpgcheck=0
%end
```

## 延时任务

*   `at 14:27`：定时任务，在某一格式执行什么命令，`Ctrl + d`发起任务
*   `at now+1min`：一分钟后执行任务
*   `at -l`：查看任务列表
*   `at -c ID`：查看任务的内容
*   `at -r ID`：取消任务执行
*   当任务有输出时，输出会以邮件的形式发送给at任务的发起者，例`echo hello`
*   `at`的黑白名单
    *   `/etc/at.deny`：`at`命令的黑名单中的用户无法执行定时任务
    *   `/etc/at.allow`：`at`命令的白名单，之有名单中出现的用户才可以执行at命令，优先级高于黑名单，当白名单存在黑名单失效。如果 不存在则新建。

## 定时任务

`systemctl status crond`，查看定时任务控制服务

*   `crontab -e -u root`：编辑定时任务
*   定时任务格式：`分、时、日、月、周`。
*    `* * * * * `表示每分钟执行一次
*   `*/2 * * * *`：每两分钟执行一次
*   `*/2 09-17 * * *`：每9点到17点每隔两分钟执行一次
*   `*/2 */2 * * *`：每过两小时零两分钟执行一次
*   `*/2 09-17 1 3,5 5`：三月和五月的每周周五和三月一日、五月一日，9点到17点每两分钟执行一次
*   `*/2 09-17 * * 5`：每周周五09点到17点每隔两分钟执行一次
*   当程序开启时定时任务生效

>   配置文件路径`/var/spool/cron/username`最后一个为用户名
>
>   *   `crontab`
>       *   `crontab -e -u`：编辑指定用户的定时任务表
>       *   `crontab -l -u`：查看指定用户的定时任务
>       *   `crontab -r -u`：删除指定用户的定时任务
>   *   自定义定时配置文件，该方式的定时任务使用`crontab -l`不能查看
>       *   `/etc/cron.d/`在该目录下新建文件就可`* * * * *  root  action`
>   *   黑白名单
>       *   `/etc/cron.deny`：黑名单中的用户无法执行定时任务
>       *   `/etc/cron.allow`：命令的白名单，之有名单中出现的用户才可以执行at命令，优先级高于黑名单，当白名单存在黑名单失效。如果 不存在则新建。
>       *   这两个名单都不会影响`/etc/cron.d/`目录中的定时任务的发起和执行

## 查看邮件

*   `mail -u root`：查看指定用户的邮件，不指定则查看当前用户的邮件
*   `1`：查看第一封邮件
*   `q`：退出
*   `> /var/spool/mail/root`：清空邮箱 

## 系统临时文件的管理

*   临时文件的存储位置：`/tmp/`
*   临时文件的配置文件：`/usr/lib/tmpfile.d/tmp.conf`
    *   自定义清理文件`westos`：`d /mnt/westos 777 root root 5s`
*   生成文件的`systemd-tmpfiles --create /usr/lib/tmpfile.d/`读取目录里所有文件并按照其规则去建立
*   清理文件的`systemd-tmpfiles --clean /usr/lib/tmpfile.d/tmp.conf`

