#!/bin/bash

pid1=$(ps -C script4.1 -o pid --sort=pid | sed -n 2p | awk '{print $1}')
renice +10 -p "$pid1"
pid3=$(ps -C script4.1 -o pid --sort=pid | sed -n 4p | awk '{print $1}')
kill $pid3
