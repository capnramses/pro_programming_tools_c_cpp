/*
Example of a C program that uses assertions.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/
#include <string.h>
#include <stdio.h>
#include <assert.h>

/*
Change a character in a string to the null terminator.
Asserts if out of bounds.
PARAMS
str       - A char array. Cannot be a NULL pointer.
str_len   - Maximum bytes allocated for length of str.
str_index - Byte index in str to change to `\0`.
*/
void my_str_truncate( char* str, int str_len, int str_index ) {
  // Abort program if str was NULL.
  assert( str && "str parameter was NULL" );
  // Abort if str_index was outside of allowed range
  assert( str_index >= 0 && str_index < str_len );

  str[str_index] = '\0';
}

deliberate error to see if CI works

int main() {
  char name[10];
  strncpy( name, "anton", 10 );
  int new_length = 3;                      // try changing to a number >= 10
  my_str_truncate( name, 10, new_length ); // try replacing name with NULL
  // should print "ant"
  printf( "truncated: %s\n", name );

  return 0;
}

