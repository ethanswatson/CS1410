cmake_minimum_required(VERSION 3.6)
project(HW1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Bug.cpp Bug.hpp TestCases.cpp TestCases.hpp)
add_executable(HW1 ${SOURCE_FILES})