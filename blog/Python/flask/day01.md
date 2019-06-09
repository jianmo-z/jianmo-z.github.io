# day01

## 认识web-URL

> URL是`Uniform Resource Locator`，统一资源定位符
>
> URL组成`scheme://host:port/path/?query-string=xxx#anchor`

* `scheme`：访问的协议
* `host`：主机名
* `port`：端口
* `path`：查找路径
* `query-shring`：查询字符串
* `anchor`：锚点，后台不用管，前端用来做页面定位

## web服务

* web服务器：处理http请求，相应静态文件，常见的：nginx、apache；
* 应用服务器：负责处理逻辑的服务器，比如：php、python代、java代码，应用服务器tomcat(java)、uwsgi(python)；
* web应用框架：一般使用某种语言，封装了常见的web功能的框架就是web应用框架，flask(python)，Django(python)以及spring boot(java)、SSH(java)。

## Content-type和Mine-type的作用和区别

> 在服务器和客户端之间传输数据的类型

* `Content-type`：既可以指定传输数据的类型，又可以指定数据的编码类型
* `Mine-type`：只能指定数据的类型

## DEBUG模式

