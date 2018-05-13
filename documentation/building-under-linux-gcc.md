# Building under Linux/GCC

Ensure CMake 3.10.1 and GCC 6.4 or higher are installed.
To compile Idlib, open a console, change to the directory in which the source of the library is located in, and enter
```
cmake CMakeLists.txt
make all
```
To execute the unit tests, enter
```
make check
```
