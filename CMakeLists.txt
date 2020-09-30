cmake_minimum_required(VERSION 3.5.1)

project(opencv_gtest LANGUAGES C CXX)

add_subdirectory(googletest)

find_package(OpenCV REQUIRED COMPONENTS core QUIET)

add_executable(opencv_gtest test_runner.cpp test.cpp)

target_link_libraries(opencv_gtest PRIVATE gtest gmock opencv_core)
