# day02

## Mariadb安装

> 参考链接(**无坑**)：https://www.cnblogs.com/yhongji/p/9783065.html
>
> `pdf`文件：[Centos安装Mariadb](./Centos安装Mariadb.pdf)

## SQL通用语法

1. SQL语句可以单行或多行书写，以`分号;`或`\g`结束；
2. 可以使用空格和锁紧来增强语句的可读性；
3. `MySQL`数据库的`SQl`语句不区分大小写，关键建议使用大写；
4. `3种`注释方法
   * 单行注释：使用`-- 注释`或`# 注释`开头，使用`#`是MySQL独有的，`--`和`#`需要一个空格；
   * 多行注释：`/* 注释 */`

## SQL分类

1. `DDL(Data Definition Language)`：数据定义语言
   * 用来定义数据库对象：数据库、表、列等。关键字：`create`、`drop`、`alter`等。
2. `DML(Data Manipulation Language)`：数据操作语言
   * 用来对数据库中表的数据进行**增删改**。关键字：`insert`、`delete`、`update`等。
3. `DQL(Data Query Language)`：数据查询语句
   * 用来**查询**数据库中表的记录(数据)。关键字：`select`、`where`等。
4. `DCL(Data Control Language)`：数据控制语言
   * 用来定义数据库的访问权限和安全级别，及创建用户。关键字：`GRANT`、`REVOKE`等。

## DDL：操作数据库和表

### 操作数据库

> `CRUD`操作
>
> 1. `C-Create`：创建
>    * 创建数据库：`create database 数据库名;`
>    * 创建数据库，判断不存在再创建：`create database if not exists 数据库名;`
>    * 创建数据库并指定字符集：`create database 数据库名 character set 字符集名;`
>    * 创建一个`db4`的数据库，判断是否存在，并指定字符集为`gbk`：`create database if not exists db4 character set gbk;`
> 2. `R-Retrieve`：查询
>    * 查询数据库的名称：`show databases;`
>    * 查看某个(`mysql`)数据库的创建语句：`show create database mysql;`
> 3. `U-Update`：修改
>    * 修改数据库的字符集：`alter database 数据库名称 character set 字符集名称`；
> 4. `D-Delete`：删除
>    * 删除数据库：`drop database 数据库名称;`
>    * 删除`db4`数据库，判断存在再删除：`drop database if exists db4;`
> 5. 使用数据库
>    * 查询当前正在使用的数据库：`select database();`
>    * 使用数据库：`use 数据库名称;`

### 操作表

> `CRUD`操作：
>
> 1. `C-Create`：创建
>
>    - 复制表：`create table stu like student;`，复制`student`表新名为`stu`；
>
>    - 创建表：
>
>      ```mysql
>       create table 表名(
>       	列名1 数据类型1,
>       	列名2 数据类型2,
>          ... ...
>       	列名n 数据类型n
>       ); -- 最后一列，不需要添加逗号,
>      ```
>
>      - 数据库数据类型：
>        
>        - `int`：整数类型，`age int,`；
>        - `double`：小数类型，`score double(5, 2)`，`5`表示数据宽度，`2`表示小数的数据宽度；
>        - `date`：日期，只包含年月日，`yyyy-MM-dd；`
>        - `datetime`：日期，包含年月日时分秒，`yyyy-MM-dd HH:mm:ss；`
>        - `timestamp`：时间戳类型，包含年月日时分秒，`yyyy-MM-dd HH:mm:ss`，如果不给该字段赋值或赋值为`null`，那么就会自动把当前的系统时间用来赋值；
>        - `varchar`：字符串，`name varchar(20)`，`name`最大五个字符；
>        - `text`：存储文本数据，存储比较大的字符串。
>        
>      - 创建表
>        
>        ```mysql
>        create table student(
>            id int, 
>            name varchar(32), 
>            age int, 
>            score double(4, 1), 
>            birthday date, 
>            insert_time timestamp  /* 这里没有逗号 */
>        );
>        ```
>
> 2. `R-Retrieve`：查询
>
>    - 查询某个数据库中所有的表名称：`show tables;`
>    - 查询表结构：`desc 表名;`
>
> 3. `U-Update`：修改
>
>    - 修改表名：`alter table 表名 rename to 新表名;`
>    - 修改表的字符集：
>      - 查看`student`表的字符集：`show create table student;`
>      - 修改`student`表的字符集为`utf8`：`alter table student character set utf8;`
>    - 添加一列：`alter table add 列名 数据类型;`，`alter table student add gender varchar(10);`
>    - 修改列名、类型：
>      - 修改列名和类型：`alter table 表名 change 旧列名 新列名 新类型;`，`alter table student change gender sex varchar(20);`；
>      - 修改列类型：`alter table 表名 modify 列名 新类型`，`alter table student modify sex varchar(10);`
>    - 删除列：`alter table 表名 drop 列名`，`alter table student drop sex;`
>
> 4. `D-Delete`：删除
>
>    - 删除表：`drop table 表名;`，`drop table student;`
>    - 删除表，判断存在再删除：`drop table if exists 表名;`，`drop table if exists student;`

