# day06

## web服务器软件

> * 服务器：安装了服务器软件的计算机；
> * 服务器软件：接收用户的请求，处理请求，做出响应；
> * `web`服务器软件：是服务软件中的一种；
>   * 在`web`服务器软件中，可以部署web项目，让用户通过浏览器来访问这些项目；
>   * 即`web`容器。
> * `JavaEE`：`Java`语言在企业级开发中使用的技术规范的总和，一共规定了`13`项大的规范。
>
> 常见`Java`相关的`web`服务器软件：
>
> * `webLogic`：`oracle`公司，大型的`JavaEE`服务器，支持所有的`JavaEE`规范，收费；
> * `webSphere`：`IBM`公司，大型的`JavaEE`服务器，支持所有的`JavaEE`规范，收费；
> * `JBOSS`：`JBOSS`公司，大型的`JavaEE`服务器，支持所有的`JavaEE`规范，收费；
> * `Tomcat`：`Apache`基金组织，中小型的`JavaEE`服务器，仅仅支持少量的`JavaEE`规范`servlet/jsp`，开源免费。

## Tomcat学习

### Tomcat安装

1. 下载安装包：`http:///tomcat.apache.org`；
2. 安装：解压安装包即可；
3. 卸载：删除目录即可；
4. 启动：`startup.sh`脚本；
5. 关闭：`shutdown.sh`脚本；
6. 配置：部署项目的方法。
   * 方式一：直接将项目文件放到`webapps`目录下，将项目打成一个`war`包，将`war`包放置到`webapps`目录下，自动解压缩；
   * 方式二：修改配置文件`conf/server.xml`，在`Host`标签体中添加`<Context docBase="项目存放路径" path="web访问虚拟目录"/>`标签；
   * **方式三**：`conf/Catalina/localhost`目录下创建任意名称的`XXX.xml`配置文件，内容为`<Context docBase="项目存放路径"/>`，`web`访问虚拟目录就是配置文件名：`ip:port/XXX`，热部署。

## 静态项目和动态项目

> 静态项目和动态项目目录结构的区别：
>
> * `java`动态项目的目录结构：
>   * 项目的根目录
>     * `WEB-INF`目录：
>       * `web.xml`：`web`项目的核心配置文件
>       * `classes目录`：放置字节码文件的目录
>       * `lib目录`：放置依赖的`jar`包

## Tomcat集成IDEA

> 将`Tomcat`集成到`IDEA`中，并创建`JavaEE`的项目，部署项目。

## Servlet入门

> `servlet`就是一个接口，定义了`Java`类被浏览器访问到(`tomcat`识别)的规则。将来自定义一个类，实现`servlet`接口，复写方法。

### 快速入门

1. 创建`JavaEE`项目；

2. 定义一个类，实现`servlet`接口`implements Servlet`；

   * `void init(ServletConfig config)`：
   * `void service(ServletRequest req, ServletResponse res)`：
   * `void destory()`：
   * `ServletConfig getServletConfig()`：
   * `String getServletInfo()`：

3. 配置`Servlet`：`web/WEB-INF/web.xml`的`<web-app>`标签内

   ```xml
   <!--配置Servlet-->
   <servlet>
       <servlet-name>demo01</servlet-name>
       <servlet-class>com_01.web.servlet.ServletDemo01</servlet-class>
   </servlet>
   
   <servlet-mapping>
       <servlet-name>demo01</servlet-name>
       <url-pattern>demo01</url-pattern>   <!--url路径名-->
   </servlet-mapping>
   ```

### Servlet执行原理

1. 当服务器接收到客户端浏览器的请求后，会解析请求`URL`路径，获取访问的`Servlet`的资源路径；
2. 查找web.xml文件，是否有对应的`<url-pattern>`标签体内容；
3. 如果有则在找到对应的`<servlet-class>`全类名；
4. `tomcat`会将字节码文件加载到内存中，并且创建对象；
5. 调用其方法。

## Servlet中的方法

### Servlet中的生命周期

