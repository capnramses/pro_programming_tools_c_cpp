/* Example of a C program hat links against a shared object (dynamic) library
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp

To create a dynamic library and set up linking with relative path to the lib:

on linux execute:
  ./build_linux.sh
on OS X execute:
  ./build_osx.sh
on Windows with GCC execute:
  ./build_windows_gcc.bat

Scripts have been created containing various alternative options for linking libraries described in the text.
Read through scripts to see commands used. eg
  more ./build_osx.h

for building with IDEs:
* follow the IDE's wizard for creating a shared/dynamic library project,
* drag second.c and second.h into the source tree,
* build the library,
* then create another project,
* drag main.c into the source tree,
* and add the shared library to the project's list of libraries to link against
*/

#include "second.h" // copy in declarations of functions from second.c
#include <stdio.h>

int main() {
  printf( "hi from main()!\n" );
  second();

  return 0;
}
