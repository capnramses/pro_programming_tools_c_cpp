/*
Example of a trivial C++ program that allocates memory.
C++ with output streams and new/delete
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/
#include <iostream> // contains cout and cerr

int main( void ) {
  int* my_pointer = new int[16];
  if ( !my_pointer ) {                                           // if malloc() returned NULL then something went wrong
    std::cerr << "ERROR: memory allocation failed" << std::endl; // print to standard error output stream
    return 1;                                                    // exit program with error code 1
  }
  std::cout << "allocated " << 16 * sizeof( int ) << " bytes, starting at address " << my_pointer << std::endl;
  delete[] my_pointer;
  return 0;
}