- `void init(ServletConfig config)`：被创建，只执行一次，加载资源；
  - 默认情况下，第一次被访问时，Servlet被创建。
  - 可以手动配置Servlet的创建时机。
    1. 第一次被访问时创建：`<load-on-startup>`为负数；
    2. 在服务器启动时创建：`<load-on-startup>`为正整数或`0`。
  - `Servlet`的`init`方法，只能执行一次，说明一个`Servlet`在内存中只存在一个实例，即单例设计模式。
    - 多个用户同时访问时，可能存在线程安全问题；
    - 解决：尽量不要再`Servlet`中定义成员变量，即使定义了成员变量，也不要对其修改值；
- `void service(ServletRequest req, ServletResponse res)`：提供服务，执行多次；
  - 每次访问`Servlet`是，`service`方法都会被调用一次。
- `void destory()`：被销毁，只执行一次，释放资源。
  - `Servlet`被销毁时执行，服务器**正常关闭**，`Servlet`被销毁，才会执行`destroy`方法。

```java
package com_01.web.servlet;

import javax.servlet.*;
import java.io.IOException;

public class ServletDemo02 implements Servlet {
	/**
	 * 申请资源
	 * 初始化方法：在Servlet被创建时执行，且只会被执行一次
	 * @param servletConfig
	 * @throws ServletException
	 */
	@Override
	public void init(ServletConfig servletConfig) throws ServletException {
		System.out.println("init...");
	}

	/**
	 * 获取ServletConfig对象，Servlet的配置对象
	 * @return
	 */
	@Override
	public ServletConfig getServletConfig() {
		return null;
	}

	/**
	 * 提供服务
	 * 提供服务器的方法：每一次Servlet被访问时执行，可以执行多次
	 * @param servletRequest
	 * @param servletResponse
	 * @throws ServletException
	 * @throws IOException
	 */
	// 提供服务的方法
	@Override
	public void service(ServletRequest servletRequest, ServletResponse servletResponse) throws ServletException, IOException {
		System.out.println("service");
	}

	/**
	 * 获取Servlet的一些信息，版本，作者，一般不会去实现
	 * @return
	 */
	@Override
	public String getServletInfo() {
		return null;
	}

	/**
	 * 释放资源
	 * 销毁方法：在服务器正常关闭时执行，且只执行一次。
	 */
	@Override
	public void destroy() {
		System.out.println("destroy...");
	}
}
```

## Servlet3.0

> `Servlet3.0`新标准优点：支持注解配置，可以不需要`web.xml`了。
>
> 步骤：
>
> 1. 创建`JavaEE`项目，选择`Servlet`的版本`3.0`以上，可以不创建`web.xml`；
> 2. 编写一个类，实现`Servlet`接口；
> 3. 复写方法；
> 4. 在类上使用`@WebServlet`注解，进行配置。
>    1. 方式一：`@WebServlet(urlPatterns = "/资源路径")`；
>    2. 方式二：`@WebServlet("/资源路径")`。
>
> ```java
> package com_01.web.servlet;
> 
> import javax.servlet.*;
> import javax.servlet.annotation.WebServlet;
> import java.io.IOException;
> 
> //@WebServlet(urlPatterns = "/demo01")  // 方式一
> @WebServlet("/demo01")  // 方式二，更简洁
> public class ServletDemo01 implements Servlet {
> 	@Override
> 	public void init(ServletConfig servletConfig) throws ServletException {}
> 
> 	@Override
> 	public ServletConfig getServletConfig() {
> 		return null;
> 	}
> 
> 	@Override
> 	public void service(ServletRequest servletRequest, ServletResponse servletResponse) throws ServletException, IOException {
> 		System.out.println("Servlet 3.0");
> 	}
> 
> 	@Override
> 	public String getServletInfo() {
> 		return null;
> 	}
> 
> 	@Override
> 	public void destroy() {}
> }
> ```

## IEDA和tomcat配置

> 1. `IDEA`会为每一个`tomcat`部署的项目单独建立一份配置文件`Using CATALINA_BASE`：
>
>    * `Using CATALINA_BASE: "C:\Users\Pip\.IntelliJIdea2019.3\system\tomcat\_java_ee"`
>
> 2. 项目空间有两处
>
>    * 工作空间项目，此项目方便程序员开发操作；
>    * `tomcat`部署的`web`项目，`tomcat`真正访问的项目。
>
>    > `IDEA`会把工作空间的文件同步到`tomcat`部署的`web`项目中。
>
> 3. `WEB-INF`目录下的资源不能被浏览器直接访问；
>
> 4. 断点调试，加断点再以`Debug`模式启动`tomcat`项目。

