# day09

## JSON

> `JSON`(`JavaScript Object Notaton`)，`JavaScript`对象表示法，`JSON`现在多用于存储和交换文本信息的语法，类似`XML`。`JSON`比`XML`更小、更快、更易于解析。

## JSON语法规则

> 1. 数据在名称/值对中：`json`数据是由键值对构成的；
>    - **键**：用引号(单双都可以)引起来，也可以不使用引号。
>    - **值**的取值类型：
>      - 数字(整数或者字符串)；
>      - 字符串(在双引号中)；
>      - 逻辑值(`true`或`false`)；
>      - 数组(在方括号中)，例：`{"person":[{}, {}]}`；
>      - 对象(在花括号中)，例：`{"address" {"province":"陕西", .. ..}}`；
>      - `null`。
> 2. 数据由逗号分隔：多个键值对由逗号分隔；
> 3. 花括号保存对象：使用`{}`定义`json`格式；
> 4. 方括号保存数组：`[]`。

## 获取JSON数据

> 1. `json对象.键名`；
> 2. `json对象["键名"]`;
> 3. `数组对象[索引]`。

## JSON数据和Java对象的相互转化.

> 使用`JSON`解析器，常见解析器：`Jsonlib`、`Gson`、`fastjson`、`jackson`。

### JSON转Java对象

> `json`对象转`Java`使用步骤：
>
> 1. 导入`jackson`的相关`jar`包；
> 2. 创建`jackson`的核心对象`ObjectMapper`；
> 3. 调用`ObjectMapper`的相关方法进行转化；
>    - `readValue(json字符串, Class)`

### Java对象转JSON

> `Java`对象转`json`使用步骤：
>
> 1. 导入`jackson`的相关`jar`包；
>
> 2. 创建`jackson`的核心对象`ObjectMapper`；
>
> 3. 调用`ObjectMapper`的相关方法进行转化；
>
>    - `writeValue(参数1, obj)`；
>      - `参数1`：
>        - `File`：将`obj`对象转化为`JSON`字符串，并保存到执行的文件中；
>        - `Writer`：将`obj`对象转化为`JSON`字符串，并将`JSON`数据填充到字节输出流中；
>        - `OutputStream`：将`obj`对象转化为`JSON`字符串，并将`JSON`数据填充到字节输出流中。
>    - `writeValueAsString()`：将对象转化为`JSON`字符串；
>    - `writeValueAsBytes()`
>
> **JSON注解**：
>
>    - `@JsonIgnore`：排除属性，给成员变量、`Getter`和`Setter`上任意一个上加即可；
>    - `@JsonFormat`：属性值的格式化。
>
> 复杂数据类型转化：
>
> * `List`：数组；
> * `Map`：与对象格式一致。

### 测试代码

