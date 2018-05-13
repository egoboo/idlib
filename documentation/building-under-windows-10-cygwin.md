# Building under Windows/Cygwin

Cygwin usually ships with a very outdated version of CMake and GCC.
However, to compile Idlib, CMake 3.10.1 or higher and GCC 6.4.0 or higher are required.
Follow
[this guide](building-under-windows-10-cygwin/how-to-install-a-more-recent-cmake-version-on-cygwin.md)
to install/update CMake on Cygwin
and
[this guide](building-under-windows-10-cygwin/how-to-install-a-more-recent-gcc-version-on-cygwin.md)
to install/update GCC on Cygwin.

To compile Idlib, open a Cygwin console, change to the directory in which the source of the library is located in, and enter
```
cmake CMakeLists.txt
make all
```

To execute the unit tests, enter
```
make check
```
