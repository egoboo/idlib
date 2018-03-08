# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)
# Project name and settings.
project(idlib-math-geometry-library CXX)
message("building Idlib: Math Geometry Library")
set_project_default_properties()

# Include directory locations.
include_directories(${PROJECT_SOURCE_DIR}/src)
# Determine source files and compile them as C++.
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# Determine header files.
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)

# Define compilation output.
add_library(idlib-math-geometry-library STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(idlib-math-geometry-library PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(idlib-math-geometry-library INTERFACE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(idlib-math-geometry-library idlib-math-library)

IF(idlib-with-documentation)
  IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(idlib-math-geometry-library-doc ${DOXYGEN_EXECUTABLE} COMMENT "build Idlib: Math Geometry Library documentation")
  ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
  ENDIF(DOXYGEN_FOUND)
ENDIF(idlib-with-documentation)
