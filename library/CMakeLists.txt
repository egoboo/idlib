# Minimum required CMake version.
cmake_minimum_required(VERSION 3.6)

# Project name and language.
project(idlib-library CXX)

# C++ 17 is still not supported in CMake 3.8 as an argument to CMAKE_CXX_STANDARD.
#set(CMAKE_CXX_STANDARD 17)

# Set the default properties.
set_project_default_properties()

# Include directory locations.
include_directories(${PROJECT_SOURCE_DIR}/src)
# Determine source files and compile them as C++.
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# Determine header files.
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)

# Define compilation output.
add_library(idlib-library STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(idlib-library PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(idlib-library INTERFACE "${PROJECT_SOURCE_DIR}/src")

# == Doxygen ==================================================================================== #

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(idlib-library-doc ${DOXYGEN_EXECUTABLE} COMMENT "build Idlib documentation")
ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
ENDIF(DOXYGEN_FOUND)
