#!/bin/bash

man bash | grep -o '\b[A-Za-z]\{4,\}\b' | tr '[:upper:]' '[:lower:]' | sort | uniq -c | sort -nr | head -n 3
