# 12范围Range
```
package main

import	"fmt"

/*
	range关键字用于for循环中迭代数组(array)、切片(slice)、通道(channel)或集合(map)
的元素。
	返回值：
		第一个表示下标
		第二个表示值
	如果是map：
		第一个表示key
		第二个表示value

	用 '_'去接收一个变量表示不关心这个变量的值，起到占位的作用，该位置的值会被抛弃掉
*/
func main() {
	a := [] int{1, 2, 4, 5}
	m := map[int]string{1:"hello", 2:"world", 3:"hi"}
	fmt.Println(a)

	for index, num := range a { // 如果不关心下标，可以设置为 '_'
		fmt.Println("index =", index, "num =", num)
	}



	for key, value := range m{
		fmt.Println("key =", key, " value =", value)
	}
}

```