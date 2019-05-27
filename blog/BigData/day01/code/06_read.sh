#!/bin/bash

read -p "Please input username:" name
echo "Your name is {$name}"

read -p "Please input phone number(3S-timeout):" -t 3 phone
if [ $phone ];then
    echo "Your phone number is {$phone}"
else
    echo -e "\nTimeout!!!"
fi

