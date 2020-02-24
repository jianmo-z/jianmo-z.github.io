# day08

## 会话技术

> 会话：一次会话中包含多次请求和响应，客户端和服务器之间的会话。
>
> * 功能：主要是用来在一次会话的范围内的多次请求共享数据，因为http协议是无状态的，所以每一次的请求都是独立的。
> * 方式：
>   * 客户端会话技术：`Cookie`；
>   * 服务端会话技术：`Session`。

## Cookie

> 客户端会话技术，将数据保存到客户端。

### 快速入门

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

### Cookie的实现细节

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

### Cookie的特点和作用

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

## JSP