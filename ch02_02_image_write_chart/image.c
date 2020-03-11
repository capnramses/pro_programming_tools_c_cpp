/*
Some helper functions for editing images in memory.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/

#include "image.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t rgba_to_hex( uint8_t r, uint8_t g, uint8_t b, uint8_t a ) { return (uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | (uint32_t)a; }

void hex_to_rgba( uint32_t rgba, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a ) {
  assert( r && g && b && a );

  *r = ( uint8_t )( ( rgba & 0xFF000000 ) >> 24 );
  *g = ( uint8_t )( ( rgba & 0x00FF0000 ) >> 16 );
  *b = ( uint8_t )( ( rgba & 0x0000FF00 ) >> 8 );
  *a = ( uint8_t )( rgba & 0x000000FF );
}

struct image_t image_alloc( int width, int height, int n_channels ) {
  struct image_t image;
  memset( &image, 0, sizeof( struct image_t ) );
  image.data = (uint8_t*)calloc( width * height, n_channels );
  assert( image.data );

  image.width      = width;
  image.height     = height;
  image.n_channels = n_channels;
  return image;
}

void image_free( struct image_t* image ) {
  assert( image && image->data );

  free( image->data );
  memset( image, 0, sizeof( struct image_t ) );
}

void image_clear( struct image_t* image, uint32_t rgba ) {
  assert( image && image->data );
  uint8_t bytes[4];
  hex_to_rgba( rgba, &bytes[0], &bytes[1], &bytes[2], &bytes[3] );
  for ( int i = 0; i < image->width * image->height; i++ ) { memcpy( &image->data[i * image->n_channels], bytes, image->n_channels ); }
}

void image_draw_pixel( struct image_t* image, int x, int y, uint32_t rgba ) {
  assert( image && image->data );
  assert( x >= 0 && x < image->width && y >= 0 && y < image->height );

  uint8_t r = 0, g = 0, b = 0, a = 0xFF;
  hex_to_rgba( rgba, &r, &g, &b, &a );
  int first_byte_idx = ( y * image->width + x ) * image->n_channels;
  if ( image->n_channels > 0 ) { image->data[first_byte_idx] = r; }
  if ( image->n_channels > 1 ) { image->data[first_byte_idx + 1] = g; }
  if ( image->n_channels > 2 ) { image->data[first_byte_idx + 2] = b; }
  if ( image->n_channels > 3 ) { image->data[first_byte_idx + 3] = a; }
}

void image_draw_line( struct image_t* image, int x0, int y0, int x1, int y1, uint32_t rgba ) {
  assert( image && image->data );
  assert( x0 >= 0 && x0 < image->width && x1 >= 0 && x1 < image->width );
  assert( y0 >= 0 && y0 < image->height && y1 >= 0 && y1 < image->height );

  int x = x0;
  int y = y0;
  // original deltas between start and end points
  int d_x = x1 - x0;
  int d_y = y1 - y0;
  // increase rate on each axis
  int i_x = 1;
  int i_y = 1;
  // remember direction of line on each axis
  if ( d_x < 0 ) {
    i_x = -1;
    d_x = abs( d_x );
  }
  if ( d_y < 0 ) {
    i_y = -1;
    d_y = abs( d_y );
  }
  // scaled deltas (used to allow integer comparison of <0.5)
  int d2_x = d_x * 2;
  int d2_y = d_y * 2;
  // identify major axis (remember these have been absoluted)
  if ( d_x > d_y ) {
    // initialise error term
    int err = d2_y - d_x;
    for ( int i = 0; i <= d_x; i++ ) {
      image_draw_pixel( image, x, y, rgba );
      if ( err >= 0 ) {
        err -= d2_x;
        y += i_y;
      }
      err += d2_y;
      x += i_x;
    } // endfor
  } else {
    // initialise error term
    int err = d2_x - d_y;
    for ( int i = 0; i <= d_y; i++ ) {
      image_draw_pixel( image, x, y, rgba );
      if ( err >= 0 ) {
        err -= d2_y;
        x += i_x;
      }
      err += d2_x;
      y += i_y;
    } // endfor
  }   // endif
} // endfunc

uint32_t image_get_pixel( struct image_t image, int x, int y ) {
  assert( x >= 0 && x < image.width && y >= 0 && y < image.height );

  int first_byte_idx = ( y * image.width + x ) * image.n_channels;
  uint8_t r = 0, g = 0, b = 0, a = 0xFF;
  if ( image.n_channels > 0 ) { r = image.data[first_byte_idx]; }
  if ( image.n_channels > 1 ) { g = image.data[first_byte_idx + 1]; }
  if ( image.n_channels > 2 ) { b = image.data[first_byte_idx + 2]; }
  if ( image.n_channels > 3 ) { a = image.data[first_byte_idx + 3]; }
  return rgba_to_hex( r, g, b, a );
}

void image_write_binary_ppm( const char* filename, struct image_t image ) {
  assert( filename );

  FILE* fptr = fopen( filename, "wb" );
  {
    // write header
    fprintf( fptr, "P6\n" );
    fprintf( fptr, "%i %i\n", image.width, image.height );
    fprintf( fptr, "255\n" );
    // write body
    fwrite( image.data, 1, image.width * image.height * image.n_channels, fptr );
  }
  fclose( fptr );
}