# day07

## 会话技术

> 会话：一次会话中包含多次请求和响应，客户端和服务器之间的会话。
>
> * 功能：主要是用来在一次会话的范围内的多次请求共享数据，因为`http`协议是无状态的，所以每一次的请求都是独立的。
> * 方式：
>   * 客户端会话技术：`Cookie`；
>   * 服务端会话技术：`Session`。

## Cookie快速入门

> `Cookie`技术是客户端会话技术，将数据保存到客户端。
>
> 使用步骤：
>
> 1. 创建`Cookie`对象，绑定数据；
>    - 构造函数`Cookie(String name, string value)`；
> 2. 发送`Cookie`对象；
>    - `response.addCookie(Cookie cookie)`；
> 3. 获取`Cookie`，拿到数据；
>    - `Cookie[] request.getCookies()`。

#### 设置Cookie

```java
package com_01.web.Cookie;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/CookieTest01")
public class CookieTest01 extends HttpServlet {
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		// 1.创建Cookie对象
		Cookie cookie = new Cookie("msg", "tom");
		// 2.添加Cookie到response对象中
		resp.addCookie(cookie);
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
	}
}
```

#### 获取Cookie

```java
package com_01.web.Cookie;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/CookieTest02")
public class CookieTest02 extends HttpServlet {
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// 获取Cookie
		Cookie[] cookies = request.getCookies();
		if(cookies != null) {
			for (Cookie cookie : cookies) {
				System.out.println(cookie.getName() + ":" + cookie.getValue());
			}
		}

	}

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		this.doPost(request, response);
	}
}
```

## Cookie的实现细节

> 1. 一次可不可以发送多个`cookie`？
>
>    > 可以，创建多个`cookie`对象，使用`response`对象的方法`addCookie`方法发送`cookie`即可。
>
> 2. `cookie`在浏览器中保存多长时间？
>
>    > * 默认情况下，浏览器关闭后，`cookie`数据被销毁。
>    > * 设置`cookie`持久化存储，`Cookie.setMaxAge(int seconds)`
>    >   * 正数：将`cookie`数据写到硬盘的文件中，持久化存储，表示cookie的存活时间。
>    >   * 零：删除`cookie`信息，
>    >   * 负数：默认值，`cookie`数据存储到内存中。
>
> 3. `cookie`能不能存储中文？
>
>    > 在`tomcat 8`之前，`cookie`不能直接存储中文数据，需要将中文数据转码，一般采用`URL`编码；在`tomcat 8`之后，`cookie`支持中文数据。
>
> 4. `cookie`共享问题？
>
>    > 默认情况下`cookie`不能共享。`Cookie.setPath(String path)`，设置`cookie`共享，默认情况下设置为当前的虚拟路径。设置`path`为`"/"`则可以共享`cookie`数据。
>
> 5. 不同`tomcat`服务器间`cookie`共享问题？
>
>    > `Cookie.setDomain(String path)`，如果设置一级域名相同，那么多个服务器之间`cookie`可以共享。例：`setDomain(".baidu.com")`，那么`news.baidu.com`和`tieba.baidu.com`可以共享`cookie`。

## Cookie的特点和作用

> 特点：
>
> 1. cookie存储数据在客户端浏览器；
> 2. 浏览器对于单个`cookie`的大小也有限制(4kb)，对于同一个域名下的总`cookie`数量也有限制(20个)；
>
> 作用：
>
> 1. `cookie`一般用于存储少量的**不太敏感**的信息；
> 2. 在不登录的情况下，完成服务器对客户端的身份识别。

## Session

> 服务端会话技术，在**一次会话**的多次请求间共享数据，将数据保存在服务端的对象中，`HttpSession`。
>
> 1. 获取`HttpSession`对象：`HttpSession request.getSession();`
> 2. 使用`HttpSession`对象：
>    * 设置属性值：`void session.setAttribute(String var1, Object var2);`
>    * 获取属性值：`HttpSession session.getSession();`

## Session原理

> * 服务器如何确保在同一会话范围内，多次获取的`session`对象是同一个？
>
>   > `Session`的实现是依赖于`Cookie`的。

