# 正则表达式

## 通用字符作为原子

| 符号 | 含义                                       |
| ---- | ------------------------------------------ |
| \w   | 匹配任意一个字母、数字或下划线             |
| \W   | 匹配除字符、数字或下划线以外的任意一个字符 |
| \d   | 匹配任意一个十进制数                       |
| \D   | 匹配除十进制数以外的任意一个其他字符       |
| \s   | 匹配任意一个空白字符                       |
| \S   | 匹配除空白字符以外的任意一个其他字符       |

## 元字符

| 符号   | 含义                                                         |
| ------ | ------------------------------------------------------------ |
| .      | 匹配除换行符以外的任意字符                                   |
| ^      | 匹配字符串的开始位置                                         |
| $      | 匹配字符串的结束位置                                         |
| *      | 匹配0次、1次或多次前面的原子                                 |
| ?      | 匹配0次或依次前面的原子                                      |
| +      | 匹配1次或多次前面的原子                                      |
| {n}    | 前面的原子恰好出现n次                                        |
| {n}    | 前面的原子至少出现n次                                        |
| {n, m} | 前面的原子至少出现n次，至多出现m次                           |
| \     | 模式选择符：例：pattern = python\php #匹配这两个均满足条件，类似或逻辑 |
| ()     | 模式单位符：小的原子组成大的原子进行使用                     |

## 模式修正

| 符号 | 含义                                                         |
| ---- | ------------------------------------------------------------ |
| I    | 匹配时忽略大小写                                             |
| M    | 多行匹配                                                     |
| L    | 做本地化识别匹配                                             |
| U    | 根据Unicode字符及解析字符                                    |
| S    | 让`.`匹配包括换行符，即用了该模式修正后，`.`匹配就可以匹配任意字符了 |

例：

```
import re
pattern = '(python){2}'
string = '''abcdfphp34pythony_pyPYTHONpythonPYTHON'''
result = re.search(pattern, string, re.I) # re.I 忽视大小写
print(result)
```

## 贪婪模式和懒惰模式

> `p.*y`：设置贪婪模式
>
> `p.*?y`设置懒惰模式
>
> 例：
>
> ```python
> import re
> pattern = 'p.*y' # 贪婪模式
> pattern1 = 'p.*?y' # 懒惰模式
> string = '''abcdfphp34pythony_pypythonPYTHON'''
> result = re.search(pattern, string) # re.I 忽视大小写
> print(result)
> result1 = re.search(pattern1, string) # re.I 忽视大小写
> print(result1)
> ```
>
> 运行结果：
>
> ```python
> <_sre.SRE_Match object; span=(5, 22), match='php34pythony_pypy'>
> <_sre.SRE_Match object; span=(5, 12), match='php34py'>
> ```

## 正则表达式常见函数

* `re.match()`函数

  ```
  import re
  string = 'apythonhelloworldnicetomeetyoupy'
  pattern = '.python.'
  result = re.match(pattern, string)
  result1 = re.match(pattern, string).span() # span 只显示下标
  
  print(result)
  print(result1)
  ```
  运行结果：

  ```
  <_sre.SRE_Match object; span=(0, 8), match='apythonh'>
  (0, 8)
  ```

  > `re.match()`只会从刚开始匹配，如果不满足则返回`None`

* `re.search()`函数

  ```
  import re
  string = 'helloworldpythonnicetomeetyoupy'
  pattern = '.python.'
  result = re.match(pattern, string)
  result1 = re.search(pattern, string)
  print(result)
  print(result1)
  ```
  运行结果：

  ```
  None
  <_sre.SRE_Match object; span=(9, 17), match='dpythonn'>
  ```

  > `re.search()`从任意位置开始匹配

* 全局匹配函数

  * `re.compile()`函数，对正则表达式进行预编译
  * `re.findall()`函数，根据正则表达式从源字符串中将匹配的结果全部找出。

  ```
  import re
  string = 'apythonhelloworldnicetomeetpythonpythonc'
  # pattern = re.compile('.python.')
  # result = pattern.findall(string)
  result = re.compile('.python.').findall(string)
  print(result)
  ```

  运行结果：

  ```
  ['apythonh', 'tpythonp']
  ```

* `re.sub()`函数

  > `re.sub(pattern, rep, string, max)`
  >
  > 参数一：对应的正则表达式
  >
  > 参数二：要替换成的字符串
  >
  > 参数三：源字符串
  >
  > 参数四：最大替换的次数，不写默认全部替换

  ```
  import re
  string = 'apythonhelloworldnicetomeetpythonpythonc'
  result = re.sub('python', 'ZHANGHUI', string, 1)
  print(result)
  ```

  运行结果：

  ```
  aZHANGHUIhelloworldnicetomeetpythonpythonc
  ```

## 三道练习题

* 匹配.com或.cn后缀的URL网址

  ```
  import re
  string = 'https://www.baidu.com"<>'
  pattern = '[a-zA-Z]+://[^\s]*[.com|.cn]'
  
  result = re.search(pattern, string)
  print(result)
  ```

* 匹配电话号码

  > ```
  > import re
  > string = '<scr"67629037872tex" ss1.bdstatic.com">ads</s129-12345678sadf0289-1234567cript>'
  > pattern = '[0-9]{11}|\d{4}-\d{7}|\d{3}-\d{8}'
  > result = re.findall(pattern, string)
  > print(result)
  > ```

* 匹配电子邮件地址

  > 邮件地址格式：user@mail.server.name 
  >
  > ```
  > import re
  > # 邮件地址格式：username@server.name
  > # pattern = '\w+@\w+\.\w+' # 不好的一个
  > pattern = '\w+([.+-]\w+)*@\w+([.-]\w+)*\.\w+([.-]\w+)*'
  > string = '<scr"67629037872tex" "144+3-8122879@qq.com.cn">ads</s129-12345678sadf0289-1234567cript>'
  > result = re.search(pattern, string)
  > print(result)
  > ```
  >
  > 运行结果：
  >
  > ```
  > <_sre.SRE_Match object; span=(22, 45), match='144+3-8122879@qq.com.cn'>
  > ```
