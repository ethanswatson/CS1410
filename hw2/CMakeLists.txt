cmake_minimum_required(VERSION 3.6)
project(HW2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SortStats.cpp SortStats.hpp TestCases.cpp TestCases.hpp)
add_executable(HW2 ${SOURCE_FILES})