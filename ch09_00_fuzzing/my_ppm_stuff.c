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
#include "my_ppm_stuff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct image_t ppm_read( const char* filename ) {
  struct image_t image;
  memset( &image, 0, sizeof( struct image_t ) );
  image.n_channels = 3; // 3 for RGB

  FILE* fptr = fopen( filename, "rb" ); // ‘rb’ is ‘read binary’
  if ( !fptr ) { return image; }
  {
    // read header
    char line[2048];
    char type[2];
    int n = fscanf( fptr, "%c%c\n", &type[0], &type[1] );
    if ( 2 != n || type[0] != 'P' || type[1] != '6' ) {
      assert( false ); /***** deliberate crash for the fuzzer to find and can be easily fixed ******/

      fclose( fptr );
      return image;
    }
    while ( fgets( line, 2048, fptr ) ) {
      if ( line[0] == '#' ) { continue; } // skip comments added by GIMP etc
      int n = sscanf( line, "%i %i\n", &image.width, &image.height );
      fgets( line, 2048, fptr ); // ignore max_val
      break;
    }

    // read body
    size_t pixel_data_sz = image.width * image.height * image.n_channels;
    image.ptr            = malloc( pixel_data_sz );
    if ( !image.ptr ) {
      fclose( fptr );
      return image;
    }
    n = fread( image.ptr, pixel_data_sz, 1, fptr );
    if ( 1 != n ) {
      fclose( fptr );
      free( image.ptr );
      memset( &image, 0, sizeof( struct image_t ) );
      return image;
    }
  }
  fclose( fptr );
  return image;
}

bool ppm_write( const char* filename, struct image_t image ) {
  FILE* fptr = fopen( filename, "wb" );
  if ( !fptr ) { return false; }
  {
    fprintf( fptr, "P6\n%i %i\n255\n", image.width, image.height );
    size_t sz = image.width * image.height * image.n_channels;
    int n     = fwrite( image.ptr, sz, 1, fptr );
    if ( 1 != n ) {
      fclose( fptr );
      return false;
    }
  }
  fclose( fptr );
  return true;
}
