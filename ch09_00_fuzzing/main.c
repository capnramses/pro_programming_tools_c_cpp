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

#include "my_ppm_stuff.h" // the header for my image functions
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char** argv ) {
  char file_in[1024], file_out[1024];
  strncpy( file_in, "in.ppm", 1023 );
  strncpy( file_out, "out.ppm", 1023 );
  if ( argc > 1 ) { strncpy( file_in, argv[1], 1023 ); }
  if ( argc > 2 ) { strncpy( file_in, argv[2], 1023 ); }

  // i want to test this function that reads an image
  struct image_t image = ppm_read( file_in );
  if ( !image.ptr ) {
    fprintf( stderr, "ERROR: could not read image `%s`\n", file_in );
    return 1;
  }

  // and i'll secondarily make sure the writer works afterwards
  bool success = ppm_write( file_out, image );
  if ( !success ) {
    fprintf( stderr, "ERROR: could not write image `%s`\n", file_out );
    return 1;
  }

  free( image.ptr );
  return 0;
}
