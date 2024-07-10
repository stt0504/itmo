#!/bin/bash

if [[ "$#" -ne 1 ]]
then
echo "Error: incorrect arguments number"
exit 1
fi

filename=$(basename -- "$1")

if [[ ! -f "$filename" ]] && [[ ! -d "$filename" ]]
then
echo "Error: no such file"
exit 1
fi

trash_dir="/home/.trash"
if [[ ! -d "$trash_dir" ]]
then
mkdir "$trash_dir"
fi

number=$(cat /home/user/lab4/.number)
((number++))
echo "$number" > /home/user/lab4/.number
ln -- "$filename" "/home/.trash/$number"
rm -- "$filename"

echo "$PWD/$filename $number" >> "/home/.trash.log"
