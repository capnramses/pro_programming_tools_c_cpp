/* Example for running LLVM's scan-build on.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/

#include <stdio.h>

int main() {
  int array[3] = { 10, 11, 12 };
  printf( "array[4] = %i\n", array[4] );
  return 0;
}
