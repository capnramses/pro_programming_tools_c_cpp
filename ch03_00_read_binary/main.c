/*
Example of a C program that reads a binary PPM image file.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define FILE_IN "in.ppm"

int main() {
  const char* filename = "in.ppm";

  FILE* fptr = fopen( filename, "rb" ); // ‘rb’ is ‘read binary’
  if ( !fptr ) {
    fprintf( stderr, "ERROR opening file `%s`\n", filename );
    return 1;
  }
  {
    // read header
    char type[2];
    int width, height, max_val;
    int n = fscanf( fptr, "%c%c %i %i %i\n", &type[0], &type[1], &width, &height, &max_val );
    if ( 5 != n ) {
      fprintf( stderr, "ERROR reading file `%s`\n", filename );
      return 1;
    }

    // read body
    size_t pixel_data_sz    = width * height * 3; // 3 for RGB
    uint8_t* pixel_data_ptr = malloc( pixel_data_sz );
    n                       = fread( pixel_data_ptr, pixel_data_sz, 1, fptr );
    if ( 1 != n ) {
      fprintf( stderr, "ERROR reading file `%s`\n", filename );
      return 1;
    }
  }
  fclose( fptr );
  printf( "parsed PPM file `%s`\n", filename );

  return 0;
}
