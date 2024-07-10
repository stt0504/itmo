#!/bin/bash

ps -eo pid,start_time | sort -k2 | tail -n 2 | head -n 1 | awk '{print $1}'
