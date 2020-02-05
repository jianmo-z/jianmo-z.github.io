# day07

## Map集合

> `java.util.map<k, v>`集合
>
> 1. `Map`集合是一个双列集合，一个元素包含两个值`(key，value)`；
> 2. `Map`集合中的元素，`key`和`value`的数据类型可以相同，也可以不同；
> 3. `Map`集合中的元素，`key`不可以重复，`value`是可以重复的；
> 4. `Map`集合中的元素，`key`和`value`是一一对应的。

## Map常见实现类

* `HashMap<k,v>`：无序集合；
  1. `HashMap`集合底层是哈希表：查询速度快；
     * `JDK1.8`之前：数组+单项链表
     * `JDK1.8`之后：数组+单项链表/红黑树(链表长度超过8时)：提高查询速度
  2. `HashMap`集合是一个无序的集合，存储元素和取出元素的顺序可能不一致。
* `LinkedHashMap`：哈希表和链接列表实现，是`HashMap`的子类。
  1. `LinkedHashMap`集合底层是哈希表+链表；
  2. `LinkedHashMap`集合是一个有序的集合，存储元素和取出元素的顺序是一致的。

## Map接口常用方法

* `public V put(K var1, V var2);`：把指定的键值对添加到`Map`集合中，如果`key`不重复返回`null`，如果`key`重复，用新的`value`替换原来的`value`并返回原来的`value`；

* `public V remove(Object var1);`：根据指定的键值，删除指定的键值对并返回`value`，不存在则返回`null`；

* `public V get(Object var1);`：根据指定的键值，返回对应的`value`，如果元素不存在则返回`null`；

* `public boolean containsKey(Object var1);`：判断集合中是否包含指定的键，包含则返回`true`，否则返回`false`；

* `public Set<K> keySet();`：获取`Map`集合中所有的键，返回`Set`类型的集合。

* `public Set<Map.Entry<K, V>> entrySet();`：获取`Map`集合中所有的键值对，并返回一个`Set`类型的集合。

> **代码示例**见`HashMap类`。

### 遍历集合

* `keySet`：获取`key`，然后通过`key`找对应`value`对集合进行遍历；
* `entrySet`：获取键值对对集合进行遍历。

## HashMap类

> 当`HashMap`类使用自定义数据类型作为`key`时，必须要重写`hashCode`方法和`equals`方法，以保证`key`唯一。

```java
package com_01.jianmo.Map;

import java.util.HashMap;
import java.util.Map;

public class HashMapTest {
    public static void main(String[] args) {
        HashMap<String, String> m = new HashMap<>();

        // put方法
        m.put("aaa", "啊啊啊");
        m.put("ccc", "擦擦擦");
        m.put("bbb", "不不不");
        System.out.println(m);

        // remove方法
        System.out.println(m.remove("aaa"));

        // get方法
        System.out.println(m.get("bbb"));

        // containsKey方法
        System.out.println("containsKey(ccc)：" + m.containsKey("ccc"));

        // keySet方法：对集合进行遍历
        System.out.print("keys：");
        for(String i:m.keySet()) {
            System.out.print(i + ":" + m.get(i) + " ");
        }
        System.out.println();

        // entrySet方法：对集合进行遍历
        System.out.print("entrySet：");
        for (Map.Entry<String, String> i : m.entrySet()) {
            System.out.print(i.getKey() + ":" + i.getValue() + " ");
        }
        System.out.println();
    }
}
```

## LinkedHashMap类

> `LinkedHashMap`继承自`HashMap`，底层结构是`哈希表+链表(记录元素存储进去的顺序)`，`LinkedHashMap`具有可预知的迭代顺序。

```java
package com_01.jianmo.Map;

import java.util.LinkedHashMap;
import java.util.HashMap;

public class LinkedHashMapTest {
	public static void main(String[] args) {
		LinkedHashMap<String, String> m1 = new LinkedHashMap<>();

		m1.put("aaa", "AAA");
		m1.put("bbb", "BBB");
		m1.put("ccc", "CCC");

		System.out.println(m1);  // {aaa=AAA, bbb=BBB, ccc=CCC}


		HashMap<String, String> m2 = new HashMap<>();

		m2.put("aaa", "AAA");
		m2.put("bbb", "BBB");
		m2.put("ccc", "CCC");

		System.out.println(m2);  // {aaa=AAA, ccc=CCC, bbb=BBB}
	}
}
```

