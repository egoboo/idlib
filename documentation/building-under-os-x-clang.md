# Building under OS X/CLANG

Ensure CMake 3.10.1 and CLANG 4.0 or higher are installed.
To compile Idlib, open a console, change to the directory in which the source of the library is located in, and enter
```
cmake CMakeLists.txt
make all
```
To execute the unit tests, enter
```
make check
```
