#!/bin/bash

echo $$ > .handler_pid
iter=0

get_b_send_number()
{
b=$(cat .b)
echo "Got b; b=$b" >> file
if [[ b -gt b_prev ]]; then
((pos++))
digit=0
echo "b is greater than $b_prev; pos = $pos, digit=$digit" >> file
fi
((digit++))
echo "b is not greater than $b_prev; pos = $pos, digit=$digit" >> file
guessed_number="${guessed_number:0:pos}$digit${guessed_number:pos+1}"
echo "new guessed number: $guessed_number" >> file

b_prev=$b
echo "b_prev now is = $b" >> file

echo "$guessed_number" > .number
echo "sig to generator: handler is sending number" >> file
((iter++))
echo $iter > .iter
kill -USR1 $(cat .generator_pid)
}
trap 'get_b_send_number' USR1

s()
{
echo "handler: start" >> file
echo "writing handler pid into file" >> file
pos=0
digit=0
b_prev=0
echo "guessed number is \#####" >> file
guessed_number="#####"
echo "$guessed_number" > .number
echo "sig to generator: handler is waiting of b" >> file
kill -USR1 $(cat .generator_pid)
}
trap 's' USR2

while true; do
:
done