## Session的实现细节

> 1. 当客户端关闭后，服务端不关闭，两次获取`session`是否为同一个？
>
>    > 默认情况不是同一个，如果需要相同，然后创建`cookie`，键为`JSESSION`，设置`cookie`持久化保存。
>    >
>    > ```java
>    > // 1.获取session
>    > HttpSession session = request.getSession();
>    > 
>    > // 设置JSESSIONID的Cookie
>    > final Cookie cookie = new Cookie("JSESSIONID", session.getId());
>    > cookie.setMaxAge(120);
>    > response.addCookie(cookie);
>    > 
>    > // 2.存储数据
>    > session.setAttribute("msg", "hello session");
>    > ```
>
> 2. 客户端不关闭，服务端关闭后，两次获取的`session`是同一个吗？
>
>    > 不是同一个，但是确保数据不丢失，`tomcat`已经默认进行了序列化和反序列化操作。
>    >
>    > * `session`的钝化：序列化，在服务器正常关闭之前，将`session`对象序列化到硬盘上；
>    > * `session`的活化：反序列化，在服务器启动后，将`session`文件转化为内存中的`seion`对象。
>
> 3. `session`什么时候被销毁？
>
>    > 1. 服务器关闭；
>    > 2. `session`对象调用`invalidate()`方法，即`session`自杀；
>    > 3. `session`默认的失效时间为30分钟，可以在`tomcat`配置文件中进行配置。

## Session的特点

> 1. `session`用于存储一次会话的多次请求的数据，存在服务端；
> 2. `session`可以存储任意类型和任意大小的数据；

## session和cookie区别

> 1. `Session`数据存储在服务端，`Cookie`在客户端；
> 2. `Session`没有数据大小限制，`Cookie`有限制；
> 3. `Session`数据安全，`Cookie`相对不安全。

## JSP

> `JSP`(`Java Server Pages`)：`Java`服务器端页面，是一种特殊的页面。其中既可以直接定义`html`标签，又可以定义`Java`代码，用于简化书写，`JSP`本质就是一个`Servlet`。

### JSP脚本

> 1. `<% Java代码 %>`：定义的`Java`代码，在`service`方法中，`service`中可以定义什么，该脚本就可以定义什么；
> 2. `<%! Java代码 %>`：定义的`java`代码，`jsp`转换后的`java`类的成员位置，成员变量，成员方法，静态代码块；
> 3. `<%= Java代码 %>`：定义的`Java`代码，会输出到页面上，输出语句中可以定义什么，就该脚本就可以定义什么；
> 4. `<%@ page import=“java.net.URLEncoder” %>`：进行`java`包的导入。

### JSP内置对象

> 在`jsp`页面中不需要获取和创建，就可以直接使用的对象。
>
> `jsp`一共有`9`个内置对象：
>
> * `request`
> * `response`
> * `out`：字符输出流队形，将数据输出到页面上。
>   * `response.getWirter()`和`out.wirter()`区别，`tomcat`服务器真正给客户端做出响应之前，会先找`response`缓冲区数据，再找`out`缓冲区数据，则`response.getWriter()`数据永远在`out.writer()`之前。

## JSP进阶

> `jsp`是一个特殊的页面既可以写`html`又可以写`java`代码。

### JSP指令

> 用于配置`jsp`页面和导入资源文件，`<%@ 指令名称 属性名1=属性值2 属性名2=属性值2 ... %>`。
>
> 指令分类：
>
> 1. `page`：配置`jsp`页面。
>    * `contentType`：等同于`response.setContentType()`
>      * 设置响应的`mime`类型以及字符接；
>      * 设置当前页面的字符集(只能是高级的`IDE`才能生效，如果使用低级工具，则需要设置`pageEncoding`才能生效)。
>    * `import`导`java`包；
>    * `errorPage`：当前页面发生异常后自动跳转到指定的错误页面；
>    * `isErrorPage`：标识当前页面是否是错误页面。
>      * `true`：是，可以使用内置对象`exception`；
>      * `flase`：否，默认值，不可以使用内置对象`exception`。
> 2. `include`：页面包括的，导入页面的资源文件；
>    * `<%@ include file="top.jsp" %>`
> 3. `taglib`：导入`JSTL`标签资源。
>    * `<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>`
>      * `prefix`：前缀，自定义；

