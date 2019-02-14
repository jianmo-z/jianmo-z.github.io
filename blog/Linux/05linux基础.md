# Linux基础

## 日志采集服务

>   查看日志状态：`systemctl status rsyslog.service`
>
>   **获取配置文件的帮助信息：`man 5 rsyslog.conf`**
>
>   日志：`*.*`：第一个`*`表示什么类型，第二个`*`表示该服务程序的日志级别
>
>   *   日志的位置：`/var/log/`
>       *   `/var/log/messages`：服务信息日志
>       *   `/var/log/secure`：系统登录日志
>       *   `/var/log/cron`：定时任务日志
>       *   `/var/log/maillog`：邮件日志
>       *   `/var/log/boot.log`：系统启动日志
>   *   日志的类型：
>       *   `auth`：pam产生的日志
>       *   `authpriv`：ssh，ftp等登录信息的验证信息
>       *   `cron`：时间任务相关
>       *   `kern`：内核
>       *   `lpr`：打印
>       *   `mail`：邮件
>       *   `mark(syslog)-rsyslog`：服务内部的信息，时间标识
>       *   `news`：新闻组
>       *   `user`：用户程序产生的相关信息
>       *   `uucp`：unix tounix copy，unix主机之间相关的通讯
>       *   `local 1-7`：自定义的日志系统
>
>
>   *   日志级别：记录的内容逐次减少
>       1.  `debug`调试信息：有调式信息的，日志信息最多
>       2.  `info`重要事件 ：一般信息的日志，最常用
>       3.  `notice`重要通知：最具有重要性的普通条件的信息
>       4.  `warning`警报：警告级别
>       5.  `err`错误：错误级别，阻止某个功能或者模块不能正常工作的信息 
>       6.  `crit`临界：严重级别，阻止整个系统或者整个软件哎能不能正常工作的信息
>       7.  `alert`：需要立即修改的信息
>       8.  `emerg`系统不可用：内核崩溃等严重信息
>       9.  `none`：什么都不记录
>   *   例：`*.*;mail.none    /var/log/message`，把所有服务的所有日志信息保存到`/var/log/meesage`文件中，不保存`mail`的信息。

##    日志同步

>配置文件`/etc/rsyslog.conf`，修改完重启服务`systemctl restart rsyslog`
>
>   *   客户端(日志发送方)：`*.*    @ipaddr`：一个`@`表示使用`udp`协议，两个`@`表示使用`tcp`协议
>   *   服务端(日志接收方)：`$ModLoad imudp`、`$UDPServerRun 514`，开启接收的模块，并且打开接收的端口
>   *   设置防火墙可以通过客户端的日志 / 关闭防火墙
>
>   日志采集的格式：`/etc/rsyslog.conf`
>
>   *   ```
>       $template LOGFMT, "%timegenerated% %FROMHOST-IP% %syslogtag% %msg% \n"
>       *.*    /var/log/test;LOGFMT
>       ```
>
>   *   `LOGFMT`：相当于定义了一个变量
>
>   *   `%timegenerated%`：显示日志时间
>
>   *   `%FROMHOST-IP%`：显示主机IP
>
>   *   `%syslogtag%`：日志记录目标
>
>   *   `%msg%`：日志内容
>

## 时间同步

>  配置文件`/etc/chrony.conf`、服务程序
>
>   *   服务端(时间源)：
>
>       ```
>       allow 172.25.254.0/24 ##允许那些客户端来同步本机时间，在配置文件的22行
>       local stratum 10 ##本机不同步任何主机的时间，本机作为时间源，在配置文件的29行
>       ```
>
>   *   客户端(同步时间源)：
>
>       ```
>       server 172.25.254.100 iburst ##本机立即同步172.25.254.100这台主机的时间
>       ```
>
>   设置完后需要重启同步时间服务：`systemctl restart chronyd.service`
>
>   查看时间同步源：`chronyc sources -v`

## 查看系统时间