## DML：增删改表中数据

### 添加数据

> 语法：`insert into 表名(列名1, 列名2, ..., 列名n) values(值1, 值2, ..., 值n);`

* 列名和值需要一一对应；
* 如果表名，不定义列名，则默认给所有的值添加值，`insert into student VALUES(2, "王五", 19, 61.0, "1970-1,1", NULL);`，可以设置不想添加的值为`NULL`；
* 除过数字类型，其他类型需要使用引号(单双引号都可以)引起来。

### 删除数据

> 语法：`delete from 表名 [where 条件];`，删除`student`表中`id = 1`的数据`delete from student WHERE id = 1;`
>
> 删除表中所有的数据：
>
> 1. `delete from 表名; ` ，删除所有数据，是一条条删除的，效率慢；
> 2. `truncate table 表名;`  ，先删除表，然后再创建一个空表，**效率高**。

* 如果不加条件，则删除表中所有数据；
* 如果要删除表中所有的记录建议使用`truncate table 表名;`

### 修改数据

> 语法：`update 表名 set 列名1 = 值1, 列名2 = 值2, ..., 列名n = 值n [where 条件]; `，修改表中数据`UPDATE student set score = 70,"name" = "王五" WHERE id = 2;`。

* 如果不加条件，那么表中所有的数据都会被修改。

## DQL：查询表中的数据

> 语法：
>
> ```mysql
> select 
> 	字段列表
> from
> 	表名列表
> where
> 	条件列表
> group by
> 	分组字段
> having
> 	分组之后的条件
> order by
> 	排序
> limit
> 	分页限定
> ```

### 基础查询

1. 多个字段的查询

   > `select 字段名1, 字段名2, ..., 字段n from 表名`；

   * 如果查询所有字段，则可以使用`*`来替代字段列表；

2. 去除重复

   > `distinct`，当结果集的多行值相同的时候才会去除重复的值。

3. 计算列

   > 一般可以使用四则运算计算一些列的值，一般只用数值型的计算

   * `IFNULL(expr1,expr2)`：`null`参与的运算，计算结果都为`null`。
     * `expr1`：那个字段需要判断是否为`null`；
     * 如果`expr1`字段为`null`，则使用`expr2`替换`null`。

4. 起别名

   > `AS`关键字给字段起别名，且`as`也可以省略。

```mysql
-- 查询所有信息
SELECT * FROM student;

-- 查询姓名和年龄
SELECT  NAME,  age  FROM student;

-- 除去重复的结果集
SELECT DISTINCT address FROM student;
SELECT DISTINCT NAME, address FROM student;  -- 结果集行必须全部相同

-- 计算Math和English之和
SELECT NAME, math, english, math + english FROM student;

-- 如果有Null 参数的运算结果，计算结果都为null
-- 将null替换为0，
-- IFNULL(expr1,expr2)，如果expr1是null，则替换为expr2，不是null使用原来的值
SELECT NAME, math, english, IFNULL(math, 0) + IFNULL(english,0) FROM student;

-- 起别名：使用as给查询的字段起别名，或者空格
SELECT NAME, math, english, IFNULL(math, 0) + IFNULL(english,0) as '总分' FROM student;
SELECT NAME, math 数学, english 英语, IFNULL(math, 0) + IFNULL(english,0) 总分 FROM student;
```

### 条件查询

1. `where`字句后跟条件；
2. 运算符：
   * `>`、`<`、`<=`、`>=`，`=`、`<>`，不等于用`<>`表示；
   * `BETWEEN...AND`，该区间是闭区间，`BETWEEN A AND B;`表示`[A, B]`；
   * `IN(集合)`
   * `LIKE`模糊查询
     * 占位符`_`：单个任意字符；
     * 占位符`%`：多个任意字符。
   * `and 或 &&`
   * `or 或 ||`
   * `not 或 !`

