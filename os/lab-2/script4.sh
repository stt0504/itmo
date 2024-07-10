#!/bin/bash

echo -n > file4
for process_dir in /proc/[0-9]*/
do
pid=$(basename "$process_dir")
ppid=$(grep -E "^PPid:" "$process_dir/status" | awk '{print $2}')
sum_exec_runtime=$(grep -E "^se.sum_exec_runtime" "$process_dir/sched" | awk '{print $3}')
nr_switches=$(grep -E "^nr_switches" "$process_dir/sched" | awk '{print $3}')
if [ -n "$sum_exec_runtime" ] && [ -n "$nr_switches" ]
then art=$(printf "%.4f" $(echo "scale=4; $sum_exec_runtime / $nr_switches" | bc))
else art="null"
fi
echo "ProcessID=$pid : Parent_ProcessID=$ppid : Average_Running_Time=$art" >> file4
done
sort -t'=' -k3  -n -o file4 file4
