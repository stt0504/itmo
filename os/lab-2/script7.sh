#!/bin/bash

for process_dir in /proc/[0-9]*/
do
read_bytes=$(grep -E "^read_bytes:" "$process_dir/io" | awk '{print $2}')
pid=$(basename "$process_dir")
echo "PID=$pid:ReadBytes=$read_bytes" >> tmp1
done

sleep 60

for process_dir in /proc/[0-9]*/
do
read_bytes=$(grep -E "^read_bytes:" "$process_dir/io" | awk '{print $2}')
pid=$(basename "$process_dir")
read_bytes_prev=$(awk -F':' '$1==$pid {print $2}' tmp1)
diff=$((read_bytes - read_bytes_prev))
echo "PID=$pid:Difference=$diff:$(cat $process_dir/cmdline | tr '\0' ' ')" >> tmp2
done

sort -t'=' -k3 -rn tmp2 | head -n 3
rm tmp1
rm tmp2
