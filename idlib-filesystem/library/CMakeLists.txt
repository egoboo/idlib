# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)
# Project name and settings.
project(idlib-filesystem-library CXX)
message("building Idlib: File System Library")
set_project_default_properties()

# Include directory locations.
include_directories(${PROJECT_SOURCE_DIR}/src)
# Determine source files and compile them as C++.
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# Determine header files.
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)

# Define compilation output.
add_library(idlib-filesystem-library STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(idlib-filesystem-library PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(idlib-filesystem-library INTERFACE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(idlib-filesystem-library idlib-library)

IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(idlib-filesystem-library-doc ${DOXYGEN_EXECUTABLE} COMMENT "build Idlib: File System Library documentation")
ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
ENDIF(DOXYGEN_FOUND)
