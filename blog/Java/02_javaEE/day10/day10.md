# day10

## 框架介绍

> - 框架：它是项目开发中的一套解决方案，不同的框架解决不同的问题。
> - 框架的好处：框架封装了很多的细节，使开发者可以使用极简的方式实现功能，大大提高开发效率。

## 三层架构

- 表现层：是用于展示数据；
- 业务层：是处理业务需求；
- 持久层：是与数据库交互。

## 持久层技术解决方案

> - `JDBC`技术：
>   - `Connection`
>   - `PrreparedStatement`
>   - `ResultSet`
> - `Spring`的`JdbcTemplate`
>   - `Spring`中对`jdbc`的简单封装；
> - `Apache`的`DBUtils`
>   - 与`Spring`的`JdbcTemplate`类似，也是对`jdbc`的简单封装；
>
> `JDBC`是规范，`Spring`的`JdbcTemplate`和`Apache`的`DBUtils`只是工具类，因此上面三种均不是框架

## Mybatis概述

> `Mybatis`是一个持久层框架，用`java`编写的，它封装了`jdbc`操作的很多细节，使开发者只需要关注`sql`语句本身，而无需关注注册驱动，创建连接等繁杂过程，它使用了ORM思想实现了结果集的封装。

### ORM

> `ORM`(`Object Relational Mapping`)对昂关系映射，把数据库表和实体类以及实体类的属性对应起来，让我们可以操作实体类就实现操作数据库表。

## Mybatis入门

### Mybatis的环境搭建

> 1. 创建Maven工程并导入坐标；
> 2. 创建实体类和dao的接口；
> 3. 创建Mybatis的主配置文件`SqlMapConfig.xml`；
> 4. 创建映射配置文件`UserDao.xml`。

### 环境搭建注意事项

> 1. 创建`UserDao.xml`和`UserDao.java`时名称为了和之前的知识保持一致，所以在`Mybatis`中把持久层的操作接口名称和映射文件也叫做`Mapper`，因此，`UserDao`和`UserMapper`表达的意思一样。
> 2. 在`idea`创建目录的时候，它和包不同。
>    - 包创建`com.jianmo.dao`，它是**三级目录结构**；
>    - 目录创建时`com.jianmo.dao`，是**一级目录结构**。
> 3. `Mybatis`的映射配置文件必须和`dao`接口的包结构相同。
> 4. 映射配置文件的`Mapper`标签`namespace`属性取值必须是`dao`接口的全限定类名。
> 5. 映射配置文件的操作配置，`id`属性的取值，必须是`dao`接口的方法名。
>
> 当遵守`3、4、5`点后，我们以后开发中不需要再写`dao`的实现类。
>
> 注意事项：
>
> - `xml`配置时，不要忘记在映射配置中告诉`Mybatis`要封装到哪个实体类汇总，配置的方式：指定实体类的全限定类名

### Mybatis使用步骤

> 1. 读取配置文件；
> 2. 创建`SqlSessionFactory`工厂对象；
> 3. 使用工厂生成`SqlSession`对象；
> 4. 使用`SqlSession`创建`Dao`代理对象；
> 5. 使用代理对象执行方法；
> 6. 释放资源；

```java
package com.jianmo.test;

import com.jianmo.dao.UserDao;
import com.jianmo.domain.User;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

/**
 * Mybatis入门测试案例
 */

public class MybatisTest {

	/**
	 * 入门案例
	 * @param args
	 */
	public static void main(String[] args) throws IOException {
		// 1.读取配置文件
		final InputStream resource = Resources.getResourceAsStream("SqlMapConfig.xml");

		// 2.创建SqlSessionFactory工厂
		final SqlSessionFactoryBuilder builder = new SqlSessionFactoryBuilder();  // 构建者模式
		final SqlSessionFactory factory = builder.build(resource);  // 工厂模式

		// 3.使用工厂生成SqlSession对象
		final SqlSession session = factory.openSession();

		// 4.使用SqlSession创建Dao代理对象
		final UserDao userDao = session.getMapper(UserDao.class);  // 动态代理模式

		// 5.使用代理对象执行方法
		final List<User> all = userDao.findAll();
		for (User user : all) {
			System.out.println(user);
		}

		// 6.释放资源
		session.close();
		resource.close();
	}
}
```

### Mybatis注解

> 使用步骤(基于`xml`配置)：
>
> 把`UserDao.xml`移除，在`dao`接口的方法上使用`@Select`注解，并且指定SQL语句同时需要在`SqlMapConfig.xml`中的`mapper`配置时，使用`class`属性指定`dao`接口的全限定类名。

## Mybatis实现CRUD操作

> `Mybatis`的`CRUD`、模糊查询、查询一行一列、获取插入数据的`id`、包装(`pojo`)对象查询。

