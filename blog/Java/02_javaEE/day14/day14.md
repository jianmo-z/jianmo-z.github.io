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

> - 保存；
> - 更新；
> - 删除;
> - 查询所有；
> - 查询一个；
> - 查询返回一行一列(使用聚合函数，不使用`group by`)。
>
> ```java
> package com.jianmo.jdbcTemplate;
> 
> import com.jianmo.domain.Account;
> import org.springframework.context.ApplicationContext;
> import org.springframework.context.support.ClassPathXmlApplicationContext;
> import org.springframework.jdbc.core.BeanPropertyRowMapper;
> import org.springframework.jdbc.core.JdbcTemplate;
> import org.springframework.jdbc.core.RowMapper;
> import org.springframework.stereotype.Service;
> 
> import java.sql.ResultSet;
> import java.sql.SQLException;
> import java.util.List;
> 
> /**
>  * JDBCTemplate的CRUD操作
>  */
> @Service
> public class JDBCTemplate03 {
> 	public static void main(String[] args) {
> 		// 1、获取IOC容器
> 		ApplicationContext context = new ClassPathXmlApplicationContext("bean.xml");
> 
> 		// 2、从IOC容器获取bean对象
> 		JdbcTemplate jdbcTemplate = (JdbcTemplate) context.getBean("jdbcTemplate");
> 
> 		// 3.执行sql语句
> 		// 3.1保存
> 		jdbcTemplate.update("insert into account(name, money) values(?, ?)", "insert", 800);
> 
> 		// 3.2更新
> 		jdbcTemplate.update("update account set name=?, money=? where id=?", "update", 900, 8);
> 
> 		// 3.3删除
> 		jdbcTemplate.update("delete from account where id = ?", 4);
> 
> 		// 3.4查询所有
> 		// 3.4.1方式一：lambda表达式，interface RowMapper<T>
> 		List<Account> accounts = jdbcTemplate.query("select * from account where money >= ?;",
> 				(RowMapper<Account>) (rs, rowNum) -> new Account(rs.getInt("id"), rs.getString("name"), rs.getFloat("money")), 1000f);
> 		for (Account it : accounts) {
> 			System.out.println(it);
> 		}
> 
> 		// 3.4.2方式二：Spring框架提供的封装对象，BeanPropertyRowMapper
> 		accounts = jdbcTemplate.query("select * from account where money >= ?;", new BeanPropertyRowMapper<>(Account.class), 1000f);
> 		for (Account it : accounts) {
> 			System.out.println(it);
> 		}
> 
> 		// 3.5查询一个
> 		accounts = jdbcTemplate.query("select * from account where id = ?;", new BeanPropertyRowMapper<>(Account.class), 8);
> 		System.out.println(accounts.isEmpty() ? "No result" : accounts.get(0));
> 
> 		// 3.6查询返回一行一列(使用聚合函数，但不使用group by)
> 		Integer count = jdbcTemplate.queryForObject("select count(id) from account where money > ?", Integer.class, 800);
> 		System.out.println("count:" + count);
> 	}
> }
> ```

### JdbcDaoSupport

> 多个`Dao`使用同一`jdbcTemplate`
>
> 1. 继承自`org.springframework.jdbc.core.support.JdbcDaoSupport`；
> 2. 自己写`jdbcTemplate`；

## Spring声明式事务控制

> `Spring`的事务控制都是基于`AOP`的，它既可以使用编程的方式实现，也可以使用配置的方式实现。
>
> - `PlatformTransactionManager`接口提供事务操作的方法；
> - `TransactionDefinition`接口提供事务的定义信息对象；
> - `TransactionStatus`接口提供事务具体的运行状态

### PlatformTransactionManager

> `PlatformTransactionManager`只是接口需要使用该接口的实现类，
>
> - 接口中的成员方法：
>   - 获取事务状态信息：`TransactionStatus getTransaction(TransactionDefinition definition)`；
>   - 提交事务：`void commit(TransactionStatus status)`；
>   - 回滚事务：`void rollback(TransactionStatus status)`
> - 接口的实现类有：
>   - `org.springframework.jdbc.datasource.DataSourceTransactionManager`，使用`Spring JDBC`或`iBatis`进行持久化数据时使用；
>   - `org.springframework.orm.hibernate5.HibernateTransactioinManager`，使用`Hibernate`版本进行持久化数据时使用。

### TransactionDefinition

> `TransactionDefinition`接口定义事务的信息对象。
>
> * 获取事务名称：`String getName()`；
> * 获取事务隔离级别：`int getIsolationLevel()`，四种隔离级别默认使用数据库的隔离级别；
> * 获取事务传播行为：`int getPropagationBehavior()`，`REQUIRED`**增删改**操作(默认)、`SUPPORTS`**查询**操作；
> * 获取事务超时时间：`int getTimeout()`，默认为`-1`没有超时限制，以秒为单位；
> * 获取事务是否只读：`boolean isReadOnly()`；

### TransactionStatus

> `TransactionStatus`接口描述某个实践点上事务对象的状态信息。
>
> - 刷新事务：`void flush()`；
> - 获取是否存在存储点：`boolean hasSavepoint()`；
> - 获取事务是否完成：`boolean isCompleted()`；
> - 获取事务是否为新事务：`boolean isNewTransaction()`；
> - 获取事务是否回滚：`boolean isRollbackOnly()`；
> - 设置事务回滚：`void setRollbackOnly()`；

