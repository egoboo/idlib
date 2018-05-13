# Idlib

Idlib is a C++17 cross-platform utility library for Windows, Linux, and OS X.
Idlib and is made available publicly under the
[MIT license](https://github.com/primordialmachine/idlib/blob/master/LICENSE.md)
on
[Github](https://github.com/primordialmachine/idlib).

The library was built and used under Windows/Visual Studio 2017, Linux/GCC 6, Linux/Clang, and OS X/Clang.

Visit the
[![Idlib Gitter channel](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/primordialmachine/primordialmachine?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
for more information.

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

Download or checkout the source code from https://primordialmachine.com/idlib/.
See below for build instructions for some of the individual environments.

* [Windows 10/Visual Studio Community 2017](documentation/building-under-windows-10-visual-studio-community-2017.md)
* [Windows 10/Cygwin](documentation/building-under-windows-10-cygwin.md)
* [Linux/GCC](documentation/building-under-linux-gcc.md)
* [Linux/Clang](documentation/building-under-linux-clang.md)
* [OS X/Clang](documentation/building-under-os-x-clang.md)

### Continuous Integrations Status Maxtrix

|              | master                                                                                                                                                                        | develop                                                                                                                                                                           |
| ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Travis**   | [![Build Status](https://travis-ci.org/primordialmachine/idlib.svg?branch=master)](https://travis-ci.org/primordialmachine/idlib)                                             | [![Build Status](https://travis-ci.org/primordialmachine/idlib.svg?branch=develop)](https://travis-ci.org/primordialmachine/idlib)                                                |
| **AppVeyor** | [![Build status](https://ci.appveyor.com/api/projects/status/nnj5lfdfatgs096l/branch/master?svg=true)](https://ci.appveyor.com/project/primordialmachine/idlib/branch/master) | [![Build status](https://ci.appveyor.com/api/projects/status/nnj5lfdfatgs096l/branch/develop?svg=true)](https://ci.appveyor.com/project/primordialmachine/idlib/branch/develop)   |
