#!/bin/bash
gcc -c second.c -o second.o
gcc -shared second.o -o lib/libsecond.so
gcc main.c -Llib/ -lsecond
