#!/bin/bash
#compile second.c
gcc -c second.c -o second.o
#create a static lib (archive) from second.o
ar cr libsecond.a second.o
#link the program using the static library
gcc main.c libsecond.a
