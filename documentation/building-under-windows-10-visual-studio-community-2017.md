# Building under Windows/Visual Studio Community 2017

Download, install, and update Visual Studio Community 2017.
Download and install CMake 3.10.1 or higher.
Install Google Test Adapter for Visual Studio version 0.12.3.994 or higher is installed.
To compile Idlib, open a Powershell console window, change to the directory in which the source of the library is located in, and enter
```
cmake CMakeLists.txt
```
CMake generates the solution file `idlib.sln` for platfom Win32. Open this file in Visual Studio.

To generate the solution file idlib.sln for platform x64, enter
```
cmake CMakeLists.txt -DCMAKE_GENERATOR_PLATFORM=x64
```
instead.
