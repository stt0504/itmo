#!/bin/bash

result=1
mode="+"
(tail -f pipe) |
while true; do
read line
case "$line" in

"+")
mode="+"
echo "Mode changed: +";;

"*")
mode="*"
echo "Mode changed: *";;

"QUIT")
echo "Exit"
killall tail
killall "script5.generator"
exit;;

*)
if [[ "$line" =~ ^[+-]?[0-9]+$ ]]
then
case "$mode" in
"+")
result=$((result + line));;
"*")
result=$((result * line));;
esac
echo "Result: $result"
else
echo "Error: incorrect input; \"$line\""
killall tail
killall "script5.generator"
exit
fi;;

esac
done
