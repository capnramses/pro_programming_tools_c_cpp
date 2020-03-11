/* Example of a C program with more than 1 source file
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp

Compile with:
  gcc main.c second.c
*/

#include "second.h" // copy in declarations of functions from second.c
#include <stdio.h>

int main() {
  printf( "hi from main()!\n" );
  second();

  return 0;
}
