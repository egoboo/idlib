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
#set_source_file_properties(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)
# Define compilation output.
add_library(idlib-library STATIC ${SOURCE_FILES})

# == Doxygen ==================================================================================== #

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(idlib-library-doc ${DOXYGEN_EXECUTABLE} COMMENT "build Idlib documentation")
ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
ENDIF(DOXYGEN_FOUND)