### JSP注释

> 方式一`html`注释：`<!-- 注释内容 -->`，只能注释`html`代码片段；
>
> 方式二`jsp`特有注释：`<%-- 注释内容 --%>`，可以注释`jsp`也可以注释`html`代码片段。

### JSP内置对象

> 在`jsp`页面中不需要创建，直接使用的对象

* 域对象：
  1. `pageContext`：`PageContext`类型，当前页面共享数据，还可以获取其它八个对象；
  2. `request`：`HttpServletRequest`类型，一次请求访问多个资源(转发)；
  3. `session`：`HttpSession`类型，一个会话多次请求访问多个资源共享；
  4. `application`：`ServletContext`类型，所有用户间共享数据。
* 其他：
  1. `response`：`HttpServeltResponse`类型，响应对象；
  2. `page`：`Object`类型，当前页面`servlet`的对象，表示`this`指针；
  3. `out`：`JspWriter`类型，输出对象，把数据输出到页面上；
  4. `config`：`ServletConfig`类型，`servlet`的配置对象；
  5. `exception`：`Throwable`类型，异常对象。

## MVC开发模式

> 将程序分为三个部分；
>
> 1. M：`Model`，模型，使用`JavaBean`完成；
>    * 完成具体的业务逻辑操作，如：操作数据库、封装对象；
> 2. V：`View`，视图，使用`JSP`完成；
>    * 展示数据，
> 3. C：`Controlloer`，控制器，调用模型进行业务操作，使用`Servlet`完成。
>    * 获取客户端的输入；
>    * 调用模型；
>    * 将数据交给视图展示。

### MVC优缺点

- 优点：
  - 耦合性低：方便维护，利于分工协作；
  - 重用性高；
- 缺点
  - 使得项目架构变得复杂，对开发人员要求高。

## 从MVC到REST

> https://blog.csdn.net/fuzhongmin05/article/details/81585672

## EL表达式

> `Expression Language`表达式语言，可以替换和简化`jsp`页面中`java`代码的编写。语法：`${表达式}`，例：`${3 > 4}`，返回一个`boolean`类型的数据。
>
> 注意：`jsp`默认支持`EL`表达式，如果设置`jsp`中`page`执行`isELIgnored="true"`整个`jsp`页面忽略`EL`表达式，或者`\${表达式}`忽略单个`EL`表达式

### EL作用

> 1. 运算符：
>    * 算数运算符：`+`、`-`、`*`、`/或div`、`%或mod`；
>    * 比较运算符：`>`、`<`、`>=`、`<=`、`==`、`!=`；
>    * 逻辑运算符：`&&或and`、`||或or`、`!或not`；
>    * 空运算符：`empty`，用于判断字符串、集合和数组是否为`null`并且长度是否为0。
>      * `${empty list}`，判断`list`是否为`null`且长度为0；
>      * `${not empty list}`，表示判断字符串、集合、数组对象是否不为`null`、且长度大于0；
> 2. 获取值：
>    * `EL`表达式只能从域对象中获取值，
>      * `${域名城.键名称}`：从指定域中获取指定键的值；
>        * `pageScope`从`pageContext`中获取值；
>        * `requestScope`从`request`中获取值；
>        * `sessionScope`从`session`中获取值；
>        * `applicationScope`从`application(ServletContext)`中获取值。
>      * `${键名称}`：表示依次从最小的域中查找是否有该键对应的值，直到找到为止：`pageContext` → `request` → `session` → `application(ServletContext)`；
>      * 获取对象、`List`集合、`Map`集合的数据
>        * 通过对象的**属性**来获取值`${域名城.键名称.属性名}`，回去调用对象的`Getter`方法；
>        * `List`集合：`${域名城.键名称[索引]}`，索引为`index`，获取`index`下标的值，如果越界则返回一个空字符串；
>        * `Map`集合：`${域名城.键名称.key名称}`或`${域名城.键名称["key名称"]}`都可以获取到该键值对应的值。
> 3. 隐式对象，`EL`表达式中一共有**11个**隐式对象，只需要掌握一个；
>    * `pageContext`：获取`jsp`其他八个内置对象。
>      * 获取`request`对象：`${pageContext.request}`，常用方法`${pageContext.request.contextPath}`动态获取虚拟目录。

