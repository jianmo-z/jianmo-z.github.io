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

### 方式一：配置模块

1. `import config` ，导入配置模块
2. 使用`app.config.from_object(config)`，通过模块加载配置文件

### 方式二：配置文件

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
* `any`：可以指定多种途径，再一个URL中指定多个路径，即多个URL对应一个函数

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

## 接收用户参数

1. 使用path的形式(将参数嵌入到路径中)

   > 希望可以让搜索引擎能搜索到的使用该方式

   ```python
   # 参数传递
   @app.route("/list/<int:search_id>/")
   def get_id(search_id):
   	return "search id is {}".format(search_id)
   
   
   # 指定多个路径
   @app.route("/<any(name,age):var>/<int:user_id>")
   def get_any_id(var, user_id):
   	return "get any variable is {0}, id is {1}".format(var, user_id)
   ```

2. 使用查询字符串的形式，通过`?`的形式

   > 不希望搜索引擎搜索到，可以传递多个参数使用`&`分割

   ```python
   # 通过?号的形式传递的参数
   # http://127.0.0.1:8000/d/?wd=python&time=today
   @app.route("/d/")
   def get_d():
   	wd = request.args.get("wd")
   	time = request.args.get("time")
   	return "wd = {}, time = {}".format(wd, time)
   ```

## url_for

> 函数原型`url_for(endpoint, **values):`，`url_for`将视图函数反转为`url`，如果传递的参数已经定义了就会传递，如果没有定义就使用`?`传递给视图函数，第一个参数，应该是视图函数的名字的字符串，后面的参数就是传递给`url`，传递的参数的形式是字典。

### 为什么需要url_for

1. 如果将来修改了`URL`，但是没有修改`URL`对应的函数名，就不用到处去替换`URL`了
2. `url_for`会自动的处理那些特殊的字符，比如`/`等

```python
@app.route("/url_for/<view_func>")
def get_url_for(view_func):
	if view_func == "get_id":
		ret = url_for(view_func, search_id=10)  # 多余的参数使用?传递方式传递给视图函数
	else:
		ret = url_for(view_func)
	# print(ret)  # ret逃逸，垃圾回收不是垃圾乱收
	return "{}".format(ret)
```

## 自定义URL转换器

1. 自定义一个类继承自`BaseConverter`，重写`regex`正则表达式
2. 映射到`app.url_map.converters`中
3. 添加限制参数到路由中

```python
from werkzeug.routing import BaseConverter

# 第一步
# 自己写一个类继承自BaseConverter
# 手机号码URL转换器
class TelephoneConveter(BaseConverter):
	regex = r'1[85734]\d{9}'  # 第一位为1，第二位为


# 第二步
# 添加到默认的转换器中
app.url_map.converters['tel'] = TelephoneConveter

# 第三步
# 自定义URL转换器
# 判断手机号
@app.route("/phone/<tel:phone>")
def phone_number(phone):
	return "Telephone number is {}".format(phone)
```

### to_python&to_url

* `to_python(self, value)`方法，返回值传递到`view`函数中作为参数
* `to_url(self, values)`方法，返回值将在调用`url_for`函数的时候生成符合条件的URL形式

```python
class ListConverter(BaseConverter):
	#   to_python(self, value)方法，返回值传递到view函数中作为参数
	#   to_url(self, values)方法，返回值将在调用url_for函数的时候生成符合条件的
	# URL形式
	def to_python(self, value):
		return "*".join(value.split("+"))

	def to_url(self, value):
		return "&".join(value)


app.url_map.converters['prase'] = ListConverter


# 使用加号传参
# http://127.0.0.1:8000/posts/1+2/
@app.route("/posts/<prase:post>/")
def posts(post):
	return "post is:{}".format(post)  # post is:1*2


#  http://127.0.0.1:8000/posts_to_url/
@app.route("/posts_to_url/")
def posts_to_url():
	return url_for("posts", post=['1', '2'])  # /posts/1&2/
```

