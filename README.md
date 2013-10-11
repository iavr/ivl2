ivl2 is an effort to re-implement C++ template library ivl

	http://image.ntua.gr/ivl/

in C++11.

ivl2 is currently at its very early stage of development. There is no website, release, installation or documentation yet, but it has the same licence as ivl:

	http://image.ntua.gr/ivl/license.php

More specifically, its license is dual LGPL3 + GPL2. The full license text is as follows.

-----------------------------------------------------------------------

ivl is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License
version 3 as published by the Free Software Foundation.

Alternatively, you can redistribute it and/or modify it under the terms
of the GNU General Public License version 2 as published by the Free
Software Foundation.

ivl is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

-----------------------------------------------------------------------

ivl2 constists primarily of template C++ header-only code. Non-header code refers only to test code, samples, help (documentation), or modules that will appear in the future. The current structure is:

	/include    complete header-only (.hpp) source code
	/run        simple scripts to compile and execute
	/test       primitive test code (.cpp)

Code under folder /test is only used for development, testing and debugging. It is subject to major updates or complete removal in the future.

ivl2 uses C++11 features available in implementations only recently; for this reason it is only supported by g++ 4.8.1 or later and clang 3.3 or later. Clang is only supported with libc++, its own implementation of the C++ standrd library:

	http://libcxx.llvm.org/

There are no Makefile's or project files provided. The scripts under folder /run are the simplest way to compile and run a program using ivl2. Script run/ivl is for g++ and run/livl for clang. It is best to copy them in a folder in your path, e.g. /usr/local/bin, after adjusting folders for your local copy of ivl2 and libc++ location. In this case,

	cd test/main/
	ivl test

compiles file test/main/test.cpp, produces binary test/main/test, and executes it unless there are compiler or linker errors.

Note that extension .cpp is not necessary for the source file; it may or may not be provided. Additional source files or compiler options may be specified as additional command-line arguments, but these extra source files need extensions.

Good luck!
