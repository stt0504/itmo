#!/bin/bash

sed -n 's/(WW)/Warning: /p' /var/log/anaconda/X.log > full.log
sed -n 's/(II)/Information: /p' /var/log/anaconda/X.log >> full.log
cat full.log
