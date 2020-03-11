/*
Example of a C program that reads a file from memory and casts it to a struct pointer.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define FILE_IN "in.bmp"

struct file_record_t {
  void* data;
  size_t sz;
};

// the preprocessor directives disable struct padding for the included struct.
// try removing these from similar structs and running the program - the variables may no longer align to the matching memory from the file.
#pragma pack( push, 1 )
struct bmp_file_header_t {
  char file_type[2];
  uint32_t file_sz;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t image_data_offset;
};
#pragma pack( pop )

struct file_record_t read_file( const char* filename ) {
  struct file_record_t record;
  memset( &record, 0, sizeof( struct file_record_t ) );

  FILE* fp = fopen( filename, "rb" );
  if ( !fp ) { return record; }
  fseek( fp, 0L, SEEK_END );
  record.sz   = (size_t)ftell( fp );
  record.data = malloc( record.sz );
  rewind( fp );
  fread( record.data, record.sz, 1, fp );
  fclose( fp );

  return record;
}

int main() {
  struct file_record_t record = read_file( FILE_IN );
  if ( !record.data ) {
    fprintf( stderr, "ERROR: reading file `%s`\n", FILE_IN );
    return 1;
  }
  printf( "File %s blob was read into %u bytes\n", FILE_IN, (uint32_t)record.sz );
  { // retrieve variables from file header
    struct bmp_file_header_t* file_header_ptr = (struct bmp_file_header_t*)record.data;
    printf( "BMP file header is %u bytes\n", ( uint32_t )( sizeof( struct bmp_file_header_t ) ) );
    printf( " |_file_type         = %c%c\n", file_header_ptr->file_type[0], file_header_ptr->file_type[1] );
    printf( " |_file_sz           = %u\n", (uint32_t)file_header_ptr->file_sz );
    printf( " |_reserved1         = %u\n", (uint32_t)file_header_ptr->reserved1 );
    printf( " |_reserved2         = %u\n", (uint32_t)file_header_ptr->reserved2 );
    printf( " |_image_data_offset = %u\n", (uint32_t)file_header_ptr->image_data_offset );
  }

  return 0;
}
