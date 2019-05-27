#!/bin/bash

sum=0
i=1
while [ $i -ne 101 ]  # 注意左右空格
    do
        sum=$[ $sum + $i ]
        i=$[ $i + 1 ]
done

echo "sum = $sum"
