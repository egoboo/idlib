# Minimum required CMake version.
cmake_minimum_required (VERSION 3.8)
# Project name and settings.
project(idlib-color-test CXX)
message("building Idlib: Color Tests")
set_project_default_properties()

# Add gtest library include.
include_directories("${CMAKE_BINARY_DIR}/external/googletest/googletest/include")
# Include directory locations.
include_directories(${PROJECT_SOURCE_DIR}/../library/src)
include_directories(${PROJECT_SOURCE_DIR})

# Build a list of all tests.
file(GLOB_RECURSE test_files ${PROJECT_SOURCE_DIR}/idlib/tests/*.cpp)

add_executable(idlib-color-tests-executable ${test_files})
target_link_libraries(idlib-color-tests-executable idlib-color-library)
target_link_libraries(idlib-color-tests-executable gtest gtest_main)

include(CTest)
enable_testing()
add_test(idlib-color-tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/idlib-color-tests-executable)
if (NOT MSVC)
  add_custom_target(idlib-color-check COMMAND ${CMAKE_CTEST_COMMAND} --verbose DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/idlib-color-tests-executable)
  if (NOT TARGET check)
	add_custom_target(check)
  endif()
  add_dependencies(check idlib-color-check)
endif()
