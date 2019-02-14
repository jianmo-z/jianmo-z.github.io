# Qt简介

##注意！！！注意！！！

<font size=6 color="red">Qt的安装路径和项目的路径绝对不要有中文，项目名称也不要有中文，否则需要重新安装Qt，项目还能好一点，只需要更改一下名字是可以的，Qt creator只能重新安装了。</font>



> `Qt`的死对头`MFC`，Qt商用就需要收费，非商用免费，Qt是一个开源，跨平台C++图形用户界面应用程序开发框架。即可以开发GUI程式，也可以用于开发非FUI程式。类和头文件是Q开头的 + 属性，命名的规则

## 学习Qt的要求和方法

* 掌握C++语言
* 学会查找文档
* 代码书写规则和风格

类之间的关系：

* QWidget是合成词由windows-get合成，窗口合成。
  * QDialog：对话框，由QWidget继承而来。

## 2/8原则

> 不懂的百度百度。很有名的理论。又称为20/80原则。

## Qt支持的平台

> Unix、BSD、Mac、Windows、Linux

##Qt类简单介绍

* QTacWidget：选项卡
* QLabel：标签，可以承载图片
* QTextEdit：多行编辑器
* QLineEdit：单行编辑器
* QPushButton：突出来的按钮
* QGroupBox：组合框
* QTableWidget：表格固件
* QCheckBox：选择框
* QRadioButton：多选一
* QHBoxLayout：水平布局，H：horizontal 水平布局
* QVBoxLayout：垂直布局，V：vertical 垂直布局

## 信号和槽

```
Connect(foo, SIGNAL(clicked()), bar, SLOT(on()))
/*
参数一：发送信号方
参数二：发送的什么信号，SIGNAL即为信号
参数三：接收信号方
参数四：接收到信号作出的响应，SLOT即为槽
*/
```

> 快捷键：
>
> F4：部件编辑
>
> F3：信号和槽的编辑
>
> Ctrl + H ：水平布局
>
> Ctrl + L ：垂直布局
>
> Alt + Shift + r：预览

