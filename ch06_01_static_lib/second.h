/* Example of a C program hat links against a library
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/

#ifndef SECOND_H_
#define SECOND_H_

/* Make sure a C++ compiler treats these C function names as C symbols. */
#ifdef __cplusplus
extern "C" {
#endif

void second();

#ifdef __cplusplus
}
#endif

#endif // you can replace all three #...  with just `#pragma once` at the top
