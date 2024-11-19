# 11切片slice
```
package main

import "fmt"

/*
定义切片:声明一个未指定大小的数组来定义切片
	var identifier []type // 切片不需要说明长度

或者使用make()函数来创建切片:
	var slicel []type = make([]type, len)
	slicel := make([]type, len)

指定容量:(可以省略不写),要求length <= capacity,符合逻辑
	make([]T, length, capacity)


len()
cap()

append()
copy()
*/

func main(){
	var arr = [] int{1, 3, 4, 5, 3, 2, 7}
	a := arr[1:5]
	b := arr[:5]
	c := arr[1:]
	d := arr[len(arr) - 1:len(arr) - 0]

	fmt.Println(a)
	fmt.Println(b)
	fmt.Println(c)
	fmt.Println(d)


	var array = make([]int, 5, 7)
	fmt.Println(array)
	fmt.Println("len =", len(array), "\ncap =", cap(array))


	arrayAppend := append(array, 1)
	fmt.Println(arrayAppend)


	arrayCopy := make([]int, 3)
	// 如果len(array_copy) < len(array_append)那么只会复制len(array_copy)个元素
	copy(arrayCopy, arrayAppend)
	fmt.Println(arrayCopy)
}

```