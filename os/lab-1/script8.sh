#!/bin/bash

cut -d ':' -f 1,3 /etc/passwd | sort -t ':' -k 2n