```mysql
-- 查询年龄大于20岁
SELECT * FROM student WHERE age >= 20;

-- 查询年龄等于20岁的
SELECT * FROM student WHERE age = 20;

-- 查询年龄不等于20岁的
SELECT * FROM student WHERE age <> 20;

-- 查询年龄大于等于20小于等于30，使用and或者&&
SELECT * FROM student WHERE age >= 20 AND age <= 30;
SELECT * FROM student WHERE age >= 20 && age <= 30;
SELECT * FROM student WHERE age BETWEEN 20 AND 30;

-- 查询年龄22岁，18岁，25岁
SELECT * FROM student WHERE age = 18 OR age = 22 OR age = 25;
SELECT * FROM student WHERE age IN(18, 22, 25);

-- 查询英语成绩为null的
SELECT * FROM student WHERE english = NULL;  -- 错误，null不能使用=、!=进行判断
SELECT * FROM student WHERE english is NULL;  -- 查询英语成绩为null
SELECT * FROM student WHERE english is NOT NULL;  -- 查询英语成绩不为null

-- 查询班级姓马的
SELECT * FROM student WHERE NAME LIKE '马%';

-- 查询第二字是化的人
SELECT * FROM student WHERE NAME LIKE '_化%';

-- 查询姓名是三个字的人
SELECT * FROM student WHERE NAME LIKE '___';

-- 查询姓名中包含德的人
SELECT * FROM student WHERE NAME LIKE '%德%';
```

### 排序查询

> 语法：
>
> ```mysql
> order by 
> 	排序字段1 排序方式1, 
> 	排序字段2 排序方式1, 
> 	  ...     ...   , 
> 	排序字段n 排序方式n
> ```
>
> 排序方式：默认升序排序
>
> * `ASC`，升序默认方式；
> * `DESC`，降序。
>
> 如果有**多个排序条件**，则当前面的条件值一样时，才会判断第二条件。

```mysql
-- 按照数学成绩排序，默认升序
SELECT * FROM student ORDER BY math;  -- 默认升序ASC排序
SELECT * FROM student ORDER BY math DESC;  -- 降序DESC排序

-- 按照数学成绩排名，如果数学成绩一样则按照英语成绩排序
SELECT * FROM student ORDER BY math, english;  -- 英语成绩升序
SELECT * FROM student ORDER BY math, english DESC;  -- 英语成绩降序
```

### 聚合函数

> 将一列数据作为一个整理，进行纵向计算。
>
> 1. `count`：计算数量；
>    * 选择非空的列：主键；
>    * `count(*)`
> 2. `max`：计算最大值；
> 3. `min`：计算最小值；
> 4. `sum`：计算和；
> 5. `avg`：计算平均值。
>
> 聚合函数的计算会排除`null`值，解决方案。
>
> * 选择不包含非空的列进行计算；
> * 使用`IFNULL`函数，替换`null`值。

```mysql
-- 计算当前班级有多少个人
SELECT COUNT(NAME) from student;  -- 8条数据
SELECT COUNT(english) from student;  -- 7条数据，排除null值
SELECT COUNT(IFNULL(english,0)) from student;  -- 8条数据，替换null值
SELECT COUNT(*) from student;  -- 8条数据，只要该行有一个数据不为空，则算作一条数据

-- 数学成绩最大值和最小值
SELECT MAX(math) FROM student;
SELECT MIN(math) FROM student;

-- 数学和英语成绩的和
SELECT SUM(math) FROM student;
SELECT SUM(english) FROM student;  -- 排除null值得英语成绩

-- 数学成绩的平均值
SELECT AVG(math) FROM student;
```

### 分组查询

> 语法：`GROUP BY 分组字段;`
>
> 1. 分组之后查询的字段：**分组字段**、**聚合函数**。
> 2. 在`WHERE`和`HAVing`的区别？
>    * `WHERE`在分组之前进行限定，如果不满足条件，则不参与分组；`HAVING`在分组之后胡进行限定，如果不满足条件则不会被查询出来。
>    * `WHERE`后不可以跟聚合函数，而`HAVING`可以进行聚合函数的判断。

```mysql
-- 男女分组的平均分以及男女个数
SELECT sex, COUNT(id) 人数, AVG(math) as 平均分 FROM student GROUP BY sex;

-- 男女分组的平均分以及男女个数，且分数低于70的人不参与分组
SELECT sex, COUNT(id) 人数, AVG(math) as 平均分 FROM student WHERE math >= 70  GROUP BY sex;


-- 男女分组的平均分以及男女个数，且分数低于70的人不参与分组，且分组人数需要大于两个人
SELECT sex, COUNT(id) 人数, AVG(math) as 平均分 FROM student WHERE math >= 70  GROUP BY sex HAVING COUNT(id) > 2;
SELECT sex, COUNT(id) 人数, AVG(math) as 平均分 FROM student WHERE math >= 70  GROUP BY sex HAVING 人数 > 2;
```

