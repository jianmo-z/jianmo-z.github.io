# Qt实现记事本

## 升级加法运算为四则运算

> 项的概念：item
>
> Combo Box：下拉列表框
>
> QMessageBox ：消息框

## 记事本的实现

> **使用`mainwidows`继承而来**
> 新建(&F)，alt + F 快捷键

## 相关头文件和函数(重点)

> 简单说一下，嘻嘻，**实心黑点即代表了所需要的头文件，又代表了类名**，因为Qt的头文件和类名是一样的，所以这样比较简单好记，**空心的圆圈代表了，类的方法，**以及类方法的使用，和函数原型以及使用的例子。

* QFile

  * setFilename(cosnt QString &)//设置文件名称

      ```
      QFile file;
      QDir::setCurrent("/tmp");
      file.setFileName("readme.txt");
      QDir::setCurrent("/home");
      file.open(QIODevice::ReadOnly);      // opens "/home/readme.txt" under Unix
      ```

  * file.open(QIODevice::ReadOnly); //打开文件并设置权限，枚举类型，返回值为`bool`

      ```
      #include <stdio.h>

      void printError(const char* msg)
      {
          QFile file;
          file.open(stderr, QIODevice::WriteOnly);
          file.write(msg, qstrlen(msg));        // write to stderr
          file.close();
      }
      ```

  * file.close(); //关闭文件

      ```
      [virtual] void QFileDevice::close()
      Reimplemented from QIODevice::close().
      Calls QFileDevice::flush() and closes the file. Errors from flush are ignored.
      ```

* ui->textEdit

  * setText(QString) //把QString输出到textEdit

      ```
      [slot] void QTextEdit::setText(const QString &text)
      Sets the text edit's text. The text can be plain text or HTML and the text edit will try to guess the right format. Use setHtml() or setPlainText() directly to avoid text edit's guessing. 
      This function was introduced in Qt 4.2
      ```

  * ui->textEdit->append(time_t);//末尾追加时间

      ```
      void append(string text)

      Appends a new paragraph with text to the end of the TextEdit. In order to append without inserting a new paragraph, call  myTextEdit.insert(myTextEdit.length, text) instead.
      ```

  * ui->textEdit->setFont(font); //为当前文本设置字体
  * ui->textEdit->setTextColor(color);//为当前文本设置颜色
  * ui->textEdit->toPlainText(); //取出textEdit当中的纯文本

* QMessageBox

  * QmessageBox::information(...)//弹出一个对话框

    ```
    [static] StandardButton QMessageBox::information(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons = Ok, StandardButton defaultButton = NoButton)
    ```

* QFileDialog //选择文件，Dialog静态方法调用

  * getOpenFileName(...) //当打开一个文件，参数查帮助

    ```
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.xpm *.jpg)"));//tr 设置过滤
    ```

  * file.isEmpyt() //判断一个字符串是不是为空，返回值为bool

  * getsaveFileName(...)//保存一个文本信息

    ```
    [static] QString QFileDialog::getSaveFileName(QWidget *parent = Q_NULLPTR, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString *selectedFilter = Q_NULLPTR, Options options = Options())
    This is a convenience static function that will return a file name selected by the user. The file does not have to exist.
    It creates a modal file dialog with the given parent widget. If parent is not 0, the dialog will be shown centered over the parent widget.

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
    "/home/jana/untitled.png",
    tr("Images (*.png *.xpm *.jpg)"));

    The file dialog's working directory will be set to dir. If dir includes a file name, the file will be selected. Only files that match the filter are shown. The filter selected is set to selectedFilter. The parameters dir, selectedFilter, and filter may be empty strings. Multiple filters are separated with ';;'. For instance:

    "Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"

    The options argument holds various options about how to run the dialog, see the QFileDialog::Option enum for more information on the flags you can pass.
    The default filter can be chosen by setting selectedFilter to the desired value.
    The dialog's caption is set to caption. If caption is not specified, a default caption will be used.
    ```


  * qDebug()  //输出调试信息

* QDir //传入一个起始目录

  * QDir::currentPath() //获取当前路径和文件名

      ```
      [static] QString QDir::currentPath()
      Returns the absolute path of the application's current directory. The current directory is the last directory set with QDir::setCurrent() or, if that was never called, the directory at which this application was started at by the parent process.
      ```

* QTextStream

  * QTextStream in(file); //文本与文本流关联,重载了>>，与下面一样

  * QTextStream out(file); //文本与文本流关联，重载了<<，与上面一样



* QAction
  * triggered(bool checked == false)//菜单信号，点击一下的时候响应

* QFontDialog

  * getFont(&OK, this) //获取系统字体

    ```
    bool ok;
      QFont font = QFontDialog::getFont(
                      &ok, QFont("Helvetica [Cronyx]", 10), this);
      if (ok) {
          // the user clicked OK and font is set to the font the user selected
      } else {
          // the user canceled the dialog; font is set to the initial
          // value, in this case Helvetica [Cronyx], 10
      }
    ```

* QFont

  * QFont font = QFontDialog::getFont(&OK, this);//获取系统字体，Ok为一个bool类型的变量

* QColorDialog

  * const QColor color = QColorDialog::getColor(Qt::red, this0;设置颜色，默认为红色)
  * color.isValid(); //判断颜色是否有效

* QDateTime

  * QDateTime current = QDateTime::currentDateTime() //获取当前时间
  * QString time = current.toString("yyyy-M-dd hh:mm:ss");//格式化时间

  ​
