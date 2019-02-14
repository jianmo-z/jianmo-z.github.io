# Qt在win设置应用程序图标

## 参考链接:

https://blog.csdn.net/chenlong12580/article/details/7389588
https://blog.csdn.net/goodtomsheng/article/details/44869423

*   第一步

    >   在Qt的帮助手册中查找`Setting the Application Icon`，即可获取帮助

*   第二步

    >   我先直接引用一下，如果大家英文和我一样菜直接跳到第三步就可以了，这里只是Win的，其他的操作系统请在本搜索页进行查找。

```
Setting the Application Icon on Windows
First, create an ICO format bitmap file that contains the icon image. This can be done with e.g. Microsoft Visual C++: Select File|New, then select the File tab in the dialog that appears, and choose Icon. (Note that you do not need to load your application into Visual C++; here we are only using the icon editor.)
Store the ICO file in your application's source code directory, for example, with the name myappico.ico.
Then, assuming you are using qmake to generate your makefiles, you only need to add a single line to your .pro project file:

  RC_ICONS = myappico.ico

Finally, regenerate your makefile and your application. The .exe file will now be represented by your icon in Explorer.
However, if you already have an .rc file, for example, with the name myapp.rc, which you want to reuse, the following two steps will be required. First, put a single line of text to the myapp.rc file:

  IDI_ICON1               ICON    DISCARDABLE     "myappico.ico"

Then, add this line to your myapp.pro file:

  RC_FILE = myapp.rc

If you do not use qmake, the necessary steps are: first, create an .rc file and run the rc or windres program on the .rc file, then link your application with the resulting .res file. 

```

*   第三步

    *   创建一个`*.ico`的图标文件，放在目录下，建议直接放在编译的目录下。这里假设文件名为`myappico.ico`
    *   将`RC_ICONS = myappico.ico`添加到你的`.pro`文件中
    *   如果你的项目下有`.rc`文件，将` IDI_ICON1               ICON    DISCARDABLE     "myappico.ico"`添加到文件中
    *   然后将`RC_FILE = myapp.rc`添加到你的`myapp.pro`文件中

*   第四步

    >   顺利完成

