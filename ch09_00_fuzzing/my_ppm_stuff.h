/* This is a test program for fuzzing the ppm_read() and ppm_write() functions using AFL.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
Compile:
  afl-gcc -g -o test_ppm_fuzz main.c my_ppm_stuff.c -I ./

Run:
  afl-fuzz -i fuzzer_inputs/ -o fuzzer_outputs/ -- ./test_ppm_fuzz @@

or to run and ignore warnings run the script I made:
  ./fuzzme.sh
*/
#pragma once
#include <stdbool.h>
#include <stdint.h>

struct image_t {
  uint8_t* ptr;
  int width, height, n_channels;
};

struct image_t ppm_read( const char* filename );

bool ppm_write( const char* filename, struct image_t image );
