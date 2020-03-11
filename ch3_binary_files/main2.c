/*
Example of a C program that reads an entire binary file.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file_record {
  void* data;
  size_t sz;
};
/* NOTE:
In the following C program we use `struct file_record` to refer to the type.
In C++ you can just use `file_record` to refer to the type.
To get this same shorthand in C declare the above struct as:

typedef struct file_record {
  void* data;
  size_t sz;
} file_record;
*/

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

  // do something with file data here

  free( record.data );
  return 0;
}
