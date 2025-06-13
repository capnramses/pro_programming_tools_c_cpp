/*
Example of a trivial C++ program that allocates memory.
C++ with C-style printf() and memory allocation.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/
#include <cstdio>  /* contains printf() */
#include <cstdlib> /* contains malloc() and free() */

int main( void ) {
  int* my_pointer = (int*)malloc( 16 * sizeof( int ) );     // C++ requires a cast on the return type of malloc()
  if ( !my_pointer ) {                                      // if malloc() returned NULL then something went wrong
    fprintf( stderr, "ERROR: memory allocation failed\n" ); // print to standard error output stream
    return 1;                                               // exit program with error code 1
  }
  printf( "allocated %u bytes, starting at address %p\n", (int)( 16 * sizeof( int ) ), (void*)my_pointer );
  free( my_pointer );
  return 0;
}
