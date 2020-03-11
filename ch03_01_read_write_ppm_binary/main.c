/*
Example of a C program that reads a binary PPM image file and writes it out as a new PPM file.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_IN "in.ppm"
#define FILE_OUT "out.ppm"

struct image_t {
  uint8_t* ptr;
  int width, height, n_channels;
};

struct image_t ppm_read( const char* filename ) {
  struct image_t image;
  memset( &image, 0, sizeof( struct image_t ) );
  image.n_channels = 3; // 3 for RGB

  FILE* fptr = fopen( filename, "rb" ); // ‘rb’ is ‘read binary’
  if ( !fptr ) { return image; }
  {
    // read header
    char type[2];
    int max_val;
    int n = fscanf( fptr, "%c%c %i %i %i\n", &type[0], &type[1], &image.width, &image.height, &max_val );
    if ( 5 != n || type[0] != 'P' || type[1] != '6' ) {
      fclose( fptr );
      return image;
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

int main() {
  struct image_t image = ppm_read( FILE_IN );
  if ( !image.ptr ) {
    fprintf( stderr, "ERROR:reading image from `%s`\n", FILE_IN );
    return 1;
  }
  printf( "parsed PPM from `%s`\n", FILE_IN );

  // write again to test reading worked
  bool ret = ppm_write( FILE_OUT, image );
  if ( !ret ) {
    fprintf( stderr, "ERROR:writing image to `%s`\n", FILE_OUT );
    return 1;
  }
  printf( "wrote PPM file to `%s`\n", FILE_OUT );

  return 0;
}
