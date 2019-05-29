# Hadoop入门

[TOC]

## 什么是Hadoop?

1. Hadoop是一个由Apache基金会锁开发的分布式系统基础架构
2. 主要用来解决海量数据的**存储(HDFS)**和海量数据的分析**计算(MapReduce)**问题
3. 广义上来说：Hadoop通常是指一个更广泛的概念－－HADOOP生态

## hadoop的优势

1. 高可靠性：因为Hadoop假设计算元素和存储会出现故障，所以它维护多个工作数据副本，在出现故障时可以对失败的节点重新分布处理；
2. 高拓展性：在集群分配任务数据，可方便的扩展数以千计的节点；
3. 高效性：在MapReduce的思想下，Hadoop是并行工作的，以加快任务处理速度；
4. 高容错性：自动保存多份副本数据，并且能够自动将失败的任务重新分配。

## Hadoop组成

1. **Hadoop HDFS**(磁盘)：高可靠、高吞吐量的分布式文件系统

   1. **NameNode(nn)**：存储文件的[元数据](<https://baike.baidu.com/item/%E5%85%83%E6%95%B0%E6%8D%AE>)以及每个文件的块列表和块所在的DataNode；
   2. **DataNode(dn)**：本地文件系统存储文件块数据，以及校验和；
   3. Secondary NameNode(2nn)：监控HDFS状态的辅助后台程序。

2. **Hadoop YARN**(OS)：作业调度与其他集群资源管理的框架

   1. **Resource Manager(rm，总资源)**：处理客户端请求、启动/监控ApplicationMaster、监控NodeManager、资源调度；
   2. **Node Manager(nm，节点资源)**：单个节点上的资源管理、处理来自Resource Manager的命令、处理来自Application Mster的命令；
   3. Application Master：数据切分、为应用程序申请资源，并分配给内部任务、任务监控与容错；
   4. Container：对任务运行环境的抽象，封装CPU、内存等多维资源以及环境变量、启动命令等任务运行相关的信息。

3. Hadoop MapReduce(应用程序)：分布式的离线并行计算框架

   > MapReduce将计算过程分为两个阶段：Map和Reduce

   1. Map阶段并行处理输入数据
   2. Reduce阶段对Map结果进行汇总

4. Hadoop Common(辅助工具)：支持其他模块的工具模块

5. 大数据技术生态体系

## Hadoop运行模式

1. 本地模式(default)：需要单独进程，直接可以运行
2. 伪分布式模式：等同于完全分布式，只有一个节点
   1. HDFS上运行MapReduce
   2. YARN上运行MapReduce
3. 完全分布式模式：多个节点一起运行
