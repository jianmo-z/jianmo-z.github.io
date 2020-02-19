# day03

## 多表查询

> 查询语法：
>
> ```mysql
> select
> 	列名列表  -- 可以写多个
> from
> 	表名列表  -- 可以写多个
> ```

## 笛卡尔积

> 有两个集合`A`，`B`，取这个两个集合的所有组成情况，要完成多表查询，需要消除无用的笛卡尔数据。

## 多表查询分类

### 内连接查询

> 1. 隐式内连接：使用`where`条件消除无用数据；
> 2. 显式内连接：`select 字段列表 from 表名1 [inner] join 表名2 on 条件;`，`inner`可以省略不写；
> 3. 内连接查询注意：
>    * 从哪些表中查询数据；
>    * 查询条件是什么，即有效数据？无效数据？；
>    * 查询那些字段。
>
> ```mysql
> /*
> 	2.1内连接查询：隐式内连接
> 	使用where消除无用数据
> */
> 
> -- 查询所有员工信息和对应的部门信息
> SELECT * FROM emp, dept WHERE dept.id = emp.dept_id;
> 
> -- 查询所有员工表的名称、性别和部门表的名称
> SELECT emp.id, emp.`NAME`, emp.gender, dept.`name` FROM emp, dept WHERE emp.id = dept.dept_id;
> 
> -- 标准sql语句
> SELECT
> 	t1.id,  -- 员工表的id
> 	t1.`NAME`,  -- 员工表的姓名
> 	t1.gender,  -- 员工表的性别
> 	t2.`name`   -- 部门表的名臣
> FROM
> 	emp t1,
> 	dept t2
> WHERE
> 	t1.dept_id = t2.id;
> 
> /*
> 	2.1内连接查询：显式内连接
> */
> 
> SELECT * from emp INNER JOIN dept ON emp.dept_id = dept.id;
> SELECT * from emp JOIN dept ON emp.dept_id = dept.id;  -- INNER可省略
> ```

### 外连接查询

> 1. 左外连接：查询左表所有数据以及交集数据，`select 字段列表 from 表1 left [outer] join 表2 on 条件;`，`outer`可以省略不写；
> 2. 右外连接：查询右表所有数据以及交集数据，`select 字段列表 from 表1 right [outer] join 表2 on 条件;`，`outer`可以省略不写；
>
> ```mysql
> /*
> 	3.1外连接查询：左外连接
> */
> 
> -- 查询所有员工信息，如果员工有部门，则查询部门名称
> SELECT t1.*, t2.name from emp t1 LEFT JOIN dept t2 on t1.dept_id = t2.id;
> 
> -- 查询所有部门信息，如果部门有员工，则查询员工信息
> SELECT t2.*, t1.name  from dept t1 LEFT JOIN emp t2 on t1.id = t2.dept_id;
> 
> /*
> 	3.2外连接查询：右外连接
> */
> 
> -- 查询所有部门信息，如果部门有员工，则查询员工信息
> SELECT t1.*, t2.name from emp t1 RIGHT JOIN dept t2 on t1.dept_id = t2.id;
> 
> -- 查询所有员工信息，如果员工有部门，则查询部门名称
> SELECT t2.*, t1.name from dept t1 RIGHT JOIN emp t2 on t1.id = t2.dept_id;
> ```

### 子查询

> 查询中嵌套传，称嵌套查询为子查询。
>
> 子查询的不同情况：
>
> 1. 子查询的结果是单行单列
>    * 子查询可以作为条件，使用运算符(`<，>…`)去判断。
> 2. 子查询的结果是多行单列，子查询的结果是单行多列；
>    * 使用运算符`IN`来判断。
> 3. 子查询的结果是多行多列；
>    * 子查询可以作为一张虚拟表进行表查询。
>
> ```mysql
> /*
> 	4.子查询
> */
> 
> -- 查询工资最高的员工信息
> -- 1.查询最高工资
> SELECT max(emp.salary) from emp;
> -- 2.查询员工信息，并且工资等于9000
> SELECT * FROM emp WHERE emp.salary = 9000;
> -- 合并两个sql语句，子查询
> SELECT * FROM emp WHERE emp.salary = (SELECT MAX(emp.salary) from emp);
> 
> /*
> 	4.1子查询:结果是单行单列
> */
> 
> -- 查询员工工资小于平均工资的人
> SELECT * FROM emp WHERE emp.salary < (SELECT AVG(emp.salary) from emp);
> 
> /*
> 	4.1子查询:结果是多行单列 或 结果是单行多列
> */
> 
> -- 查询财务部和市场部所有的员工信息
> SELECT * from emp WHERE dept_id IN(SELECT id FROM dept WHERE name = "财务部" || name = "市场部");
> 
> /*
> 	4.1子查询:结果是多行多列
> */
> 
> -- 查询员工入职日期是2011-11-11之后的员工信息和部门信息
> SELECT t1.*, t2.* from dept t1, (SELECT * FROM emp WHERE emp.join_date > "2011-11-11") t2 WHERE t1.id = t2.dept_id;  -- t2表是一张虚拟表
> 
> -- 使用普通内连接查询
> SELECT t1.*, t2.* FROM dept t1, emp t2 WHERE t1.id = t2.dept_id && t2.join_date > "2011-11-11";
> ```

## 事务

