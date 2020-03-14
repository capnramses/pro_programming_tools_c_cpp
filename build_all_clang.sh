#!/bin/bash
# Author: Anton Gerdelan
# Folders with deliberate errors have builds commented out so that this script can be used for CI checks.

# any error code causes script to exit with error code
set -e
# echo everything
set -x

echo on

CC=clang
CPP=clang++
FLAGS="-Wall -Wextra -Werror -pedantic -fsanitize=address -fsanitize=undefined"

echo "cd ch00_00_c/"
cd ch00_00_c/
$CC $FLAGS main.c

echo "cd ../ch00_01_cpp_malloc/"
cd ../ch00_01_cpp_malloc/
$CPP $FLAGS main.cpp

echo "cd ../ch00_02_cpp_new_delete/"
cd ../ch00_02_cpp_new_delete/
$CPP $FLAGS main.cpp

echo "cd ../ch01_00_assertions/"
cd ../ch01_00_assertions/
$CC $FLAGS main.c

echo "cd ../ch01_01_unit_test/"
cd ../ch01_01_unit_test/
$CC $FLAGS main.c

echo "cd ../ch02_00_image_output/"
cd ../ch02_00_image_output/
$CC $FLAGS main.c

echo "cd ../ch02_01_image_pixel_functions/"
cd ../ch02_01_image_pixel_functions/
$CC $FLAGS main.c

echo "cd ../ch02_02_image_write_chart/"
cd ../ch02_02_image_write_chart/
$CC $FLAGS main.c image.c

echo "cd ../ch03_00_read_binary/"
cd ../ch03_00_read_binary/
$CC $FLAGS main.c

echo "cd ../ch03_01_read_write_ppm_binary/"
cd ../ch03_01_read_write_ppm_binary/
$CC $FLAGS main.c

echo "cd ../ch03_02_read_entire_file/"
cd ../ch03_02_read_entire_file/
$CC $FLAGS main.c

echo "cd ../ch03_03_struct_padding/"
cd ../ch03_03_struct_padding/
$CC $FLAGS main.c

echo "cd ../ch04_00_deliberate_crash/"
cd ../ch04_00_deliberate_crash/
$CC $FLAGS main.c

echo "cd ../ch05_00_gprof/"
cd ../ch05_00_gprof/
$CC $FLAGS main.c

echo "cd ../ch05_01_timers/"
cd ../ch05_01_timers/
$CC $FLAGS main.c

echo "cd ../ch06_00_multi_file/"
cd ../ch06_00_multi_file/
$CC $FLAGS main.c second.c

echo "cd ../ch06_01_static_lib/"
cd ../ch06_01_static_lib/
bash build.sh

echo "cd ../ch06_02_dynamic_lib/"
cd ../ch06_02_dynamic_lib/
# -fPIC to let us call printf() from the library with Clang
$CC $FLAGS -fPIC -c second.c -o second.o
$CC $FLAGS -shared second.o -o lib/libsecond.so
# basic version
$CC $FLAGS main.c -Llib/ -lsecond
# flag rpath version
$CC $FLAGS main.c -Llib/ -lsecond -Wl,-rpath,\$ORIGIN/lib/
# export rpath version
export LD_RUN_PATH=\$ORIGIN/lib/
$CC $FLAGS main.c -lsecond -Llib/

echo "cd ../ch06_03_makefile/"
cd ../ch06_03_makefile/
make

echo "cd ../ch06_04_cmake/"
cd ../ch06_04_cmake/
rm -rf build/
mkdir build/
cd build/
cmake ..
cmake --build .
cd ..

echo "cd ../ch07_00_clang_format/"
cd ../ch07_00_clang_format/
$CC $FLAGS main.c second.c

echo "cd ../ch08_00_scan_build/"
#cd ../ch08_00_scan_build/
#$CC $FLAGS main.c

echo "cd ../ch08_01_clang_tidy/"
#cd ../ch08_01_clang_tidy/
#$CC $FLAGS main.c

echo "cd ../ch09_00_fuzzing/"
cd ../ch09_00_fuzzing/
$CC $FLAGS main.c my_ppm_stuff.c

echo "cd ../ch10_00_asm/"
cd ../ch10_00_asm/
$CC $FLAGS -S my_file.c

echo "cd ../ch11_00_valgrind_asan/"
cd ../ch11_00_valgrind_asan/
$CC $FLAGS main.c

echo "cd ../ch11_01_ubsan/"
#cd ../ch11_01_ubsan/
#$CC $FLAGS main.c

echo "cd ../ch11_03_cachegrind/"
cd ../ch11_03_cachegrind/
$CC $FLAGS main.c

echo "cd ../ch13_00_streams/"
cd ../ch13_00_streams/
$CC $FLAGS main.c

cd ..
