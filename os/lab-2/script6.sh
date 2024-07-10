#!/bin/bash

max_mem=0
for process_dir in /proc/[0-9]*/
do
mem=$(grep "VmRSS" "$process_dir/status" | awk '{print $2}')
if [[ -n "$mem" ]]
then
if [ "$mem" -gt "$max_mem" ]
then
max_mem="$mem"
max_pid=$(basename "$process_dir")
fi
fi
done
echo "script: $max_pid"
echo "top: $(top -o %MEM -n 1 | tail -n +8 | head -n 1 | awk '{print $2}')"
