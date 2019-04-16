# Docker入门学习

[TOC]

## Docker 镜像

> Docker镜像含有启动镜像所需要的**文件系统及其内容**，因此，其用于创建并启动docker容器
>
> * 采用分层构建机制，最底层为bootfs，然后是rootfs
>   * bootfs：用于系统引导的文件系统，包括bootloader和kernel，容器启动完成后会被卸载节约内存资源
>   * rootfs：位于bootfs之上，表现为docker容器的根文件系统
>     * 传统模式中，系统启动之时，内核挂载rootfs时会首先将其挂载为"只读"模式，完整性自检完成后将其重新挂载为读写模式；
>     * docker中，rootfs由内核挂载为"只读"模式，然后通过"联合挂载"技术额外挂载一个"可写"层。

## Docker Image Layer

* 位于下层的镜像称为父镜像(parent iamge)，最底层的称为基础镜像(base image)
* 最上层为“可读写”层，其下的均为“只读”层

## Docker Registry

> 启动镜像时，docker daemon 先从本地获取镜像，如果本地不存在，则从远程下载。要求使用https

## 镜像生成

* Dockerfile
* 基于容器制作
* Docker Hub automated builds

## 基于容器制作镜像

* Usage：`docker commit [OPTIONS] CONTAINER [REPOSITORY[:TAG]]`

  > `docker commit -p b1 `
  >
  > 基于正在运行的`b1`容器制作镜像，`-p`参数表示暂停`b1`镜像然后制作，执行完该命令后会生成一个没有仓库没有TAG的镜像。
  >
  > 使用`docker tag hash_value [REPOSITORY[:TAG]]`为一个没有标签的镜像打上标签。
  >
  > 使用`-c`参数，修改`list`，修改镜像开启后运行的命令`CMD`，`-a`指定作者信息等等

* 删除镜像

  > `docker image rm pip/httpd:v0.1-1`删除镜像时候，只是删除了TAG当TAG为0时才真正的删除。(一个容器可以有多个标签)

* 制作镜像并修改参数

  > ` docker commit -a "jianmo <jianmo.pip@gmail.com>" -c 'CMD ["/bin/httpd" ,"-f", "-h", "/data/html"]' -p b1 ainihu/httpd:v0.2.0`
  >
  > 参数：
  >
  > * `-a`：指定作者
  > * `-c`：修改列表，即环境变量
  > * `-p`：暂停容器
  > * `ainihu/httpd:v0.2.0`：仓库名和版本号，注意用`ainihu/httpd`在远程仓库必须存在否则会报错，`:`后面的是版本号

* 镜像推到远程仓库

  > 推镜像之前需要登录`docker login -u ainihu`，`-u`指定用户名，登录成功会提示
  >
  > 登录成功后才厚权限将镜像推到镜像服务器：`docker push ainihu/httpd:v0.2.0 `

  ```
  root@msi-localhost:~# docker login -u ainihu
  Password: 
  WARNING! Your password will be stored unencrypted in /root/.docker/config.json.
  Configure a credential helper to remove this warning. See
  https://docs.docker.com/engine/reference/commandline/login/#credentials-store
  
  Login Succeeded
  root@msi-localhost:~# docker push ainihu/httpd:v0.2.0  
  The push refers to repository [docker.io/ainihu/httpd]
  abbd7aa6d78b: Pushed 
  0b97b1c81a32: Mounted from library/busybox 
  v0.2.0: digest: sha256:9d6e360f317a3a4824969ec42cdf210fe1a5cc7b1b0b68e5dca08a6b3455d53f size: 734
  ```

* `docker`查看环境变量

  > `docker inspect t2`，查看t2容器的环境变量

### 在阿里云上建立仓库并导入

> 查看官方的步骤：<https://cr.console.aliyun.com/repository/cn-hangzhou/ainihu/httpd/details>

## 镜像保存打包和装入

* 镜像打包：`Usage:  docker save [OPTIONS] IMAGE [IMAGE...] `

  > ```
  > root@msi-localhost:~# docker save -o image.gz ainihu/httpd
  > ainihu/httpd         ainihu/httpd:v0.1.0  ainihu/httpd:v0.2.0  
  > root@msi-localhost:~# docker save -o image.gz ainihu/httpd:v0.1.0 ainihu/httpd:v0.2.0 
  > root@msi-localhost:~# ls
  > image.gz
  > ```
  >
  > `-o`：指定输出到那个文件中，生成的文件可以使用`docker load`

* 镜像导入：`Usage:  docker load [OPTIONS]`

  > ```
  > root@msi-localhost:~# docker image ls
  > REPOSITORY                                       TAG                 IMAGE ID            CREATED             SIZE
  > registry.cn-hangzhou.aliyuncs.com/ainihu/httpd   v0.2.0              9cfb3e04f0e9        37 minutes ago      1.2MB
  > nginx                                            alpine              031c45582fce        36 hours ago        16.1MB
  > busybox                                          latest              af2f74c517aa        9 days ago          1.2MB
  > nginx                                            latest              881bd08c0b08        5 weeks ago         109MB
  > busybox                                          <none>              d8233ab899d4        8 weeks ago         1.2MB
  > quay.io/coreos/flannel                           v0.11.0-amd64       ff281650a721        2 months ago        52.6MB
  > redis                                            3.2-alpine          6e94a98d3442        6 months ago        22.9MB        
  > root@msi-localhost:~# docker load -i ./image.gz 
  > 20092f16a244: Loading layer [==================================================>]   2.56kB/2.56kB
  > Loaded image: ainihu/httpd:v0.1.0
  > Loaded image: ainihu/httpd:v0.2.0
  > root@msi-localhost:~# docker image ls
  > REPOSITORY                                       TAG                 IMAGE ID            CREATED             SIZE
  > ainihu/httpd                                     v0.1.0              cae716686bdf        3 minutes ago       1.2MB
  > ainihu/httpd                                     v0.2.0              9cfb3e04f0e9        37 minutes ago      1.2MB
  > registry.cn-hangzhou.aliyuncs.com/ainihu/httpd   v0.2.0              9cfb3e04f0e9        37 minutes ago      1.2MB
  > nginx                                            alpine              031c45582fce        36 hours ago        16.1MB
  > busybox                                          latest              af2f74c517aa        9 days ago          1.2MB
  > nginx                                            latest              881bd08c0b08        5 weeks ago         109MB
  > busybox                                          <none>              d8233ab899d4        8 weeks ago         1.2MB
  > quay.io/coreos/flannel                           v0.11.0-amd64       ff281650a721        2 months ago        52.6MB
  > redis                                            3.2-alpine          6e94a98d3442        6 months ago        22.9MB
  > root@msi-localhost:~# 
  > ```
