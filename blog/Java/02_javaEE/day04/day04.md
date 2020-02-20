# day04

## JDBC

### JDBC概念

> `JDBC`(`Java DataBase Connectivity`)，`Java`语言操作数据库。`JDBC`定义的一套操作所有关系型数据库的规则，即接口。各个数据库厂商实现这套接口，提供数据库驱动`jar`包，我们可以使用这套接口编程，真正执行的代码是驱动`jar`包中的实现类。

### JDBC快速入门

1. 导入驱动`jar`包；
2. 注册驱动；
3. 获取数据库的连接对象`Connection`；
4. 定义`sql`语句；
5. 获取执行`sql`语句的对象`Statement`;
6. 执行`sql`语句，接受返回结果；
7. 处理结果；
8. 释放资源。

```java
package com_01.jianmo.jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;

public class JdbcDemo01 {
	public static void main(String[] args) throws Exception {
		// 1.导入jar包
		// 2.注册驱动
		Class.forName("com.mysql.jdbc.Driver");

		// 3.获取数据库连接对象
		Connection conn = DriverManager.getConnection("jdbc:mysql://192.168.91.103:3306/db1", "root", "123456");

		// 4.定义sql语句
		String sql = "update account set balance = 1000 where id = 1;";

		// 5.获取执行sql的对象Statement
		Statement statement = conn.createStatement();

		// 6.执行sql获取结果
		int count = statement.executeUpdate(sql);

		// 7.处理结果
		System.out.println(count);

		// 8.释放资源
		statement.close();
		conn.close();
	}
}
```

## 详解sql操作各个类

## DriverManager

> 驱动管理类，用于管理JDBC驱动程序的基本服务。

### 注册驱动

> 告诉程序该使用哪一个数据库驱动`jar`包。`mysql5`只有的驱动`jar`包之后可以自动注册驱动；
>
> ```java
> // 2.注册驱动
> Class.forName("com.mysql.jdbc.Driver");
> ```
>
> 注册驱动的内部实现代码：类的静态代码块，创建类时执行一次
>
> ```java
> static {
>     try {
>         DriverManager.registerDriver(new Driver());
>     } catch (SQLException var1) {
>         throw new RuntimeException("Can't register driver!");
>     }
> }
> ```

### 获取数据库连接

> 静态方法：`public static Connection getConnection(String url, String user, String password)`
>
> * `url`：`jdbc:mysql://ip(域名):port/数据库名称`，如果是本机`mysql`服务端，且端口是默认端口，可简写为：`jdbc:mysql:///数据库名称`；
> * `user`：用户名；
> * `password`：密码。
>
> ```java
> // 3.获取数据库连接对象
> Connection conn = DriverManager.getConnection("jdbc:mysql://192.168.91.103:3306/db1", "root", "123456");
> ```

## Connection

> 数据库连接类

### 获取执行sql的对象

* `Statement createStatement()`
* `PreparedStatement prepareStatement(String var1)`

### 管理事务

1. 开启事务：`void setAutoCommit(boolean autoCommit)`，调用该方法设置`false`，即开启事务；
2. 提交事务：`void commit()`；
3. 回滚事务：`void rollback()`；

## Statement

