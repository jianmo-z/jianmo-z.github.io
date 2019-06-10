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

1. 在`app.run()`传入参数`DEBUG=True`
2. 设置`app.debug=True`
3. 通过配置参数`app.config.update(DEBUG=True)`
4. 通过配置文件设置DEBUG模式`app.config.from_object(config)`

## PIN码

> 在运行程序后会生成PIN码，有PIN码就可以在网页上进行调试

## config配置

### 方式一：加载

1. `import config` ，导入配置模块
2. 使用`app.config.from_object(config)`，通过模块加载配置文件

### 方式二：加载

1. 使用`app.config.from_pyfile("./config.py")`，通过文本文件加载配置
2. 必须包含文件的后缀名，不局限于使用`.py`文件，`.txt`文件也能用
3. 可以传递`silent`参数，当为`False`配置文件不存在报错；`True`配置文件不存在不报错，使用默认配置

## URL与函数的映射

### 映射关系

```python
@app.route("/list/")
def my_list():
	return "my list"
```

### URL参数传递

```python
@app.route("/list/<search_id>")
def get_id(search_id):
	return "search id is {}".format(search_id)
```

> 注意`app.route`的参数使用`<>`包围起来并且在函数的参数名必须相同，可以有多个用`/`分割

### 限制参数的数据类型

* `string`:默认的数据类型，节后没有任何斜杠`/`的文本
* `int`：接收整形
* `float`：接收浮点类型
* `path`：和`string`类似，但是接收斜杠`/`
* `uuid`：只接收`uuid`字符串
* `any`：可以指定多种途径

```python
# 限制参数类型传递
@app.route("/list/<int:search_id>/")
def get_id(search_id):
	return "search id is {}".format(search_id)

# any指定多个途径
@app.route("/<any(name,age):var>/<int:user_id>")
def get_any_id(var, user_id):
	return "get any variable is {0}, id is {1}".format(var, user_id)
```



