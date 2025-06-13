/*
Example of a C program that reads an entire binary file into memory.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file_record_t {
  void* data;
  size_t sz;
};

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

int main( void ) {
  struct file_record_t record = read_file( "in.ppm" );
  if ( !record.data ) {
    fprintf( stderr, "ERROR: reading file `in.ppm`\n" );
    return 1;
  }
  printf( "put entire file `in.ppm` in memory. %u bytes. data %p\n", (unsigned int)record.sz, (void*)record.data );
  return 0;
}
