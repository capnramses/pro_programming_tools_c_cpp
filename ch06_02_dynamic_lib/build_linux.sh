#!/bin/bash
# Author: Anton Gerdelan

# any error code causes script to exit with error code
set -e


gcc -c second.c -o second.o
gcc -shared second.o -o lib/libsecond.so
gcc main.c -Llib/ -lsecond