> 运行结果：
>
> 1. 访问`http://127.0.0.1:8000/posts/1+2/`
>
>    结果：`post is:1*2`
>
> 2. 访问`http://127.0.0.1:8000/posts_to_url/`
>
>    结果：`/posts/1&2/`

## 小细节知识点

### 局域网中其他电脑访问我的网站

> 绑定`0.0.0.0`地址，在run时加入参数`host="0.0.0.0"`

### 指定端口号

> 通过`app.run(port=5000)`，指定参数

### url唯一

> `app.route("/list/")`，通过`http://127.0.0.1:5000/list`和`http://127.0.0.1:5000/list/`都能访问
>
> `app.route('/list')`，仅能通过`http://127.0.0.1:5000/list`访问

### GET&POST请求

> 通过`app.route`加`methods`参数列表指定访问的时候接受的方式。
>
> * `GET`：通过url传参，有长度限制，传输少量数据。只会在服务器上获取资源，不改变服务器的状态。
> * `POST`：通过http请求头传参在`Form Data`中，可以用来传输大文件、密码和用户名等隐私信息，提交数据。
> * 在`flask`中默认使用`GET`方法，，如果想要设置自己的请求方式，那么应该传递`methods`列表


## 重定向

> 页面体现上表现为浏览器从一个页面自动跳转到另一个页面

- 永久重定向：状态码`301`，多个旧网址被废弃了要转到一个新的网站。
- 临时重定向：状态吗`302`，表示页面暂时性跳转。

> `flask`的重定向是通过`flask.redirect(location, code=30x)`实现的，`location`表示重定向的位置，`code`表示状态码，在`location`位置应该配合使用`url_for`使用

```python
@app.route('/')
def hello_world():
	return 'Hello World!'


@app.route("/login/")
def login():
	return "login web page"


@app.route("/profile/")
def profile():
	name = request.args.get('name')
	if not name:
		return redirect(url_for("login"), code=302)  # 不指定code默认302
	else:
		return "your name is {}".format(name)
```

## response响应

> `flask = werkzeug + sqlalchemy + jinja2`
>
> * `werkzeug`：处理网络请求相关
> * `sqlalchemy`：处理数据相关的
> * `jinja2`：处理模板相关的

* 如果返回一个合法的相应对象，则直接返回，即`Response`对象
* 如果返回的是一个字符串，则`flask`会创建一个`werkzeug.wrappers.Response`对象，以字符串作为主体，状态码为`200`，`MIME`类型为`text/html`，返回该对象。
* 如果是返回的是元组，元组中的数据类型是`response,status,headers`，就会覆盖`Response`的属性，`headers`可以使一个列表或者字典，作为额外的消息头。
* 如果以上条件都不满足，`flask`会假设返回值是一个合法的`WSGI`应用程序，并通过`Response.force_type(rv,request.environ)`转化为一个请求对象

### 视图函数可以返回的类型

1. 字符串，将字符串包装成`Response`对象返回
2. 返回元组，元祖的形式必须为`response,status,headers`，`headers`可以使一个列表或者字典，作为额外的消息头。
3. 返回`Response`及其子类
4. 如果返回的不是上面的类型可以自定义响应类型

### 自定义响应

1. 必须继承`Response`类，转换成支持的类型然后调用父类的`force_type`方法
2. 必须实现方法`force_type(cls, response, environ=None)`，用来处理不能识别的返回值类型
3. 必须指定`app.response_class`为你自己的类

```python
class JSONResponse(Response):
	@classmethod
	def force_type(cls, response, environ=None):
		"""
		这个方法只有视图函数返回字符串、非元祖，非Rseponse对象才调用
		:param response:
		:param environ:
		:return:
		"""
		# print(response)
		# print(type(response))
		if isinstance(response, dict):  # 是字典
			response = jsonify(response)
			return super(JSONResponse, cls).force_type(response)
```

> `jsonify`可以将字典转化成`json`对象，还将该对象包装成`Response`对象