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

> a

## 过滤器链(配置多个过滤器)