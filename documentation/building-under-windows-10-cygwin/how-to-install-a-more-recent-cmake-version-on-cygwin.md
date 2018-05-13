# How to install a more recent CMake version on Cygwin

Cygwin usually ships with a very outdated version of CMake.
However, to compile Idlib, CMake 3.10.1 or higher is required.
To compile and install this  version of CMake on Cygwin, open the Cygwin terminal and enter the following commands
```
wget https://cmake.org/files/v3.10/cmake-3.10.1.tar.gz
tar -xzf cmake-3.10.1.tar.gz
cd cmake-3.10.1
./configure --system-curl
make all
make install
```