>   `timedatectl`：查看系统详细
>
>   `timedatectl list-timezones `：查看时区列表
>
>   `timedatectl set-timezones Asia/Shanghai`：设置时区
>
>   `timedatectl set-time  "2018-11-11 11:11"`：设置时间
>
>   `timedatectl set-local-rtc 0/1` ：是否使用UTC时间
>
>   *   `0`设置为UTC时间，`1`设置为LOCAL时间
>
>   `cat /etc/adjtime`：查看时间

## 日志查看

>   `journalctl`：日志查看工具
>
>   *   `-n 3`：查看最近三条日志
>   *   `-p err`：查看错误日志
>   *   `-o verbose _PID=pid _COMM=command`：查看指定pid的日志，该进程可以是已经死亡的
>   *   `--since "2018-10-13 12:00"`：查看从什么时间开始的日志
>   *   `` --until "2018-10-14 12:00" `：查看从什么时间结束的日志
>
>   使用`systemd-journal`保存系统日志
>
>   1.  `mkdir /var/log/journal`建立一个目录保存`journal`日志
>   2.  `chgrp systemd-journal /var/log/journal`
>   3.  `chmod g+s /var/log/journal`
>   4.  `ps aux | grep systemd-journald`
>   5.  `killall -1 systemd-journald-pid`
>   6.  `ls /var/log/journal`，查看保存的文件

## 网络配置

>   1.  IP：由32位bit位组成
>
>   2.  子网掩码：用来划分网络区域。
>
>   3.  IP通信判定：网络位一致，主机位不一致
>
>   4.  网络通信工具：`ping`
>
>   5.  `ifconfig`
>
>       *   `ifconfig device ip/24`：设置ip地址和子网掩码
>
>
>       *   关闭网卡接口：`ifconfig 网卡名 down`
>       *   开启网卡接口：`ifconfig 网卡 up`
>       *   查看网卡所有的`ip`：`ip addr show`
>
>   6.  修改ip
>
>       *   图形修改
>           *   图形界面设置` nm-connection-editor `
>           *   命令模式下图形修改`nmtui`
>
>       *   命令修改
>           *   `nmcli `：后面可以加参数对网卡进行配置和连接与断开，`NetworkManager`服务必须开启，`device_name`为网卡名
>               *   `nmcli device show`：查看网卡信息
>               *   `nmcli device status device_name`：查看网卡服务接口状态信息
>               *   `nmcli device connect device_name`：启用网卡
>               *   `nmcli device disconnect device_name`：关闭网卡接口
>               *   `nmcli connection show`：查看网卡配置信息
>               *   `nmcli connection down device_name`：关闭网卡
>               *   `nmcli connection up device_name`：开启网卡
>               *   `nmcli connection delete device_name`：删除网卡信息
>
>       *   修改配置文件：`/etc/sysconfig/network-scripts/device_name`，`device_name`为网卡的配置文件名字，自行替换`redhat7/centos7`一般为`ifcfg-eth0`，配置的文件名为`ifcfg-`开头。
>
>           *   `DEVICE=eth0`：网卡的设备名
>           *   `ONBOOT=yes`：开机是否自启
>           *   `BOOTPROTO=dhcp/static/none`：三个中的一个，`dhcp`动态分配，`static`静态IP，`none`类似`static`
>           *   `IPADDR=172.25.254.108`：`IP`地址
>               *   配置多个`IP`，`IPADDR0`、`IPADDR1`、... ...
>           *   `PREFIX=24`/`NETMASK=255.255.255.0`：子网掩码
>               *   配置多个子网掩码对应`IP`，`PREFIX0`、`PREFIX1`、... ...
>           *   `NAME=eth0`：配置名字
>
>           示例：
>
>           单个IP配置
>
>           ```
>           DEVICE=eth0
>           ONBOOT=yes
>           BOOTPROTO=static
>           IPADDR=172.25.254.108 #IP设置仅供参考，不同情况，不同IP
>           PREFIX=24
>           GATEWAY=172.25.254.111 # 网关配置，见下面
>           NAME=eth0
>           ```
>
>           多个IP配置
>
>           ```
>           DEVICE=eth0
>           ONBOOT=yes
>           BOOTPROTO=static
>           IPADDR0=172.25.254.108 #IP设置仅供参考，不同情况，不同IP
>           PREFIX0=24
>           GATEWAY0=172.25.254.111 # 网关配置，见下面
>           IPADDR1=172.25.0.108 #IP设置仅供参考，不同情况，不同IP
>           PREFIX1=24
>           GATEWAY1=172.25.254.222 # 网关配置，见下面
>           NAME=eth0
>           ```
>
>   7.  lo回环接口
>
>       >   可以用来测试本机的通信协议是否完好，用于本机内部的通信。
>
>   8.  网关配置
>
>       >   `vim /etc/sysconfig/network`，全局网关，针对没有设定网关的网卡配置文件
>       >
>       >   查看防火墙策略：`firewall-cmd --list-all`
>       >
>       >   添加防火墙策略：`firewall-cmd --permanent --add-masquerade`，主机作路由转换
>       >
>       >   重新加载服务：`firewall-cmd --list-all`
>
>   9.  DNS解析配置
>
>       >   `vim /etc/resolv.conf`，配置文件位置，`DNS`服务器`nameserver 114.114.114.114`，也可以在网卡的配置文件中设置`DNS1=IP`。
>       >
>       >   `/etc/hosts`，本机暂存域名和IP的键值对，本地解析文件`IP 域名`
>       >
>       >   ​
>       >
>       >   在网络配置文件中可以添加`DNS1=8.8.8.8`或者其他的`IP`地址
>       >
>       >   如果远程的`dns`和本地的`host`域名解析冲突，通过修改`/etc/nsswitch.conf`来设置优先级别，在第39行。
>
>   10.  dhcp服务设置自己的DNS
>
>      >   当网卡使用`dhcp`模式的时候网卡会使用`dhcp`服务器的`DNS`，如果不需要`dhcp`的DNS提供的信息，把`/etc/sysconfig/network-scripts/ifcfg-eth0`里面加上`PEERDNS=no`，使用自己的`DNS`不使用`dhcp`提供的服务
>
>   11.  man手册的帮助文档
>
>        >   `/usr/share/doc/initscripts-9.49.37/sysconfig.txt`，其中的数字会不同版本号的原因，按`Tab`补齐就可以了。

## dhcp服务

>   配置文件`/etc/dhcp/dhcpd.conf`拷贝模板配置文件`cp /usr/share/doc/dhcp-4.2.5/dhcpd.conf.example /etc/dhcp/dhcpd.conf`
>
>   *   `yum install -y dhcp`，安装`dhcp`服务
>
>   *   `cp /usr/share/doc/dhcp-4.2.5/dhcpd.conf.example /etc/dhcp/dhcpd.conf`
>
>   *   `vim /etc/dhcp/dhcpd.conf`，编辑配置文件
>
>       *   `subnet`：分配的IP地址
>       *   `netmark`：子网掩码
>       *   `range IP1 IP2;`：分配的IP池范围
>       *   `option routers IP;`：网关
>
>   *   完整配置文件示例
>
> ```
> 
>       # dhcpd.conf
>       #
>       # Sample configuration file for ISC dhcpd
>       #
>
>       # option definitions common to all supported networks...
>       option domain-name "example.org";
>       option domain-name-servers ns1.example.org, ns2.example.org;
>
>       default-lease-time 600;
>       max-lease-time 7200;
>
>       # Use this to enble / disable dynamic dns updates globally.
>       #ddns-update-style none;
>
>       # If this DHCP server is the official DHCP server for the local
>       # network, the authoritative directive should be uncommented.
>       #authoritative;
>
>       # Use this to send dhcp log messages to a different log file (you also
>       # have to hack syslog.conf to complete the redirection).
>       log-facility local7;
>
>       # No service will be given on this subnet, but declaring it helps the 
>       # DHCP server to understand the network topology.
>
>
>       # This is a very basic subnet declaration.
>
>       subnet 172.25.254.0 netmask 255.255.255.0 {
>         range 172.25.254.50 172.25.254.80;
>         option routers 172.25.254.250;
>       }
> ```
>
>   *   服务端：`/var/lib/dhcpd/dhcpd.leases`
>
>   *   客户端：`/var/log/message`

