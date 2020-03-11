/* Example for running LLVM's clang-tidy on.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp

File with a few issues that clang-tidy or scan-build should pick up

Compile:
  clang main.c

Lint:
  clang-tidy main.c
*/
#include <stdio.h>

int main() {
  int x = 10;
  int y = 0;

  // division by zero
  int z = x / y;
  printf( "z = %i\n", z );

  // array bounds
  int my_array[3] = { 10, 20, 30 };
  printf( "my_array[3] = %i\n", my_array[3] );

  return 0;
}
