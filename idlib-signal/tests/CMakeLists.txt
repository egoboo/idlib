# Minimum required CMake version.
cmake_minimum_required (VERSION 3.8)
# Project name and settings.
project(idlib-signal-test CXX)
message("building Idlib: Signal Tests")
set_project_default_properties()

# Add gtest library include.
include_directories("${CMAKE_BINARY_DIR}/external/googletest/googletest/include")
# Include directory locations.
include_directories(${PROJECT_SOURCE_DIR}/../library/src)
include_directories(${PROJECT_SOURCE_DIR})

# Build a list of all tests.
file(GLOB_RECURSE test_files ${PROJECT_SOURCE_DIR}/idlib/tests/*.cpp)

add_executable(idlib-signal-tests-executable ${test_files})
target_link_libraries(idlib-signal-tests-executable idlib-signal-library)
target_link_libraries(idlib-signal-tests-executable GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(idlib-signal-tests-executable)
