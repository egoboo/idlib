# Building under Windows/Visual Studio Community 2022

Download, install, and update Visual Studio Community 2022.
Ensure the Test Adapter for Google Test is installed.
Download and install CMake 3.30 or higher.
To compile Idlib, open a Powershell console window, change to the directory in which the source of the library is located in, and enter
```
cmake CMakeLists.txt
```
CMake generates the solution file `idlib.sln` for your platform (which is usually x64). Open this file in Visual Studio.

To generate the solution file idlib.sln for Win32 platform, enter
```
cmake CMakeLists.txt -DCMAKE_GENERATOR_PLATFORM=Win32
```

To generate the solution file idlib.sln for x64 platform, enter
```
cmake CMakeLists.txt -DCMAKE_GENERATOR_PLATFORM=x64
```
