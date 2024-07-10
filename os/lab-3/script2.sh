#!/bin/bash

at now + 2 minutes -f script1 &
tail -f ~/report &
