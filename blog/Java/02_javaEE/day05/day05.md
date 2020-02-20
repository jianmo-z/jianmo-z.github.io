# day05

## 数据库连接池

> 数据库连接池就是一个容器(集合)，存放数据库连接的容器。当系统初始化好后，容器被创建，容器中会申请一些连接对象，当用户来访问数据库时，从容器中获取连接对象，用户访问完后，将连接对象归还给容器(集合)。

### 优点

1. 节约资源；
2. 用户访问高效；

### 实现

> 由数据库厂商实现该接口。

1. 标准接口：`DataSource`，在`javax.sql`包下的
   1. 获取连接：`getConnection()`方法从连接池中获取连接；
   2. 归还连接：`Connection.close()`归还连接到连接池中，如果连接对象`Connection`是从连接池中获取的，那么调用`Connection.close()`方法，则不会再关闭连接了，而是归还连接。
2. 常用数据库连接池
   1. `C3P0`：数据库连接池技术；
   2. `Druid`：数据库连接池实现技术，由阿里巴巴提供。

### C3P0数据库连接池

> `C3P0`连接池使用
>
> 步骤：
>
> 1. 导入`jar`包和依赖`jar`包，需要导入`mysql`的`jar`包；
> 2. 设置配置文件；
>    1. 名称：`c3p0.properties` 或`c3p0-config.xml`；
>    2. 配置文件是项目的类路径下，即项目`src`目录下。
> 3. 创建核心对象，数据库连接词对象：`ComboPooledDataSource`；
> 4. 通过`getConnection()`方法获取连接。
>
> ```java
> package com_01.jianmo.datasource.C3P0;
> 
> import com.mchange.v2.c3p0.ComboPooledDataSource;
> 
> import javax.sql.DataSource;
> import java.sql.Connection;
> import java.sql.SQLException;
> 
> public class C3P0Test {
> 	public static void main(String[] args) throws SQLException {
> 		// 1.创建连接池对象
> 		// DataSource ds = new ComboPooledDataSource();  // 使用默认配置
> 		DataSource ds = new ComboPooledDataSource("otherC3P0");  // 使用指定名称的配置
> 
> 		// 2.获取连接池对象
> 		final Connection connection = ds.getConnection();
> 
> 		// 3. 打印连接对象
> 		System.out.println(connection);
> 
> 	}
> }
> ```

### Druid数据库连接池

> 步骤
>
> 1. 导入`jar`包，需要导入`mysql`的`jar`包；
> 2. 设置配置文件：
>    1. 是`properties`形式的配置文件；
>    2. 可以叫任意名称，可以放在任意目录下；
> 3. 获取数据库连接池对象：通过工厂类来获取`DruidDataSourceFactory`；
> 4. 通过`getConnection()`方法获取连接。
>
> ```java
> package com_01.jianmo.datasource.Druid;
> 
> import com.alibaba.druid.pool.DruidDataSourceFactory;
> 
> import javax.sql.DataSource;
> import java.io.FileReader;
> import java.sql.Connection;
> import java.util.Properties;
> 
> public class DruidTest {
> 	public static void main(String[] args) throws Exception {
> 		// 1.设置配置文件
> 		Properties properties = new Properties();
> 		properties.load(new FileReader("E:\\IdeaProjects\\java_ee\\day05\\src\\druid.properties"));
> 
> 		// 2.获取连接池对象
> 		DataSource dataSource = DruidDataSourceFactory.createDataSource(properties);
> 
> 		// 3.获取一个连接
> 		Connection connection = dataSource.getConnection();
> 
> 		// 4.打印连接池对象
> 		System.out.println(connection);
> 
> 	}
> }
> ```

## Spring JDBC

