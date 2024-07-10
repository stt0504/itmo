#!/bin/bash

grep -r -o '[A-Za-z0-9]+@[A-Za-z0-9]+\.[A-Za-z]{2,}' /etc | tr '\n' ',' > emails.lst
