#!/bin/bash

ps -eo pid,cmd | grep "[0-9]* /sbin/" | awk '{print $1}'  > file2