### 分页查询

> 语法：`LIMIT 开始的索引, 每页查询的条数;`
>
> 索引计算公式：`开始的索引 = (当前的页码 - 1) * 每页显示的条数`
>
> `limit`语法是一个**方言**，`limit`语法只能在`mysql`中使用

```mysql
-- 公式：开始的索引 = (当前的页码 - 1) * 每页显示的条数

-- 每页显示三条，显示第一页
SELECT * FROM student LIMIT 0, 3;

-- 每页显示三条，显示第二页
SELECT * FROM student LIMIT 3, 3;

-- 每页显示三条，显示第三页
SELECT * FROM student LIMIT 6, 3;
```

## 约束

> 对表中的数据进行限定，从而保证数据的正确性、有效性和完整性。
>
> 约束分类：
>
> 1. 主键约束：`primary key`；
> 2. 非空约束：`not null`；
> 3. 唯一约束：`unique`；
> 4. 自动增长：`auto_increment`；
> 5. 外键约束：`foreign key`。
> 6. 级联操作

1. 非空约束(not null)：值不能为`null`。

   * 在创建表时，添加约束；
   * 创建完表后，添加非空约束；
   * 删除非空约束。

   ```mysql
   -- 创建表时添加非空约束
   CREATE TABLE stu (
   	age INT,
   	NAME VARCHAR(32) NOT NULL  -- name 非空约束
   );
   
   -- 删除name的非空约束
   ALTER TABLE stu MODIFY NAME VARCHAR(32);
   
   -- 创建完表后，添加非空约束
   ALTER TABLE stu MODIFY NAME VARCHAR(32) NOT NULL;
   ```

2. 唯一约束(unique)：值不能重复，`mysql`中，唯一约束限定的列的值可以有多个`null`。

   * 在创建表时，唯一约束；
   * 创建完表后，添加唯一约束；
   * 删除唯一约束。

   ```mysql
   -- 创建表时添加唯一约束
   CREATE TABLE stu (
   	id INT,
   	phone_number VARCHAR(11) UNIQUE  -- phone_number 唯一约束
   );
   
   -- 删除phone_number的唯一约束
   -- ALTER TABLE stu MODIFY phone_number VARCHAR(11);  删除失败
   ALTER TABLE stu DROP INDEX phone_number;
   
   -- 创建表后，添加唯一约束
   ALTER TABLE stu MODIFY phone_number VARCHAR(11) UNIQUE;
   ```

3. 主键约束(primary key)：主键非空且唯一，主键一张表只有一个字段为主键，主键就是表中记录的唯一标识。

   * 在创建表时，添加主键约束；
   * 创建完表后，添加主键约束；
   * 删除主键约束。

   ```mysql
   -- 主键非空且唯一，主键一张表只有一个字段为主键，主键就是表中记录的唯一标识。
   
   -- 创建表时添加主键约束
   CREATE TABLE stu (
   	id int PRIMARY KEY,  -- 给id添加主键约束
   	NAME VARCHAR(32)
   );
   
   -- 删除主键约束
   -- ALTER TABLE stu MODIFY id int;  错误，不生效
   ALTER TABLE stu DROP PRIMARY key; -- 每个表只有一个主键，所以不需要指定列
   
   -- 创建完表后，添加主键
   ALTER TABLE stu MODIFY id int PRIMARY KEY;
   ```

4. 自动增长(auto_increment)：如果某一列是数值类型的，使用`auto_increment`可以来完成值得自动增长，**一般配合主键使用**。

   * 在创建表时，添加自动增长；
   * 创建完表后，添加添加自动增长；
   * 删除自动增长。

   ```mysql
   -- 创建表时添加自动增长
   CREATE TABLE stu (
   	id int PRIMARY KEY AUTO_INCREMENT,  -- 给id添加主键约束，且自动增长
   	NAME VARCHAR(32)
   );
   
   -- 删除自动增长
   ALTER TABLE stu MODIFY id int;
   
   -- 添加自动增长
   ALTER TABLE stu MODIFY id int auto_increment;
   ```

