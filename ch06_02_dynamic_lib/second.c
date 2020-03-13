/* Example of a C program hat links against a library
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/
#include "second.h" // include any symbol 'export' from the declarations
#include <stdio.h>

void second() {
	printf( "Hi, from second.c!\n" );
}
