#!/bin/bash

echo $$ > .generator_pid
echo "generator is sending pid into file" >> file

#hidden_number=$((RANDOM % 90000 + 10000))
hidden_number=99999
echo "hidden number is $hidden_number" >> file

get_number()
{
echo "generator gets number!" >> file
guessed_number=$(cat .number)
echo "number is.. $guessed_number?" >> file
b=0
for ((i=0; i<5; i++)); do
digit_hidden=${hidden_number:$i:1}
digit_guessed=${guessed_number:$i:1}
if [[ "$digit_guessed" =~ ^[0-9]$ && $digit_hidden -eq $digit_guessed ]]; then
((b++))
fi
done
echo "b counted is $b" >> file
echo "$b" > .b
echo "sig to handler: sending b!" >> file
kill -USR1 $(cat .handler_pid)
}
trap 'get_number' USR1

while [ ! -s .handler_pid ]; do
sleep 0.1
echo ".handler_pid is empty" >> file
done

echo "sig to handler: start handler" >> file
echo "pid:" >> file
cat .handler_pid >> file
kill -USR2 $(cat .handler_pid)
while [[ "$b" -ne 5 ]]; do
:
done
echo "b = $b!"
kill $(cat .handler_pid)
