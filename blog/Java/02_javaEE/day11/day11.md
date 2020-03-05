# day11

## Mybatis的延迟加载

### 需要延迟加载的问题提出？

> 在一对多中，当我们有一个用户，它有100个账户。
>
> - 在查询用户的时候，要不要把关联的账户查出来？
>
> - 在查询账户的时候，要不要把关联的用户查出来？

### 延迟加载

> 在真正使用数据时才发起查询，不用的时候不查询，按需加载(懒加载)。

### 立即加载

> 不管用不用，只要一调用，马上发起查询。

### 四种表关系对应的加载策略

> 一对多、多对一、一对一和多对多；
>
> 延迟加载：一对多，多对多；
>
> 立即加载：多对一，一对一。

## 如何实现Mybatis的延迟加载

> 1. 配置开启延迟加载；
> 2. 配置延迟加载`Dao`文件。

## Mybatis的缓存

> 存储在内存中的临时数据。

### 为什么使用缓存

> 减少和数据库的交互次数，提高执行效率。

### 使用缓存的条件

> - 可以使用缓存：
>
>   1. 经常查询并且不经常改变的；
>   2. 数据的正确与否结果影响不大。
>
> - 不适用于缓存：
>
>   1. 经常改变的数据；
>   2. 数据的正确与否对最终结果影响很大。
>
>   > 如：商品的库存、银行的汇率和股市的价格。

## Mybatis的一级缓存和二级缓存

> - 一级缓存：
>
>   > 它指的是`Mybatis`中`SqlSession`对象的缓存，当执行查询之后，查询的记过会同时存入到`SqlSession`为我们提供的一块区域中，该区域是一个`Map`结构，当查取一个的数据时，`Mybatis`会现在`SqlSession`中查询是否有，如果有则直接取出数据。当`SqlSession`对象消失时，`Mybatis`的一级缓存也就消失了。
>
> - 二级缓存
>
>   > 它指的是`Mybatis`中`SqlsessionFactory`对象的缓存，由同一个`SqlSessionFactory`对象创建的`SqlSession`共享其缓存。
>
>   - 二级缓存使用步骤：
>     1. 设置`Mybatis`框架开启二级缓存，在`SqlMapConfig.xml`中配置信息；
>     2. 让当前的映射文件支持二级缓存，在`*Dao.xml`文件中配置；
>     3. 让当前的操作支持二级缓存，在`select`标签中配置。

## Mybatis注解开发

### CRUD注解开发

```java
package com.jianmo.test;

import com.jianmo.domain.User;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

/**
 * 在Mybatis中针对注解一共有四个注解
 *  - @Select
 *  - @Insert
 *  - @Update
 *  - @Delete
 */
public interface UserDao {

	/**
	 * 查询所有用户
	 * @return
	 */
	@Select("select * from user;")
	List<User> findAll();

	/**
	 * 保存用户
	 * @param user
	 */
	@Insert("insert into user(username, address, sex, birthday) values(#{username}, #{address}, #{sex}, #{birthday})")
	void saveUser(User user);

	/**
	 * 更新用户
	 * @param user
	 */
	@Update("update user set username=#{username}, address=#{address}, sex=#{sex}, birthday=#{birthday} where id=#{id}")
	void updateUser(User user);

	/**
	 * 删除用户
	 * @param id
	 */
	@Delete("delete from user where id=#{id}")
	void deleteUserByID(Integer id);

	@Select("select * from user where id=#{id}")
	User findByID(Integer id);

	@Select("select * from user where username like #{username}")
	List<User> findByName(String username);

	@Select("select count(id) from user;")
	Integer findTotal();
}
```

### 多表注解开发：一对一

```java
package com.jianmo.dao;

import com.jianmo.domain.Account;
import org.apache.ibatis.annotations.One;
import org.apache.ibatis.annotations.Result;
import org.apache.ibatis.annotations.Results;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.mapping.FetchType;

import java.util.List;

public interface AccountDao {
	/**
	 * 查询所有账户并且获取每个账户所属的用户信息：两个表查询
	 * 一对一
	 * @return
	 */
	@Select("select * from account;")
	@Results(id = "accountMap", value = {
			@Result(id = true, property = "id", column = "id"),
			@Result(property = "uid", column = "uid"),
			@Result(property = "money", column = "money"),
			@Result(property = "user", column = "uid",
					one = @One(select = "com.jianmo.dao.UserDao.findByID", fetchType = FetchType.LAZY))
	})
	List<Account> findAll();

	@Select("select * from account where uid=#{uId}")
	List<Account> findByUID(Integer uId);
}
```

### 多表注解开发：一对多