> 执行`sql`的类，用于执行静态`sql`语句并返回其生成的结果的对象。
>
> * `boolean execute(String var1)`：可以执行任意的`sql`语句，了解；
> * `int executeUpdate(String var1)`：执行`DML(增删改)`的`sql`语句、`DDL(表、和库操作)`的`sql`语句；
>   * 返回值：表示受影响的行数，可以通过影响的行数判断`DML`语句是否执行成功。
> * `ResultSet executeQuery(String var1)`：执行`DQL(查)`语句。
>
> ```java
> package com_01.jianmo.jdbc;
> 
> import java.sql.Connection;
> import java.sql.DriverManager;
> import java.sql.SQLException;
> import java.sql.Statement;
> 
> 
> /*
>  *  给数据库中插入一条数据
>  * */
> 
> public class JdbcDemo01Insert {
> 	public static void main(String[] args) {
> 
> 		try {
> 			Class.forName("com.mysql.jdbc.Driver");
> 		} catch (ClassNotFoundException e) {
> 			e.printStackTrace();
> 		}
> 
> 		try (
> 				Connection connection = DriverManager.getConnection("jdbc:mysql://192.168.91.103:3306/db1", "root", "123456");
> 				Statement statement = connection.createStatement()
> 		) {
> 			String sql = "insert into account values(3, '王五', 1500);";
> 
> 			final int count = statement.executeUpdate(sql);
> 			if (count > 0) {
> 				System.out.println("插入" + count + "条数据");
> 			} else {
> 				System.out.println("插入数据失败");
> 			}
> 		} catch (SQLException e) {
> 			e.printStackTrace();
> 		}
> 	}
> }
> \
> ```

## ResultSet

> 结果集类，封装查询的结果对象。
>
> * `boolean next()`：游标(索引)向下移动一行；
> * `XXX getXXX(int columnIndex)`或`XXX getXXX(String columnIndex)`：获取数据
>   * `XXX`：代表某个数据类型；
>   * `columnIndex`：
>     * `int`类型：指定那一列的数据，代表编号，从`1`开始，如`int getInt(int columnIndex)`、`String getString(int columnIndex)`；
>     * `String`类型：指定列名称，如`int getInt(String columnIndex)`、`String getString(String columnIndex)`。
> * 获取数据使用步骤：
>   1. 游标向下移动一行；
>   2. 判断是否有数据`boolean next()`返回值；
>   3. 获取数据。
>
> ```java
> package com_01.jianmo.jdbc;
> /*
>  * 删除数据库中一条数据
>  * */
> 
> import java.sql.*;
> 
> public class jdbcDemo04Query {
> 	public static void main(String[] args) {
> 		try {
> 			Class.forName("com.mysql.jdbc.Driver");
> 		} catch (ClassNotFoundException e) {
> 			e.printStackTrace();
> 		}
> 		ResultSet resultSet = null;
> 		try (
> 				final Connection connection = DriverManager.getConnection("jdbc:mysql://192.168.91.103:3306/db1", "root", "123456");
> 				final Statement statement = connection.createStatement()
> 		) {
> 
> 			String sql = "select * from account;";
> 			resultSet = statement.executeQuery(sql);
> 
> 			// 获取数据
> 			while (resultSet.next()) { // 刚开始游标指向表头，需要下移
> 				int id = resultSet.getInt(1);
> 				String name = resultSet.getString(2);
> 				int balance = resultSet.getInt("balance");
> 				System.out.println("id:" + id + ", " + "name:" + name + ", " + "balance:" + balance);
> 			}
> 		} catch (SQLException e) {
> 			e.printStackTrace();
> 		} finally {
> 			if (resultSet != null) {
> 				try {
> 					resultSet.close(); // 释放结果集资源
> 				} catch (SQLException e) {
> 					e.printStackTrace();
> 				}
> 			}
> 		}
> 	}
> }
> ```

## PreparedStatement

> 执行`sql`类，比`Statement`类更加强大，预编译`sql`，参数使用`?`作为占位符。

### sql注入问题

> SQL注入问题：在拼接sql时，有一些sql的特殊关键字参与字符串的拼接，会造成安全性问题；

### sql注入问题解决

