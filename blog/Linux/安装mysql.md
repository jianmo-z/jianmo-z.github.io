# 安装数据库

## 参考链接
>   https://www.cnblogs.com/LvLoveYuForever/p/5585197.html
>   https://blog.csdn.net/jxq0816/article/details/79797304

## 使用yum安装

```
yum install -y mariadb-devel
yum install -y mariadb-server
yum install -y mariadb
systemctl start mariadb
systemctl enable mariadb
```

>   前三行是安装数据库和一些基础的配置等
>
>   第四行启动数据库的服务
>
>   第五行将数据库添加到开机自启中

## 配置root密码

>   刚安装完的数据库是需要设置密码的使用`mysqladmin -u root -p password passwd`，`passwd`是你要设置的`root`密码，回车会提示输入密码，因为是新安装所以没有密码直接再一次回车就可以了。

## 登录到Mysql

>   输入`mysql -u root -p`回车，然后输入刚才设置的密码就可以了
>
>   `show databases;`查看数据库
