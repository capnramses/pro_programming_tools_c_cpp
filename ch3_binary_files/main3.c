/*
Example of a C program that reads an entire binary file and casts to a pointer representing a Windows BMP header.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack( push, 1 ) // pack byte-by-byte ... no padding
struct bmp_file_header {
  char file_type[2]; // ‘char’ -> we expect ASCII characters
  uint32_t file_sz;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t image_data_offset;
};
#pragma pack( pop ) // revert to default byte-alignment

struct file_record {
  void* data;
  size_t sz;
};

struct file_record read_file( const char* filename ) {
  struct file_record record;
  memset( &record, 0, sizeof( struct file_record ) );

  FILE* fp = fopen( filename, "rb" );     // 'read binary'
  if ( !fp ) { return record; }           // error opening file
  fseek( fp, 0L, SEEK_END );              // jump to end-of-file (EOF)
  record.sz   = (size_t)ftell( fp );      // byte position gives length
  record.data = malloc( record.sz );      //
  rewind( fp );                           // jump back to start
  fread( record.data, record.sz, 1, fp ); // should return 1
  fclose( fp );
  return record;
}

int main( int argc, char** argv ) {
  if ( argc < 2 ) {
    printf( "Usage: Give a file to open as the first argument to this program (or drag an image file onto the binary)\n" );
    return 0;
  }
  printf( "opening file `%s`\n", argv[1] );
  struct file_record record = read_file( argv[1] );

  // cast to PPM struct pointer
  struct bmp_file_header* file_header_ptr = (struct bmp_file_header*)record.data;
  {
    printf( "file type: %c%c\n", file_header_ptr->file_type[0], file_header_ptr->file_type[1] );
    printf( "file size: %u bytes\n", file_header_ptr->file_sz );
    printf( "img data byte offset: %u\n", file_header_ptr->image_data_offset );
  }
  if ( file_header_ptr->file_type[0] != 'B' || file_header_ptr->file_type[1] != 'M' ) {
    fprintf( stderr, "ERROR: file `%s` is not a Windows BMP\n", argv[1] );
    free( record.data );
    return 1;
  }
  free( record.data );
  return 0;
}
