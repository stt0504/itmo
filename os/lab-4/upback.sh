#!/bin/bash

restore_dir="/home/user/restore/"
rm -rf "$restore_dir"
mkdir $restore_dir

backup_dir="/home/user/Backup-*"
latest_backup=$(ls -d $backup_dir | awk -F '-' '{print $0, $2$3$4}' | sort -k2 | awk '{print $1}' | tail -n 1)

for file in $(find $latest_backup -type f | grep -v -E "^*\.[0-9]{4}-[0-9]{2}-[0-9]{2}$"); do
cp $file $restore_dir
done
