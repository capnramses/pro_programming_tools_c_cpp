/*
create a static library from this file. eg on linux:

ar cr libsecond.a second.c

*/

#include <stdio.h>

void second() {
	printf( "Hi, from second.c!\n" );
}
