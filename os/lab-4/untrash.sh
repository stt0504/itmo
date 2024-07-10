#!/bin/bash

if [[ "$#" -ne 1 ]]
then
echo "Error: incorrect arguments number"
exit 1
fi

filename=$(basename -- "$1")

while read line; do
full_path=$(echo "$line" | awk '{print $1}')
name=$(basename "$full_path")
if [[ "$name" == "$filename" ]]
then
echo "Restore file $full_path? (y/n) "
read answer < /dev/tty
if [[ "$answer" == "y" ]]
then

directory=$(dirname "$full_path")
if [[ ! -d "$directory" ]]
then
echo "No such directory. File will be restored into home directory"
directory="/home/"
fi

while [[ -f "$directory/$name" ]]; do
echo "File with such name already exists. Please change name: "
read name < /dev/tty
done

id=$(echo "$line" | awk '{print $2}')
ln /home/.trash/"$id" "$directory/$name"
rm /home/.trash/"$id"
awk '$2 != id' id=$id /home/.trash.log > temp && mv temp /home/.trash.log
break

fi
fi
done < /home/.trash.log
