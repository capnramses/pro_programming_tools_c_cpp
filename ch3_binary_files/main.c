/*
Example of a C program that reads a binary PPM image file.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char** argv ) {
  if ( argc < 2 ) {
    printf( "Usage: Give a file to open as the first argument to this program (or drag an image file onto the binary)\n" );
    return 0;
  }
  printf( "opening file `%s`\n", argv[1] );
  uint8_t* pixel_data_ptr = NULL;
  {
    FILE* fptr = fopen( argv[1], "rb" ); // 'rb' is 'read binary'
    char type[2];
    int32_t width, height, max_val;
    int n = fscanf( fptr, "%c%c %i %i %i\n", &type[0], &type[1], &width, &height, &max_val );
    if ( 5 != n ) {
      fprintf( stderr, "ERROR: reading PPM file header from `%s`\n", argv[1] );
      fclose( fptr );
      return 1;
    }
    size_t pixel_data_sz = width * height * 3; // 3 for RGB
    pixel_data_ptr       = malloc( pixel_data_sz );
    if ( !pixel_data_ptr ) {
      fprintf( stderr, "ERROR: allocating memory\n" );
      fclose( fptr );
      return 1;
    }
    fread( pixel_data_ptr, pixel_data_sz, 1, fptr );
    fclose( fptr );
  }

  // do something with pixel data here

  free( pixel_data_ptr );
  return 0;
}
