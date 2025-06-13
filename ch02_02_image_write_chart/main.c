/*
Example of a C program for quick and dirty chart image creation.
For something nicer looking move to anti-aliased line drawing (example: Wu) and add a line thickness parameter.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
Compile:    gcc main.c image.c
*/

#include "image.h"
#include <assert.h>
#include <math.h>

float lerpf( float x, float x_i, float x_f, float y_i, float y_f ) {
  float x_r = x_f - x_i;
  float x_n = ( x - x_i ) / x_r;
  float y_r = y_f - y_i;
  float y   = x_n;
  return y_r * y + y_i;
}

int main( void ) {
  { // do an image with a chart
    const int width = 32, height = 24, n_channels = 3;
    struct image_t image = image_alloc( width, height, n_channels );
    assert( image.data );
    const uint32_t background_rgba = 0xF0F0F0FF;
    const uint32_t axis_rgba       = 0x404040FF;
    const uint32_t plot_point_rgba = 0x000000FF;
    const uint32_t plot_line_rgba  = 0x8888DDFF;
    int plot_x[4]                  = { 3, 13, 23, 28 };
    int plot_y[4]                  = { 18, 11, 3, 8 };

    // clear image and draw axes
    image_clear( &image, background_rgba );
    image_draw_line( &image, 1, height - 2, width - 2, height - 2, axis_rgba );
    image_draw_line( &image, 1, 1, 1, height - 2, axis_rgba );
    // draw plot lines and points
    for ( int i = 0; i < 3; i++ ) { image_draw_line( &image, plot_x[i], plot_y[i], plot_x[i + 1], plot_y[i + 1], plot_line_rgba ); }
    for ( int i = 0; i < 4; i++ ) { image_draw_pixel( &image, plot_x[i], plot_y[i], plot_point_rgba ); }

    image_write_binary_ppm( "out.ppm", image );
    image_free( &image );
  }
  { // draw a rainbow image
    const int width = 1024, height = 64, n_channels = 3;
    struct image_t image = image_alloc( width, height, n_channels );
    for ( int y = 0; y < height; y++ ) {
      for ( int x = 0; x < width; x++ ) {
        float t       = (float)x / (float)width;
        float r       = t < 0.5f ? lerpf( t, 0.0f, 0.5f, 1.0f, 0.0f ) : 0.0f;
        float g       = t < 0.5f ? lerpf( t, 0.0f, 0.5f, 0.0f, 1.0f ) : lerpf( t, 0.5f, 1.0f, 1.0f, 0.0f );
        float b       = t < 0.5f ? 0.0f : lerpf( t, 0.5f, 1.0f, 0.0f, 1.0f );
        uint32_t rgba = rgba_to_hex( r * 255.0f, g * 255.0f, b * 255.0f, 0xFF );
        image_draw_pixel( &image, x, y, rgba );
      }
    }
    image_write_binary_ppm( "out2.ppm", image );
    image_free( &image );
  }
  return 0;
}

