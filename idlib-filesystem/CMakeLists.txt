# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)

# Project name and language.
project(idlib-filesystem CXX)
message("building Idlib: File System")

# Add subdirectories for the library and the tests.
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/library)
if (idlib-with-tests)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
