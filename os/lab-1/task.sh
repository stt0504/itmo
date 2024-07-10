#!/bin/bash

if [[ "$#" -lt 10 ]]
then
count=0
for param in "$@"
do
((count++))
echo "parameter $count = $param"
done
fi
