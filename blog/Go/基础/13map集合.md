# 13map集合
```
package main

import "fmt"

/*
map是一个内建函数make可以使用map关键字来定义Map

定义map
	方法一：
		var map_variable map[key_data_type]value_data_type
	方法二：
		map_variable := make(map[key_data_type]value_data_type)

插入元素：
	map_variable[new_key] = value

查找元素:
	value, ok := map_variable[key]
	如果存在ok为true，并且value为key所对应的值，如果不存在则为false

如果不初始化map，就会创建一个nil map, nil map 不能用来存放键值对

delete()函数：如果要删除的值不存在则不操作
	delete(map_variable, key)
*/

func main() {
/*
	//如果不初始化map，就会创建一个nil map, nil map 不能用来存放键值对
	var dic map[int]string	      // 没有初始化
	var dic  = map[int]string{}   // 初始化了，但是为空

	dic[1] = "hello"
	dic[2] = "hi"
	dic[3] = "world"
*/
	var dic  = map[int]string{}

	dic[1] = "hello"
	dic[2] = "hi"
	dic[3] = "world"

	value, ok := dic[3]
	if ok { // 如果存在
		fmt.Println("vaule =", value)
	}else {
		fmt.Println("Not exist")
	}
	fmt.Println("map的值为:", dic)

	delete(dic, 5) // 要删除的key不存在所以不操作

	delete(dic, 3)
	fmt.Println("map的值为:", dic)
}

```