## Servlet体系结构

> * `Servlet`接口；
>   * `GenericServlet`抽象类，实现了`Servlet`接口部分方法，只需要实现`service`方法即可；
>     * `HttpServlet`抽象类，实现了`GenericServlet`抽象类部分方法。

### GenericServlet

> 将`Servlet`接口中其他的方法做了默认空实现，只将`service()`方法作为抽象方法，将来定义`Servlet`类是，可以继承`GenericServlet`，实现`service()`方法，也可以自己重写其他的方法。
>
> ```java
> package com_01.web.servlet;
> 
> import javax.servlet.*;
> import javax.servlet.annotation.WebServlet;
> import java.io.IOException;
> 
> @WebServlet("/demo02")
> public class Demo02GenericServlet extends GenericServlet {
> 	@Override
> 	public void service(ServletRequest servletRequest, ServletResponse servletResponse) throws ServletException, IOException {
> 		System.out.println("GenericServlet...");
> 	}
> }
> ```

### HttpServlet

> 对`HTTP`协议的封装，简化操作，对`http`的不同请求封装了不同的方法。
>
> * `protected void doGet(HttpServletRequest req, HttpServletResponse resp)`：处理`http`的`get`请求；
> * `protected void doPost(HttpServletRequest req, HttpServletResponse resp)`：处理`http`的`post`请求。
>
> ```java
> package com_01.web.servlet;
> 
> import javax.servlet.ServletException;
> import javax.servlet.annotation.WebServlet;
> import javax.servlet.http.HttpServlet;
> import javax.servlet.http.HttpServletRequest;
> import javax.servlet.http.HttpServletResponse;
> import java.io.IOException;
> 
> @WebServlet({"/demo03", "/demo03-bak"})  // 配置多个访问路径
> public class Demo03HttpServlet extends HttpServlet {
> 	/**
> 	 * 处理http的get请求
> 	 * @param req
> 	 * @param resp
> 	 * @throws ServletException
> 	 * @throws IOException
> 	 */
> 	@Override
> 	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
> 		System.out.println("doGet...");
> 	}
> 
> 	/**
> 	 * 处理http的post请求
> 	 * @param req
> 	 * @param resp
> 	 * @throws ServletException
> 	 * @throws IOException
> 	 */
> 	@Override
> 	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
> 		System.out.println("doPost...");
> 	}
> }
> ```

### Servlet相关配置

> * 一个`Servlet`可以定义多个访问路径：`@WebServlet({"/demo03", "/demo03-bak"})`；
> * 路径定义规则：
>   * 方式一：`/XXX`，单级路径访问资源；
>   * 方式二：`/XXX/XXX`或`/XXX/*`多层路径，星号表示通配符且优先级最低；
>   * 方式二：`*.do`，例：`demo4.do`就会访问到`*.do`配置的路径，且不能加`/`，否则会报错。

## HTTP协议

> `HTTP`(`Hyper Text Transfer Protocol`)超文本传输协议，定义了客户端好服务端通信时发送数据的格式。
>
> 特点：
>
> * 基于`TCP/IP`的高级协议；
> * `http`协议的默认端口号是`80`；
> * 基于`请求Request/响应Response`模型的，一次请求对应一次响应；
> * 无状态的：每次请求之间相互独立，不能交互数据。
>
> 历史版本：
>
> * `1.0版本`：每一次请求都会简建立新的连接；
> * `1.1版本`：复用刚才的连接。

## Request

