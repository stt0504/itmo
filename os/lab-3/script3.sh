#!/bin/bash

weekday=7
echo "*/5 * * * $weekday /home/user/lab3/script1" | crontab
