# Minimum required CMake version.
cmake_minimum_required (VERSION 3.8)
# Project name and settings.
project(idlib-test CXX)
message("building Idlib Tests")
set_project_default_properties()

# Add gtest library include.
include_directories("${CMAKE_BINARY_DIR}/external/googletest/googletest/include")
# Include directory locations.
include_directories(${PROJECT_SOURCE_DIR}/../library/src)
include_directories(${PROJECT_SOURCE_DIR})

# Build a list of all tests.
file(GLOB_RECURSE test_files ${PROJECT_SOURCE_DIR}/idlib/tests/*.cpp)

add_executable(idlib-tests-executable ${test_files})
target_link_libraries(idlib-tests-executable idlib-library)
target_link_libraries(idlib-tests-executable gtest gtest_main)

include(CTest)
enable_testing()
add_test(idlib-tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/idlib-tests-executable)
if (NOT MSVC)
  add_custom_target(idlib-check COMMAND ${CMAKE_CTEST_COMMAND} --verbose DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/idlib-tests-executable)
  if (NOT TARGET check)
	add_custom_target(check)
  endif()
  add_dependencies(check idlib-check)
endif()
