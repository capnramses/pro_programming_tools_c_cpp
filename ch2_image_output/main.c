/*
Example of a C program that outputs an image as a binary file.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void draw_pixel( uint8_t* image_ptr, int width, int n_channels, int x, int y, uint8_t r, uint8_t g, uint8_t b ) {
  int pixel_idx            = n_channels * ( y * width + x );
  image_ptr[pixel_idx + 0] = r;
  image_ptr[pixel_idx + 1] = g;
  image_ptr[pixel_idx + 2] = b;
}

int main() {
  int width = 256, height = 128, n_channels = 3;
  // allocate memory. calloc() sets all our memory to zero (black)
  uint8_t* image_ptr = calloc( 1, width * height * n_channels );

  // paint half the image image (or edit whatever you like here)
  for ( int y = 0; y < height; y++ ) {
    for ( int x = 0; x < width / 2; x++ ) {
      int pixel_idx = n_channels * ( y * width + x );
      image_ptr[pixel_idx + 0] = 255;     // red
      image_ptr[pixel_idx + 2] = 255; // blue
    }
  }

  // paint some green dots
  draw_pixel( image_ptr, width, n_channels, 0, 0, 0x00, 0xFF, 0x00 );
  draw_pixel( image_ptr, width, n_channels, 128, 64, 0x00, 0xFF, 0x00 );

  { // write file
    FILE* fptr = fopen( "out.ppm", "wb" );

    // write header (ASCII)
    fprintf( fptr, "P6\n" );
    fprintf( fptr, "%i %i\n", width, height );
    fprintf( fptr, "255\n" );
        
    // write body (binary RGB image data)
    fwrite( image_ptr, 1, width * height * n_channels, fptr );
            
    fclose( fptr );
  }
  free( image_ptr );
  return 0;
}