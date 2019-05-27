#!/bin/bash

function sum()
{
    s=0
    s=$[ $1 + $2 ]
    echo "sum is {$s}"
}

read -p "please input first num:" n1;  # ;表示一个命令结束，可以在一行写多个独立语句
read -p "please input first num:" n2;

sum n1 n2  # 调用函数并传参
