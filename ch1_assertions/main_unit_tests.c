/*
Example of a C program that uses assertions for unit tests.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/
#include <assert.h>

/* trivial function to add two integers */
int my_adder( int a, int b ) { return a + b; }

void run_tests() {
  int a_inputs[3]         = { 0, 100, -100 };
  int b_inputs[3]         = { 0, -200, 200 };
  int expected_outputs[3] = { 0, -100, 100 };
  for ( int i = 0; i < 3; i++ ) {
    int result = my_adder( a_inputs[i], b_inputs[i] );
    assert( expected_outputs[i] == result );
  }
}

int main() {
  run_tests();
  return 0;
}