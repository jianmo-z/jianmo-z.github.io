# VMware安装提示缺少kernel-headers和kernel-devel

## 参考链接

https://www.cnblogs.com/mylinux/p/5612168.html

## 解决问题

>由于问题已经解决不能重现所以我大概说一下问题，当我下载安装`VMware15`完成安装之后打开虚拟机的时候提示我找不到`kernel-headers`和`kernel-devel`，找不到就安装喽
>
><font size=5 color=red>最好使用自己系统对应版本的yum源</font>
>
>`yum install -y kernel-devel`
>
>`yum install -y kernel-headers`，提示没有找到包，但是上面的包提示安装成功了
>
>之后再打开`VMware`就可以顺利打开了
