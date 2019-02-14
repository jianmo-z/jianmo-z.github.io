# linux解压rar文件

## 参考链接

https://blog.csdn.net/caicaiatnbu/article/details/73385846

## 下载压缩包

https://www.rarlab.com/rar/rarlinux-x64-5.6.1.tar.gz

## 解压

>   `tar -zxvf rarlinux-x64-5.6.1.tar.gz`

## make

>   `cd rar `
>
>   `sudo make`,注意使用管理员权限,否则会失败

## 解压

>   1.  将rar文件解压到当前文件
>
>       >   `rar e filename.rar`
>
>   2.  将rar文件解压到filename目录下
>
>       >   `rar x filename.rar`