```java
package com.jianmo.dao;

import com.jianmo.domain.User;
import org.apache.ibatis.annotations.*;
import org.apache.ibatis.mapping.FetchType;

import java.util.List;

/**
 * 在Mybatis中针对注解一共有四个注解
 * - @Select
 * - @Insert
 * - @Update
 * - @Delete
 */
public interface UserDao {

	/**
	 * 查询所有用户
	 *
	 * @return
	 */
	@Select("select * from user;")
	@Results(id = "userMap",
			value = {
					@Result(id = true, property = "userId", column = "id"),
					@Result(property = "userName", column = "username"),
					@Result(property = "userAddress", column = "address"),
					@Result(property = "userSex", column = "sex"),
					@Result(property = "userBirthday", column = "birthday"),
			})
	List<User> findAll();

	/**
	 * 通过ID查询用户
	 *
	 * @param id
	 * @return
	 */
	@Select("select * from user where id=#{id}")
	@ResultMap(value = {"userMap"}) // 引用ResultMap
	User findByID(Integer id);

	/**
	 * 查询所有信息和对应的账户信息
	 * 一对多
	 * @return
	 */
	@Select("select * from user")
	@Results(id = "userMap4Account", value = {
			@Result(id = true, property = "userId", column = "id"),
			@Result(property = "userName", column = "username"),
			@Result(property = "userAddress", column = "address"),
			@Result(property = "userSex", column = "sex"),
			@Result(property = "userBirthday", column = "birthday"),
			@Result(property = "accounts", column = "id",
					many = @Many(select = "com.jianmo.dao.AccountDao.findByUID", fetchType = FetchType.EAGER)),
	})
	List<User> findAllWithAccounts();
}
```

### 注解配置缓存

> - 一级缓存默认开始不用关心，使用同一个`OpenSession`；
> - 配置文件(`SqlMapConfig.xml`)加`Dao`**接口**注解(`***Dao.java`)；

#### 配置文件

> `settings`配置`setting`标签的属性`cacheEnabled`；

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE configuration        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <!-- 引入外部配置文件 -->
    <properties resource="jdbcConfig.properties"></properties>

    <!-- 开启Mybatis二级缓存 -->
    <settings>
        <setting name="cacheEnabled" value="true"/>
    </settings>

    <!-- 配置别名 -->
    <typeAliases>
        <package name="com.com.jianmo.domain"/>
    </typeAliases>

    <!-- 配置环境 -->
    <environments default="mysql">
        <environment id="mysql">
            <transactionManager type="JDBC"></transactionManager>
            <dataSource type="POOLED">
                <property name="driver" value="${jdbc.driver}"/>
                <property name="url" value="${jdbc.url}"/>
                <property name="username" value="${jdbc.username}"/>
                <property name="password" value="${jdbc.password}"/>
            </dataSource>
        </environment>
    </environments>

    <!-- 指定带有注解的dao接口所在位置 -->
    <mappers>
        <package name="com.jianmo.dao"/>
    </mappers>
</configuration>
```

#### Dao接口配置

> 给接口添加注解`@CacheNamespace(blocking = true)`

```java
package com.jianmo.dao;

import com.jianmo.domain.User;
import org.apache.ibatis.annotations.*;
import org.apache.ibatis.mapping.FetchType;

import java.util.List;

/**
 * 在Mybatis中针对注解一共有四个注解
 * - @Select
 * - @Insert
 * - @Update
 * - @Delete
 */
@CacheNamespace(blocking = true)  // 开启二级缓存
public interface UserDao {

	/**
	 * 查询所有用户
	 *
	 * @return
	 */
	@Select("select * from user;")
	@Results(id = "userMap",
			value = {
					@Result(id = true, property = "userId", column = "id"),
					@Result(property = "userName", column = "username"),
					@Result(property = "userAddress", column = "address"),
					@Result(property = "userSex", column = "sex"),
					@Result(property = "userBirthday", column = "birthday"),
			})
	List<User> findAll();

	/**
	 * 通过ID查询用户
	 *
	 * @param id
	 * @return
	 */
	@Select("select * from user where id=#{id}")
	@ResultMap(value = {"userMap"}) // 引用ResultMap
	User findByID(Integer id);

	/**
	 * 查询所有信息和对应的账户信息
	 * 一对多
	 * @return
	 */
	@Select("select * from user")
	@Results(id = "userMap4Account", value = {
			@Result(id = true, property = "userId", column = "id"),
			@Result(property = "userName", column = "username"),
			@Result(property = "userAddress", column = "address"),
			@Result(property = "userSex", column = "sex"),
			@Result(property = "userBirthday", column = "birthday"),
			@Result(property = "accounts", column = "id",
					many = @Many(select = "com.jianmo.dao.AccountDao.findByUID", fetchType = FetchType.EAGER)),
	})
	List<User> findAllWithAccounts();
}
```