## Sping基于XML的声明式实物配置步骤

> 1. 配置事务管理器；
> 2. 配置事务的通知；
>    1. 导入`bean.xml`对事务的约束，`tx`和`aop`的名称空间和约束；
>    2. 使用`<tx:advice>`配置事务通知；
>       - 属性：
>         - `id`：给事务通知起一个唯一标识；
>         - `tranaction-manager`：给事务通知提供一个事务管理器引用；
> 3. 配置`AOP`的通用切入点表达式；
> 4. 建立事务通知和`AOP`切入点表达式的对应关系；
> 5. 配置事务的属性，事务的通知在`<aop:advisor>`标签的内部配置，属性有：。
>    - `isolation`：指定事务的隔离级别，默认值是数据库的隔离级别；
>    - `propagation`：用于指定事务的传播行为，默认值是`REQUIRED`，即**增删改**的选择，表示一定有事务；**查询**方式：`SUPPORTS`
>    - `read-only`：用于指定是否只读，只有查询方法才能设置为`true`，默认值为`false`；
>    - `timeout`：指定事务的超时时间，默认值为`-1`，表示永不超时，指定数值单位为秒。
>    - `rollback-for`：用于指定一个异常，当产生该异常时，事务回滚，其他异常，事务不回滚，**没有默认值**，表示任何异常**都回滚**；
>    - `no-rollback-for`：与`rollback-for`相反，用于指定一个异常，当产生该异常时，事务不回滚，其他异常，事务回滚。**没有默认值**，表示任何异常**都回滚**；
>
> ```xml
> <?xml version="1.0" encoding="UTF-8"?>
> <beans xmlns="http://www.springframework.org/schema/beans"
>        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
>        xmlns:aop="http://www.springframework.org/schema/aop"
>        xmlns:tx="http://www.springframework.org/schema/tx"
>        xsi:schemaLocation="
>         http://www.springframework.org/schema/beans
>         http://www.springframework.org/schema/beans/spring-beans.xsd
>         http://www.springframework.org/schema/tx
>         http://www.springframework.org/schema/tx/spring-tx.xsd
>         http://www.springframework.org/schema/aop
>         http://www.springframework.org/schema/aop/spring-aop.xsd">
> 
> 
>     <!-- 由业务层向DAO逐层配置，逻辑会比较清晰 -->
>     <!-- 配置业务层注入accountService依赖 -->
>     <bean id="accountService" class="com.jianmo.service.impl.AccountServiceImpl">
>         <property name="accountDao" ref="accountDao"></property>
>     </bean>
> 
>     <!-- 注入accountDao依赖 -->
>     <bean id="accountDao" class="com.jianmo.dao.impl.AccountDaoImpl">
>         <property name="dataSource" ref="DataSource"></property>
>     </bean>
> 
>     <!-- 配置JDBC的DataSource -->
>     <bean id="DataSource" class="org.springframework.jdbc.datasource.DriverManagerDataSource">
>         <property name="driverClassName" value="com.mysql.jdbc.Driver"></property>
>         <property name="url" value="jdbc:mysql://192.168.91.103:3306/spring"></property>
>         <property name="username" value="root"></property>
>         <property name="password" value="123456"></property>
>     </bean>
> 
>     <!-- Spring中基于XML的声明式事务控制配置步骤 -->
>     <!-- 1、配置事务管理器 -->
>     <bean id="transactionManager" class="org.springframework.jdbc.datasource.DataSourceTransactionManager">
>         <property name="dataSource" ref="DataSource"></property>
>     </bean>
> 
>     <!-- 2、配置事务的通知 -->
>     <tx:advice id="txAdvice" transaction-manager="transactionManager">
>         <!-- 5、配置事务的属性，事务的通知在<aop:advisor>标签的内部配置。
>                 属性：
>                     isolation：指定事务的隔离级别，默认值是数据库的隔离级别；
>                     propagation：用于指定事务的传播行为，默认值是REQUIRED，即增删改的选择，表示一定有事务；查询方式：SUPPORTS
>                     read-only：用于指定是否只读，只有查询方法才能设置为true，默认值为false；
>                     timeout：指定事务的超时时间，默认值为-1，表示永不超时，指定数值单位为秒。
>                     rollback-for：用于指定一个异常，当产生该异常时，事务回滚，其他异常，事务不回滚，没有默认值，表示任何异常都回滚；
>                     no-rollback-for：与rollback-for相反，用于指定一个异常，当产生该异常时，事务不回滚，其他异常，事务回滚，没有默认值，表示任何异常都回滚；
>          -->
>         <tx:attributes>
>             <!-- 偏特化transfer优先级比*高 -->
>             <tx:method name="find*" propagation="SUPPORTS" read-only="true"/>
>             <tx:method name="transfer" propagation="REQUIRED" read-only="false"/>
>         </tx:attributes>
>     </tx:advice>
> 
>     <!-- 3、配置AOP -->
>     <aop:config>
>         <!-- 配置切入点表达式 -->
>         <aop:pointcut id="pt1" expression="execution(* com.jianmo.service.impl.*.*(..))"/>
>         <!--4、建立切入点表达式和事务通知的对应关系；-->
>         <aop:advisor advice-ref="txAdvice" pointcut-ref="pt1"></aop:advisor>
>     </aop:config>
> </beans>
> ```