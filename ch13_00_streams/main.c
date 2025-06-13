/*
This program demonstrates use of 3 streams
* reads from stdin
* writes to stdout
* writes to stderr

Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp

Compile (Note: not readily portable to Windows due to use of unistd.h)
  gcc main.c

To Run:
  ./a.out

This program is similar to the `cat` command

* When run it will wait for input from stdin.

(1) You can type something in and when done hit CTRL+D to add 'end of file' to the stream.

Example input:
  "Hello it's Anton"
  CTRL+D

(2) Or you can pipe something in to the stream eg.
  cat test_data.txt | ./a.out

The `cat` program will write the contents of `test_data.txt` to stdout,
and the pipe `|` directs this to the stdin of ./a.out

(3) You can further redirect the stdout and stderr of ./a.out to files or pipe again to other programs.
  cat test_data.txt | ./a.out > stdout.txt 2> stderr.txt
  cat test_data.txt | ./a.out | cat
*/

#include <stdio.h>  // for printf() and size_t
#include <unistd.h> // for read(). not portable to Windows
#include <stdlib.h> // for malloc()
#include <stdint.h> // for uint8_t
#include <string.h> // for memcpy()

int main( void ) {
  printf( "test line to stdout\n" );
  fprintf( stderr, "test line to stderr\n" );
  printf( "this program reads from stdin. either type something in or pipe something in from another command.\n" );

  size_t blob_capacity           = 1024 * 1024; // start at 1MB
  const size_t blob_extension_sz = 1024 * 1024; // extend by 1MB at a time
  size_t blob_data_read_sz       = 0;           // number of bytes actually copied into blob
  uint8_t* blob                  = malloc( blob_capacity );
  if ( !blob ) {
    fprintf( stderr, "malloc error\n" );
    return 1;
  }

  /* read stdin in small chunks until there's nothing left in the stream */
  {
    int fd                      = fileno( stdin );
    const size_t chunk_capacity = 1024 * 1024; // try to read 1MB at a time
    size_t count                = chunk_capacity;

    uint8_t* chunk = malloc( count );
    if ( !chunk ) {
      fprintf( stderr, "malloc error\n" );
      return 1;
    }
    ssize_t chunk_read_sz = 0;
    do {
      chunk_read_sz = read( fd, chunk, count );

      // if blob is oversized then extend it
      if ( blob_data_read_sz + chunk_read_sz > blob_capacity ) {
        blob_capacity += blob_extension_sz;
        blob = realloc( blob, blob_capacity );
        if ( !blob ) {
          fprintf( stderr, "ERROR: failed to reallocate memory\n" );
          return 1;
        }
      }

      // copy the chunk read into the big blob buffer
      memcpy( blob + blob_data_read_sz, chunk, chunk_read_sz );
      blob_data_read_sz += chunk_read_sz;
    } while ( chunk_read_sz > 0 );
    free( chunk );
  }

  /* repeat writing data to stdout until whole buffer is written */
  {
    int fd           = fileno( stdout ); // stdout
    size_t n_written = 0;

    for ( size_t offset = 0; blob_data_read_sz > 0; blob_data_read_sz -= n_written, offset += n_written ) {
      n_written = write( fd, blob + offset, blob_data_read_sz );
      if ( n_written == 0 ) {
        fprintf( stderr, "ERROR: writing to stdout\n" );
        return 1;
      }
    }
  }

  free( blob );

  return 0;
}
