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

## Spring对bean的管理细节

> 1. 创建`bean`的三种方式；
> 2. `bean`对象的作用范围；
> 3. `bean`对象的生命周期。

### 创建bean的三种方式

- 方式一：使用默认构造函数创建

  > 在`Spring`的配置文件中使用`bean`标签，配置`id`和`class`属性后，没有其他属性和标签，采用的就是默认构造函数创建`bean`对象，此时如果类中没有默认构造函数，则对象无法创建。
  >
  > ```xml
  > <bean id="accountService" class="com.jianmo.service.impl.AccountServiceImpl" ></bean>
  > ```

- 方式二：使用普通工厂中的**成员方法**创建对象(使用某个类中的**成员方法**创建对象，并存入`Spring`容器)

  > ```xml
  > <bean id="accountServiceFactory" class="com.jianmo.factory.AccountServiceFactory"></bean>
  > <bean id="accountService" factory-bean="accountServiceFactory" factory-method="getAccountService"></bean>
  > ```

- 方式三：使用普通工厂中的**静态方法**创建对象(使用某个类中的静态方法创建对象，并存入**Spring**容器)

  > ```xml
  > <bean id="accountService" class="com.jianmo.factory.StaticAccountServiceFactory" factory-method="getAccountService"></bean>
  > ```

### bean对象的作用范围

> - `bean`标签的`scope`属性，用于指定`bean`的作用范围。
>   - `singleton`：只创建单例对象，默认值；
>   - `prototype`：创建多例对象；
>   - `request`：作用于web应用的请求范围；
>   - `session`：作用于web应用的会话范围；
>   - `global-session`：作用于集群环境的绘画范围(全局绘画范围)，当不是集群范围时，就等于session。

### bean对象的生命周期

> - 单例对象：单例对象的生命周期和容器的生命周期一样。
>   - **创建**：当容器创建时创建对象；
>   - **使用**：只要容器在，对象一直在；
>   - **销毁**：容器销毁，对象销毁；
> - 多例对象：
>   - **创建**：使用对象时`Spring`创建对象；
>   - **使用**：对象只要被使用就会一直存活；
>   - **销毁**：当对象长时间不用且没有别的对象引用时，由Java的垃圾回收器回收。

## Spring依赖注入

> 依赖注入(`Dependency Injection`)，依赖关系的管理交给`Spring`来维护，当前类需要用到其他类的对象，有`Spring`为我们提供，我们只需要在配置文件中说明依赖关系的维护，就称为**依赖注入**。
>
> - 能注入的三类类型：
>   - 基本类型和`String`；
>   - 其他`bean`类型(在配置文件中或者注解配置过的`bean`)；
>   - 复杂类型/集合类型。
> - 注入的三种方式，只能选择其中之一**不能混用**：
>   - 使用构造函数提供；
>   - 使用`set`方法提供；
>   - 使用注解提供。

### 注入方式-构造函数：

> - 优势：在获取`bean`对象是，注入数据是**必须操作**，否则对象无法创建成功；
> - 劣势：改变了`bean`对象的实例化方式，在创建对象时，如果用不到这些数据，也必须提供。
>
> 使用构造函数注入：通过`bean`标签的子标签`constructor-arg`的属性注入；
>
> - `type`：用于指定要注入的数据的数据类型，该类型也是构造函数中某个或某些参数的类型；
> - `index`：用于指定要注入的数据给构造函数中指定索引位置的参数赋值，参数索引的位置要从`0`开始；
> - `name`：用于指定给构造函数中指定名称的参数赋值，常用`name`指定参数；
> - `value`：用于提供基本和`String`类型的数据；
> - `ref`：用于指定其他的`bean`类型，指的就是`Spring`的`IOC`的核心容器中出现过的`bean`对象。
>
> ```xml
> <!-- Spring中的依赖注入：构造函数注入-->
> <bean id="now" class="java.util.Date"/>
> <bean id="accountService" class="com.jianmo.service.impl.AccountServiceImp01" >
>     <constructor-arg name="name" value="张三"/>
>     <constructor-arg name="age" value="18"/>
>     <constructor-arg name="birthday" ref="now"/>
> </bean>
> ```

### 注入方式-set方法：

> `set`方式注入是更常用的方式。
>
> - 优势：创建对象时没有明确的限制，可以直接使用默认构造函数；
> - 劣势：如果有某个成员变量必须有值，则获取对象时`set`方法有可能没有执行。
>
> 使用构造函数注入：通过`bean`标签的子标签`property`的属性注入；
>
> - `name`：用于指定注入时所调用的`set`方法**名称**，即`set`方法去掉`set`，首字母变小写；
> - `value`：用于提供基本和`String`类型的数据；
> - `ref`：用于指定其他的`bean`类型，指的就是`Spring`的`IOC`的核心容器中出现过的`bean`对象。
>
> ```xml
> <!-- Spring中的依赖注入：set方法注入-->
> <bean id="now02" class="java.util.Date"/>
> <bean id="accountService02" class="com.jianmo.service.impl.AccountServiceImpl02" >
>     <property name="name" value="张三"></property>
>     <property name="age" value="19"></property>
>     <property name="birthday" ref="now02"></property>
> </bean>
> ```

### 注入方式-复杂类型/集合类型：

> - 用于给`List`结构集合注入的标签：`list`、`array`和`set`；
> - 用于给`Map`结构集合注入的标签：`map`和`props`；
>
> **结构相同标签可以互换**；
>
> ```xml
> <!-- Spring中的依赖注入：复杂类型注入-->
> <bean id="accountService03" class="com.jianmo.service.impl.AccountServiceImpl03" >
>     <property name="myStrArray">
>         <array>
>             <value>张三</value>
>             <value>李四</value>
>         </array>
>     </property>
>     <property name="myList">
>         <list>
>             <value>王五</value>
>             <value>王麻子</value>
>         </list>
>     </property>
>     <property name="mySet">
>         <set>
>             <value>王五</value>
>             <value>王麻子</value>
>         </set>
>     </property>
> 
>     <property name="myMap">
>         <map>
>             <entry key="王五" value="陕西西安"></entry>
>             <entry key="张三">
>                 <value>北京朝阳</value>
>             </entry>
>         </map>
>     </property>
> 
>     <property name="myProperties">
>         <props>
>             <prop key="aaa">AAA</prop>
>             <prop key="bbb">BBB</prop>
>         </props>
>     </property>
> </bean>
> ```