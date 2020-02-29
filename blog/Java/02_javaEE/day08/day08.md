# day08

## Filter过滤器

> `web`中的过滤器：当访问服务器的资源时，过滤器可以将请求拦截下来，完成一些特殊的功能。

### 过滤器的作用

> 一般用于完成通过的操作，如：登陆验证、统一编码处理、敏感字符过滤；

## 使用步骤

> 1. 定义一个类，实现接口`Filter`；
> 2. 复写方法；
> 3. 过滤器配置拦截路径；
>    * `web.xml`文件配置；
>    * 注解配置，注解是一个字符串数组可以配置多个路径.
>
> ```java
> package com_01.web.Filter;
> 
> import javax.servlet.*;
> import javax.servlet.annotation.WebFilter;
> import java.io.IOException;
> 
> 
> @WebFilter("/*")  // 访问所有资源之前都会执行该过滤器
> public class FilterImplTest01 implements Filter {
> 	@Override
> 	public void init(FilterConfig filterConfig) throws ServletException {
> 
> 	}
> 
> 	@Override
> 	public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
> 		System.out.println("FilterImplTest01");
> 
> 		// 放行
> 		filterChain.doFilter(servletRequest, servletResponse);
> 	}
> 
> 	@Override
> 	public void destroy() {
> 
> 	}
> }
> ```

### web.xml配置

> ```xml
> <?xml version="1.0" encoding="UTF-8"?>
> <web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
>          xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
>          xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
>          version="3.1">
> 
>     <filter>
>         <filter-name>demo02</filter-name>
>         <filter-class>com_01.web.Filter.FilterImplTest02</filter-class>
>     </filter>
> 
>     <filter-mapping>
>         <filter-name>demo02</filter-name>
>         <url-pattern>/*</url-pattern>  <!-- 拦截路径 -->
>     </filter-mapping>
> 
> </web-app>
> ```

## 过滤器执行流程

> 执行顺序：`启动tomcat服务器` → `init Filter` → `请求服务` → `init Servlet` → `before doFilter` → `servlet service` → `after doFilter` → `停止服务` → `destroy Servlet` → `destroy Filter`
>
> ```java
> package com_01.web.Filter;
> 
> import javax.servlet.*;
> import javax.servlet.annotation.WebFilter;
> import java.io.IOException;
> 
> @WebFilter("/*")
> public class FilterImplTest03 implements Filter {
> 	public void destroy() {
> 		System.out.println("destroy Filter");
> 	}
> 	
> 	public void doFilter(ServletRequest req, ServletResponse resp, FilterChain chain) throws ServletException, IOException {
> 		System.out.println("before doFilter");// 对request对象的请求消息进行增强
> 		// 放行
> 		chain.doFilter(req, resp);
> 		System.out.println("after doFilter");  // 对response对象的响应消息进行增强
> 	}
> 
> 	public void init(FilterConfig config) throws ServletException {
> 		System.out.println("init Filter");
> 	}
> 
> }
> ```

## 过滤器生命周期方法

> 在服务器启动后，会创建`Filter`对象，然后调用`init`方法。
>
> `Filter`对象：
>
> * `init`：用于申请资源，当服务器启动后执行一次；
> * `doFilter`：当每次被过滤的请求执行时执行一此，会被执行多次；
> * `destroy`：用于释放资源，当服务器正常关闭时执行一次。
>
> 执行顺序：`启动tomcat服务器` → `init Filter` → `请求服务` → `init Servlet` → `before doFilter` → `servlet service` → `after doFilter` → `停止服务` → `destroy Servlet` → `destroy Filter`

## 过滤器配置详情

### 拦截路径配置

> 1. 具体的资源路径：`/index.jsp`，只有访问`index.jsp`资源时，过滤器才会被执行。
> 2. 拦截目录：`/user/*`，访问`/user`下的所有资源时，过滤器都会被执行；
> 3. 后缀名拦截：`*.jsp`，访问所有后缀名`jsp`资源时，过滤器都会被执行，没有`/`开头；
> 4. 拦截所有资源：`/*`，访问所有资源时过滤器都会被执行。

### 拦截方式配置

> 资源被访问的方式。
>
> * 配置方式：
>   * 注解配置`dispatcherTypes`属性；
>     * `REQUEST`：默认值，浏览器直接请求资源；
>     * `FORWARD`：转发访问资源；
>     * `INCLUDE`：包含访问资源；
>     * `ASYNC`：异步访问资源；
>     * `ERROR`：错误跳转资源；
>    
>   * `web.xml`配置
>   
>     ```xml
>     <filter>
>         <filter-name>demo01</filter-name>
>         <filter-class>com_01.web.Filter.FilterImplTest03</filter-class>
>     </filter>
>     
>     <filter-mapping>
>         <filter-name>demo01</filter-name>
>         <url-pattern>/*</url-pattern>
>         <dispatcher>REQUEST</dispatcher>
>     </filter-mapping>
>     ```

## 过滤器链(配置多个过滤器)
### 过滤器执行顺序

> **执行顺序**，如果有两个过滤器：过滤器1和过滤器2
>
> 1. `过滤器1`
> 2. `过滤器2`
> 3. `资源执行`
> 4. `过滤器2`
> 5. `过滤器1`

### 过滤器先后顺序问题

>
>1. 注解配置：按照类名的字符串比较规则比较，值小的先执行。
>2. `web.xml`配置：`<filter-mapping>`标签谁定义在上面谁先执行。

## 设计模式-动态代理模式

