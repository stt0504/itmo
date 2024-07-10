#!/bin/bash

ps -U user | tail -n +2 | wc -l > file1
ps -U user -o pid,cmd >> file1
