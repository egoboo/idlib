# Minimum required CMake version.
cmake_minimum_required (VERSION 3.8)
# Project name and settings.
project(idlib-color-test CXX)
message("building Idlib: Color Tests")
set_project_default_properties()

# Include directory locations.
include_directories(${PROJECT_SOURCE_DIR}/../library/src)
include_directories(${PROJECT_SOURCE_DIR})

# Build a list of all tests.
file(GLOB_RECURSE test_files ${PROJECT_SOURCE_DIR}/idlib/tests/*.cpp)

add_executable(idlib-color-tests-executable ${test_files})
target_link_libraries(idlib-color-tests-executable idlib-color-library)
target_link_libraries(idlib-color-tests-executable GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(idlib-color-tests-executable)