> 1. 装饰模式
> 2. **代理模式**
>    * 概念：
>      1. 真实对象：被代理的对象；
>      2. 代理对象：
>      3. 代理模式：代理对象代理真实对象，达到增强真实对象功能的目的；
>    * 实现方式：
>      1. 静态代理：有一个类文件描述代理模式；
>      2. 动态代理：在内存中形成代理类。
> 3. 动态代理实现步骤：
>    1. 代理对象和真实对象实现相同的接口；
>    2. 获取代理对象，`代理对象 = public static Object newProxyInstance(ClassLoader loader, Class<?>[] interfaces, InvocationHandler h)`；
>    3. 使用代理对象调用方法；
>    4. 增强方法。
>       * 增强参数列表；
>       * 增强返回值；
>       * 增强函数功能；
>
> ```java
> package cn.itcast.proxy;
> 
> import java.lang.reflect.InvocationHandler;
> import java.lang.reflect.Method;
> import java.lang.reflect.Proxy;
> 
> public class ProxyTest {
> 
>     public static void main(String[] args) {
>         // 1.创建真实对象
>         Lenovo lenovo = new Lenovo();
> 
>         // 2.动态代理增强lenovo对象
>         /*
>          * 三个参数： 1. 类加载器：真实对象.getClass().getClassLoader() 2.
>          * 接口数组：真实对象.getClass().getInterfaces() 3. 处理器：new InvocationHandler()
>          */
>         SaleComputer proxy_lenovo = (SaleComputer) Proxy.newProxyInstance(lenovo.getClass().getClassLoader(),
>                 lenovo.getClass().getInterfaces(), new InvocationHandler() {
>                     /*
>                      * 代理逻辑编写的方法：代理对象调用的所有方法都会触发该方法执行 参数： 1. proxy:代理对象 2. method：代理对象调用的方法，被封装为的对象
>                      * 3. args:代理对象调用的方法时，传递的实际参数
>                      */
>                     @Override
>                     public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
>                         /*
>                          * System.out.println("该方法执行了...."); System.out.println(method.getName());
>                          * System.out.println(args[0]);
>                          */
> 
>                         // 判断是否是sale方法
>                         if (method.getName().equals("sale")) {
>                             // 1.增强参数
>                             double money = (double) args[0];
>                             money = money * 0.85;
>                             System.out.println("专车接你....");
>                             // 使用真实对象调用该方法
>                             String obj = (String) method.invoke(lenovo, money);
>                             System.out.println("免费送货...");
>                             // 2.增强返回值
>                             return obj + "_鼠标垫";
>                         } else {
>                             Object obj = method.invoke(lenovo, args);
>                             return obj;
>                         }
> 
>                     }
>                 });
> 
>         // 3.调用方法
> 
>         /*
>          * String computer = proxy_lenovo.sale(8000); System.out.println(computer);
>          */
> 
>         proxy_lenovo.show();
>     }
> }
> ```

## Listener-监听器

> 监听器，`web`的三大组件之一。
>
> - 时间监听机制：
>   - 事件：一个事件；
>   - 事件源：事件发生的地方；
>   - 监听器：一个对象；
>   - 注册监听：将**事件**、**事件源**和**监听器**绑定在一起，当事件源上发生某个事件后，执行监听器代码。

### ServletContextListener

> `ServletContextListener`监听器接口，监听`servletContext`对象的创建和销毁。
>
> * `void contextDestroyed(ServletContextEvent sce)`：`ServletContext`对象被销毁之前会调用该方法；
> * `void contextInitialized(ServletContextEvent sce)`：`ServletContext`对象创建后会调用该方法；

### 监听器的步骤

> 1. 定义一个类实现`ServletContextListener`接口；
>
> 2. 复写方法；
>
> 3. 配置
>
>    1. 注解配置
>
>       ```java
>       package com_03.web.Listener;
>       
>       import javax.servlet.ServletContext;
>       import javax.servlet.ServletContextEvent;
>       import javax.servlet.ServletContextListener;
>       import javax.servlet.annotation.WebListener;
>       import java.io.FileInputStream;
>       import java.io.FileNotFoundException;
>       import java.io.IOException;
>       
>       @WebListener
>       public class ListenerTest implements ServletContextListener {
>       	@Override
>       	public void contextInitialized(ServletContextEvent servletContextEvent) {
>       		// 1.获取servletContext对象
>       		final ServletContext servletContext = servletContextEvent.getServletContext();
>       		// 2.加载资源对象
>       		final String contextConfigureLocation = servletContext.getInitParameter("contextConfigureLocation");
>       		// 3.获取真实路径
>       		final String realPath = servletContext.getRealPath(contextConfigureLocation);
>       		// 4.加载数据进内存
>       		try (FileInputStream fileInputStream = new FileInputStream(realPath)) {
>       			// 读数据
>       		} catch (FileNotFoundException e) {
>       			e.printStackTrace();
>       		} catch (IOException e) {
>       			e.printStackTrace();
>       		}
>       
>       		System.out.println("contextInitialized");
>       	}
>       
>       	@Override
>       	public void contextDestroyed(ServletContextEvent servletContextEvent) {
>       		System.out.println("contextDestroyed");
>       	}
>       }
>       ```
>
>    2. `web.xml`配置，使用`<context-param>`标签指定初始化参数：
>
>       ```xml
>       <listener>
>           <listener-class>com_03.web.Listener.ListenerTest</listener-class>
>       </listener>
>       <!-- 指定初始化参数 -->
>       <context-param>
>           <param-name>contextConfigureLocation</param-name>
>           <param-value>/src/filepath</param-value>
>       </context-param>
>       ```