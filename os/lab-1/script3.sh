#!/bin/bash

echo "Enter the action number
1 - open Nano editor
2 - open Vi editor
3 - open Links browser
4 - exit"

read number
case "$number" in
1 )
nano
./script3
;;
2 )
vi
./script3
;;
3 )
links
./script3
;;
4 )
exit
;;
esac
