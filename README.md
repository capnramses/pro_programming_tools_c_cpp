# Professional Programming Tools for C and C++: Example Code

Code samples from the book *Professional Programming Tools for C and C++* by Anton Gerdelan and Katja Žibrek.

## Repository Structure

This repository is split into folders, named after the corresponding book chapter.
Code snippets from each chapter are put into a stand-alone program with a `main()` function. The first example in each
chapter is called `main.c`. For further snippets, additional stand-alone programs are found in `main2.c`, `main3.c`, etc.
Only a few specific examples comprise more than one file per program, and compilation for those is described in the book text.

## How to Compile and Run Examples

Use any compiler of your choice to build a sample. For example, to build the first assertions example with GCC and run it from a terminal:

```
$ cd ch1_assertions
$ gcc -o my_program main.c
$ ./my_program
```

In Visual Studio create a new project and drag the appropriate `.c` file into your source code tree before building.

Some examples require command line arguments to run, such as the file name of an image to open.
Read the comments in each source code file for instructions.

## License

Please refer to LICENSE.txt.