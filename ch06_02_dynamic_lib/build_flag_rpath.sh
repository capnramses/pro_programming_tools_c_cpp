#!/bin/bash
#compile second.c
gcc -c second.c -o second.o
#create a shared object lib (dynamically linked library) from second.o
gcc -shared second.o -o lib/libsecond.so
#set the local library relative path and
#link the program using the shared object library
gcc main.c -Llib/ -lsecond -Wl,-rpath,\$ORIGIN/lib/
