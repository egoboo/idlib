# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)
# Project name and settings.
project(idlib-hll-library CXX)
message("building Idlib: Compiler Construction Library")
set_project_default_properties()

# Include directory locations.
include_directories(${PROJECT_SOURCE_DIR}/src)
# Determine source files and compile them as C++.
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# Determine header files.
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)

# Define compilation output.
add_library(idlib-hll-library STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(idlib-hll-library PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(idlib-hll-library INTERFACE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(idlib-hll-library idlib-parsing-expression-library)

IF(idlib-with-documentation)
  IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(idlib-hll-library-doc ${DOXYGEN_EXECUTABLE} COMMENT "build Idlib: HLL (High Level Language) documentation")
  ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
  ENDIF(DOXYGEN_FOUND)
ENDIF(idlib-with-documentation)
