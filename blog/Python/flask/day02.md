# day02

## 模板

> 两个常见的模板系统

* `Jinja2`：速度快被广泛使用
  * 让前后端分离；
  * 减少了flask的耦合性，页面逻辑放在模板中，业务逻辑放在视图函数中，将页面与业务解耦有助于diamante的维护；
  * 提供控制语句、继承等高级功能，减少了开发的复杂度。
* `Marko`：借鉴`Django`、`Jinja2`
  * 性能和`Jinja2`近似
  * 有大型网站在使用，如：豆瓣、Reddit
  * 支持在模板中写几乎原生的Python语法的代码，对Python工程师友好，开发效率高
  * 自带完整的缓存系统，提供了有好的拓展接口

### 模板路径

1. 默认的模板路径在项目的根目录下`templates`目录下查找模板；
2. 如果想自己指定模板可以通过`Flask()`创建app的时候，通过`template_folder`指定模板目录。

## 模板渲染

* `{{ 变量 }}`： 用来存放变量以及模板表达式，[参考链接](<http://www.bjhee.com/jinja2-statement.html>)
* `{% 代码 %}`： 用来放控制语句

> 1. 在使用`render_template`渲染模板的时候，可以传递关键字参数，以后直接在模板中使用就可以了。
> 2. 如果你的参数过多，那么可以将所有的参数放到一个字典中，然后在传字典参数的时候，使用`**`，将字典打散成字典参数。
>
> `{{ username }}`渲染`html`代码

```python
@app.route("/post/")
def my_list():
	info = {
		"username": "pip",
		"age": 18,
		"profile": {
			"gender": False,
			"address": "China",
			"height": "180",
		}
	}
	# return render_template("index.html", username="pip", age=18)
	# return render_template("index.html", context=info)  # 使用时候需要通过context.*来引用变量
	return render_template("index.html", **info)  # 把info当做显示指定的方式传递进去
```

```html
    <h1>通过传入参数的方式</h1>
    <h1>username: {{ username }}</h1>
    <h1>age: {{ age }}</h1>
    <h1>profile: {{ profile.address }}</h1>
    <h1>height: {{ profile['height'] }}</h1>
    <h1>gender: {{ profile["gender"] }}</h1>

{#    <h1>通过context的方式传参</h1>#}
{#    <h1>username: {{ context.username }}</h1>#}
{#    <h1>age: {{ context.age }}</h1>#}
```

## url_for在模板中的使用

> 后端代码


```python
@app.route("/home/")
def home():
	return render_template("home.html")


@app.route("/login/<uid>/")
def login(uid):
	return "登录" + "id = " + uid
```
>前段页面

```html
<h1>用户登录页面</h1>
{#    {{ 变量 }} 用来存放变量以及模板表达式#}
{#    {% 代码 %} 用来放控制语句#}
<p><a href="{{ url_for("login", ref="/", uid = 1) }}">登录</a></p>
{# ref：path方式传递参数 #}
{# uid：表示传递的参数 #}
```

> 可以通过`a`标签进行`url_for`反转，并且可以传递参数，两种不同的方式`path`和查询字符串的方式传递，注意变量名。

## 过滤器

> 过滤器是通过管道符号来使用的`|`，例如：`{{ name | length}}`，过滤器相当于是一个函数，把当前的变量传入到过滤器中，然后过滤器根据自己的功能返回相应的值再渲染到页面中。`Jinja2`内置过滤器[点击查看](<http://jinja.pocoo.org/docs/2.10/templates/#list-of-builtin-filters>)。
>
> 基本语法：`{{ variable | 过滤器名字}}`

### 常用过滤器

* `abs(value)`：返回一个数值的绝对值，`-1 | abs`。
* `default(value, default_value, boolean=false)`：如果当前变量没有值，则使用参数中的值来替代。
* `wscape(value)/e`：转移字符，会将`<`、`>`等符号转义成HTML中的符号。
* `first(value)`：返回一个序列的第一个元素，`name | firse`。
* `format(value, *args, **kwargs)`：格式化字符串，`{{ "%s" - "%s"}|format("Hello", "pip!")}`，结果：`Hello - pip!`。
* `last(value)`：返回一个序列的最后一个元素。
* `length(value)`：返回一个序列或者字典的长度。
* `join(value, d=u'')`：将一个序列用d这个参数的值拼接成字符串。
* `safe(value)`：如果开启了全局转义，那么`safe`过滤其会将变量关掉转义。
* `int(value)`：将值转换为`int`类型。
* `float(value)`：将值转换为`float`类型。
* `lower(value)`：将字符串转换成小写。
* `upper(value)`：将字符串转换为大写。
* `replace(value, old, new)`：将`old`替换为`new`的字符串。
* `truncate(value, length=255, killwords=false)`：截取`length`长度的字符串。
* `striptages(value)`：删除字符串中的HTML标签，如果出现多个空格，将替换成一个空格。
* `trim(value)`：截取字符串前面和后面的空白字符
* `string(value)`：将变量转换成字符串。
* `wordcount(value)`：统计长字符串中单词出现的次数，`{{ "hello world" | wordcount }}`。

### default过滤器详讲

> 默认值过滤器，如果当前变量没有值，则使用参数中的默认值。`boolean`为`Ture`是`None`、空元组和空列表等也会使用默认值，`False`时不存在该变量时候才会使用默认值，可以使用`or`来替代`default`过滤器。

```html
<h1>name is: {{ name | default("无名氏", boolean=True) }}</h1>
<h1>default_name is: {{ default_name | default("无名氏", boolean=True) }}</h1>
<h1>or_name is: {{ name or "无名氏" }}</h1>
```

day19