# day14

## Spring-JdbcTemplate

> `Spring`对`Jdbc`操作的一层封装；
>
> - 作用：用于和数据交互，实现对表的`CRUD`操作；

### JdbcTemplate基本用法

```java
package com.jianmo.jdbcTemplate;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.datasource.DriverManagerDataSource;
import org.springframework.stereotype.Service;

/**
 * JDBCTemplate的基本用法：IOC配置
 */
@Service
public class JDBCTemplate02 {
	public static void main(String[] args) {
		// 1、获取IOC容器
		ApplicationContext context = new ClassPathXmlApplicationContext("bean.xml");

		// 2、从IOC容器获取bean对象
		JdbcTemplate jdbcTemplate = (JdbcTemplate)context.getBean("jdbcTemplate");

		// 3.执行sql语句
		jdbcTemplate.execute("insert into account(name, money) values ('李四', 800)");
	}
}
```

### bean配置文件

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        http://www.springframework.org/schema/beans/spring-beans.xsd">

    <!-- 配置Spring-JdbcTemplate -->
    <bean id="jdbcTemplate" class="org.springframework.jdbc.core.JdbcTemplate">
        <property name="dataSource" ref="DataSource"></property>
    </bean>

    <!-- 配置JDBC的DataSource -->
    <bean id="DataSource" class="org.springframework.jdbc.datasource.DriverManagerDataSource">
        <property name="driverClassName" value="com.mysql.jdbc.Driver"></property>
        <property name="url" value="jdbc:mysql://192.168.91.103:3306/spring"></property>
        <property name="username" value="root"></property>
        <property name="password" value="123456"></property>
    </bean>
</beans>
```

## Spring-JdbcTemplate的CRUD

> - 保存：
> - 更新：
> - 删除：
> - 查询所有：
> - 查询一个：
> - 查询返回一行一列(使用聚合函数，不使用`group by`)：

## Spring事务控制