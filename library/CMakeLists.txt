# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)

# Project name and language.
project(idlib-library CXX)

# Idlib library compiles against C++ 17.
if (NOT MSVC)
  set(CMAKE_CXX_STANDARD 17)
endif()

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

IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(idlib-library-doc ${DOXYGEN_EXECUTABLE} COMMENT "build Idlib documentation")
ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
ENDIF(DOXYGEN_FOUND)