```java
package com_01.jianmo.test;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com_01.jianmo.domain.Person;
import org.junit.Test;

import java.io.IOException;
import java.lang.reflect.Array;
import java.util.*;

public class JacksonTest {
	@Test
	public void Object2JSON() throws JsonProcessingException {
		// 1.创建Person对象
		final Person person = new Person("张三", 21, false, new Date());
		// 2. 创建ObjectMapper对象
		ObjectMapper objectMapper = new ObjectMapper();
		// 3.Object2JSON
		final String s = objectMapper.writeValueAsString(person);
		// 4.打印json字符串
		System.out.println(s);
		/*
		* {"name":"张三","age":21,"gender":false}  // 使用@JsonIgnore
		* 或
		* {"name":"张三","age":21,"gender":false,"birthday":"2020-02-29"}  // 使用@JsonFormat(pattern = "yyyy-MM-dd")
		* */

	}

	@Test
	public void Object2JSONList() throws JsonProcessingException {
		// 1.创建Person对象
		final Person p1 = new Person("张三", 21, false, new Date());
		final Person p2 = new Person("张三", 21, false, new Date());
		final Person p3 = new Person("张三", 21, false, new Date());
		List<Person> person = new ArrayList<>();
		person.add(p1);
		person.add(p2);
		person.add(p3);
		// 2. 创建ObjectMapper对象
		ObjectMapper objectMapper = new ObjectMapper();
		// 3.Object2JSON
		final String s = objectMapper.writeValueAsString(person);
		// 4.打印json字符串
		System.out.println(s);
	}

	@Test
	public void Object2JSONMap() throws JsonProcessingException {
		// 1.创建Person对象
		final Person p1 = new Person("张三", 21, false, new Date());
		final Person p2 = new Person("张三", 21, false, new Date());
		final Person p3 = new Person("张三", 21, false, new Date());
		Map<String, Person> person = new HashMap<>();
		person.put("张三1", p1);
		person.put("张三2", p2);
		person.put("张三3", p3);
		// 2. 创建ObjectMapper对象
		ObjectMapper objectMapper = new ObjectMapper();
		// 3.Object2JSON
		final String s = objectMapper.writeValueAsString(person);
		// 4.打印json字符串
		System.out.println(s);
	}

	@Test
	public void JSON2Object() throws IOException {
		// 1.创建json字符串
		final String s = "{\"name\":\"张三\",\"age\":21,\"gender\":false}";
		// 2. 创建ObjectMapper对象
		ObjectMapper objectMapper = new ObjectMapper();
		// 3.JSON2Object
		final Object obj = objectMapper.readValue(s, Person.class);
		// 4.打印Person对象
		System.out.println(obj); // Person{name='张三', age=21, gender=false}
	}
}
```

### Person类

```java
package com_01.jianmo.domain;


import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonIgnore;

import java.util.Date;


public class Person {
	private String name;
	private Integer age;
	private boolean gender;

	// @JsonIgnore  // 忽略该属性
	@JsonFormat(pattern = "yyyy-MM-dd")  // 年月日
	private Date birthday;

	public Person() {
	}

	public Person(String name, Integer age, boolean gender, Date birthday) {
		this.name = name;
		this.age = age;
		this.gender = gender;
		this.birthday = birthday;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Integer getAge() {
		return age;
	}

	public void setAge(Integer age) {
		this.age = age;
	}

	public boolean isGender() {
		return gender;
	}

	public void setGender(boolean gender) {
		this.gender = gender;
	}

	public Date getBirthday() {
		return birthday;
	}

	public void setBirthday(Date birthday) {
		this.birthday = birthday;
	}

	@Override
	public String toString() {
		return "Person{" +
				"name='" + name + '\'' +
				", age=" + age +
				", gender=" + gender +
				", birthday=" + birthday +
				'}';
	}
}
```

## Redis

> `redis`是一个款高性能的`NOSQL`系列的非关系型数据库，`redis`做缓存。
>
> 1. 数据之间没有关联关系；
> 2. 数据存储在内存中。

### Redis简介

> `Redis`使用C语言开发的一个开源的高性能键值对(`key-value`)数据库，目前为止`Redis`支持的键值数据类型如下：
>
> - 键值数据类型：
>   1. 字符串类型`string`；
>   2. 哈希类型`hash`；
>   3. 列表类型`list`；
>   4. 集合类型`set`；
>   5. 有序集合类型`sortedset`。
> - `redis`的应用场景：
>   - 缓存：数据查询、短连接、新闻内容、商品内容等等；
>   - 聊天室在线好友列表；
>   - 任务队列：秒杀、抢购、12306等等；
>   - 应用排行榜；
>   - 网站访问统计；
>   - 数据过期处理，可以精确到毫秒；
>   - 分布式集群架构中的`session`分离。

## Redis数据结构

> `redis`存储的是：`key-value`格式的数据，其中`key`都是字符串，`value`有5种不同的数据结构。
>
> - `value`键值数据类型：
>   1. 字符串类型`string` : `string`；
>   2. 哈希类型`hash` : `map`；
>   3. 列表类型`list` : `linkedlist`；
>   4. 集合类型`set` : `hashset`；
>   5. 有序集合类型`sortedset` : 可以排序的`hashset`。