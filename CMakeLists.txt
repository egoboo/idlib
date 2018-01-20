# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)

# Project name and language.
project(idlib CXX)

# Enable/disable compilation and execution of unit tests.
# The value of this option can be set from the command-line by -Didlib-with-tests=(ON|OFF).
option(idlib-with-tests "enable/disable compilation and execution of unit tests. ON enables compilation and execution of unit tests, OFF disables compilation and execution of unit tests. Initial value is ON." ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/buildsystem/set_project_default_properties.cmake)

# Add module "googletet".
# TODO: This ensures that "googletest" is compiled against C++ 17.
#       However, isn't it possible to simply use set(CMAKE_CXX_STANDARD 17)?
if (CMAKE_CXX_COMPILER MATCHES ".*clang")
  set(CMAKE_CXX_FLAGS "-DGTEST_LANG_CXX11=1 -std=gnu++11")
else()
  set(CMAKE_CXX_FLAGS "-DGTEST_LANG_CXX11=1")
endif()
set(googletest_dir "${CMAKE_CURRENT_SOURCE_DIR}/external/googletest")
add_subdirectory("${googletest_dir}" EXCLUDE_FROM_ALL)

# Ensure the "check" target exists.
if (NOT MSVC)
  if (NOT TARGET check)
	add_custom_target(check)
  endif()
endif()

# Add subdirectories for the library and the tests.
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/library)
if (idlib-with-tests)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
