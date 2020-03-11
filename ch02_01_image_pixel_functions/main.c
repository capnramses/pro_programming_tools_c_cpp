/*
Example of a C program that outputs an image as a binary file using some additional painting functions.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct image_t {
  uint8_t* ptr;
  int width, height, n_channels;
};

// get the 1D memory index for a 2D pixel coordinate
int pixel_index( int x, int y, int width, int n_channels ) { return n_channels * ( y * width + x ); }

// set the colour of a given pixel
void draw_pixel( struct image_t image, int x, int y, uint8_t red, uint8_t green, uint8_t blue ) {
  int pixel_idx            = pixel_index( x, y, image.width, image.n_channels );
  image.ptr[pixel_idx + 0] = red;
  image.ptr[pixel_idx + 1] = green;
  image.ptr[pixel_idx + 2] = blue;
}

void paint_area( struct image_t image, int min_x, int min_y, int max_x, int max_y, uint8_t red, uint8_t green, uint8_t blue ) {
  for ( int y = min_y; y <= max_y; y++ ) {
    for ( int x = min_x; x <= max_x; x++ ) { draw_pixel( image, x, y, red, green, blue ); }
  }
}

void write_ppm_bin( const char* filename, struct image_t image ) {
  FILE* f_ptr = fopen( filename, "wb" );
  // ASCII header
  fprintf( f_ptr, "P6\n%i %i\n255\n", image.width, image.height );
  // binary body
  size_t sz = image.width * image.height * image.n_channels;
  fwrite( image.ptr, 1, sz, f_ptr );
  fclose( f_ptr );
}

int main() {
  struct image_t image;
  image.width = image.height = 512;
  image.n_channels           = 3;
  image.ptr                  = calloc( 1, image.width * image.height * image.n_channels );

  draw_pixel( image, 0, 0, 0xFF, 0x00, 0x00 );
  paint_area( image, 16, 16, 511, 511, 0x00, 0xFF, 0xFF );
  paint_area( image, 32, 32, 256, 256, 0x00, 0x7F, 0xFF );

  write_ppm_bin( "out.ppm", image );

  free( image.ptr );
  return 0;
}
