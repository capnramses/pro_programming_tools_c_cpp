/* Example of a C program that builds using CMake
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
Compile:
After installing CMake, use the cmake-gui program to build a project file for your IDE
or on the command line:
mkdir build
cd build
cmake ..
cmake --build .
*/

#include "two.h" // copy in declarations of functions from second.c
#include <stdio.h>

int main() {
  printf( "hi from main()!\n" );
  two();

  return 0;
}
