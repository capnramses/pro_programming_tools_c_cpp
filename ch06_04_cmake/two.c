/* Example of a C program that builds using CMake
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/
#include <stdio.h>
#include <math.h>

void two() {
  float p = powf( 2.0f, 32.0f );
  printf( "Hi, from two.c!\nThe biggest 32-bit number is ~%.0f\n", p );
}
