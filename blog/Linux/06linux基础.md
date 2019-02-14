# Linux基础

## 虚拟机的安装

>   关于这部分我不想写，个人觉得没必要，多踩坑多百度，自然就能解决。本人装系统已经装吐了，所以真的不想写了，请自行百度。

## 虚拟机管理命令

*   `virt-manager`：超级用户执行，开启虚拟机管理器

*   `virsh list`：查看正在运行的虚拟机

    *   `virsh list --all`：查看所有的虚拟机状态

*   `virsh start 虚拟机名`：打开一个虚拟机

*   `virt-viewer 虚拟机名`：查看一个虚拟机

*   `virsh shutdown 虚拟机名`：关闭一个正在运行的虚拟机，需要进入系统后才可以关闭

*   `virsh desroy 虚拟机名`：虚拟机直接断电关机

*   `virsh undefine 虚拟机名`：删除虚拟机


## 复制/移动虚拟机

*   第一步拷贝`系统文件`：`/var/lib/libvirt/images/`目录下的`.qcow2`的文件，不同的名字表示不同的虚拟机
*   第二部拷贝`配置文件`：`/etc/libvirt/qemu`目录下对应的虚拟机的配置文件
*   第三步创建`创建虚拟机`：要求拷贝完母盘和配置文件，`virsh create 配置文件`，需要将母盘移动到`/var/lib/libvirt/images`目录中否则会提示找不到文件，这个恢复是一次性的
*   第四步`恢复虚拟机`：`virsh define 虚拟机名.xml`，`xml`文件是虚拟机的配置文件

## 脚本安装虚拟机

>以`.sh`结尾
>
>第一行`#!/bin/bash`指定解释器
>
>*   自动安装虚拟机脚本，所有的命令都是在一行上，所以需要加` \`
>
>    ```
>    #!/bin/bash
>
>    virt-install \
>    --cdrom /镜像路径 \
>    --ram 1024  \
>    --cpus 1 \
>    --disk /var/lib/libvirt/images/test.qcow2,bus=virtio,size=10 \
>    --name test \
>    --network bridge=br0,model=virtio
>    ```
>    *   `--cdrom`：镜像的路径
>    *   `--ram`：内存分配的大小
>    *   `cpus`：分配的CPU的个数
>    *   `disk`：生成的母板的位置，`bus`：接口的io类型为`虚拟io`，`size`：硬盘大小`10GB`
>    *   `--name`：虚拟机的名字
>    *   `--network`：网络模式，`bridge=br0`：从物理网卡`br0`上桥接，`model`：模式为`虚拟io`

## 脚本制作虚拟机快照

```
#!/bin/bash
qemu-img create -f qcow2 -b \
/var/lib/libvirt/images/$1.qcow2 \
/var/lib/libvirt/images/$2.qcow2

virt-install \
--name $2 \
--ram 1024 \
--cpus 1 \
--disk /var/lib/libvirt/images/$2.qcow2,bus=virtio \
--network bridge=br0,model=virtio \
--import &
```

## 脚本

>   `$1`：脚本的第一个参数
>
>   `$2`：脚本的第二个参数

## reset脚本实现

```
#!/bin/bash

virsh destroy $1
rm -rf /var/lib/libvirt/images/$1.qcow2
qemu-img create -f qcow2 \
-b /var/lib/libvirt/images/$2.qcow2 \
/var/lib/libvirt/images/$1.qcow2

virsh start $1
virt-viewer $1 &
```