5. 外键约束(foreign key)：让表与表之间产生关系，从而保证数据操作的正确性。

   > 外键值可以为`null`但是不可以为主表中不存在的外键值。
   >
   > 语法添加外键约束：
   >
   > ```mysql
   > create table 表名(
   > 	...
   >     外键列 
   >     constraint 外键名称 foreign key (外键列名称) reference 主表名称(主表列名称)
   > );
   > ```

   * 创建表时添加外键约束；

     ```mysql
     create table 表名(
     	...
         外键列 
         constraint 外键名称 foreign key (外键列名称) reference 主表名称(主表列名称)
     );
     ```

   * 删除外键；

     ```mysql
     ALTER TABLE 表名 DROP FOREIGN KEY 外键名称;
     ```

   * 在创建表之后添加外键。

     ```mysql
     ALTER TABLE 表名 ADD CONSTRAINT 外键名称 FOREIGN KEY (外键列名称) REFERENCES 主表名称(主表列名称);
     ```

   ```mysql
   -- 创建部门表(id,dep_name,dep_location)
   -- 一方，主表
   create table department(
   	id int primary key auto_increment,
   	dep_name varchar(20),
   	dep_location varchar(20)
   );
   
   -- 创建员工表(id,name,age,dep_id)
   -- 多方，从表
   create table employee(
   	id int primary key auto_increment,
   	name varchar(20),
   	age int,
   	dep_id int, -- 外键对应主表的主键
   	CONSTRAINT emp_dept_fk FOREIGN KEY (dep_id) REFERENCES department(id)
   );
   
   
   -- 添加2个部门
   insert into department values (null, '研发部','广州'), (null, '销售部', '深圳');
   
   -- 添加员工,dep_id表示员工所在的部门
   INSERT INTO employee (NAME, age, dep_id) VALUES ('张三', 20, 1);
   INSERT INTO employee (NAME, age, dep_id) VALUES ('李四', 21, 1);
   INSERT INTO employee (NAME, age, dep_id) VALUES ('王五', 20, 1);
   INSERT INTO employee (NAME, age, dep_id) VALUES ('老王', 20, 2);
   INSERT INTO employee (NAME, age, dep_id) VALUES ('大王', 22, 2);
   INSERT INTO employee (NAME, age, dep_id) VALUES ('小王', 18, 2);
   
   
   -- 查询部门信息
   select * from department;
   
   -- 查询员工信息
   select * from employee;
   
   
   -- 删除employee表的外键
   ALTER TABLE employee DROP FOREIGN KEY emp_dept_fk;
   
   -- 添加employee表的外键
   ALTER TABLE employee ADD CONSTRAINT emp_dept_fk FOREIGN KEY (dep_id) REFERENCES department(id);
   ```

6. 级联操作：操作两张关联的表操作。

   > 语法：级联更新和级联删除可以只添加一个也可以都添加。
   >
   > ```java
   > ALTER TABLE 表名 ADD CONSTRAINT 外键名称 FOREIGN KEY (外键列名称) REFERENCES 主表名称(主表列名称) ON UPDATE CASCADE ON DELETE CASCADE;
   > ```
   >
   > * 级联更新：`ON UPDATE CASCADE`；
   > * 级联删除：`ON DELETE CASCADE`。
   >
   > 实际开发中级联操作使用**十分谨慎**

   ```mysql
   -- 删除employee表的外键
   ALTER TABLE employee DROP FOREIGN KEY emp_dept_fk;
   
   -- 重新添加employee表的外键，设置级联更新
   ALTER TABLE employee ADD CONSTRAINT emp_dept_fk FOREIGN KEY (dep_id) REFERENCES department(id) ON UPDATE CASCADE;
   
   -- 删除employee表的外键
   ALTER TABLE employee DROP FOREIGN KEY emp_dept_fk;
   
   -- 重新添加employee表的外键，设置级联更新和级联删除
   ALTER TABLE employee ADD CONSTRAINT emp_dept_fk FOREIGN KEY (dep_id) REFERENCES department(id) ON UPDATE CASCADE ON DELETE CASCADE;
   ```

## 数据库的设计

1. 多表之间的关系；
2. 数据库设计的范式。

## 多表之间的关系

> 1. 一对一关系：人和身份证的关系，一个人只能对应一个身份证，一个身份证只能对应一个人；
> 2. 一对多(多对一)关系：部门和员工的关系，一个部门有多个员工，一个员工之能对应一个部门；
> 3. 多对多关系：学生和课程，一个学生可以有多个课程，一个课程可以有多个学生。

## 范式

> 表设计规范，使表设计合理。

### 数据库的备份与还原