## JSTL标签

> `JSP`(`JavaServer Pages Tag Library`)，`JSP`标准标签库，由`Apache`组织提供的开源的免费的`JSP`标签。

### 使用步骤

1. 导入`jstl`相关的`jar`包；
2. 导入标签库，`taglib`执行`<%@ taglib %>`；
3. 使用标签。

### 常用JSTL标签

1. `if`相当于`java`代码的`if`；
   * `test`：必须属性，接收`boolean`表达式，
     * 如果表达式为`true`，则显示标签体内容；如果表达式为`false`，则不显示标签体内容。
     * 一般情况下，`test`属性值会结合`el`表达式一起使用。
   * `c:if`标签没有`else`情况，想要`else`情况，则可以再定义一个`c:if`标签；
2. `choose`相当于`java`代码的`switch`；
   * `when`标签表示判断，相当于`case`；
   * `otherwise`标签，相当于`default`。
3. `foreach`相当于`java`代码的`for`循环。
   * 循环
     * `begin`:开始值
     * `end`:结束值
     * `var`:临时变量
     * `step`:步长
     * `varStatus`:循环状态对象
       * `index`:容器中元素的索引，从0开始
       * `count`:循环次数，从1开始
   * 迭代容器
     * `items`:容器元素
     * `var`: 容器中元素的临时变量
     * `varStatus`:循环状态对象
       * `index`:容器中元素的索引，从0开始
       * `count`:循环次数，从1开始	

```jsp
<%@ page import="java.util.List" %>
<%@ page import="java.util.ArrayList" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head>
    <title>JSTLTest</title>
</head>
<body>

    <%--
        c:if标签，类似于Java中的if判断语句。
            1.属性：
                * test：必须属性，接收boolean表达式，
                   * 如果表达式为true，则显示标签体内容；
                   * 如果表达式为false，则不显示标签体内容。
    --%>
    <c:if test="true">
        我是true
    </c:if>

    <%--
        c:choose标签，类似于Java中的switch语句
            1.when标签表示判断，相当于case
            2.otherwise标签，相当于default
    --%>
    <% request.setAttribute("num", 3); %>
    <c:choose >
        <c:when test="${num == 1}">今天星期一</c:when>
        <c:when test="${num == 2}">今天星期二</c:when>
        <c:when test="${num == 3}">今天星期三</c:when>
        <c:when test="${num == 4}">今天星期四</c:when>
        <c:when test="${num == 5}">今天星期五</c:when>
        <c:when test="${num == 6}">今天星期六</c:when>
        <c:when test="${num == 7}">今天星期日</c:when>
        <c:otherwise>输入非法</c:otherwise>
    </c:choose>

    <%--
        c:foreach标签，类似于Java中的for循环
            * 循环
                * begin:开始值
                * end:结束值
                * var:临时变量
                * step:步长
                * varStatus:循环状态对象
                    * index:容器中元素的索引，从0开始
                    * count:循环次数，从1开始
            * 迭代容器
                * items:容器元素
                * var: 容器中元素的临时变量
                * varStatus:循环状态对象
                    * index:容器中元素的索引，从0开始
                    * count:循环次数，从1开始
    --%>
    <c:forEach begin="1" end = "10" var = "i" step="2" varStatus="s">
        <br>${i} -> index:${s.index} -> count:${s.count}
    </c:forEach>

    <%
        List<Integer>  list = new ArrayList();
        list.add(3);
        list.add(5);
        list.add(1);
        list.add(12);
        request.setAttribute("list", list);
    %>

    <br>遍历容器：
    <c:forEach items="${requestScope.list}" var = "it" >
        <br>${it}
    </c:forEach>


</body>
</html>
```

## 三层架构