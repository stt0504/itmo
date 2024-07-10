#!/bin/bash

> file
./generator &
./handler
echo "Total iteration count: " $(cat .iter)
