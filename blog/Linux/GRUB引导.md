# 系统引导修复

## 参考链接

>   http://www.cnblogs.com/klb561/p/8933967.html
>
>   https://blog.csdn.net/mao0514/article/details/51397193
>
>   https://blog.csdn.net/gatieme/article/details/59127020

## 问题简述

>   我的是redhat7.3系统，装完系统后出现了这个错误，引导错误

![GRUB引导错误](./Picture/GRUB引导错误.png)

## 解决问题

*   第一步找到`boot`，`ls`查看分区信息

    *   如果你是自己给boot单独的分区那么使用`ls (hd0,gpt1)/grub`来查看系统引导`boot`在那个分区
    *   如果不是的话使用如图的方式找出自己的`boot`分区在那里

    >   主要是为了找到`boot`分区

*   第二步临时设置引导

    *   `set prefix=(hd0,gpt7)/boot/grub2`

    *   `set root=(hd0,gpt7)`

        >   这个是我自己修复引导的时候设置的，`prefix`是设置GRUB，不同的分区是不同，根据自己的电脑找到正确的`boot`

*   第三步进入系统

    >   执行：`insmod normal`
    >
    >   执行：`normal`
    >
    >   此时就应该就进入系统了，到这里并没有完成，因为这个引导是暂时的如果下次重启还需要这样设置，所以让它永久生效是十分必要的。

*   第四步更新`grub`

    >`grub2-install /dev/sdb`安装`grub`
    >
    >我的硬盘是`128G + 1T`所以我有两个盘，虽然我的系统在1T机械硬盘的第七个分区，但是我设置grub是`grub2-install /dev/sda`

*   第五步结束掉了

    >试着重启下看是否恢复了，如果没有成功，检查下步骤或者找一下其他的教程毕竟每个人的环境不一样。希望你能顺利解决。

    ​

