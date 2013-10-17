# [ivl2](https://github.com/iavr/ivl2)

ivl2 is an effort to re-implement C++ template library [ivl](http://image.ntua.gr/ivl/) in C++11. We refer to ivl2 as ivl in the sequel.

The library is currently at its very early stage of development. There is no website, release, installation or documentation yet. The only available information on the project is currently restricted to this file.

### Licence

ivl has a dual LGPLv3 + GPLv2 license. See file LICENSE for the complete license text; further explanations are provided [here](http://image.ntua.gr/ivl/license.php).

### Directory structure

ivl constists primarily of template C++ header-only code. Non-header code refers only to test code, samples, help (documentation), or modules that will appear in the future. The current structure is:

	/doc        documentation: currently only license files
	/include    complete header-only (.hpp) source code
	/run        simple scripts to compile and execute
	/test       primitive test code (.cpp)

Code under folder /test is only used for development, testing and debugging. It is subject to major updates or complete removal in the future.

### Requirements

ivl uses C++11 features available in implementations only recently; for this reason it is only supported by [g++ 4.8.1](http://gcc.gnu.org/gcc-4.8/) or later and [clang 3.3](http://llvm.org/releases/download.html#3.3) or later. Clang is only supported with [libc++](http://libcxx.llvm.org/), its own implementation of the C++ standard library.

### Building

There is no Makefile or project file provided. The bash scripts under folder `/run` are the simplest way to compile and run a program using ivl. Script `/run/ivl` is for g++ and `/run/livl` for clang. It is best to copy them in a folder in your path, e.g. `/usr/local/bin`, after adjusting folders for your local copy of ivl and libc++ location. In this case,

	cd test/main/
	ivl test

compiles file `/test/main/test.cpp`, produces binary `/test/main/test`, and executes it unless there are compiler or linker errors.

Extension `.cpp` is not necessary for the main source file. Additional source files or compiler options may be specified as additional command-line arguments, but extensions are needed for extra source files.

*Good luck!*
