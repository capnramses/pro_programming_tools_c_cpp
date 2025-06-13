/* Example of a C program that builds using a Makefile
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
Compile:
  make
*/

#include "two.h" // copy in declarations of functions from second.c
#include <stdio.h>

int main( void ) {
  printf( "hi from main()!\n" );
  two();

  return 0;
}
