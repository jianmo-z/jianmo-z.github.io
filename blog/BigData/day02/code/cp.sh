#!/bin/bash

HOSTS="202 203 204 205"
SUBNET_IP="192.168.91."
SOURCE=/opt/*
DEST=/opt/


for host in $HOSTS
    do
        # dothings
        ip=$SUBNET_IP$host
        scp -r $SOURCE  root@$ip:$DEST > /dev/null
        if [ $? -eq 0 ];then
            echo $ip send success
        else
            echo $ip send failed
	    exit 1
        fi

        echo -e "\n"
done

