#!/bin/bash
# Author: Anton Gerdelan

# any error code causes script to exit with error code
set -e

#compile second.c
gcc -c second.c -o second.o
#create a shared object lib (dynamically linked library) from second.o
gcc -shared second.o -o lib/libsecond.so
export LD_RUN_PATH=\$ORIGIN/lib/
gcc -o ./a.out main.c -lsecond -Llib/
