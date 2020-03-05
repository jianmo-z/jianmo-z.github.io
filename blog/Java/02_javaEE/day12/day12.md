# day12

## Spring概述

> `Spring`是分层的`Java SE/EE`应用`full-stack`轻量级开源框架，以`IoC`(`Inverse Of Control`)控制反转和`AOP`(`Aspect Oriented Programming`)面向切面编程为内核，提供了展现层`Spring MVC`和持久层`Spring JDBC`以及业务层事务管理等众多的企业级应用技术，还能整合开源世界众多的第三方著名框架和类库，逐渐成为使用最多的`JavaEE`企业应用开源框架。

### spring的优势

> - 方便解耦，简化开发；
> - `AOP`编程的支持；
> - 声明式事务的支持；
> - 方便程序的测试；
> - 方便集成各种优秀的框架；
> - 降低`JaveEE API`的使用难度；
> - `Java`源码是经典学习返利；

## 程序耦合与解耦

> - 耦合：程序间的依赖关系；
>   - 类之间的耦合；
>   - 方法间的耦合。
> - 解耦：
>   - 依赖程序间的依赖关系；
> - 实际开发：
>   - 编译期不依赖，运行时才依赖。
> - 解耦思路：
>   1. 使用反射创建对象，避免使用`new`关键字；
>   2. 通过读取配置文件来获取要创建的对象全限定类名；

## IOC

> `IOC`(`Inversion of Control`)控制反转，把创建对象的权利交给框架，用来**削减**计算机程序的**耦合**(接触代码中的依赖关系)，是框架的重要特征，并面向对象编程的专用术语，包括`DI`(`Dependency Injection`)依赖注入，和`DL`(`Dependency Lookup`)依赖查找。

## Spring入门

> 1. 获取核心容器对象；
> 2. 通过`id`在容器中获取对象；
> 3. 使用对象。

### Spring使用步骤

> ```java
> package com.jianmo.ui;
> 
> import com.jianmo.dao.IAccountDao;
> import com.jianmo.service.IAccountService;
> import org.springframework.context.ApplicationContext;
> import org.springframework.context.support.ClassPathXmlApplicationContext;
> 
> /**
>  * 模拟一个表现层，用于调用业务层
>  */
> public class Client {
> 
> 	/**
> 	 * 获取spring的IOC核心容器，并根据id获取对象
> 	 * @param args
> 	 */
> 	public static void main(String[] args) {
> 		// 1.获取核心容器对象
> 		ApplicationContext context = new ClassPathXmlApplicationContext("bean.xml");
> 
> 		// 2.通过id在容器中获取对象
> 		IAccountDao accountDao = (IAccountDao)context.getBean("accountDao");
> 		IAccountService accountService = (IAccountService)context.getBean("accountService");
> 
> 		// 3. 打印对象
>         System.out.println(accountDao);
>         System.out.println(accountService);
>     }
> }
> ```

### ApplicationContext常用实现类

> - `ClassPathXmlApplicationContext`：加载类路径下的配置文件，要求配置文件必须在类路径下，不在则不能加载；
> - `FileSystemXmlApplicationContext`：加载磁盘任意路径下的路径文件，必须有访问权限；
> - `AnnotationConfigApplication`：用于读取注解创建容器。

### 核心容器的两个接口区别

> - `ApplicationContext`：构建核心容器时，创建对象采用的策略是立即加载的方式，适用于单例模式下使用，**采用此接口定义容器对象**，可以通过配置实现单例和多例模式下；
> - `BeanFactory`：构建核心容器时，创建对象采取的策略师延迟加载的方式，适用于多例模式下使用。