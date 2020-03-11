gcc -c second.c -o second.o
gcc -shared second.o -o libsecond.dll
gcc main.c -L./ -lsecond