> 消息格式：
>
> 1. 请求行；
>
>    * 请求方式，`HTTP`协议一共有7钟，常用的有两种：
>      * `GET`：请求参数在请求行中，`url`长度有限制的，不太安全，
>      * `POST`：请求参数在请求行中，`url`长度没有限制，较安全。
>
>    > ```html
>    > 请求方式 请求url 请求协议/版本
>    > GET /login.html HTTP/1.1
>    > ```
>
> 2. 请求头，键值对的形式；
>
>    * `Host`：本地主机名；
>    * `User-Agent`：浏览器告诉服务器，我访问你使用的浏览器版本信息，可以在服务器端获取该头的信息，解决浏览器的兼容性问题。
>    * `Referer`：告诉服务器，我(当前请求)从哪里来。
>      * 作用一：防盗链
>      * 作用二：统计工作
>
>    > ```html
>    > 请求头名称1: 请求头值1,请求头名称2: 请求头值2,...,请求头名称n: 请求头值n
>    > ```
>
> 3. 请求空行；
>
> 4. 请求体，`GET`没有请求体，`POST`有请求体，因为`POST`的数据存放在请求体中，GET数据放在`URL`中。
>
>    * 封装`POST`请求消息的请求参数。
>
>    > ```html
>    > username=zhangsan
>    > ```

## Request&Response原理

### tomcat服务器内部处理

> 1. `tomcat`服务器会根据请求`url`中的资源路径，创建对应的`ServletDemo01`的对象；
> 2. `tomcat`服务器会根据`request`和`response`对象，`request`对象中封装请求消息数据；
> 3. `tomcat`将`request`和`response`两个对象传递给`service`方法，并且调用`service`方法；
> 4. 程序员可以通过`request`对象获取请求消息数据，通过`response`对象设置响应消息数据；
> 5. 服务器再给浏览器做出响应之前，会从`response`对象中拿程序员设置的响应消息类型。

### Request&Response作用

> 1. `request`和`response`对象是由服务器创建的，程序员只是使用；
> 2. `request`对象是来获取请求消息的，`response`对象是来设置响应消息。

## Request对象继承体系结构

* `ServletRequest`：接口；
  * `HttpServletRequest`：接口，继承自`ServletRequest`接口；
    * `org.apache.catalina.connector.RequestFacde`：类，继承自`HttpServletRequest`。

## Request功能

> `Request`请求参数中文乱码。
>
> * `get`方式：`tomcat8`已经将`get`方式的乱码问题解决。
> * `post`方式：在获取参数前设置流的字符集`request.setCharacterEncoding("utf-8")`。

* 获取请求消息数据：

  * 获取请求行数据：`GET /day07/demo01?name=tom HTTP/1.1`
    * 方法请求方式`String getMethod()`：`GET`；
    * **获取虚拟目录**`String getContextPath()`：/`day07`；
    * 获取`Servlet`路径`String getServletPath()`：`/demo01`；
    * 获取get方式的请求参数`String getQueryString()`：`name=tom`；
    * **获取请求方法**；
      * `URI`统一资源标识符：`String getRequestURI()`即`/day14/demo01`
      * `URL`统一资源定位符：`StringBuffeer getRequestURL()`即：`http://localhost/day14/demo01`；
    * 获取协议及版本`String getProtocol()`：`HTTP/1.1`；
    * 获取客户机`ip`地址`String getRemoteAddr()`。
  * 获取请求头数据：
    * `String getHeader(String name)`：通过请求头名称获取请求头的值；
    * `Enumeration<String> getHeaderNames()`：获取所有的请求头信息，`Enumeration`功能类似迭代器。
  * 获取请求体数据，只有`POST`请求方式才有请求体，在请求体中封装了POST请求的请求参数：
    1. 先获取流(**字节流或字符流**)对象；
       * `BufferReader getReader()`：获取字符输入流，只能操作字符数据；
       * `ServletInputStream getInputStream()`：获取字节数据流，可以操作所有类型数据，常用于文件上传。
    2. 再从流对象中拿数据。

