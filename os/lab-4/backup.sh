#!/bin/bash

date=$(date +%Y-%m-%d)
backup_dir="/home/user/Backup-$date"
source_dir="/home/user/source"
report_file="/home/user/backup-report"

create=true
for dir in /home/user/Backup-*; do
if [[ -d "$dir" ]]; then
dir_date=$(basename "$dir" | cut -d'-' -f2-)
date_diff=$((($(date -d "$date" +%s) - $(date -d "$dir_date" +%s))/86400))
if [[ $date_diff -lt 7 ]]; then
current_backup="$dir"
create=false
fi
fi
done

if [[ "$create" = "true" ]]; then
mkdir $backup_dir
cp -r "$source_dir"/* "$backup_dir"
echo "A new backup has been created: $backup_dir" >> "$report_file"
echo "List of copied files: " >> "$report_file"
ls "$source_dir" >> "$report_file"
else
echo "Changes have been made to the current backup: $current_backup at $date" >> "$report_file"
for file in "$source_dir"/*; do
filename=$(basename "$file")
dest_path="$backup_dir/$filename"
if [[ -f "$dest_path" ]]; then
if [[ $(stat -c%s "$file") -ne $(stat -c%s "$dest_path") ]]; then
mv "$dest_path" "$dest_path.$date"
cp "$file" "$dest_path"
echo "$filename has been updated, the previous version is saved as $filename.$date" >> "$report_file"
fi
else
cp "$file" "$backup_dir"
echo "the file was copied: $filename" >> "$report_file"
fi
done
fi
