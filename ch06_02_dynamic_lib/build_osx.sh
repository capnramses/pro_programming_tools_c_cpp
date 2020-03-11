#!/bin/bash

#compile second.c and
#create a shared object lib (dynamically linked library) from second.o
clang -shared second.c -o lib/libsecond.dylib

#create the program
clang main.c -L lib/ -lsecond

echo "=====PREVIOUS PATHS====="
#you can use otool -L on the binary to check the library paths as built
otool -L ./a.out
#and the ID of the library
otool -D lib/libsecond.dylib

# make the path to the library relative to the location of the program's binary so we can run it from another working directory
install_name_tool -change lib/libsecond.dylib \
@executable_path/lib/libsecond.dylib ./a.out

# change the library's 'ID' so that it's name (path) is relative to the binary as well
install_name_tool -id @executable_path/lib/libsecond.dylib lib/libsecond.dylib

echo "====UPDATED PATHS====="
#confirm changes
otool -L ./a.out
otool -D lib/libsecond.dylib
