#!/bin/bash

while [ "$str" != "q" ]
do
res="$res$str"
read str
done
echo "$res"
