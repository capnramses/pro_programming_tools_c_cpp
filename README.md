# Professional Programming Tools for C and C++: Example Code

![](https://github.com/capnramses/pro_programming_tools_c_cpp/workflows/build_all/badge.svg)

> [!NOTE]\
> Code samples from the book *Professional Programming Tools for C and C++* by Anton Gerdelan and Katja Žibrek.
> The book information page is at [http://antongerdelan.net/pro_programming_tools_book/](http://antongerdelan.net/pro_programming_tools_book/).

## How to use this Repository

* This repository is split into folders, one for each code example.
* Folders are numbered after the corresponding book chapter, and then by order of appearance within the chapter.
* Code snippets from each chapter are put into a stand-alone program with a `main()` function.
* Most examples comprise just a single file called `main.c` and should be straight-forward to compile with any compiler.
Some examples have a `main.cpp` and should be compiled with a C++ compiler.
* Some examples require command line arguments to run, such as the file name of an image to open.
* See comments at the top of source code for further compilation and running instructions.

For example, to build the first assertions example with GCC and run it from a terminal:

```
cd ch01_00_assertions
gcc -o my_program main.c
./my_program
```

For Microsoft Visual Studio:

* Create a new, empty, C++ **console** (not Desktop) project.
* Drag the appropriate `.c` files into your source code tree before building.
* When compiling, Visual Studio will prompt you to switch to its safer versions of some functions, or disable the warning.

## License

Please refer to `LICENSE.txt`.

> This is free and unencumbered software released into the public domain.
> 
> Anyone is free to copy, modify, publish, use, compile, sell, or
> distribute this software, either in source code form or as a compiled
> binary, for any purpose, commercial or non-commercial, and by any
> means.
> 
> In jurisdictions that recognize copyright laws, the author or authors
> of this software dedicate any and all copyright interest in the
> software to the public domain. We make this dedication for the benefit
> of the public at large and to the detriment of our heirs and
> successors. We intend this dedication to be an overt act of
> relinquishment in perpetuity of all present and future rights to this
> software under copyright law.
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
> EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
> MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
> IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
> OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
> ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
> OTHER DEALINGS IN THE SOFTWARE.
> 
> For more information, please refer to <https://unlicense.org>

## Help, Questions, Bug Reports

Please feel free to use the [Issues](https://github.com/capnramses/pro_programming_tools_c_cpp/issues) tab on this GitHub project to ask for help or to report bugs. If frequent questions pop up we will create a FAQ section on this README.

## Contributions and Pull Requests

Please feel encouraged to make a pull request (PR) to correct or clarify code.

Some rough guidelines for making a PR:

* Bug fixes and operating-system specific fixes are very welcome.
* When making a PR please make sure both the PR, and the code, is commented clearly for other book readers.
* Do not introduce code copy-pasted from elsewhere as there are licensing and copyright issues with this.
* Please do not submit `CMakeLists.txt` or build scripts for the entire book or for individual chapters. There is a specific chapter dedicated to introducing build systems.
* Please do not submit project or solution files for a particular IDE.
* Code in examples is copy-pasted from the book. If the PR needs to modify these please add a comment to those lines indicating why the change was important.
* Code style and language version changes are discouraged unless they fix a bug.
* If you are happy to be added to a contributors list then please add your name, as you would like it to appear, as a bullet at the bottom of this file.

## Contributors

* [Anton Gerdelan](https://github.com/capnramses) - Initial code.