### 注解方式

```java
package com.jianmo.dao;

import com.jianmo.domain.QueryVo;
import com.jianmo.domain.User;
import org.apache.ibatis.annotations.*;

import javax.management.Query;
import java.util.List;

/**
 * 用户持久层接口
 */

public interface UserDao {
	/**
	 * 查询所有数据
	 * @return
	 */
	@Select("select * from user;")
	List<User> findAll();

	/**
	 * 保存用户信息
	 * @param user
	 */
	@SelectKey(statement = "select last_insert_id();",keyProperty = "id", keyColumn = "id", before = false, resultType = Integer.class)
	@Insert("insert into user(username, address, sex, birthday) values(#{username}, #{address}, #{sex}, #{birthday})")
	void saveUser(User user);

	/**
	 * 更新用户信息
	 * @param user
	 */
	@Update("update user set username=#{username}, address=#{address}, sex=#{sex}, birthday=#{birthday} where id=#{id}")
	void updateUser(User user);

	/**
	 * 删除用户信息
	 * @param userID
	 */
	@Delete("delete from user where id=#{userID}")
	void deleteUser(Integer userID);


	/**
	 * 根据id查询用户
	 * @param userID
	 * @return
	 */
	@Select("select * from user where id=#{userID}")
	User findByID(Integer userID);

	/**
	 * 通过用户名模糊查询用户，参数需要提供%
	 * @param name
	 * @return
	 */
	@Select("select * from user where username like #{name}")  // 方式一模糊查询，sql预编译，参数占位符(优)
	// @Select("select * from user where username like '%${value}%'")  // 方式二模糊查询，字符串拼接，必须写成value
	List<User> findByName(String name);

	/**
	 * 查询总记录数
	 * @return
	 */
	@Select("select count(id) from user")
	Integer findTotal();

	/**
	 * 根据QueryVo查询中的条件查询用户
	 *
	 * @param vo
	 * @return
	 */
	@Select({"select * from user where username  like #{user.username}"})
	List<User> findUserByVo(QueryVo vo);
}
```

### xml方式

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.jianmo.dao.IUserDao">

    <!-- 配置 查询结果的列名和实体类的属性名的对应关系 -->
    <resultMap id="userMap" type="uSeR">
        <!-- 主键字段的对应 -->
        <id property="userId" column="id"></id>
        <!--非主键字段的对应-->
        <result property="userName" column="username"></result>
        <result property="userAddress" column="address"></result>
        <result property="userSex" column="sex"></result>
        <result property="userBirthday" column="birthday"></result>
    </resultMap>


    <!-- 查询所有 -->
    <select id="findAll" resultMap="userMap">
        <!--select id as userId,username as userName,address as userAddress,sex as userSex,birthday as userBirthday from user;-->
        select * from user;
    </select>

    <!-- 保存用户 -->
    <insert id="saveUser" parameterType="user">
        <!-- 配置插入操作后，获取插入数据的id -->
        <selectKey keyProperty="userId" keyColumn="id" resultType="int" order="AFTER">
            select last_insert_id();
        </selectKey>
        insert into user(username,address,sex,birthday)values(#{userName},#{userAddress},#{userSex},#{userBirthday});
    </insert>

    <!-- 更新用户 -->
    <update id="updateUser" parameterType="USER">
        update user set username=#{userName},address=#{userAddress},sex=#{userAex},birthday=#{userBirthday} where id=#{userId}
    </update>

    <!-- 删除用户-->
    <delete id="deleteUser" parameterType="java.lang.Integer">
        delete from user where id = #{uid}
    </delete>
    
    <!-- 根据id查询用户 -->
    <select id="findById" parameterType="INT" resultMap="userMap">
        select * from user where id = #{uid}
    </select>

    <!-- 根据名称模糊查询 -->
    <select id="findByName" parameterType="string" resultMap="userMap">
          select * from user where username like #{name}
        <!-- select * from user where username like '%${value}%'-->
   </select>

    <!-- 获取用户的总记录条数 -->
    <select id="findTotal" resultType="int">
        select count(id) from user;
    </select>

    <!-- 根据queryVo的条件查询用户 -->
    <select id="findUserByVo" parameterType="com.jianmo.domain.QueryVo" resultMap="userMap">
        select * from user where username like #{user.username}
    </select>
</mapper>
```

## Mybatis的参数深入类型

### OGNL表达式

> `OGNL`(`Object Graphic Navigation Language`)对象图导航语言，是通过对象中的方法来获取数据，在写法上把`get`给省略了。
>
> 获取用户名称：
>
> - 类中的写法：`user.getUsername();`
> - `OGNL`表达式写法：`user.username();`
>
> `Mybatis`中可以直接写`username`不指定对象名，是因为`parameterType`中已经提供了属性所属的类。