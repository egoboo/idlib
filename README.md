# Idlib

## Synopsis

C++ utility library.
Requires CMake 3.8.x.
Builds under GCC 6 or higher, CLANG 3.8 or higher, or Microsoft Visual Studio Community 2017.

## Building under Cygwin.
To compile Idlib, open a terminal, change to the directory in which this README.md file is found, and enter
```
cmake CMakeLists.txt
make all
```
To execute the unit tests, enter
```
make check
```
Cygwin usually ships with a very outdated version of CMake. However, to compile Idlib, CMake 3.10.1 or higher is required.
To update to this version, download the package `cmake-{version}.tar.gz` and compile and install it.
```
tar -xzf cmake-{version}.tar.gz
cd cmake-{version}
./configure
make all
make install
```
where `{version}` is the CMake version number which should be `3.10.1` or higher.

## License
Idlib is made available publicly under the
[MIT License](https://github.com/primordialmachine/idlib/blob/master/LICENSE).

### Contact
Developers can usually be found in the Primordial Machine Gitter channel:
[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/primordialmachine/primordialmachine?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)


### Continuous Integrations Status Maxtrix

|              | master                                                                                                                                                                        | develop                                                                                                                                                                           |
| ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Travis**   | [![Build Status](https://travis-ci.org/primordialmachine/idlib.svg?branch=master)](https://travis-ci.org/primordialmachine/idlib)                                             | [![Build Status](https://travis-ci.org/primordialmachine/idlib.svg?branch=develop)](https://travis-ci.org/primordialmachine/idlib)                                                |
| **AppVeyor** | [![Build status](https://ci.appveyor.com/api/projects/status/nnj5lfdfatgs096l/branch/master?svg=true)](https://ci.appveyor.com/project/primordialmachine/idlib/branch/master) | [![Build status](https://ci.appveyor.com/api/projects/status/nnj5lfdfatgs096l/branch/develop?svg=true)](https://ci.appveyor.com/project/primordialmachine/idlib/branch/develop)   |
