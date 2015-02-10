cmake_minimum_required (VERSION 2.8.7)

project(idlib-test CXX)

# C++ 17 is still not supported in CMake 3.8 as an argument to CMAKE_CXX_STANDARD.
#set(CMAKE_CXX_STANDARD 17)

# Set the default properties.
set_project_default_properties()

# Add gtest library include.
include_directories("${CMAKE_BINARY_DIR}/external/googletest/googletest/include")
# Include directory locations.
include_directories(${CMAKE_BINARY_DIR}/library/src)
include_directories(${CMAKE_BINARY_DIR}/tests)

# Build a list of all tests.
file(GLOB_RECURSE test_files ${PROJECT_SOURCE_DIR}/idlib/tests/*.cpp)

add_executable(idlib-test-binary ${test_files})
target_link_libraries(idlib-test-binary idlib-library)
target_link_libraries(idlib-test-binary gtest gtest_main)

include(CTest)
enable_testing()
add_test(idlib-test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/idlib-test-binary)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/idlib-test-binary)

