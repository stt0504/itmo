#!/bin/bash

rm -rf pipe
mkfifo pipe
./script5.handler &
./script5.generator
rm -rf pipe
