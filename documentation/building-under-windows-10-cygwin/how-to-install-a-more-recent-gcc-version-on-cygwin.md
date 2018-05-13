# How to install a more recent GCC version on Cygwin

Cygwin usually ships with a very outdated version of GCC.
However, to compile Idlib, GCC 6.4.0 or higher is required.
To compile and install this  version of GCC on Cygwin, open the Cygwin terminal and enter the following commands
```
C:\cygwin64>setup-x86_64.exe -q -P wget -P gcc-g++ -P make -P diffutils -P libmpfr-devel -P libgmp-devel -P libmpc-devel
wget http://ftp.halifax.rwth-aachen.de/gnu/gcc/gcc-6.4.0/gcc-6.4.0.tar.gz
tar xf gcc-6.4.0.tar.gz
mkdir build-gcc
cd build-gcc
../gcc-6.4.0/configure --program-suffix=-6.4.0 --enable-languages=c,c++ --disable-bootstrap --disable-shared
make -j4
make install
```
