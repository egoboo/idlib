# Idlib

Idlib is a C++17 cross-platform utility library for Windows, Linux, and OS X.
Idlib and is made available publicly under the
[MIT license](https://github.com/egoboo/idlib/blob/master/LICENSE.md)
on
[Github](https://github.com/egoboo/idlib).

The library was built and used under Windows/Visual Studio 2017, Linux/GCC 6, Linux/Clang, and OS X/Clang.

### Featurette

* CMake-based build system
   builds under Windows/Visual Studio, Cygwin/GCC, Linux/GCC and OS X/Clang
* Google Test integration for Visual Studio
* math
	* generic vectors of arbitrary dimensions for all floating-point types
	* generic matrices of arbitrary number of rows and columns for all floating-point types
	* generic geometric primitives (points, lines, rays, aabbs, …) of arbitrary dimensions for all floating-point types
	* translation transformations of geometric primitives
	* coming soon:
		* full support for all standard transformations (scale, shear, rotation, …)
		* viewing and projection transformations (“look at”, “perspective projection”, orthographic projection”)
	* colors RGB and RGBA colors for all floating-point types and for Bytes
	* file system abstraction on Windows,  Linux, OS X
	* reading and writing files using memory mappings
	* creating/copying/deleting files and directories
	* enumerating directory contents
	* obtaining file system information (e.g. application data directories)
* Byte-order detection and conversion
* parsing template-metafunction parser-builder for Parsing Expression Grammars
* signals and slots type-safe signals-slots
* misc. C++ utilities
	* transform iterators
	* singletons with sub-typing
	* iterator ranges
	* sub-range values
	* …

### Build instructions

Checkout the source code from https://github.com/egoboo/idlib by
```
git clone https://github.com/egoboo/idlib 
git submdoule init
git submodule update
```
See below for build instructions for some of the individual environments.

* [Windows 11/Visual Studio Community 2022](documentation/building-under-windows-11-visual-studio-community-2022.md)
* [Windows 10/Cygwin](documentation/building-under-windows-10-cygwin.md)
* [Linux/GCC](documentation/building-under-linux-gcc.md)
* [Linux/Clang](documentation/building-under-linux-clang.md)
* [OS X/Clang](documentation/building-under-os-x-clang.md)

Only Windows 11/Visual Studio Community 2022 environment is officially supported due to a lack of maintainers for the other environments.

### Continuous Integrations Status Maxtrix

|              | master                                                                                                                                                                        | develop                                                                                                                                                                           |
| ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Travis**   | [![Build Status](https://travis-ci.org/primordialmachine/idlib.svg?branch=master)](https://travis-ci.org/primordialmachine/idlib)                                             | [![Build Status](https://travis-ci.org/primordialmachine/idlib.svg?branch=develop)](https://travis-ci.org/primordialmachine/idlib)                                                |
| **AppVeyor** | [![Build status](https://ci.appveyor.com/api/projects/status/vmwpjyqlsv2uqihi/branch/master?svg=true)](https://ci.appveyor.com/michaelheilmann/idlib/branch/master)           | [![Build status](https://ci.appveyor.com/api/projects/status/vmwpjyqlsv2uqihi/branch/develop?svg=true)](https://ci.appveyor.com/michaelheilmann/idlib/branch/develop)   |
