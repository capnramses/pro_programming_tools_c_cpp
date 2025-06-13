/* Example of a C program that can be profiled with Gprof
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp

To compile:
  gcc -pg -g main.c -o my_program

To run:
  ./my_program

To tabulate profiling results after running:
  gprof ./my_program gmon.out > results.txt
*/

#include <stdio.h>

void great_greatchild() {
  for ( int i = 0; i < 0x10000000; i++ ) { ; }
}

void grandchild() {
  for ( int i = 0; i < 0x1000000; i++ ) { ; }
  great_greatchild();
}

void child() {
  for ( int i = 0; i < 0x100000; i++ ) { ; }
  grandchild();
}

void parent() {
  for ( int i = 0; i < 0x1000; i++ ) { ; }
  child();
}

int main( void ) {
  parent();

  return 0;
}
