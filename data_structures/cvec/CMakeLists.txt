cmake_minimum_required(VERSION 3.22)
project(cvec)

set(CMAKE_CXX_STANDARD 23)

add_library(cvec library.cpp)
add_subdirectory(doctest_tests)
