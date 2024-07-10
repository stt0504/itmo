#!/bin/bash

datetime=$(date "+%Y-%m-%d_%H:%M:%S")
mkdir /home/test &&
{
echo "catalog test was created successfully" > ~/report
touch /home/test/"$datetime"
}
ping -c 1 www.net_nikogo.ru ||
{
datetime=$(date "+%Y-%m-%d %H:%M:%S")
echo "$datetime host is unavailable" >> ~/report
}
