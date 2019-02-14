# vim自动补齐括号

## 参考链接
https://blog.csdn.net/yangss123/article/details/77606421

## 问题解决

> 将下面的代码添加到`~/.vimrc`中

```
inoremap ( ()<ESC>i

inoremap [ []<ESC>i

inoremap { {}<ESC>i

inoremap < <><ESC>i

inoremap ' ''<ESC>i

inoremap " ""<ESC>i>""">'''>>>>}}>]]>))
```

## 更多设置

```
set nu：设置显示行号，取消显示为set noun

set ai：自动对齐，即自动补齐TAB或者空格

set cindent shiftwidth=4：设置缩进为4个空格长

set tabstop=4：设置TAB宽度为四个空格

set smartindent：智能的选择对齐方式

set autoindent：当前行的对齐方式应用到下一行 

```
