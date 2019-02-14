#include "getFileList.h"

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

vector<string> get_file_list(string &dir)
{
	vector<string> ret;

    DIR * p_dir = NULL;
    struct stat st;
    struct dirent *p = NULL;

    p_dir = opendir(dir.c_str());
    p = readdir(p_dir);

    while(p)
    {
        lstat(p->d_name, &st);
        if(*p->d_name == '.') // 不打开隐藏文件
        {
            p = readdir(p_dir);//打开下一个文件
            stat(p->d_name, &st);
            continue;
        }
		ret.push_back(string(p->d_name));
        //printf("%s\n", p->d_name);//打印文件名
        p = readdir(p_dir);//打开下一个文件
    }
	closedir(p_dir);
    return ret;
}
