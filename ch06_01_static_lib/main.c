/* Example of a C program hat links against a static library
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp

To create a static lib from second.c
  gcc -c second.c -o second.o
  ar cr libsecond.a second.o

Compiles a program with
  gcc main.c libsecond.a
*/

#include "second.h" // copy in declarations of functions from second.c
#include <stdio.h>

int main( void ) {
	printf( "hi from main()!\n" );
	second();

	return 0;
}
