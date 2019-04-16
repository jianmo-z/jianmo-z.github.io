# Docker入门学习

[TOC]

## Docker Registry分类

* `Sponsor Registry`：第三方的`registry`，供客户和`Docker`社区使用
* `Mirror Registry`：第三方的`registry`，只让客户使用
* `Vendor Registry`：由发布`Docker`镜像的供应商提供的`registry`
* `Private Registry`：通过设有防火墙和额外的安全层的私有实体提供的`registry`

> `docker`默认使用`https`可以手动指定`http`

## 私有docker-registry

> 开源项目：[harbor](<https://github.com/goharbor/harbor>)

## OOME

> 当`linux`内核内存不够的时候`linux`内核会杀死部分进程，以释放内存，一旦发生`OOME`任何进程都有可能被杀死，包括`docker daemon`在内，所以docker特地调整了`docker daemon`的`OOME`。`OOM`
> 的值越大越优先级越高则越容易被杀死

