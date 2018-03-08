# Minimum required CMake version.
cmake_minimum_required(VERSION 3.8)
# Project name and settings.
project(idlib-color-library CXX)
message("building Idlib: Color Library")
set_project_default_properties()

# Include directory locations.
include_directories(${PROJECT_SOURCE_DIR}/src)
# Determine source files and compile them as C++.
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# Determine header files.
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)

# Define compilation output.
add_library(idlib-color-library STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(idlib-color-library PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(idlib-color-library INTERFACE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(idlib-color-library idlib-type-library)

IF(idlib-with-documentation)
  IF(DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(idlib-color-library-doc ${DOXYGEN_EXECUTABLE} COMMENT "build Idlib: Color Library documentation")
  ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
  ENDIF(DOXYGEN_FOUND)
ENDIF(idlib-with-documentation)
