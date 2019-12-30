# win打包Qt项目

## 第一步

>   重新编译项目使用`Release`版编译，找到`Release`编译的可执行文件，只把可执行文件拿出来，如果有资源文件也一并拿出来，放入一个空的文件夹中。

## 第二步

>   在Qt的安装路径中搜索`windeployqt.exe`程序，右键打开文件所在的位置
>
>   推荐一个工具`everything`可以在`win`中快速的查找文件

## 第三步

*   方法一
      >将`windeployqt.ext`文件所在的路径加入`win`的`PATH`中在哪个文件夹中都可以使用这个命令进行打包了。`windeployqt.ext` + `空格` + `要打包的文件名`在`cmd`中执行即可。

   *   方法二

       >   使用`cmd`并切换路径到要发布的可执行文件中，复制`windeployqt.ext`的绝对路径和文件名，然后后面跟上一个空格再跟上要发布的可执行文件的文件名。

## 第四步

>   打包成功后即可发布出来了。

## 其他问题参考链接

1. https://www.cnblogs.com/iriczhao/p/11268336.html
2. https://blog.csdn.net/ze_202020/article/details/78524264

> 缺什么到那个目录里面赋值对应的`dll`，名称里面不能有`d`字母，根据提示可依次添加`Qt5Widgetsd.dll`，`Qt5Guid.dll`，`Qt5Cored.dll`和`libgcc_s_dw2-1.dll`
>
> Qt安装对应套件目录下找到插件文件夹：`D:\Qt\5.12.6\mingw73_32\plugins\platforms`文件夹，该文件夹中有几个DLL文件，删除其中文件名末尾后含有字符`d`的dll文件。`d`表示`debug`时用的`dll`

