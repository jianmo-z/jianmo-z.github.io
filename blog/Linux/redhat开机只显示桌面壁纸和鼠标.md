# redhat开机只显示桌面壁纸和鼠标

<font size=6 color=red> 注意：使用自己系统版本的镜像安装，否则可能会引起不良反应</font>

> 以下两条命令均为root用户权限执行
>
>   * 进入到命令模式下:`init 3`
>   * 重新安装gnome：`yum reinstall -y gnome-*`

> 经过修改发现我是修改了gnome的默认显示的工作区窗口个数导致的该回原来的就可以了
