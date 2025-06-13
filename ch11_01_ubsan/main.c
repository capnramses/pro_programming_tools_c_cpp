/* This is a simple program with memory errors to find with Clang's UBSan.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp

Compile:
  clang -fsanitize=undefined main.c
Run:
  ./a.out
*/

#include <stdio.h>

int main( void ) {
  int b = -1;
  b     = b << 1; // shift a negative number
  printf( "b = %i\n", b );

  int c = 1 << 32; // 1 is cast to a 32-bit integer
  printf( "c = %i\n", c );
  return 0;
}
