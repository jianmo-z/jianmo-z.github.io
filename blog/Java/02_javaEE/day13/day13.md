# day13

## Spring中IOC的常用注解

> 注解配置和`XML`的`IOC`配置，目的一样，功能也一样，只是方式不同。

## 常用IOC注解分类

> 常用`IOC`注解按照作用分为四类。
>
> - 用于创建对象的注解：作用与在`XML`配置文件中编写一个`<bean>`标签实现的功能是一样的；
>
>   - `@Component`：
>     - 作用：用于把当前类对象存入`Spring`容器中；
>     - 属性：
>       - `value`：用于指定`bean`的`id`，不写时，默认值为当前类名且首字母改为小写；
>   - `@Controller`(表现层)、`@Service`(业务层)、`@Repository`(持久层)：该三个注解的作用和属性与`@Componect`是一模一样的，目的是`Spring`框架为我们提供明确的三层使用的注解，使三层对象更加清晰。
>
> - 用于注入数据的注解：作用与在`XML`配置文件中的`<bean>`标签中写一个`<property>`标签的作用是一样的；
>
>   - `@Autowired`：
>     - 作用：自动**按照类型注入**，
>       - 一个对应匹配：只要容器中有唯一的`bean`对象类型和要注入的变量类型匹配，就可以注入成功，
>       - 没有对应匹配：如果`IOC`容器中没有任何`bean`的类型和要注入的变量类型匹配则报错
>       - 多个对应匹配：`IOC`容器中有多个`bean`的类型和要注入的变量类型匹配，且没有`id`和要注入的名称一致，则报错；
>     - 出现位置：可以是**成员变量**上，也可以是**成员方法**上；
>     - r注意：当使用注解注入时，`set`方法就不是必须的了。
>   - `@Qualifier`：
>     - 作用：在按照类型注入的基础上再按照名称注入，它再给类成员注入时不能单独使用(和`@Autowired`配合使用)，但是再给方法参数注入时可以单独使用；
>     - 属性：
>       - `value`：用于指定注入`bean`的`id`；
>   - `@Resource`：
>     - 作用：直接按照`bean`的`id`注入，可以独立使用；
>     - 属性：
>       - `name`：用于指定`bean`的`id`；
>     - 问题记录：无法使用该注解时，[参考链接](https://blog.csdn.net/BlackPlus28/article/details/82828400)
>
>   > `@Autowired`、`@Qualifier`和`@Resource`这三类注解只能注入`bean`类型的数据，而基本类型和`String`类型则无法使用上述注解实现，而且，集合类型的注入只能通过`XML`来实现。
>
>   - `Value`：
>     - 作用：用于注入基本类型和`String`类型的数据；
>     - 属性：
>       - `value`：用于指定数据的值，它可以使用`Spring`中`SpEL`(即：`Spring`的`el`表达式)，`SpEL`的写法`${表达式}`；
>
> - 用于改变作用范围的注解：组用与在`XML`配置文件中的`<bean>`标签中使用`scope`属性实现的功能是一样的；
>
>   - `Scope`：
>     - 作用：用于指定`bean`的作用范围；
>     - 属性：
>       - `value`：指定范围的取值，常用取值`singleton`、`prototype`
>       - 
>
> - 与生命周期相关的注解(了解)：组用与在`XML`配置文件中的`<bean>`标签中使用`init-method`和`destory-method`属性的作用是一样的。
>
>   - `PreDestroy`：
>     - 作用：用于指定销毁方法，注解销毁函数；
>   - `PostConstruct`：
>     - 作用：用于指定初始化方法，注解初始化函数。

## 注解配置替代XML配置

> 通过一个配置类来取代`bean.xml`文件。
>
> - `@Configruation`：
>
>   - 作用：指定当前类是一个配置类；
>   - 注意：当配置类作为`AnnotationConfigApplicationContext`对象创建的参数时，该注解的参数可以不写。
>
> - `@ComponentScan`：
>
>   - 作用：用于通过注解指定`Spring`在创建容器时要扫描的包；
>   - 属性：
>     - `value`：它和`basePackages`的作用一样，都是用于指定创建容器时要扫描的包，使用此注解就等同于在`XML`中配置`<context:component-scan>`标签；
>
> - `@Bean`：
>
>   - 作用：把当前方法的返回值作为`bean`对象存入`Spring`的`IOC`容器中作为`value`值；
>   - 属性：
>     - `name`：用于指定`bean`的`id`，即为`key`值，默认值为当前方法名；
>
>   > 当使用注解配置方法时，如果方法有参数，`Spring`框架会去容器中查找有没有可用的`bean`对象，查找方式与`Autowried`注解的方式一样。
>   
> - `@Import`：
>
>   - 作用：用于导入其他的配置类；
>   - 属性：
>     - `value`：用于指定其他配置类的字节码，使用`Import`注解之后，有`Import`注解的类就是父(主)配置类，而导入的都是子配置类。
>
> - `@PropertySource`：
>
>   - 作用：用于指定`properties`文件的位置，读取`properties`数据
>   - 属性：
>     - `value`：指定文件的名称和路径，**关键字**：`classpath`表示类路径下，例：`classpath:com/config/jdbcConfig.properties`。

## Spring和Junit的整合

> - 问题分析
>   - `junit`单元测试中，没有`main`方法也能执行，是因为`junit`集成了一个`main`方法，该方法就会判断当前测试类中那些方法`@Test`注解，则让有`@Test`注解的方法执行就可以了。
>   - `junit`不会管我们是否采用了`Spring`框架，所以在执行测试方法时，`junit`不会读取配置文件/配置类创建`Spring`核心容器。
> - 问题结论：
>   - 当测试方法执行时，没有`IOC`容器，就算写了`@Autowired`注解，也无法实现注入。

### 步骤

> 1. 导入`Spring`整合`junit`的`jar`包(坐标)；
> 2. 使用`junit`提供的一个注解把原有的`main`替换成`Spring`提供的；
>    * `@RunWith`
> 3. 告知`Spring`的运行期，`Spring`的`IOC`创建是基于`XML`还是注解，并且指定位置；
>    - `@ContextConfiguration`
>      - `locations`：指定`XML`文件的位置，加上`classpath`关键字，表示在类路径下；
>      - `classes`：指定注解类的位置；
>
> 注意：当使用`Spring 5.X`版本的时候，要求`junit`版本是`4.12`及以上。

## 动态代理对象

### 基于接口的动态代理

> - 基于接口的动态代理：
>   - 涉及的类：`Proxy`；
>   - 提供方：`JDK`官方。
> - 如何创建动态代理对象：
>   - 使用`Proxy`类中的`newProxyInstance`方法；
> - 创建代理对象的要求：
>   - 被代理类最少实现一个接口，如果没有则不能使用；
> - `newProxyInstance`方法的参数：
>   - `ClassLoader`参数：类加载器，它是用于加载对象字节码的，和被代理对象使用相同的类加载器；
>   - `Class[]`参数：字节码数组，它是用于让代理对象和被代理对象有相同方法；
>   - `InvocationHandler`参数：用于提供增强的代码，它是让我们写如何代理，一般都是一个该接口的实现类，通常情况下都是匿名内部类，此接口的实现类都是谁用谁写，参数一般传递为：`new InvocationHandler(){ /* 实现方法invoke */ }`。

### 基于子类的动态代理

> - 基于接口的动态代理
>   - 涉及的类：`Enhancer`；
>   - 提供方：第三方`cglib`库。
> - 如何创建代理对象：
>   - 使用`Enhancer`类中的`create`方法；
> - 创建代理对象的要求：
>   - 被代理类不能是最终类。
> - `create`方法的参数：
>   - `Class`：字节码，它用于指定被代理对象的字节码；
>   - `Callback`：如何提供增强的代码，一般写的都是该接口的子接口实现类`MethodInterceptor`。

## AOP

> 面向切面编程`AOP`(`Aspect Oriented Programming`)，通过预编译方式和运行期动态代理实现程序的统一维护的一种技术。
>
> - 作用：在程序运行期间，不修改源码对已有方法进行增强；
> - 优势：
>   - 减少重复代码；
>   - 提高开发效率；
>   - 维护方便。

## AOP专业术语

> - `Joinpoint`：连接点，是指那些被拦截到的点，在`Spring`中，这些点指的就是方法，因为`Spring`只支持方法类型的连接点；
> - `Pointcut`：切入点，是指要对那些`Joinpoint`进行拦截的定义；
> - `Advice`：通知/增强，指拦截到`Joinpoint`之后要做的事情就是通知，通知的类型有：
>   - 前置通知；
>   - 后置通知；
>   - 异常通知；
>   - 最终通知；
>   - 环绕通知；
> - `Introduction`：引介，引介是一种特殊的通知在不修改类代码的前提下，`Introduction`可以在运行期为类动态地添加一些方法或`Field`；
> - `Target`：目标代理，代理的目标对象；
>   - `Weaving`：织入，是指把增强应用到目标对象来创建新的代理对象的过程，`Spring`采用动态代理织入，而`AspectJ`采用编译器织入和类装载器织入；
> - `Proxy`：代理，一个类被`AOP`织入增强后，就产生一个结果代理类；
> - `Aspect`：切面，是切入点和通知(引介)的结合。

## AOP的XML配置

> 1. 把通知`bean`交给`Spring`来管理；
> 2. 使用`aop:config`标签表明`AOP`的配置
> 3. 使用`aop:config`标签表明`AOP`的配置
>    - `id`属性：给切面提供一个唯一标识；
>    - `ref`属性：指定通知类`bean`的`ID`；
> 4. 在`aop:aspect`内部使用对应的标签来配置通知的类型，让`printLog`方法在切入点执行之前执行，即**前置通知**(`aop:before`)。
>    - `method`属性：指定某个类(例：`Logger`)中那个方法是前置通知；
>    - `pointcut`属性：用于指定切入点表达式，该表达式目的是说明对业务层那些方法进行增强。

## Spring-AOP切入点表达式

> - 关键字：`execution(表达式)`；
>
> - 切入点表达式：`访问修饰符 返回值 包名.包名...包名.类名.方法名(参数列表)`，例：`public void com.jianmo.service.impl.AccountServiceImpl.saveAccount()`；
>   - **访问修饰符可以省略**，例：`void com.jianmo.service.impl.AccountServiceImpl.saveAccount()`；
>   - **返回值使用通配符**，表示任意返回值都可以使用，例：`* com.jianmo.service.impl.AccountServiceImpl.saveAccount()`；
>   - **包名可以使用通配符**，表示任意包，有几级包就需要写几个，例：`* *.*.*.*.AccountServiceImpl.saveAccount()`；
>   - **包名可以使用**`..`**表示当前包和子包**，例：`* *..AccountServiceImpl.saveAccount()`；
>   - **类名和方法名都可以使用**`*`**来实现通配**，例：`* *..*.*()`；
>   - 参数列表，可以直接写数据类型：
>     - 基本类型直接写名称，例：`int`；
>     - 引用类型写`包名.类名`的方式，例：`java.lang.String`；
>   - **参数列表通配符**表示任意类型，但是必须**有参数**：
>     - `* *..*.*(*)`；
>   - **参数列表有无参数均可**，即全通配的方式：
>     - `* *..*.*(..)`；
>
> - 全通配写法：`* *...*(..)`；
> - 实际开发中切入点表达式的通常写法，**切到业务层实现类下**的所有方法`* com.jianmo.service.impl.*.*(..)`；

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        http://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/aop
        http://www.springframework.org/schema/aop/spring-aop.xsd">

    <!-- 配置spring的IOC，把Service对象配置为bean对象 -->
    <bean id="accountService" class="com.jianmo.service.impl.AccountServiceImpl"></bean>

    <!-- 配置Logger类 -->
    <bean id="logger" class="com.jianmo.utils.Logger"></bean>

    <!-- 配置AOP -->
    <aop:config>
        <aop:aspect id="loggerAdvice" ref="logger">
            <!-- 配置通知的类型，并且建立通知方法和切入点的关联 -->
            <!-- 指定切入点方法：<aop:before method="printLog" pointcut="execution(public void com.jianmo.service.impl.AccountServiceImpl.saveAccount())"></aop:before> -->
            <!-- 全通配写法：<aop:before method="printLog" pointcut="execution(* *..*.*(..))"></aop:before> -->
            <aop:before method="printLog" pointcut="execution(* com.jianmo.service.impl.*.*(..))"></aop:before>
        </aop:aspect>
    </aop:config>
</beans>
```

## AOP五种常用通知-XML配置

> - **前置通知**(`aop:before`)：在切入点方法执行之前执行；
>
> - **后置通知**(`aop:after-returning`)：在切入点方法正常执行之后执行；
>
> - **异常通知**(`aop:after-throwing`)：在切入点方法产生异常之后执行；
>
> - **最终通知**(`aop:after`)：无论切入点是否正常结束都会在其后执行；
>
> - **环绕通知**(`aop:around`)：当配置环绕通知后，切入点方法不会执行需要手动调用，但通知方法会执行。
>
>   - 解决：`Spring`框架提供了一个接口`ProceedingJoinPoint`解决该问题，该接口有一个方法`proceed()`，此方法就是明确调用切入点，该接口可以作为环绕通知的方法参数，在程序执行时，`Spring`框架会提供该接口的实现类使用。
>   - **注意**：环绕通知是`Spring`框架提供的一种可以在代码中手动控制增强方法何时执行的方式。
>
>   > ```java
>   > /**
>   >  * 打印日志，环绕通知
>   >  */
>   > public Object aroundPrintLog(ProceedingJoinPoint joinPoint) {
>   >     Object ret = null;
>   >     try {
>   >         System.out.println("User define: beforePrintLog start record ...");  // 前置通知
>   >         final Object[] args = joinPoint.getArgs();  // 获取方法执行的参数
>   >         ret = joinPoint.proceed(args);  // 明确业务层的切入点方法调用
>   >         System.out.println("User define: afterPrintLog start record ...");  // 后置通知
>   >         return ret;
>   >     } catch (Throwable throwable) {
>   >         System.out.println("User define: exceptionPrintLog start record ...");  // 异常通知
>   >         throwable.printStackTrace();
>   >         throw new RuntimeException("aroundPrintLog");
>   >     } finally {
>   >         System.out.println("User define: finallyPrintLog start record ...");  // 最终通知
>   >     }
>   > }
>   > ```
>
> 总结：**后置通知**和**异常通知**只能有一个执行；
>
> - 通用切入点表达式
>   - 使用`<aop:pointcut>`标签定义切入点表达式，`<aop>`通知标签属性`pointcut-ref`引用表达式：
>     - `id`：指定表达式唯一标志;
>     - `expression`：指定表达式内容；
>   - 注意：该标签定义在`<aop:aspect>`内部只能当前`<aop:aspect>`切面内使用，当标签定义在`<aop:aspect>`外部且在`<aop:aspect>`标签前声明，则当前`aop`的切面都能使用。

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        http://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/aop
        http://www.springframework.org/schema/aop/spring-aop.xsd">

    <!-- 配置spring的IOC，把Service对象配置为bean对象 -->
    <bean id="accountService" class="com.jianmo.service.impl.AccountServiceImpl"></bean>

    <!-- 配置Logger类 -->
    <bean id="logger" class="com.jianmo.utils.Logger"></bean>

    <!-- 配置AOP -->
    <aop:config>
        <aop:aspect id="loggerAdvice" ref="logger">
            <!-- 配置切入点表达式：id指定表达式唯一标志；expression指定表达式内容 -->
            <aop:pointcut id="accountServiceAspect" expression="execution(* com.jianmo.service.impl.*.*(..))"/>

            <!-- 前置通知 -->
            <aop:before method="beforePrintLog" pointcut-ref="accountServiceAspect"></aop:before>

            <!-- 后置通知 -->
            <aop:after-returning method="afterReturningPrintLog" pointcut-ref="accountServiceAspect"></aop:after-returning>

            <!-- 异常通知 -->
            <aop:after-throwing method="afterThrowingPrintLog" pointcut-ref="accountServiceAspect"></aop:after-throwing>

            <!-- 最终通知 -->
            <aop:after method="afterPrintLog" pointcut-ref="accountServiceAspect"></aop:after>

            <!-- 配置环绕通知 -->
            <aop:around method="aroundPrintLog" pointcut-ref="accountServiceAspect"></aop:around>
        </aop:aspect>
    </aop:config>
</beans>
```

### 测试程序运行

> 测试：前置通知、后置通知、异常通知、最终通知在有异常和无异常时的执行结果。
>
> - **异常通知**(`aop:after-throwing`)：在切入点方法产生异常之后执行；
> - **最终通知**(`aop:after`)：无论切入点是否正常结束都会在其后执行；
>
> ```
> 有异常抛出：
> beforePrintLog start record ...
> saveAccount
> exceptionPrintLog start record ...
> finallyPrintLog start record ...
> 
> 无异常抛出：
> beforePrintLog start record ...
> saveAccount
> afterPrintLog start record ...
> finallyPrintLog start record ...
> ```

## AOP五种常用通知-注解配置

> - 步骤：
>   1. 配置切面类的注解；
>   2. 配置切面类的方法通知注解；
>   3. 开启注解配置通知，`bean.xml`配置`<aop:aspectj-autoproxy></aop:aspectj-autoproxy>`或在切面类上使用注解`@EnableAspectJAutoProxy`。
> - **注意**：
>   - 注解通知配置(`前置`、`后置`、`异常`、`最终`)时，会出现调用顺序异常，建议使用环绕通知；
>   - 可以在切面类内定义一个方法用作定义**切入点表达式**，然后使用切面类的其他方法则可以调用该表达式。

```java
package com.jianmo.utils;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.*;
import org.springframework.stereotype.Component;

/**
 * 记录日志的工具类
 */
@Component("logger")
@Aspect  // 表示当前类是一个切面类
public class Logger {
	// 定义切入点表达式
	@Pointcut("execution(* com.jianmo.service.impl.*.*(..))")
	private void pointcutExpression(){}

	/**
	 * 打印日志，前置通知执行
	 */
	@Before("pointcutExpression()")  // 设置前置通知
	public void beforePrintLog() {
		System.out.println("beforePrintLog start record ...");
	}

	/**
	 * 打印日志，后置通知执行
	 */
	@AfterReturning("pointcutExpression()")  // 设置后置通知
	public void afterReturningPrintLog() {
		System.out.println("afterPrintLog start record ...");
	}

	/**
	 * 打印日志，异常通知执行
	 */
	@AfterThrowing("pointcutExpression()")  // 设置异常通知
	public void afterThrowingPrintLog() {
		System.out.println("exceptionPrintLog start record ...");
	}

	/**
	 * 打印日志，最终通知执行
	 */
	@After("pointcutExpression()")  // 设置最终通知
	public void afterPrintLog() {
		System.out.println("finallyPrintLog start record ...");
	}

	/**
	 * 打印日志，环绕通知
	 */
	@Around("pointcutExpression()")  // 设置环绕通知
	public Object aroundPrintLog(ProceedingJoinPoint joinPoint) {
		Object ret = null;
		try {
			System.out.println("User define: beforePrintLog start record ...");  // 前置通知
			final Object[] args = joinPoint.getArgs();  // 获取方法执行的参数
			ret = joinPoint.proceed(args);  // 明确业务层的切入点方法调用
			System.out.println("User define: afterPrintLog start record ...");  // 后置通知
			return ret;
		} catch (Throwable throwable) {
			System.out.println("User define: exceptionPrintLog start record ...");  // 异常通知
			throwable.printStackTrace();
			throw new RuntimeException("aroundPrintLog");
		} finally {
			System.out.println("User define: finallyPrintLog start record ...");  // 最终通知
		}
	}
}
```

