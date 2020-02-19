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
		final Statement statement = conn.createStatement();

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

