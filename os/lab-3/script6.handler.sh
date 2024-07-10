#!/bin/bash

echo $$ > .pid

result=1

usr1()
{
mode="+"
}
trap 'usr1' USR1

usr2()
{
mode="*"
}
trap 'usr2' USR2

sigterm()
{
mode="stop"
}
trap 'sigterm' SIGTERM

while true; do
case "$mode" in
"+")
result=$((result + 2))
echo "result: $result"
;;
"*")
result=$((result * 2))
echo "result: $result"
;;
"stop")
echo "Stopped"
exit
;;
*)
:
;;
esac
sleep 1
done