> `JDBC Template`简化`JDBC`编程。是`Spring`框架对`JDBC`的简单封装。
>
> 步骤：
>
> 1. 导入`jar`包；
> 2. 创建`JDBC Template`对象，依赖于数据源`DataSource`
>    * `JDBC Template template = new JdbcTemplate(datasource);`
> 3. 调用`JDBC Template`方法来完成`CRUD`的操作：
>    * `update()`：执行`DML`语句，增、删、改语句；
>    * `queryForMap()`：查询结果将结果集封装为`map`集合，**查询的结果集只能是1不能是0或多个**；
>    * `queryForList()`：查询结果将结果集封装为`List`集合；
>    * `query()`：查询结果，将结果封装为`JavaBean`对象；
>      * `RowMapper`参数，一般使用`BeanPropertyRowMapper`实现类，可以完成数据到`JavaBean`的自动封装，`new BeanPropertyRowMapper<类型>(类型.class)`。
>    * `queryForObject()`：查询结果，将结果封装为对象。
>      * 一般用于**聚合函数**的查询。
>
> ```java
> package com_01.jianmo.datasource.JDBCTemplate;
> 
> import com.alibaba.druid.pool.DruidDataSourceFactory;
> import com_01.jianmo.datasource.domain.Emp;
> import org.junit.Assert;
> import org.junit.Before;
> import org.junit.Test;
> import org.springframework.jdbc.core.BeanPropertyRowMapper;
> import org.springframework.jdbc.core.JdbcTemplate;
> import org.springframework.jdbc.core.RowMapper;
> 
> import javax.sql.DataSource;
> import java.io.FileReader;
> import java.sql.ResultSet;
> import java.sql.SQLException;
> import java.util.List;
> import java.util.Map;
> import java.util.Properties;
> 
> public class JDBCTemplatePractice {
> 	public Properties properties = null;
> 	public DataSource dataSource = null;
> 	public JdbcTemplate jdbcTemplate = null;
> 
> 	// 初始化资源
> 	@Before
> 	public void init() throws Exception {
> 		// 1.设置配置文件
> 		properties = new Properties();
> 		properties.load(new FileReader("E:\\IdeaProjects\\java_ee\\day05\\src\\druid.properties"));
> 
> 		// 2.获取连接池对象
> 		dataSource = DruidDataSourceFactory.createDataSource(properties);
> 
> 		// 3.创建JDBC Template对象
> 		jdbcTemplate = new JdbcTemplate(dataSource);
> 
> 	}
> 
> 
> 	// 操作一：修改一号数据的salary为10000
> 	@Test
> 	public void test01() {
> 		String sql = "update emp set salary = ? where id = ?;";
> 		int count = jdbcTemplate.update(sql, 10000, 1);
> 		Assert.assertEquals(1, count);
> 	}
> 
> 	// 操作二：添加一条数据
> 	@Test
> 	public void test02() {
> 		String sql = "insert emp values(?, ?, ?, ?, ?, ?)";
> 		int count = jdbcTemplate.update(sql, null, "沙师弟", "男", 3000, "2013-01-01", 1);
> 		Assert.assertEquals(1, count);
> 	}
> 
> 	// 操作三：删除刚才添加的数据
> 	@Test
> 	public void test03() {
> 		String sql = "delete from emp where name = ?;";
> 		int count = jdbcTemplate.update(sql, "沙师弟");
> 		Assert.assertEquals(1, count);
> 	}
> 
> 	// 操作四：查询id为1记录，并封装为Map集合，查询的结果集只能是1不能是0或多个
> 	@Test
> 	public void test04() {
> 		String sql = "select * from emp where id = ?;";
> 		Map<String, Object> stringObjectMap = jdbcTemplate.queryForMap(sql, 1);
> 
> 		// for(Map.Entry<String, Object> it: stringObjectMap.entrySet()) {
> 		// 	System.out.println(it.getKey() + ":" + it.getValue());
> 		// }
> 		System.out.println(stringObjectMap);
> 	}
> 
> 	// 操作五：查询所有记录，将其封装为List
> 	@Test
> 	public void test05() {
> 		String sql = "select * from emp;";
> 		final List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql);
> 		for (Map<String, Object> i : maps) {
> 			System.out.println(i);
> 		}
> 	}
> 
> 	// 操作六：查询所有记录，将其封装为Emp对象的List集合
> 	@Test
> 	public void test06() {
> 		String sql = "select * from emp;";
> 		final List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql);
> 		final List<Emp> Emps = jdbcTemplate.query(sql, new RowMapper<Emp>() {
> 			@Override
> 			public Emp mapRow(ResultSet resultSet, int i) throws SQLException {
> 				Emp emp = new Emp();
> 				emp.setId(resultSet.getInt("id"));
> 				emp.setName(resultSet.getString("name"));
> 				emp.setGender(resultSet.getString("gender"));
> 				emp.setSalary(resultSet.getDouble("salary"));
> 				emp.setJoin_date(resultSet.getDate("join_date"));
> 				emp.setDept_id(resultSet.getInt("dept_id"));
> 				return emp;
> 			}
> 		});
> 
> 		for (Emp it : Emps) {
> 			System.out.println(it);
> 		}
> 
> 	}
> 
> 	// 操作六简化操作
> 	@Test
> 	public void test061() {
> 		String sql = "select * from emp;";
> 		final List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql);
> 		final List<Emp> Emps = jdbcTemplate.query(sql, new BeanPropertyRowMapper<Emp>(Emp.class));
> 
> 		for (Emp it : Emps) {
> 			System.out.println(it);
> 		}
> 
> 	}
> 
> 	// 操作七：查询总记录数
> 	@Test
> 	public void test07() {
> 		String sql = "select count(id) as 'count' from emp;";
> 		Long count = jdbcTemplate.queryForObject(sql, Long.class);
> 		System.out.println("一共有" + count + "条数据");
> 	}
> }
> ```