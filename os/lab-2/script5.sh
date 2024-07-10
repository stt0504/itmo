#!/bin/bash

echo -n > file5
prev_ppid=$(echo "$(head -n 1 file4)" | awk '{print substr($3, 18)}')
count=0
sum=0
while read line; do
echo "$line" >> file5
new_ppid=$(echo "$line" | awk '{print substr($3, 18)}')
art=$(echo "$line" | awk '{print substr($5, 22)}')
if [ "$prev_ppid" != "$new_ppid" ]; then
avg=$(echo "scale=4; $sum / $count" | bc)
sed -i '$d' file5
echo "Average_Running_Children_of_ParentID=$prev_ppid is $avg" >> file5
echo "$line" >> file5
sum=0
count=0
fi
sum=$(echo "$sum + $art" | bc)
((count++))
prev_ppid="$new_ppid"
done < file4
avg=$(echo "scale=4; $sum / $count" | bc)
echo "Average_Running_Children_of_ParentID=$prev_ppid is $avg" >> file5
