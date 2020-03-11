/*
Some helper functions for editing images in memory.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/

#pragma once /* "only include this file once" - should work on all C and C++ compilers now in place of header guards */

#include <stdint.h> /* so i can use uint8_t and uint32_t types in the interface */

/* struct to represent an image in memory for eg editing */
struct image_t {
  int width, height, n_channels;
  uint8_t* data; /* tightly-packed pixel data ( no padding bytes ) */
};

/* converts 4 individual colour channel bytes into a 32-bit colour code eg 127,0,0,255 returns 0x7F0000FF */
uint32_t rgba_to_hex( uint8_t r, uint8_t g, uint8_t b, uint8_t a );

/* converts a 4-channel colour code eg 0x7F0000F into separate bytes for the 4 channels */
void hex_to_rgba( uint32_t rgba, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a );

/* returns an image_t struct with zeroed memory allocated for usage */
struct image_t image_alloc( int width, int height, int n_channels );

/* deallocates and zeroes an image_t struct */
void image_free( struct image_t* image );

/* wipe the image to a specified colour */
void image_clear( struct image_t* image, uint32_t rgba );

/* colours a pixel at (x,y) in image from 1-byte-per-channel code eg 0x11223344 for red=0x11, green=0x22, blue=0x33, alpha=0x44
if the image has less than 4 channels the trailing bytes are ignored */
void image_draw_pixel( struct image_t* image, int x, int y, uint32_t rgba );

/* draws a line of colour rgba in image from (x0,y0) to (x1,y1) using Bresenham's line algorithm */
void image_draw_line( struct image_t* image, int x0, int y0, int x1, int y1, uint32_t rgba );

/* returns RGBA colour, 1 byte per channel, as eg 0x11223344 for red=0x11, green=0x22, blue=0x33, alpha=0x44 */
uint32_t image_get_pixel( struct image_t image, int x, int y );

/* output an image as a binary PPM P6 file. most image viewers and editors should know this format eg GIMP */
void image_write_binary_ppm( const char* filename, struct image_t image );
