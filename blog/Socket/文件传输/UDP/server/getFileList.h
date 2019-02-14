#ifndef __GETFILELIST_H__ 
#define __GETFILELIST_H__ 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <vector>
#include <string>

/*
 * 函数名: get_file_list
 * 参数:   dir,要获取列表的目录
 * 返回值: 文件列表
 * 函数作用:
 *		获取指定目录下的所有的文件名
 * 注意事项:
 *		不会列出隐藏文件,即以.开头的文件名
 */
using std::vector;
using std::string;

vector<string> get_file_list(string &dir);

#endif // __GETFILELIST_H__ 