* 其他功能：

  * 获取请求参数**通用方式**，不论是get还是post请求方式都可以使用下列方法获取请求参数：

    * `String getParameter(String name)`：根据参数名称获取参数值；
    * `String[] getParameterValues(String name)`：根据参数名称获取参数值的数组；
    * `Enumeration<String> getParameterNames()`：获取所有参数的请求名称；
    * `Map<String, String[]> getParameterMap()`：获取所有参数的`map`键值对集合。

  * 共享数据：

    - 域对象：一个有作用范围的对象，可以在范围内共享数据。
    - `request`域：代表一次请求的范围，一般用于请求转发的多个资源中共享数据；
    - 存储数据：`void setAttribute(String name, Object obj)`； 
    - 通过键获取值：`Obejct getAttribute(String name)`；
    - 通过键移除键值对：`void removeAttribute(String name)`。

  * 请求转发，一种在服务器内部的资源跳转方式：

    1. 通过`Request`对象获取请求转发器对象：`RequestDispatcher getRequestDispatcher(String path)`；

    2. 使用`RequestDispatcher `对象来进行转发`forward(ServletReques request, ServletResponse response)`；

       > 请求转发特点：
       >
       > * 浏览器地址栏不发生变化；
       > * 只能转发到当前服务器内部资源中；
       > * 转发是一次请求

  * 获取`ServletContext`：通过`request`对象获取：

    * 获取`ServletContext`：`ServletContext getServletContext();`

```java
package com_02.web.request;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.Map;

@WebServlet("/RequestTest")
public class RequestTest extends HttpServlet {
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		// 1.获取请求消息数据-获取请求行数据
		System.out.println("get方法getMethod：" + req.getMethod());            // get方法getMethod：GET
		System.out.println("get方法getContextPath：" + req.getContextPath());  // get方法getContextPath：/day07_tomcat
		System.out.println("get方法getServletPath：" + req.getServletPath());  // get方法getServletPath：/RequestTest
		System.out.println("get方法getQueryString：" + req.getQueryString());  // get方法getQueryString：null
		System.out.println("get方法getRequestURI：" + req.getRequestURI());    // get方法getRequestURI：/day07_tomcat/RequestTest
		System.out.println("get方法getRequestURL：" + req.getRequestURL());    // get方法getRequestURL：http://127.0.0.1/day07_tomcat/RequestTest
		System.out.println("get方法getProtocol：" + req.getProtocol());        // get方法getProtocol：HTTP/1.1
		System.out.println("get方法getRemoteAddr：" + req.getRemoteAddr());    // get方法getRemoteAddr：127.0.0.1

		// 2.获取请求消息数据-获取请求头数据，不区分大小写
		System.out.println("get方法getHeader：" + req.getHeader("User-Agent"));  // get方法getHeader：PostmanRuntime/7.22.0

		System.out.print("get方法getHeaderNames：");  // get方法：user-agent accept cache-control postman-token host accept-encoding connection
		final Enumeration<String> headerNames = req.getHeaderNames();
		while (headerNames.hasMoreElements()) {
			// final String name = headerNames.nextElement();
			// System.out.print(name + "=" + req.getHeader(name) + " ");
			System.out.print(headerNames.nextElement() + " ");
		}
		System.out.println();

		// 4.其他功能-获取请求参数通用方式
		System.out.println("get方法getParameter：" + req.getParameter("User-Agent"));
		System.out.println("get方法getParameterValues：" + Arrays.toString(req.getParameterValues("hobby")));

		System.out.print("get方法getParameterNames：");
		Enumeration<String> parameterNames = req.getParameterNames();
		while (parameterNames.hasMoreElements()) {
			String key = parameterNames.nextElement();
			System.out.print("<" + key +"," + req.getParameter(key) + "> ");
		}
		System.out.println();

		System.out.print("get方法getParameterMap：");
		final Map<String, String[]> parameterMap = req.getParameterMap();
		for (Map.Entry<String, String[]> it : parameterMap.entrySet()) {
			System.out.print("<" + it.getKey() +"," + Arrays.toString(it.getValue()) + "> ");
		}
		System.out.println();

		// 5.其他功能-共享数据
		req.setAttribute("msg", "hello demo03");

		// 6.其他功能-请求转发
		req.getRequestDispatcher("/demo03").forward(req, resp);

		// 7.其他功能-获取ServletContext
		System.out.println("getServletContext：" + req.getServletContext());
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		// 3.获取请求消息数据-获取请求体，只有POST方法有请求体
		BufferedReader reader = req.getReader();
		String buffer = null;
		while ((buffer = reader.readLine()) != null)
			System.out.println(buffer);
	}
}
```

