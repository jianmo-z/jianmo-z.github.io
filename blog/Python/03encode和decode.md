# encode和decode的辨析

## 参考链接

[https://blog.csdn.net/qq_40134903/article/details/80710882](https://blog.csdn.net/qq_40134903/article/details/80710882)

## 代码中字符串的默认编码形式

>   编码形式为代码本身的文件编码形式一致，想想也应当时这样

## 判断是否为unicode

>   `isinstance(str1, unicode)`，判断`str1`是否为`unicode`编码形式
>
>   获取系统默认编码形式`print sys.getdefaultencoding()`

## 辨析

*   字面意思
    *   `encode`：编码
    *   `decode`：解码
*   `encode`：把别的编码的字符串转换成`unicode`编码
    *   例：`str.decode('utf8')`，将`utf8`转换成`unicode`的编码
*   `decode`：把`unicode`转换成其他的编码形式
    *   例：`str.encode('utf8')`，将`将unicode`转换成`utf8`的编码

