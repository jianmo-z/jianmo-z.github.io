#!/bin/bash


for i in  hello world pip
    do
        echo "says:{$i}"
done

echo "==================="

# 注意区分$*和$@
for i in  "$*"
    do
        echo "says:{$i}"
done

echo "==================="

for i in  "$@"
    do
        echo "says:{$i}"
done