> 如果包含多个步骤的业务操作，被事务管理，那么这些操作要么同时成功，要么同时失败。
>
> 事务操作：
>
> 1. 开启事务：`start transaction;`
> 2. 回滚事务：`rollback;`
> 3. 提交事务：`commit;`
>
> `MySQL`数据库中事务默认自动提交，
>
> * 自动提交：
>   * `MySQL`自动提交的；
>   * 一条`DML`(增删改)语句会自动提交一次事务；
> * 手动提交：
>   * `Oracle`数据库默认是手动提交事务的；
>   * 需要先开启事务，然后再手动`commit`提交。
> * 修改事务的默认提交方式
>   * 查看`MySQL`的默认提交方式：`select @@autocommit;`
>     * `1`表示自动提交；
>     * `0`表示手动提交。
>   * 修改默认提交方式：`set @@autocommit = 0;`

## 事务的四大特征

> `ACID`事务的四大特征：
>
> 1. 原子性：是不可分割的最小操作单位，要么同时成功，要么同时失败；
> 2. 持久性：如果事务一旦提交或者回滚后，数据库会持久化的保存数据；
> 3. **隔离性**：多个事务之间，相互独立；
> 4. 一致性：事务操作前后数据总量不变，即转账操作，转账前后总账不变。

## 事务的隔离级别

> 多个事务之间隔离的，相互独立的。但是多个事务操作同一批数据，则会引发一些问题，设置不同的隔离级别就可以解决这些问题。

### 事务存在的问题

> 1. **脏读**：一个事务读取到另一个事务中没有提交的数据；
> 2. **不可重复读(虚读)**：在同一个事务中，两次读取到的数据不一样；
> 3. **幻读**：一个事务操作(DML)数据表中所有记录，另一个事务添加了一条数据，则第一个事务查询不到自己的修改。

### 事务隔离级别

> 隔离级别从小到大安全性越来越高，但是效率越来越低。
>
> `Oracle`数据库默认为`read commited`级别，`MySQL`数据库默认为`repeatable read`级别。
>
> 数据库**查询**隔离界别：`select @@tx_isolation;`
>
> 数据库**设置**隔离级别：`set global transaction isolation level 级别字符串;`，需要断开连接然后重新连接才会生效。
>
> ```mysql
> -- 查询数据库隔离级别
> SELECT @@tx_isolation;
> 
> -- 设置隔离界别：read uncommitted、read committed、repeatable read、serializable
> set global transaction isolation level repeatable read;
> ```

|      隔离级别      | 隔离名称 |         产生问题         |
| :----------------: | :------: | :----------------------: |
| `read uncommitted` | 读未提交 | 脏读、不可重复读、幻读。 |
|  `read committed`  | 读已提交 |    不可重复度、幻读。    |
| `repeatable read`  | 可重复读 |           幻读           |
|   `serializable`   |  串行化  |         没有问题         |

## SQL分类-DCL学习

> 此模块了解即可，管理用户，授权。公司中有专门的人员管理数据库，`DBA`：数据库管理员。`MySQL`的数据库用户信息在`mysql`数据库中的`user`表。

### 管理用户

1. 添加用户：
   * `CREATE USER  '用户名'@'主机名' IDENTIFIED BY '密码';`
2. 删除用户：
   * `DROP USER '用户名'@'主机名';`
3. 修改用户密码：
   * 修改普通用户密码方式一：`UPDATE user SET PASSWORD = PASSWORD("新密码") WHERE User = "用户名" and "Host" = "主机名";`
   * 修改普通用户密码方式二：`SET PASSWORD FOR "用户名"@"主机名" = PASSWORD("新密码");`
   * 忘记`root`用户密码：
4. 查询用户：`%`表示可以在任意主机访问数据库。

```mysql
USE mysql;

/*
	1.查询用户
*/

-- 2.查询user表
SELECT * from user;

/* 
	2.创建用户
*/

-- 语法：CREATE USER '用户名'@'主机名' IDENTIFIED BY '密码';
CREATE USER 'pip'@'%' IDENTIFIED BY '123456';

/* 
	3.删除用户
*/

-- 语法：DROP USER '用户名'@'主机名';
DROP USER 'pip'@'%';

/* 
	4.修改用户密码
*/

-- 方式一
UPDATE user SET PASSWORD = PASSWORD("abcdef") WHERE User = "pip" and "Host" = "%";

-- 方式二
SET PASSWORD FOR "pip"@"%" = PASSWORD("123456");
```



### 权限管理

1. 查询权限
   * `SHOW GRANTS FOR "用户名"@"主机名";`
2. 授予权限
   * `grant 权限列表 on 数据库.表名 to "用户名"@"主机名";`
3. 撤销权限
   * `revoke 权限列表 on 数据库.表名 from "用户名"@"主机名"`

```mysql
/*
	5.查询权限
*/
-- 语法：SHOW GRANTS FOR "用户名"@"主机名";
SHOW GRANTS FOR "pip"@"%";

/*
	6.授予权限
*/

-- grant 权限列表 on 数据库.表名 to "用户名"@"主机名";
grant SELECT,UPDATE,DELETE on db1.account to "pip"@"%";
grant ALL on *.* to "pip"@"%";  -- 授予pip所有库的所有表的所有操作权限

/*
	7.撤销权限
*/

-- revoke 权限列表 on 数据库.表名 from "用户名"@"主机名"
REVOKE UPDATE on db1.account from "pip"@"%";  -- 撤销pip@%的db1.account的修改权限
```
