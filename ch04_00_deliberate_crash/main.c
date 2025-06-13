/*
Example of a C program that deliberately crashes.
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp

This program deliberately causes a segmentation fault crash by dereferencing a NULL pointer.
This is done inside a few functions so that there is a stack to print.

It can be used to test:
* Running in a debugger to get a back trace.
* Running normally, and getting a core dump that can be run in a debugger.

On Linux (not currently supported on Windows Subsystem for Linux),
to allow crashes to write a core dump you usually have to change the size limit from 0.

ulimit -c

If the output is 0 then no dump will be written. Change it.

ulimit -c unlimited

On OS X create a file /etc/launchd.conf containing echo "limit core unlimited" | sudo tee -a /etc/launchd.conf
Cores will be dumped to /cores/.

On Windows you can have Visual Studio's JIT (Just In Time) Debugging enabled in a program's build.
When a program crashes the user will see a dialogue with an option to launch Visual Studio.
This should take you to the crashed line, with a stack trace.
From there you can optionally output a minidump that can be sent to the developer to reproduce the crash.

Remember to delete core dumps when you're done to free space,
and/or consider disabling core dumps again when not testing software to prevent the disk filling.

Libraries such as Google's CrashPad (C++) can be used to write a mini dump file on crash, and send the
file to a server URL. Support varies across operating systems.

On all systems you can also intercept a SIGSEGV or SIGABRT signal and print or log the stack trace with
any user-specific system details and the program version or build date.
This could be automatically sent to a server using libcurl.
Getting the list of strings in the stack trace requires system-specific calls.
*/

#include <stdio.h>

int* ptr = NULL;

void function_that_crashed( void ) {
  int value = *ptr; // should crash here. dereferencing a null pointer.
  printf( "value %i\n", value );
}

void some_intermediate_function( void ) { function_that_crashed(); }

int main( void ) {
  some_intermediate_function();
  printf( "program finished normally\n" ); // you should see this in a terminal if program didn't crash
  return 0;
}
