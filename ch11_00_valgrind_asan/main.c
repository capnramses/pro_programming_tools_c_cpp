/* This is a simple program with memory errors to find with Valgrind or Clang's ASan.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp

this code can be checked with various tools

Valgrind:
  gcc main.c -g
  valgrind --leak-check=yes ./a.out

ASan:
  clang main.c -fsanitize=address
  ./a.out
*/

#include <stdlib.h>

void my_func( void ) {
  int* x = malloc( 16 * sizeof( int ) );
  x[16]  = 0; // out of bounds of memory ( heap overrun )
              // memory is not freed
}

int main( void ) {
  my_func();
  return 0;
}
