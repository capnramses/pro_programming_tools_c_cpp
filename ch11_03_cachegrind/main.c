/* Example of a program to run Cachegrind over for cache hit/miss optimisation and branch prediction analysis.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp

Example based on https://github.com/perfanov/CacheMissExample/blob/master/cacheprofiler/cacheprofiler.cpp

Objective: to compare 3 different memory allocations for their relationship to performance and cache misses.

Compile:
  gcc -g -O3 main.c

Run:
  ./a.out 0   - accessing heap memory in sequential order
  ./a.out 1   - accessing heap memory in sequential order via pointers
  ./a.out 2   - accessing heap memory in random order via pointers

* You could add timers around the work section to get empirical measurements.

Valgrind Cachegrind:
  valgrind --tool=cachegrind  /a.out 0
  valgrind --tool=cachegrind ./a.out 1
  valgrind --tool=cachegrind ./a.out 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main( int argc, char** argv ) {
  uint32_t** ptrs = NULL;
  uint32_t* data  = NULL;

  if ( argc < 2 ) {
    printf( "usage: %s [mode]\nwhere mode is one of\n  0 - sequential array\n  1 - sequential pointers\n  2 - random access pointers\n", argv[0] );
    return 0;
  }
  int mode = atoi( argv[1] );
  if ( mode < 0 || mode > 2 ) {
    printf( "invalid mode number\n" );
    return 1;
  }
  printf( "mode is %i\n", mode );

  int count = 1024 * 1024 * 64;
  data      = malloc( count * sizeof( uint32_t ) );
  if ( !data ) { return 1; }

  // set up pointers and data
  ptrs = malloc( count * sizeof( uint32_t* ) );
  if ( !ptrs ) { return 1; }
  for ( int i = 0; i < count; i++ ) {
    data[i] = rand() % 255;
    ptrs[i] = &data[i];
  }
  // shuffle for random mode
  if ( 2 == mode ) {
    for ( int i = 0; i < count; i++ ) {
      int n         = rand() % count;
      uint32_t* tmp = ptrs[i];
      ptrs[i]       = ptrs[n];
      ptrs[n]       = tmp;
    }
  }

  // do the memory access work
  {
    int sum = 0;

    if ( 0 == mode ) {
      for ( int i = 0; i < count; i++ ) { sum += data[i]; }
    } else {
      for ( int i = 0; i < count; i++ ) { sum += *ptrs[i]; }
    }

    printf( "sum = %u\n", sum );
  }

  free( ptrs );
  free( data );

  return 0;
}