> 使用`PreparedStatement`对象来解决，后期都会使用`PreparedStatement`来完成增删改查的操作。
>
> 1. 可以防止`sql`注入；
> 2. 效率更高。
>
> sql注入解决方法
>
> * 预编译`sql`参数使用`?`作为占位符。
>   * 参数传递：`void setXXX(int var1, XXX var2)`
>     * `var1`：问号的位置，从1开始；
>     * `var2`：问号的值。
>
> ```java
> package com_01.jianmo.jdbc;
> 
> import java.sql.Connection;
> import java.sql.DriverManager;
> import java.sql.PreparedStatement;
> import java.sql.SQLException;
> 
> public class PreparedStatementTest {
> 	public static void main(String[] args) {
> 		try {
> 			Class.forName("com.mysql.jdbc.Driver");
> 		} catch (ClassNotFoundException e) {
> 			e.printStackTrace();
> 		}
> 
> 		try (
> 				Connection connection = DriverManager.getConnection("jdbc:mysql://192.168.91.103:3306/db1", "root", "123456");
> 				PreparedStatement preparedStatement = connection.prepareStatement("delete from account where id = ?;")) {
> 
> 			// 给？赋值，使用setXXX(int var1, var2)
> 			// var1:问号的位置，从1开始
> 			// var2:问号的值
> 			preparedStatement.setInt(1, 2);
> 
> 			// 执行的时候不需要传递方法：传参的是父类的，不传参的是子类的
> 			int count = preparedStatement.executeUpdate();
> 		} catch (SQLException e) {
> 			e.printStackTrace();
> 		}
> 	}
> }
> ```

## JDBC控制事务

> 一个包含多个步骤的业务操作，如果这个业务操作被事务管理，则这多个操作要么同时成功，要么同时失败。
>
> 使用`Connection`对象来管理事务。
>
> 事务的操作：
>
> 1. 开启事务：`void setAutoCommit(boolean autoCommit)`，调用该方法设置`false`，即开启事务；
>    * 执行`sql`之前开启事务；
> 2. 提交事务：`void commit()`；
>    * 当所有`sql`执行完提交事务；
> 3. 回滚事务：`void rollback()`；
>    * 发生异常，在`catch`中回滚事务；
>
> ```java
> package com_01.jianmo.jdbc;
> 
> import javax.swing.*;
> import java.sql.Connection;
> import java.sql.DriverManager;
> import java.sql.PreparedStatement;
> import java.sql.SQLException;
> 
> /**
>  * 事务操作
>  */
> public class jdbcDemo05 {
> 	public static void main(String[] args) {
> 		try {
> 			Class.forName("com.mysql.jdbc.Driver");
> 		} catch (ClassNotFoundException e) {
> 			e.printStackTrace();
> 		}
> 		Connection connection = null;
> 		PreparedStatement prep1 = null;
> 		PreparedStatement prep2 = null;
> 		try {
> 			connection = DriverManager.getConnection("jdbc:mysql://192.168.91.103:3306/db1", "root", "123456");
> 
> 			// 1.开启事务
> 			connection.setAutoCommit(false);
> 
> 			// 提交sql操作
> 			prep1 = connection.prepareStatement("update account set balance = balance - 500 where name = ?;");
> 			prep2 = connection.prepareStatement("update account set balance = balance + 500 where name = ?;");
> 
> 			// 设置参数
> 			prep1.setString(1, "张三");
> 			prep2.setString(1, "李四");
> 
> 			// 执行
> 			prep1.execute();
> 			int i = 1 / 0;  // 发生异常
> 			prep2.execute();
> 
> 			// 2.提交事务
> 			connection.commit();
> 		} catch (Exception e) {
> 			// 3.发生异常回滚事务
> 			try {
> 				connection.rollback();
> 			} catch (SQLException ex) {
> 				ex.printStackTrace();
> 			}
> 			e.printStackTrace();
> 		} finally {
> 
> 			// 后申请的资源先释放
> 			if (prep2 != null) {
> 				// 释放资源
> 				try {
> 					prep2.close();
> 				} catch (SQLException e) {
> 					e.printStackTrace();
> 				}
> 			}
> 
> 			if (prep1 != null) {
> 				// 释放资源
> 				try {
> 					prep1.close();
> 				} catch (SQLException e) {
> 					e.printStackTrace();
> 				}
> 			}
> 
> 			if (connection != null) {
> 				// 释放资源
> 				try {
> 					connection.close();
> 				} catch (SQLException e) {
> 					e.printStackTrace();
> 				}
> 			}
> 		}
> 	}
> }
> ```

